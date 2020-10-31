//
// Created by arzeo on 10/31/2020.
//

#include "Client/include/ObserverPattern/ObserverString.hpp"

ObserverString::ObserverString(Subject<std::string> &subject): _subject(subject)
{
    this->_subject.Attach(this);
    std::cout << "Hi, I'm the ObserverString \"" << ++ObserverString::_static_number << "\".\n";
    this->_number = ObserverString::_static_number;
}

ObserverString::~ObserverString()
{
    std::cout << "Goodbye, I was the ObserverString \"" << this->_number << "\".\n";
}

void ObserverString::Update(const std::string &message_from_subject)
{
    message_from_subject_ = message_from_subject;
    PrintInfo();
}

void ObserverString::RemoveMeFromTheList()
{
//    _subject.Detach(this);
    std::cout << "ObserverString \"" << _number << "\" removed from the list.\n";
}

void ObserverString::PrintInfo()
{
    std::cout << "ObserverString \"" << this->_number << "\": a new message is available --> " << this->message_from_subject_ << "\n";
}
