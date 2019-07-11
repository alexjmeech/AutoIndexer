#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "AutoIndexer.h"
using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		Catch::Session().run();
		return 0;
	}
    
	ifstream input(argv[1]);
	ofstream output(argv[2]);
	AutoIndexer(input, output);
	input.close();
	output.close();

	return 0;
}
