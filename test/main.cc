
#include <iostream>
#include <map>
#include <iomanip>

#include "colors.h"
#include "cli.h"
#include "lists.h"

int main(int arg_count, char* pased_args[]) {
  utils::Cli cli(
		"hello",
		"Just saying hello world", {
			utils::Argument("hello", "ups")
		}, {
			utils::Argument("world", "ups")
		}
	);
	cli.Parse(arg_count, pased_args);
	auto hello = cli.GetArgument<std::string>("hello");
	auto world = cli.GetOption<std::string>("world");
	std::cout << hello << " " << world << std::endl;
	return 0;
}
