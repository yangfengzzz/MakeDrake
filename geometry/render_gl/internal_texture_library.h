#pragma once

#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "common/drake_copyable.h"
#include "geometry/render_gl/internal_opengl_includes.h"

namespace drake {
namespace geometry {
namespace render_gl {
namespace internal {

/* Note to developers: Using file paths as unique identifiers prevents a texture
 library instance from recognizing changes to images on disk. This doesn't seem
 like much of a risk. In order for this failing to affect a user, the user would
 would have to:

   1. Load a mesh referencing a texture.
   2. Update the texture in another program (while holding Drake initialization
      in abeyance).
   3. Load another mesh referencing the same texture path.

 TextureLibrary doesn't regularly poll the file system to detect changes and
 only loading a mesh would cause it to consider the filesystem again. As this
 workflow seems unlikely, we'll defer this question til later.

 We can't use a sha256 of the file's contents as the key because we'd never
 recognize if a texture we already loaded had changed. We'd end up with a system
 containing *both* versions of the texture (one on the old mesh, one on the
 new). Instead, we'd use the same file path as key, but store the texture data
 *and* the sha so that we only store one version of the image. */

/* Stores a set of OpenGl textures objects, keyed by an image name. The image
 name can be a file system path or a string mnemonic with a proscribed prefix
 (see InMemoryPrefix()).

 The library's purpose is to reduce the chance of the same resource being
 parsed and stored in the OpenGl context redundantly. As such, a %TextureLibrary
 instance is associated with an instance of OpenGlContext by RenderEngineGl.

 By design, a single texture library is shared by a "family" of RenderEngineGl
 instances -- the original and all instances *cloned* from it. The library
 is threadsafe for adding new textures to the OpenGl context such that if one
 instance loads a texture, the others will benefit from it instead of blindly
 duplicating the texture in memory. This works because the cloned OpenGlContext
 instances share texture objects in GPU memory; the texture ids in this
 texture library apply equally well to every such OpenGl context. */
class TextureLibrary {
public:
    DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(TextureLibrary);

    TextureLibrary() = default;

    /* Returns the unique OpenGl identifier for the texture with the given name.
     A new OpenGl identifier will be created if one doesn't already exist.
     Errors in loading the texture are processed *silently*. This will attempt
     to load the image if:

       - a texture hasn't already been added with the given `file_name`, and
       - the `file_name` isn't prefixed with InMemoryPrefix(). Texture names
         presented with that prefix must be pre-loaded as an "in-memory" texture
         before accessing. See AddInMemoryImages().

     The caller (typically the owner of the %TextureLibrary instance) is
     responsible for partnering the %TextureLibrary with an OpenGl context. The
     texture's identifier will be created within that context (assuming it has
     been bound).

     @param file_name  The absolute path to the file containing the texture data.
     @returns A valid OpenGl identifier if the texture has been successfully
              added to the library, std::nullopt if not.
     @pre The OpenGl context "partnered" to this library has been bound. */
    std::optional<GLuint> GetTextureId(const std::string& file_name);

    /* Returns the prefix that %TextureLibrary uses to recognize a named image
     comes from in memory and should have been registered in AddInMemoryImages().
     */
    static std::string_view InMemoryPrefix() { return "from_memory://"; }

    /* Adds a set of in-memory textures to the library. The textures are presented
     in a map with (name, texture) pairs where the name is what will be referenced
     in the RenderMaterial specification that applies the texture.

     If a name already exists in the library, the texture data is *assumed* to
     be redundant and ignored.

     @pre Each name in the map has the prefix reported by InMemoryPrefix() to
     prevent possible collision with real file.
     @pre The OpenGl context "partnered" to this library has been bound. */
    void AddInMemoryImages(const std::map<std::string, std::vector<unsigned char>>& images);

    /* Reports the key to use for the texture with the given image URI.
     This resolves symlinks to prevent redundant texture definitions. */
    static std::string GetTextureKey(const std::string& file_uri);

    /* Reports if the file_name references an image type that is supported. */
    static bool IsSupportedImage(const std::string& file_name);

    /* (Testing only) Used for testing. Allows for introspection of registered
     textures. */
    const std::map<std::string, GLuint> textures() const { return textures_; }

private:
    friend class TextureLibraryTester;

    /* The mapping from requested texture file name to its OpenGl id (as existing
     in context_).  */
    std::map<std::string, GLuint> textures_;

    /* Mutex to control access to textures_. */
    std::mutex mutex_;
};

}  // namespace internal
}  // namespace render_gl
}  // namespace geometry
}  // namespace drake
