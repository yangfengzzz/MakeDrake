/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __drake_lcmt_planar_gripper_finger_face_assignment_hpp__
#define __drake_lcmt_planar_gripper_finger_face_assignment_hpp__

#include <lcm/lcm_coretypes.h>

#include <string>

namespace drake
{

/// Communicates the finger-face assignment info for a specified finger.
class lcmt_planar_gripper_finger_face_assignment
{
    public:
        /// in microseconds
        int64_t    utime;

        /// Finger name: {finger1, finger2, finger3}
        std::string finger_name;

        /// Brick face name: {PosY, NegY, PosZ, NegZ}
        std::string brick_face_name;

        /**
         * The contact point if in contact, or the proximity witness point if not in
         * contact. It is position vector from the brick's body B's origin (Bo) to a
         * point Bq (a point of B), expressed in B's frame.
         */
        double     p_BoBq_B[2];

        /**
         * {y-coordinate, z-coordinate}
         * A boolean that indicates whether this finger is in contact with the
         * specified brick face. If true, the finger is in contact and p_BoBq_B
         * indicates the actual contact point. If false, the finger is not in contact
         * and p_BoBq_B indicates the witness point to a proximity query.
         */
        int8_t     is_in_contact;

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
        inline int encode(void *buf, int offset, int maxlen) const;

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
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "lcmt_planar_gripper_finger_face_assignment"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int lcmt_planar_gripper_finger_face_assignment::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_planar_gripper_finger_face_assignment::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int lcmt_planar_gripper_finger_face_assignment::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t lcmt_planar_gripper_finger_face_assignment::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* lcmt_planar_gripper_finger_face_assignment::getTypeName()
{
    return "lcmt_planar_gripper_finger_face_assignment";
}

int lcmt_planar_gripper_finger_face_assignment::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &this->utime, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    char* finger_name_cstr = const_cast<char*>(this->finger_name.c_str());
    tlen = __string_encode_array(
        buf, offset + pos, maxlen - pos, &finger_name_cstr, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    char* brick_face_name_cstr = const_cast<char*>(this->brick_face_name.c_str());
    tlen = __string_encode_array(
        buf, offset + pos, maxlen - pos, &brick_face_name_cstr, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->p_BoBq_B[0], 2);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __boolean_encode_array(buf, offset + pos, maxlen - pos, &this->is_in_contact, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_planar_gripper_finger_face_assignment::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this->utime, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    int32_t __finger_name_len__;
    tlen = __int32_t_decode_array(
        buf, offset + pos, maxlen - pos, &__finger_name_len__, 1);
    if(tlen < 0) return tlen; else pos += tlen;
    if(__finger_name_len__ > maxlen - pos) return -1;
    this->finger_name.assign(
        static_cast<const char*>(buf) + offset + pos, __finger_name_len__ - 1);
    pos += __finger_name_len__;

    int32_t __brick_face_name_len__;
    tlen = __int32_t_decode_array(
        buf, offset + pos, maxlen - pos, &__brick_face_name_len__, 1);
    if(tlen < 0) return tlen; else pos += tlen;
    if(__brick_face_name_len__ > maxlen - pos) return -1;
    this->brick_face_name.assign(
        static_cast<const char*>(buf) + offset + pos, __brick_face_name_len__ - 1);
    pos += __brick_face_name_len__;

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->p_BoBq_B[0], 2);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __boolean_decode_array(buf, offset + pos, maxlen - pos, &this->is_in_contact, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_planar_gripper_finger_face_assignment::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __int64_t_encoded_array_size(NULL, 1);
    enc_size += this->finger_name.size() + 4 + 1;
    enc_size += this->brick_face_name.size() + 4 + 1;
    enc_size += __double_encoded_array_size(NULL, 2);
    enc_size += __boolean_encoded_array_size(NULL, 1);
    return enc_size;
}

uint64_t lcmt_planar_gripper_finger_face_assignment::_computeHash(const __lcm_hash_ptr *)
{
    uint64_t hash = 0xc4fe83a1c182b84dLL;
    return (hash<<1) + ((hash>>63)&1);
}

}

#endif