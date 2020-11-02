//
// Created by arzeo on 10/31/2020.
//

#include "Client/include/ObserverPattern/Subject.hpp"
void Subject::Attach(IObserver *observer)
{
    _list_observer.push_back(observer);
}

void Subject::Detach(IObserver *observer)
{
    _list_observer.remove(observer);
}

void Subject::HowManyObserver()
{
    std::cout << "There are " << _list_observer.size() << " observers in the list.\n";
}


Subject::~Subject()
{
    _list_observer.clear();
    std::cout << "Goodbye, I was the Subject.\n";
}