/*
mapfinder - Frequency Search
Copyright (C) 2020 Jeremy Smith
-----

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
-----

INFORMATION
  www: https://github.com/jeremylsmith/mapfinder/
  e-mail: jeremy@decompiler.org
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

	if (argc == 1)
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

