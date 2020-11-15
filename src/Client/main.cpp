//
// Created by arzeo on 10/26/2020.
//

#include <iostream>
#include <Application/Application.hpp>

int main(const int ac, const char **av)
{
    if (ac != 2)
        return (84);
    Rtype::Application app("Rtype", 960, 540, av[1]);

    app.run();

    return 0;
}
