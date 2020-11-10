//
// Created by arzeo on 11/9/2020.
//

#ifndef RTYPE_ASOCKET_HPP
#define RTYPE_ASOCKET_HPP

#include <condition_variable>
#include "ISocket.hpp"

namespace Rtype {
    /**
 * ASocket is an abstraction whith the basic function for any socket type
 */
    class ASocket : public ISocket {
    };
}

#endif //RTYPE_ASOCKET_HPP
