
#include <iostream>

#include "colors.h"

int main() {
	std::cout << utils::Colorize(utils::ColorTint::kYellow) << utils::Colorize(utils::FontStyle::kBold);
	std::cout << "Holi uwu Mundo" << std::endl;
	std::cout << utils::Colorize::Reset;
	return 0;
}
