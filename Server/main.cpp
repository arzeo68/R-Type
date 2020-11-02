//
// Created by arzeo on 10/26/2020.
//

#include <type_traits>

template<typename A>
concept test_concept = std::is_integral_v<A>;

template<typename A>
void helloFunc() requires test_concept<A> {
}

int main(int, char **) {
}
