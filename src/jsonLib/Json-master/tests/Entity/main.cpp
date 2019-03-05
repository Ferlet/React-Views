#include <iostream>
#include "../../srcs/Entity/Entity.hpp"

void testArrayInitAndEqualityAndClone()
{
	json::Entity arr = {
		1000,
		"Salut",
		{
			true,
			"Je suis une Str",
			json::makeObject {
				{"Salut", 12},
				{
					"Ah.", {
						1, 2, 3, 4
					}
				}
			}
		}
	};

	json::Entity arrClone = arr.clone();
	std::cout << "test equality = " << (arr == arrClone) << std::endl;
	if ((arr == arrClone) == false)
		exit(1);
	arrClone[2][2]["Ah."][1] = 7;
	std::cout << "test equality = " << (arr == arrClone) << std::endl;
	if ((arr == arrClone) == true)
		exit(1);
	std::cout << arr.stringify(json::Entity::MINIFIED) << std::endl;
}

void testMerge()
{
	json::Entity arr = {
		1000,
		"Salut",
		"Ah"
	};

	json::Entity arr2 = {
		1001,
		"Salut2",
		"Ah2"
	};

	arr.merge(arr2);

	std::cout << arr << std::endl;


	json::Entity obj = json::makeObject {
		{"File", "File.txt"},
		{"Data", "Data1"}		
	};

	json::Entity obj2 = json::makeObject {
		{"File", "File.txt"},
		{"Data", "Data2"}		
	};

	json::Entity obj3 = json::makeObject {
		{"File", "File.txt"},
		{"Data", "Data3"}		
	};

	auto merger = [] (std::string const &key, json::Entity &first, json::Entity &second) {
		if (key == "File") {
			return;
		} else if (key == "Data") {
			if (first.isArray()) {
				first.push(second);
			} else if (second.isArray()) {
				second.push(first);
				first = second;
			} else {
				first = {
					first,
					second
				};
			}
		}
	};

	obj.merge(obj2, merger);
	obj3.merge(obj, merger);
	std::cout << obj3 << std::endl;
}

void testOperator()
{
	json::Entity ah(32);

	int a = ah.to<int>();
	long b = ah.to<long>();
	double c = ah.to<double>();

	if (b != 32 || a != b || c != 32.0)
		abort();

	ah = "Salut";
	std::string ahh = ah.to<std::string>();

	if (ahh != "Salut")
		abort();
}

int main()
{
	testArrayInitAndEqualityAndClone();

	testMerge();

	testOperator();

	return (0);
}
