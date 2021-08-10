#include <iostream>
#include <string>
void swap_ref(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
void swap_pointer(int* a, int* b) {
    int tempa = *a;
    *a = *b;
    *b = tempa;
}

int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    swap_ref(a, b);
    std::cout << std::to_string(a) + " and " + std::to_string(b) + "\n";
    swap_pointer(&c, &d);
    std::cout << std::to_string(c) + " and " + std::to_string(d) + "\n";
}