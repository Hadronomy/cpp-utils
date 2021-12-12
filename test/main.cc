
#include <iostream>

#include "colors.h"
#include "cli.h"

int main(int arg_count, char* pased_args[]) {
	utils::Cli cli(
		"Test",
		"test description",
		{
			utils::Argument("test-argument",  "Just an argument, nothing out of the ordinary...")
		},
		{
			utils::Flag("holi", "l", "HOLI")
		}
	);
	cli.Parse(arg_count, pased_args);
	return 0;
}
