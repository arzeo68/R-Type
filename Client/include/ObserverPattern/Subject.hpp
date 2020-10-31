//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_SUBJECT_HPP
#define BABEL_SUBJECT_HPP

#include <list>
#include <iostream>
#include "IObserver.hpp"

template<typename T>
class Subject {
    public:
    ~Subject();
    void Attach(IObserver *observer);
    void Detach(IObserver *observer);
    void Notify();
    void CreateMessage(T);
    void HowManyObserver();
    void SomeBusinessLogic();

    private:
    std::list<IObserver *> _list_observer;
    T _message;
};

#endif //BABEL_SUBJECT_HPP
