/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __drake_lcmt_image_hpp__
#define __drake_lcmt_image_hpp__

#include <lcm/lcm_coretypes.h>

#include <vector>
#include "lcmt_header.hpp"

namespace drake {

/// A representation of an image.
class lcmt_image {
public:
    /// The timestamp and the frame name where this image is obtained.
    drake::lcmt_header header;

    /// The image width in pixels.
    int32_t width;

    /// The image height in pixels.
    int32_t height;

    /// The physical memory size per a single row in bytes.
    int32_t row_stride;

    /// The size of `data` in bytes.
    int32_t size;

    /// The data that contains actual image.
    std::vector<uint8_t> data;

    /// The boolean to denote if the data is stored in the bigendian order.
    int8_t bigendian;

    /// The semantic meaning of pixels.
    int8_t pixel_format;

    /// The data type for a channel.
    int8_t channel_type;

    /// The compression method.
    int8_t compression_method;

public:
    /// enum for pixel_format.
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_GRAY = 0;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_RGB = 1;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_BGR = 2;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_RGBA = 3;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_BGRA = 4;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_DEPTH = 5;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_LABEL = 6;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_MASK = 7;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_DISPARITY = 8;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_BAYER_BGGR = 9;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_BAYER_RGGB = 10;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_BAYER_GBRG = 11;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_BAYER_GRBG = 12;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t PIXEL_FORMAT_INVALID = -1;
    /// enum for channel_type.
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_INT8 = 0;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_UINT8 = 1;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_INT16 = 2;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_UINT16 = 3;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_INT32 = 4;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_UINT32 = 5;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_FLOAT32 = 6;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_FLOAT64 = 7;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t CHANNEL_TYPE_INVALID = -1;
    /// enum for compression_method.
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t COMPRESSION_METHOD_NOT_COMPRESSED = 0;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t COMPRESSION_METHOD_ZLIB = 1;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t COMPRESSION_METHOD_JPEG = 2;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t COMPRESSION_METHOD_PNG = 3;
    // If you're using C++11 and are getting compiler errors saying
    // things like ‘constexpr’ needed for in-class initialization of
    // static data member then re-run lcm-gen with '--cpp-std=c++11'
    // to generate code that is compliant with C++11
    static const int8_t COMPRESSION_METHOD_INVALID = -1;

public:
    /**
     * Encode a message into binary form.
     *
     * @param buf The output buffer.
     * @param offset Encoding starts at thie byte offset into @p buf.
     * @param maxlen Maximum number of bytes to write.  This should generally be
     *  equal to getEncodedSize().
     * @return The number of bytes encoded, or <0 on error.
     */
    inline int encode(void* buf, int offset, int maxlen) const;

    /**
     * Check how many bytes are required to encode this message.
     */
    inline int getEncodedSize() const;

    /**
     * Decode a message from binary form into this instance.
     *
     * @param buf The buffer containing the encoded message.
     * @param offset The byte offset into @p buf where the encoded message starts.
     * @param maxlen The maximum number of bytes to read while decoding.
     * @return The number of bytes decoded, or <0 if an error occured.
     */
    inline int decode(const void* buf, int offset, int maxlen);

    /**
     * Retrieve the 64-bit fingerprint identifying the structure of the message.
     * Note that the fingerprint is the same for all instances of the same
     * message type, and is a fingerprint on the message type definition, not on
     * the message contents.
     */
    inline static int64_t getHash();

    /**
     * Returns "lcmt_image"
     */
    inline static const char* getTypeName();

    // LCM support functions. Users should not call these
    inline int _encodeNoHash(void* buf, int offset, int maxlen) const;
    inline int _getEncodedSizeNoHash() const;
    inline int _decodeNoHash(const void* buf, int offset, int maxlen);
    inline static uint64_t _computeHash(const __lcm_hash_ptr* p);
};

int lcmt_image::encode(void* buf, int offset, int maxlen) const {
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    return pos;
}

int lcmt_image::decode(const void* buf, int offset, int maxlen) {
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0)
        return thislen;
    else
        pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0)
        return thislen;
    else
        pos += thislen;

    return pos;
}

int lcmt_image::getEncodedSize() const {
    return 8 + _getEncodedSizeNoHash();
}

int64_t lcmt_image::getHash() {
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* lcmt_image::getTypeName() {
    return "lcmt_image";
}

int lcmt_image::_encodeNoHash(void* buf, int offset, int maxlen) const {
    int pos = 0, tlen;

    tlen = this->header._encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->width, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->height, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->row_stride, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->size, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    if (this->size > 0) {
        tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->data[0], this->size);
        if (tlen < 0)
            return tlen;
        else
            pos += tlen;
    }

    tlen = __boolean_encode_array(buf, offset + pos, maxlen - pos, &this->bigendian, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &this->pixel_format, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &this->channel_type, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int8_t_encode_array(buf, offset + pos, maxlen - pos, &this->compression_method, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    return pos;
}

int lcmt_image::_decodeNoHash(const void* buf, int offset, int maxlen) {
    int pos = 0, tlen;

    tlen = this->header._decodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->width, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->height, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->row_stride, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->size, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    if (this->size) {
        this->data.resize(this->size);
        tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->data[0], this->size);
        if (tlen < 0)
            return tlen;
        else
            pos += tlen;
    }

    tlen = __boolean_decode_array(buf, offset + pos, maxlen - pos, &this->bigendian, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &this->pixel_format, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &this->channel_type, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int8_t_decode_array(buf, offset + pos, maxlen - pos, &this->compression_method, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    return pos;
}

int lcmt_image::_getEncodedSizeNoHash() const {
    int enc_size = 0;
    enc_size += this->header._getEncodedSizeNoHash();
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __byte_encoded_array_size(NULL, this->size);
    enc_size += __boolean_encoded_array_size(NULL, 1);
    enc_size += __int8_t_encoded_array_size(NULL, 1);
    enc_size += __int8_t_encoded_array_size(NULL, 1);
    enc_size += __int8_t_encoded_array_size(NULL, 1);
    return enc_size;
}

uint64_t lcmt_image::_computeHash(const __lcm_hash_ptr* p) {
    const __lcm_hash_ptr* fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == lcmt_image::getHash) return 0;
    const __lcm_hash_ptr cp = {p, lcmt_image::getHash};

    uint64_t hash = 0xcc69e8044fc49594LL + drake::lcmt_header::_computeHash(&cp);

    return (hash << 1) + ((hash >> 63) & 1);
}

}  // namespace drake

#endif
