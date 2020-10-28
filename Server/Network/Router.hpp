/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ROUTER_
#define SRC_RTYPE_ROUTER_

#include <type_traits>

namespace RType::Network {
    /**
     * Struct serve as a null parameter for the templates
     */
    struct _nullTemplate {
    };


    template<typename IOService = _nullTemplate, typename Acceptor = _nullTemplate,
        typename SignalSet = _nullTemplate>
    class Router {
        private:
        template<typename T>
        static inline constexpr bool _isTemplateNull = std::is_same_v<T, _nullTemplate>;
        template<typename T>
        static inline constexpr bool _isValidAssigment =
            !_isTemplateNull<T> && std::is_copy_constructible_v<T>;

        public:
        Router() {
            if constexpr (std::is_constructible_v<IOService>)
                this->_service = std::make_shared<IOService>();
            if constexpr (std::is_constructible_v<Acceptor>)
                this->_acceptor = std::make_shared<Acceptor>();
            if constexpr (std::is_constructible_v<SignalSet>)
                this->_signal_set = std::make_shared<SignalSet>();
            printf("In default constr\n");
        };

        [[maybe_unused]] typename std::enable_if_t<_isValidAssigment<IOService>>
        set_io_service(IOService &&service) {
            this->_service = std::make_shared<IOService>(
                std::forward<IOService>(service));
        };

        [[maybe_unused]] typename std::enable_if_t<!_isValidAssigment<Acceptor>>
        set_acceptor(Acceptor &&acceptor) {
            printf("Set default acceptor\n");
            this->_acceptor = std::make_shared<Acceptor>(
                std::forward<Acceptor>(acceptor));
        };

        [[maybe_unused]] typename std::enable_if_t<_isValidAssigment<SignalSet>>
        set_signal_set(Acceptor &&signal_set) {
            printf("Set default signal_set\n");
            this->_signal_set = std::make_shared<SignalSet>(
                std::forward<SignalSet>(signal_set));
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
        Router(Router &&) noexcept = delete;

        private:
        std::shared_ptr<IOService> _service;
        std::shared_ptr<Acceptor> _acceptor;
        std::shared_ptr<SignalSet> _signal_set;
    };
}

#endif
