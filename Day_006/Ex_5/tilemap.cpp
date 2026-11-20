#include <iostream>
#include <limits>

int main()
{
    int width;
    int height;
    int playerX;
    int playerY;

    while(true)
    {
        std::cout << "Enter Tilemap's width: ";
        std::cin >> width;

        if(std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            std::cout << "That's not a valid number for width, try again!" << "\n";
            continue;
        }
        break;
    }

    while(true)
    {
        std::cout << "Enter Tilemap's height: ";
        std::cin >> height;

        if(std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            std::cout << "That's not a valid number for height, try again!" << "\n";
            continue;
        }
        break;
    }

    while(true)
    {
        std::cout << "Enter Player's X position : ";
        std::cin >> playerX;

        if(std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            std::cout << "That's not a valid number for position X, try again!" << "\n";
            continue;
        }
        break;
    }

    while(true)
    {
        std::cout << "Enter Player's Y position : ";
        std::cin >> playerY;

        if(std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            std::cout << "That's not a valid number for position Y, try again!" << "\n";
            continue;
        }
        break;
    }

    for(int rows=0; rows<height; rows++)
    {

        for(int col=0; col<width; col++)
        {
            if(rows == 0 || col == 0 || rows == height - 1 || col == width -1)
            {
                std::cout << "#";
                // i++;
            }
            else if(rows == playerY && col == playerX)
            {
                std::cout << "@";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }

    return 0;
}