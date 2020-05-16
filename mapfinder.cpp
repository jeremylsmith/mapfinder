/*
Copyright 2019 Jeremy Smith

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//boulderdash.bin 1 2 1 2 1 1 1 10 1 2 1 2 1 1 2 1 2 returns 594 / 2529

#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	string arg1;

	if (argc == 2)
		arg1 = argv[1];

	vector<int>searchfor;

	if (arg1 == "--help")
	{
		printf("MapFinder version 1.0\n");
		printf("(c)2019 Jeremy Smith\n");
		printf("First argument is file name to search within\n");
		printf("Second and above arguments are the numbers to search for\n");
		printf("Example: boulderdash.bin 1 2 1 2 1 1 1 10 1 2 1 2 1 1 2 1 2 returns '2529'\n");
		return 1;
	}

	for (int m = 2; m < argc; m++)
	{
		searchfor.push_back(atol(argv[m]));
	}
	
	if (searchfor.size() == 0)
	{
		printf("No input data entered\n");
		return 1;
	}
	
	if (argc == 1)
	{
		printf("No filename given\n");
		return 1;
	}
	
	vector<long>datain;
	FILE *f;
	unsigned long fsize;
	f = fopen(argv[1],"r+b");

	if (!f)
	{
		printf("Input filename not found\n");
		return 1;
	}

	if (f)
	{
		fseek(f,0,SEEK_END);
		fsize = ftell(f);
		fseek(f,0,SEEK_SET);
		unsigned char *bd;
		bd = (unsigned char *)malloc(fsize+1);

		if (!bd)
		{
			printf("Could not allocate memory for given file\n");
			return 1;
		}

		if (bd)
		{
			fread(bd,1,fsize,f);
			fclose(f);
			bd[fsize] = 0;

			for (int l = 0; l < fsize; l++)
			{
				datain.push_back(bd[l]);
			}
			vector<int>counted;
			int count = 0;
			map<long,long>addresses;

			for (int i = 0; i< datain.size(); i++)
			{
				int j = i;
				while ((datain[j] == datain[i]))
				{
					j++;
					count++;
				}
				addresses[counted.size()] = i;
				counted.push_back(count);
				count = 0;
				i = j-1;
			}

			int k;
			for (k = 0; k < counted.size(); k++)
			{
	//			printf("C:%d\n",counted[k]);
			}

			for (k = 0; k < counted.size(); k++)
			{
	//			printf("A:%d\n",addresses[k]);
			}

	int co = 0;

	for (co = 0; co < counted.size(); co++)
	{
		//3 3 2 1
		if (counted[co] == searchfor[0])
		{
			int counter = co;

			if (searchfor.size() == 1)
			{
				printf("Found: %d\n",addresses[co]);
			}
			else
			{
				//searching for 1,2,3 in 1,2,3,4,5

				//matched starts at 1 and ends at 3
				//progress starts at 1

				int matched = 1;

				//> 1 items
				while (1)
				{
					if (matched == searchfor.size())
					{
						printf("Found: %d\n",addresses[co]);
						break;
					}

					if (counted[co+matched] == searchfor[matched])
					{
	//					printf("Match");
					}
					else
						//when to stop
						break;

					matched++;
				}
			}
		}
		}
		free(bd);
		}


	}
	return 0;
}

