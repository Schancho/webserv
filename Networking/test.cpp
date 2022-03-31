#include <sstream>
#include <string>
#include <iostream>

int main ()
{
    int n;
    std::stringstream d("c");
    std::string s("c");

    d >> std::hex >> n;
    std::cout << n << std::endl;
}