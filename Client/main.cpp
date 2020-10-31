//
// Created by arzeo on 10/26/2020.
//

#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/ObserverPattern/ObserverString.hpp>

int ObserverString::_static_number = 0;


int main(int argc, char **argv)
{
    Subject *subject = new Subject;
    ObserverString *observer1 = new ObserverString(*subject);
    ObserverString *observer2 = new ObserverString(*subject);
    ObserverString *observer3 = new ObserverString(*subject);
    ObserverString *observer4;
    ObserverString *observer5;

    subject->Notify("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->Notify("The weather is hot today! :p");
    observer4 = new ObserverString(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new ObserverString(*subject);

    subject->Notify("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}