#include <iostream>
#include "polyLIB.h"


int main() {
    Polynom<double> main("files/poly.txt");
    Polynom<int> other("files/other.txt");

    std::cout << "Polynom from \"files/poly.txt\":\n";
    main.print();
    std::cout << "\nPolynom from \"files/other.txt\":\n";
    other.print();
    std::cout << "\nSum of these polynomials:\n";
    (main + other).print();
    std::cout << "\nThe first polynomial minus the second:\n";
    (main - other).print();
    std::cout << "\nThe second polynomial minus the first:\n";
    (other - main).print();
    std::cout << "\nThe second polynomial mul the first:\n";
    (main * other).print();
    std::cout << "\nConvert first polynom from double to int:\n";
    main.convert<int>().print();
}
