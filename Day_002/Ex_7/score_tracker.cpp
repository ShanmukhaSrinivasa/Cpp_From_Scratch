#include <iostream>

int main()
{
    int score = 0;

    std::cout << "Score: " << score << std::endl;

    score += 10;
    std::cout << "Killed an enemy score +10!" << std::endl;

    std::cout << "Score: " << score << std::endl;

    score += 25;
    std::cout << "Completed an objective score +25!" << std::endl;

    std::cout << "Score: " << score << std::endl;

    score -= 5;
    std::cout << "Took a penalty score -5!" << std::endl;

    std::cout << "Score: " << score << std::endl;

    double celsius = 37.0;

    double fahrenheit = celsius * 9.0 / 5.0 + 32;

    std::cout << fahrenheit << std::endl;

    return 0;
}