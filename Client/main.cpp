//
// Created by arzeo on 10/26/2020.
//

#include <Client/include/ObserverPattern/Subject.hpp>
#include <Client/include/ObserverPattern/ObserverString.hpp>
#include <Client/include/SceneManager/SceneManager.hpp>

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

/**
 * @brief
 * Test class for Scene Management
 */
class SceneTest1 : public Rtype::IScene {
public:
        SceneTest1(std::string const& message)
            : message(message)
        { }

        void onCreate() override { std::cout << "onCreate : \"" << message << "\"\n"; }
        void onDestroy() override { std::cout << "onDestroy : \"" << message << "\"\n"; }

        void onActivate() override { std::cout << "onActivate : \"" << message << "\"\n"; }
        void onDeactivate() override { std::cout << "onDeactivate : \"" << message << "\"\n"; }


private:
    std::string message;
};

void SceneTest()
{
    Rtype::SceneManager manager;

    std::shared_ptr<SceneTest1> scene1 = std::make_shared<SceneTest1>("Scene1");
    std::shared_ptr<SceneTest1> scene2 = std::make_shared<SceneTest1>("Scene2");

    unsigned int scene_idx_1 = manager.add(scene1);
    unsigned int scene_idx_2 = manager.add(scene2);

    manager.switch_to(scene_idx_1);

    manager.switch_to(scene_idx_2);

    manager.switch_to(scene_idx_1);

    manager.remove(scene_idx_1);

    manager.remove(scene_idx_2);
}

int main(int argc, char **argv)
{
    std::cout << "-----------------------------------------------------------------------------\n";
    testObserverPattern();
    std::cout << "-----------------------------------------------------------------------------\n";
    SceneTest();
    std::cout << "-----------------------------------------------------------------------------\n";
}