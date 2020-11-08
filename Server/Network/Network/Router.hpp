/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ROUTER_
#define SRC_RTYPE_ROUTER_

#include <type_traits>

#if __cplusplus > 201703L && __cpp_concepts >= 201907L
    #include <concepts>
#endif

namespace RType::Network {
    /**
     * Struct serve as a null parameter for the templates
     */
    struct _nullTemplate {
        _nullTemplate() = delete;
        ~_nullTemplate() = delete;
        _nullTemplate(const _nullTemplate &) = delete;
    };


    #if __cplusplus > 201703L && __cpp_concepts >= 201907L
    template<typename T>
    concept _isTemplateNull = std::is_same_v<T, _nullTemplate>;
    #else
    template<typename T>
    constexpr inline bool _isTemplateNull = std::is_same_v<T, _nullTemplate>;
    #endif


    #if __cplusplus > 201703L && __cpp_concepts >= 201907L
    template<typename T>
    concept _isValidAssigment = !_isTemplateNull<T> && std::is_copy_constructible_v<T>;
    #else
    template<typename T>
    constexpr inline bool _isValidAssigment =
        !_isTemplateNull<T> && std::is_copy_constructible_v<T>;
    #endif

    template<typename IOService = _nullTemplate, typename Acceptor = _nullTemplate,
        typename SignalSet = _nullTemplate>
    class Router {
        private:

        public:
        Router() {
            if constexpr (std::is_constructible_v<IOService>)
                this->_service = std::make_shared<IOService>();
            if constexpr (std::is_constructible_v<Acceptor>)
                this->_acceptor = std::make_shared<Acceptor>();
            if constexpr (std::is_constructible_v<SignalSet>)
                this->_signal_set = std::make_shared<SignalSet>();
        };

        template<typename ...Arguments>
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<IOService>>
        set_io_service(Arguments&& ...arguments) {
            this->_service = std::make_shared<IOService>(
                std::forward<Arguments>(arguments)...);
        };

        template<typename ...Arguments>
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<Acceptor>>
        set_acceptor(Arguments&& ...arguments) {
            this->_acceptor = std::make_shared<Acceptor>(
                std::forward<Arguments>(arguments)...);
        };

        template<typename ...Arguments>
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>>
        set_signal_set(Arguments&& ...arguments) {
            this->_signal_set = std::make_shared<SignalSet>(
                std::forward<Arguments>(arguments)...);
        };

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<IOService>, std::shared_ptr<IOService>>
        get_io_service() const {
            return (this->_service);
        };

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<IOService>, std::shared_ptr<IOService>>
        get_io_service() {
            return (this->_service);
        };

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<Acceptor>, std::shared_ptr<Acceptor>>
        get_io_acceptor() const {
            return (this->_acceptor);
        };
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<Acceptor>, std::shared_ptr<Acceptor>>
        get_io_acceptor() {
            return (this->_acceptor);
        };

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>, std::shared_ptr<SignalSet>>
        get_signal_set() const {
            return (this->_signal_set);
        };
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>, std::shared_ptr<SignalSet>>
        get_signal_set() {
            return (this->_signal_set);
        };

        ~Router() noexcept = default;
        Router(Router&&) noexcept = delete;

        private:
        std::shared_ptr<IOService> _service;
        std::shared_ptr<Acceptor> _acceptor;
        std::shared_ptr<SignalSet> _signal_set;
    };
}

#endif
