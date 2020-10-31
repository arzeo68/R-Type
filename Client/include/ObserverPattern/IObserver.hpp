//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_IOBSERVER_HPP
#define BABEL_IOBSERVER_HPP

#include <string>

class IObserver {
    public:
    virtual ~IObserver(){};
    virtual void Update(const std::string &message_from_subject) = 0;
};

#endif //BABEL_IOBSERVER_HPP
