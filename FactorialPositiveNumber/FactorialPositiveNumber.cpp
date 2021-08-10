
#include <iostream>

unsigned int fractional(int n) {
    if (n == 1)return 1;
    return n * fractional(n - 1);
}
int main()
{
    int n = 0;
    std::cout << "Enter your number" << std::endl;
    std::cin >> n;
    while (n <= 0) {
        std::cout << "Input must be positive integer, try again" << std::endl;
        std::cin >> n;
    }
    std::cout << fractional(n);
}

