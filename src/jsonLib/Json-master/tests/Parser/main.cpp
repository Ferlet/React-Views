#include <iostream>
#include "srcs/Parser/Parser.hpp"

int main(int ac, char **av)
{
	// if (ac == 1)
	// 	return (1);
	// std::string arg1(av[1]);
	(void) ac; (void) av;

	json::Entity opennedJson;

	std::cin >> opennedJson;

	std::cout << opennedJson << std::endl;
	return (0);
}
