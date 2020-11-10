#pragma once

#include <tuple>
#include "ComponentArray.hpp"

namespace ECS
{

template<typename... Args>
class SingletonComponentCollection {
    public:

        SingletonComponentCollection() = default;
        ~SingletonComponentCollection() = default;

        SingletonComponentCollection(SingletonComponentCollection const&) = delete;
        SingletonComponentCollection& operator=(SingletonComponentCollection const&) = delete;

        void initialize(Args... args)
        {
            m_SingleComponent = std::make_tuple(args...);
        }

        template<typename T>
        ComponentHandle<T> get()
        {
            ComponentHandle<T> Handle;

            Handle.set(&std::get<T>(m_SingleComponent));
            return Handle;
        }

    private:
        std::tuple<Args...> m_SingleComponent;
};

} // namespace ECS
