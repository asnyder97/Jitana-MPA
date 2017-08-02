/*
 * blackListCheck.h
 *
 *  Created on: Jul 26, 2017
 *      Author: andrew
 */

#ifndef BLACKLISTCHECK_H_
#define BLACKLISTCHECK_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> blackListVector()
{
	vector<string> blackList;
	ifstream bl;
	bl.open("/home/andrew/srp/DMA/BlackList.txt");
	while(!bl.eof())
	{
		string line;
		getline(bl, line);
		if (line.size() != 0)
		{
			line = line.substr(0, line.size() - 1);
			blackList.push_back(line);
		}
	}
	bl.close();
	return blackList;
}

vector<int> blackListCheck(vector<vector <string> > input)
{
	vector<string> blackList = blackListVector();
	vector<int> blID;
	for (unsigned i = 0; i < input.size(); ++i)
	{
		for (unsigned b = 0; b < blackList.size(); ++b)
		{
			size_t num = input[i][1].find(blackList[b]);
			if (num < 10000)
			{
				cout << input[i][0] << "\n";
				cout << input[i][1] << "\n";
				cout << input[i][2] << "\n";
				cout << "ID number: " << i - 1 << "\n";
				blID.push_back(i-1);
			}
		}
	}
	return blID;
}





#endif /* BLACKLISTCHECK_H_ */
