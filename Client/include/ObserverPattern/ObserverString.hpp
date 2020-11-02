//
// Created by arzeo on 10/31/2020.
//

#ifndef BABEL_OBSERVERSTRING_HPP
#define BABEL_OBSERVERSTRING_HPP

#include <Client/include/ObserverPattern/IObserver.hpp>
#include <Client/include/ObserverPattern/Subject.hpp>

class ObserverString : public IObserver {
    public:
    ObserverString();
    void registerToSubject(std::shared_ptr<Subject>);
    ~ObserverString() override;
    void Update(const std::string &message_from_subject) override;
    void RemoveMeFromTheList();

    private:
    std::string message_from_subject_;
    std::shared_ptr<Subject> _subject;
};


#endif //BABEL_OBSERVERSTRING_HPP
