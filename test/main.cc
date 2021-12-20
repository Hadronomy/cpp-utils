
#include <iostream>
#include <map>
#include <iomanip>

#include "colors.h"
#include "cli.h"
#include "command.h"
#include "lists.h"

int main(int arg_count, char* pased_args[]) {
  utils::Cli cli(
		"hello",
		"Just saying hello world",
		{
			utils::Argument("hello", "ups")
		}
	);
	cli.Parse(arg_count, pased_args);
	auto hello = cli.GetArgument<std::string>("hello");
	std::cout << hello << std::endl;
	return 0;
}
