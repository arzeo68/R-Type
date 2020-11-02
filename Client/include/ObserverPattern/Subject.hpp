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
    template <typename T>
    void Notify(T message)
    {
        auto it = _list_observer.begin();
        HowManyObserver();
        while (it != _list_observer.end()) {
            (*it)->Update(message);
            ++it;
        }
    }
    void HowManyObserver();

    private:
    std::list<IObserver *> _list_observer;
};




#endif //BABEL_SUBJECT_HPP
