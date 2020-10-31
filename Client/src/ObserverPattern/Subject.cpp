//
// Created by arzeo on 10/31/2020.
//

#include "Client/include/ObserverPattern/Subject.hpp"
template<typename T>
void Subject<T>::Attach(IObserver *observer)
{
    _list_observer.push_back(observer);
}

template<typename T>
void Subject<T>::Detach(IObserver *observer)
{
    _list_observer.remove(observer);
}

template<typename T>
void Subject<T>::Notify()
{
    auto it = _list_observer.begin();
    HowManyObserver();
    while (it != _list_observer.end()) {
        (*it)->Update(_message);
        ++it;
    }
}

template<typename T>
void Subject<T>::CreateMessage(T)
{
    this->_message = message;
    Notify();
}

template<typename T>
void Subject<T>::HowManyObserver()
{
    std::cout << "There are " << _list_observer.size() << " observers in the list.\n";
}

template<typename T>
void Subject<T>::SomeBusinessLogic()
{
    this->_message = "change message message";
    Notify();
    std::cout << "I'm about to do some thing important\n";
}

template<typename T>
Subject<T>::~Subject()
{
    _list_observer.clear();
    std::cout << "Goodbye, I was the Subject.\n";
}