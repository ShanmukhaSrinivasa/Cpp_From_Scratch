#include <iostream>

int main()
{
    int num1 = 100;
    double num2 = 100;
    char val1 = 'S';
    bool isNum = true;

    std::cout << "Size of int: " << sizeof(int) << " " << &num1 << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " " << &num2 << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " " << &val1 << std::endl;
    std::cout << "Size of bool: " << sizeof(bool) << " " << &isNum << std::endl;

    return 0;
}