/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Router class implementation
*/

#ifndef SRC_RTYPE_ROUTER_
#define SRC_RTYPE_ROUTER_

#include <type_traits>

#if __cplusplus > 201703L && __cpp_concepts >= 201907L

    #include <concepts>

#endif

namespace RType::Network {
    /**
     * Structure used as a null parameter for template
     * You shouldn't use it for others purposes
     */
    struct _nullTemplate {
        _nullTemplate() = delete;
        ~_nullTemplate() = delete;
        _nullTemplate(const _nullTemplate&) = delete;
    };


    /**
     * We do support c++20 here
     */
    #if __cplusplus > 201703L && __cpp_concepts >= 201907L
    template<typename T>
    concept _isTemplateNull = std::is_same_v<T, _nullTemplate>;
    #else
    template<typename T>
    constexpr inline bool _isTemplateNull = std::is_same_v<T, _nullTemplate>;
    #endif


    /**
     * @deprecated Doesn't works for some reasons - TODO: More debug needed
     */
    #if __cplusplus > 201703L && __cpp_concepts >= 201907L
    template<typename T>
    concept _isValidAssigment = !_isTemplateNull<T> &&
        std::is_copy_constructible_v<T>;
    #else
    template<typename T>
    constexpr inline bool _isValidAssigment =
        !_isTemplateNull<T> && std::is_copy_constructible_v<T>;
    #endif

    /**
     * The router basically hold generic type for main network part. The class target to be used only in a network.
     * It is modular to adapt as well as possible.
     * @attention I encourage you to complete this class to satisfy any more complex network implementation.
     * @warning If you left a template parameter as '_nullTemplate', you can not use functions related to this template parameter.
     * @tparam IOService The IO (Input/Output) service that should handle the work. Implementation is library dependant.
     * @tparam TCPAcceptor Acceptor system which accept incoming connection to the server. Implementation is library dependant.
     * @tparam SignalSet SignalSet is used to handle signals. Implementation is library dependant.
     */
    template<typename IOService = _nullTemplate,
        typename TCPAcceptor = _nullTemplate,
        typename UDPEndpoint = _nullTemplate,
        typename SignalSet = _nullTemplate>
    class Router {
        private:

        public:
        Router() {
            if constexpr (std::is_constructible_v<IOService>)
                this->_service = std::make_shared<IOService>();
            if constexpr (std::is_constructible_v<TCPAcceptor>)
                this->_tcp_acceptor = std::make_shared<TCPAcceptor>();
            if constexpr (std::is_constructible_v<UDPEndpoint>)
                this->_udp_endpoint = std::make_shared<UDPEndpoint>();
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
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<TCPAcceptor>>
        set_tcp_acceptor(Arguments&& ...arguments) {
            this->_tcp_acceptor = std::make_shared<TCPAcceptor>(
                std::forward<Arguments>(arguments)...);
        };

        template<typename ...Arguments>
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<UDPEndpoint>>
        set_udp_endpoint(Arguments&& ...arguments) {
            this->_udp_endpoint = std::make_shared<UDPEndpoint>(
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

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<TCPAcceptor>, std::shared_ptr<TCPAcceptor>>
        get_io_acceptor() const {
            return (this->_tcp_acceptor);
        };
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<TCPAcceptor>, std::shared_ptr<TCPAcceptor>>
        get_io_acceptor() {
            return (this->_tcp_acceptor);
        };

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>, std::shared_ptr<SignalSet>>
        get_signal_set() const {
            return (this->_signal_set);
        };
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>, std::shared_ptr<SignalSet>>
        get_signal_set() {
            return (this->_signal_set);
        };

        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>, std::shared_ptr<UDPEndpoint>>
        get_udp_endpoint() const {
            return (this->_udp_endpoint);
        };
        [[maybe_unused]] typename std::enable_if_t<!_isTemplateNull<SignalSet>, std::shared_ptr<UDPEndpoint>>
        get_udp_endpoint() {
            return (this->_udp_endpoint);
        };

        ~Router() noexcept = default;
        Router(Router&&) noexcept = delete;

        private:
        std::shared_ptr<IOService> _service;
        std::shared_ptr<TCPAcceptor> _tcp_acceptor;
        std::shared_ptr<UDPEndpoint> _udp_endpoint;
        std::shared_ptr<SignalSet> _signal_set;
    };
}

#endif
