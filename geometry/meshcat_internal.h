#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "common/drake_copyable.h"
#include "geometry/geometry_ids.h"
#include "geometry/meshcat_file_storage_internal.h"
#include "geometry/scene_graph_inspector.h"

namespace drake {
namespace geometry {
namespace internal {

/* Returns the static content for the given URL, or nullopt when the URL is
invalid. The valid static resource URLs are:
- `/`
- `/favicon.ico`
- `/index.html`
- `/meshcat.html`
- `/meshcat.js`
- `/stats.min.js` */
std::optional<std::string_view> GetMeshcatStaticResource(std::string_view url_path);

/* UuidGenerator generates random UUIDs:
https://en.wikipedia.org/wiki/Universally_unique_identifier#Version_4_(random)

This object is stateful so that each UUID will be distinct; the intended use is
to create one long-lived instance that services all requests for the lifetime of
the process.

Note that the UUIDs are *deterministically* random -- the i'th random UUID will
be the same from one run to the next. There is no re-seeding. */
class UuidGenerator final {
public:
    DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(UuidGenerator);

    UuidGenerator();
    ~UuidGenerator();

    /* Returns a newly-generated random UUID. */
    std::string GenerateRandom();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

/* Rewrites a glTF file in memory so that all of its URIs refer to assets in
FileStorage, instead of their original location.

When a glTF file has bundled assets (i.e., data URIs) this decodes and unbundles
them. Meshcat is MUCH slower at loading bundled assets compared to unbundled.

When a glTF file has relative path URIs (i.e., unbundled files on disk), this
loads the files into FileStorage so that we can serve them later, even if the
original file has disappeared in the meantime.

@param[in] gltf_filename The glTF filename, used to calculate relative paths.

@param[in,out] gltf_contents The contents of `gltf_filename`. It will be edited
  in place to replace the URIs. (We assume that the caller has already read the
  file into a string, so here we can just operate on that string as an [in,out]
  parameter instead of re-reading the file and using an output-only parameter.)

@param[in,out] storage The database where assets should be stored.

@returns The handles for all assets cited by `gltf_contents`. */
[[nodiscard]] std::vector<std::shared_ptr<const FileStorage::Handle>> UnbundleGltfAssets(
        const std::filesystem::path& gltf_filename, std::string* gltf_contents, FileStorage* storage);

/* Converts a geometry name into a meshcat path. So, a geometry named
`my_scope::Mesh` becomes my_scope/Mesh.

Note: This replaces all "::" pairs, even if there are multiple instances in
sequence, or it is at the beginning or end of a sequence.

We may produce strings of the form: "a//b", "/a", or "b/". We assume these are
not problematic for the following reasons:

  - "a//b" - meshcat treats multiple '/' in a row as a single '/'.
  - "b/" - meshcat elides trailing '/'.
  - "/a" - although this may *look* like an absolute path, our basic assumption
           is that the transformed geometry name will be concatenated to a
           longer path (so it will never accidentally be used in a way that
           would be interpreted as an absolute path).

(Examples of the slash elision can be seen in meshcat_manual_test.cc -- the
sphere and cylinder shapes.) */
template <typename T>
std::string TransformGeometryName(GeometryId geom_id, const SceneGraphInspector<T>& inspector);

}  // namespace internal
}  // namespace geometry
}  // namespace drake
