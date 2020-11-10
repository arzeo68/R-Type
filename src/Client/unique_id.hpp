#pragma once

#include <memory>
#include <cstdint>

class UniqueIDGenerator {
public:
    UniqueIDGenerator()
        : m_nNextID(0)
    { }

    ~UniqueIDGenerator() = default;

    uint32_t getID() { return m_nNextID++; }

    static const uint32_t InvalidID = UINT32_MAX;

private:
    uint32_t m_nNextID;
};

extern std::shared_ptr<UniqueIDGenerator> g_IDGenerator = nullptr;