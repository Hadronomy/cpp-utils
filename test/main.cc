
#include <iostream>
#include <map>
#include <iomanip>
#include <chrono>
#include <thread>

#include "colors.h"
#include "cli.h"
#include "hourglass.h"
#include "lists.h"

int main(int arg_count, char* pased_args[]) {
  utils::Cli cli(
		"Example",
		"Example program"
	);
	cli.Parse(arg_count, pased_args);
	utils::Hourglass::Start();
	for (int i = 0; i < 100; ++i) {

	}
	std::cout << utils::Hourglass::Stop();
	return 0;
}
