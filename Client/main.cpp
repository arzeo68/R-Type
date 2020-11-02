//
// Created by arzeo on 10/26/2020.
//

#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/ObserverPattern/ObserverString.hpp>


void testObserverPattern()
{
    auto subject = std::make_shared<Subject>();
    ObserverString *observer1 = new ObserverString();
    ObserverString *observer2 = new ObserverString();
    ObserverString *observer3 = new ObserverString();
    observer1->registerToSubject(subject);
    observer2->registerToSubject(subject);
    observer3->registerToSubject(subject);

    ObserverString *observer4;
    ObserverString *observer5;
    subject->Notify("sdfsdfsdfsdf");
    observer3->RemoveMeFromTheList();
    subject->Notify<std::string>("hello");
    observer4 = new ObserverString();
    observer4->registerToSubject(subject);
    observer5 = new ObserverString();
    observer5->registerToSubject(subject);
    subject->Notify<std::string>("good bye");
    observer5->RemoveMeFromTheList();
    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();
    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
}


int main(int argc, char **argv)
{
    testObserverPattern();
}