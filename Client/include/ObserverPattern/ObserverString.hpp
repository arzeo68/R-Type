//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_OBSERVERSTRING_HPP
#define BABEL_OBSERVERSTRING_HPP

#include <Client/include/ObserverPattern/IObserver.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>

class ObserverString : public IObserver {
    public:
    ObserverString(Subject<std::string> &subject);
    virtual ~ObserverString();
    void Update(const std::string &message_from_subject) override;
    void RemoveMeFromTheList();
    void PrintInfo();

    private:
    std::string message_from_subject_;
    Subject<std::string> &_subject;
    static int _static_number ;
    int _number;
};


#endif //BABEL_OBSERVERSTRING_HPP
