
#include <iostream>

#include "colors.h"
#include "cli.h"

int main(int arg_count, char* pased_args[]) {
	utils::Cli cli(
		"test",
		{utils::Argument("test-argument", "Just an argument, nothing out of the ordinary...")},
		{}
	);
	cli.Parse(arg_count, pased_args);
	if (cli.GetFlag("help")) {
		cli.ShowHelp();
	}
	return 0;
}
