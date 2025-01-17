/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __drake_lcmt_viewer_link_data_hpp__
#define __drake_lcmt_viewer_link_data_hpp__

#include <lcm/lcm_coretypes.h>

#include <string>
#include <vector>
#include "lcmt_viewer_geometry_data.hpp"

namespace drake {

class lcmt_viewer_link_data {
public:
    std::string name;

    int32_t robot_num;

    int32_t num_geom;

    std::vector<drake::lcmt_viewer_geometry_data> geom;

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
     * Returns "lcmt_viewer_link_data"
     */
    inline static const char* getTypeName();

    // LCM support functions. Users should not call these
    inline int _encodeNoHash(void* buf, int offset, int maxlen) const;
    inline int _getEncodedSizeNoHash() const;
    inline int _decodeNoHash(const void* buf, int offset, int maxlen);
    inline static uint64_t _computeHash(const __lcm_hash_ptr* p);
};

int lcmt_viewer_link_data::encode(void* buf, int offset, int maxlen) const {
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

int lcmt_viewer_link_data::decode(const void* buf, int offset, int maxlen) {
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

int lcmt_viewer_link_data::getEncodedSize() const {
    return 8 + _getEncodedSizeNoHash();
}

int64_t lcmt_viewer_link_data::getHash() {
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* lcmt_viewer_link_data::getTypeName() {
    return "lcmt_viewer_link_data";
}

int lcmt_viewer_link_data::_encodeNoHash(void* buf, int offset, int maxlen) const {
    int pos = 0, tlen;

    char* name_cstr = const_cast<char*>(this->name.c_str());
    tlen = __string_encode_array(buf, offset + pos, maxlen - pos, &name_cstr, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->robot_num, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->num_geom, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    for (int a0 = 0; a0 < this->num_geom; a0++) {
        tlen = this->geom[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if (tlen < 0)
            return tlen;
        else
            pos += tlen;
    }

    return pos;
}

int lcmt_viewer_link_data::_decodeNoHash(const void* buf, int offset, int maxlen) {
    int pos = 0, tlen;

    int32_t __name_len__;
    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &__name_len__, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;
    if (__name_len__ > maxlen - pos) return -1;
    this->name.assign(static_cast<const char*>(buf) + offset + pos, __name_len__ - 1);
    pos += __name_len__;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->robot_num, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->num_geom, 1);
    if (tlen < 0)
        return tlen;
    else
        pos += tlen;

    try {
        this->geom.resize(this->num_geom);
    } catch (...) {
        return -1;
    }
    for (int a0 = 0; a0 < this->num_geom; a0++) {
        tlen = this->geom[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if (tlen < 0)
            return tlen;
        else
            pos += tlen;
    }

    return pos;
}

int lcmt_viewer_link_data::_getEncodedSizeNoHash() const {
    int enc_size = 0;
    enc_size += this->name.size() + 4 + 1;
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    for (int a0 = 0; a0 < this->num_geom; a0++) {
        enc_size += this->geom[a0]._getEncodedSizeNoHash();
    }
    return enc_size;
}

uint64_t lcmt_viewer_link_data::_computeHash(const __lcm_hash_ptr* p) {
    const __lcm_hash_ptr* fp;
    for (fp = p; fp != NULL; fp = fp->parent)
        if (fp->v == lcmt_viewer_link_data::getHash) return 0;
    const __lcm_hash_ptr cp = {p, lcmt_viewer_link_data::getHash};

    uint64_t hash = 0x4b645ec7a5743a2aLL + drake::lcmt_viewer_geometry_data::_computeHash(&cp);

    return (hash << 1) + ((hash >> 63) & 1);
}

}  // namespace drake

#endif
