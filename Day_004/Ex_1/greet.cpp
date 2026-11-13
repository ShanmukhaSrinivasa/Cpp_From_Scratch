#include <iostream>

int main()
{
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;

    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    std::cout << "Hello! " << name << ", your age is: " << age << std::endl;
    
    return 0;
}