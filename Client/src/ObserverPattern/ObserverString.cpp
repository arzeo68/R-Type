//
// Created by arzeo on 10/31/2020.
//

#include "Client/include/ObserverPattern/ObserverString.hpp"

ObserverString::ObserverString()
{
}

ObserverString::~ObserverString()
{
    std::cout << "destructor" << std::endl;
}

void ObserverString::Update(const std::string &message_from_subject)
{
    std::cout << "listener received: " << message_from_subject << std::endl;
    message_from_subject_ = message_from_subject;
}

void ObserverString::RemoveMeFromTheList()
{
    if (_subject)
    {
        _subject->Detach(this);
        std::cout << "remove from list" << std::endl;
    }
}

void ObserverString::registerToSubject(std::shared_ptr<Subject> subject)
{
    _subject = subject;
    this->_subject->Attach(this);
}
