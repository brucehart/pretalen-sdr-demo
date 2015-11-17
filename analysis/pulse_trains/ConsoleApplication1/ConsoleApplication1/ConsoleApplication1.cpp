// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned int v1 = 0;
	unsigned int v2 = 0;
	unsigned int counter = 0;

	enum pulsetype { NONE, SHORT, LONG };

	pulsetype currentType = NONE;
	
	unsigned int pulseCounter = 0;
	

	std::ifstream inFile("../../pulse_train_output_left.bin", std::ios::binary);
	std::ofstream outFile("../../pulse_train_repeats_left.txt");

	while (inFile.read((char*)&v1, sizeof(unsigned int)))
	{
		if (v1 == v2)
			counter++;
		else
		{			
			if (v2 > 0)
			{
				//outFile << v2 << " repeated " << counter << " times \n";
				if (counter > 1000 )
				{
					if (currentType == SHORT)
					{
						outFile << pulseCounter << " short pulses.\n";
						pulseCounter = 1;
					}
					else
						pulseCounter++;

					currentType = LONG;

				}
				else
				{
					if (currentType == LONG)
					{
						outFile << pulseCounter << " long pulses.\n";
						pulseCounter = 1;
					}
					else
						pulseCounter++;

					currentType = SHORT;
				}
			}
			counter = 1;
			v2 = v1;
		}

	}

	inFile.close();
	outFile.close();
	
	std::cin.get();
	return 0;
}

