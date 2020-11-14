#pragma once

#include <vector>

namespace ECS
{

class NetworkPacket {
private:
    std::vector<char> m_data;
public:
    NetworkPacket() = default;
    ~NetworkPacket() = default;

    template<typename T>
    void addData(T *data)
    {
        m_data.insert(m_data.end(), (char *)data, ((char *)data) + sizeof(*data));
    }

    std::vector<char> getData()
    {
        return m_data;
    }

    int getID()
    {
        return *(int *)(m_data.data());
    }

    int getType()
    {
        return *(((int *)m_data.data()) + 1);
    }
};

} // namespace ECS
