#include <stdio.h>
#include <iostream>

using namespace std;

void getArgs(int argc, char** argv)
{
	int i = 1;
	int argCount=0;

	string shape="";
	string color="";
	string outName="";
	while(i<argc)
	{
		if (argv[i][0]=='-')
		{
			switch (argv[i][1])
			{
				case 's':
					if (argv[i+1][0]!= '-')
					{
						shape = argv[i+1];
					}
				case 's':
					if (argv[i+1][0]!= '-')
					{
						shape = argv[i+1];
					}
				

			}
		}
		i++;
	}
}

int main(int argc, char** argv)
{
	getArgs(argc, argv);
	return 0;
}