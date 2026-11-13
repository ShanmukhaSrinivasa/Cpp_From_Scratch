#include <iostream>

int main()
{
    int num1;
    int num2;
    int num3;
    double sum = 0;

    std::cout << "\t AVERAGE FINDER:" << "\n";

    std::cout << "Enter num1: ";
    std::cin >> num1;

    std::cout << "Enter num2: ";
    std::cin >> num2;

    std::cout << "Enter num3: ";
    std::cin >> num3;

    sum = num1 + num2 + num3;

    double average = static_cast<double>(sum) / 3.0;

    std::cout << "Average is: " << average << "\n";

    return 0;
}