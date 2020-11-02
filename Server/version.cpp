/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <type_traits>

template<typename A>
concept test_concept = std::is_integral_v<A>;

template<typename A>
void __attribute__((unused)) helloFunc() requires test_concept<A> {
}

int main(int, char**) {
    printf("Version: %li\n", __cplusplus);
    return (0);
}
