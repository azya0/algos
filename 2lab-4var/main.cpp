#include <iostream>
#include "polyLIB/polyLIB.h"


int main() {
    Polynom<int> main("files/poly.txt");
    Polynom<double> other("files/other.txt");
    Polynom<int> flex("files/flex.txt");

    flex.print();
    std::cout << std::endl;

    main.print();
    std::cout << std::endl;

    main.print();
    std::cout << std::endl;

    other.print();
    std::cout << std::endl;
    (main + other).print();
    std::cout << std::endl;
    (other + main).print();
    std::cout << std::endl;
    (main - other).print();
    std::cout << std::endl;
    auto huynya = (other - main);
    (huynya - flex).print();
    std::cout << std::endl;
    auto first = (other - main);
    auto second = (main - other);
    (first + second).print();
    std::cout << std::endl;
    (main * flex).print();
}
