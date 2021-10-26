#pragma once
#include <vector>
#include <string>
#include <stdexcept>

struct ByteBuffer {
    std::vector<char> m_buf;
    std::size_t offset = 0;

    template<typename T>
    void Read(T& out) {
        if (offset + sizeof(T) > m_buf.size())
            throw std::runtime_error("Tried reading out of bounds");

        std::memcpy(&out, m_buf.data() + offset, sizeof(T));

        offset += sizeof(T);
    }

    template<typename T>
    void Write(T& in) {
        if (m_buf.size() < offset + sizeof(T)) {
            m_buf.resize(offset + sizeof(T));
        }

        std::memcpy(m_buf.data() + offset, &in, sizeof(T));
        offset += sizeof(T);
    }

    void Read(char* out, size_t count) {
        if (offset + count > m_buf.size())
            throw std::runtime_error("Tried reading out of bounds");

        std::memcpy(out, m_buf.data() + offset, count);

        offset += count;
    }
};