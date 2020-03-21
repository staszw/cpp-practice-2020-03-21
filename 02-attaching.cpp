#include <iostream>
#include <string>

int main()
{
	std::cout << "What is your name? ";
	std::string s;
	std::cin >> s;
	std::cout << "Hello, " << s << '!' << std::endl;
}
