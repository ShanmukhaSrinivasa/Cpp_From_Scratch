#include <iostream>

int main()
{
    int count = 0;

    // a
    for(int i=0; i<5; i++)
    {
        count++;
    }

    std::cout << "A: " << count << "\n";

    // b
    count = 0;
    for(int i=0; i<=5; i++)
    {
        count++;
    }

    std::cout << "B: " << count << "\n";

    // c
    count = 0;
    for(int i=10; i>0; i-=3)
    {
        count++;
    }

    std::cout << "C: " << count << "\n";

    // d
    count = 0;
    int n = 0;

    while(n>0)
    {
        count++;
        n--;
    }

    std::cout << "D: " << count << "\n";

    // e
    count = 0;
    int m = 0;

    do
    {
        count++;
    } while(m > 0);

    std::cout << "F: " << count << "\n";

    // f
    count = 0;
    for(int i=0; i<10; i++)
    {
        if(i == 3)
        {
            continue;
        }

        if(i==6)
        {
            break;
        }

        count++;
    }

    std::cout << "F: " << count << "\n";

    // g
    int a = 3;
    int b = a++;
    int c = ++a;

    std::cout << "A: " << a << "\n";
    std::cout << "B: " << b << "\n";
    std::cout << "C: " << c << "\n";
    return 0;
}