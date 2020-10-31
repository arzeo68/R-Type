//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_SUBJECT_HPP
#define BABEL_SUBJECT_HPP

#include <list>
#include <iostream>
#include "IObserver.hpp"

class Subject {
    public:
    ~Subject();
    void Attach(IObserver *observer);
    void Detach(IObserver *observer);
    template<typename T>
    void Notify(T);
    void HowManyObserver();

    private:
    std::list<IObserver *> _list_observer;
};

#endif //BABEL_SUBJECT_HPP
