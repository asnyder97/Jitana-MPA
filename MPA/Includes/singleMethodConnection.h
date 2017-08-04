/*
 * singleMethodConnection.h
 *
 *  Created on: Jul 28, 2017
 *      Author: andrew
 */

#ifndef SINGLEMETHODCONNECTION_H_
#define SINGLEMETHODCONNECTION_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../Includes/parseInsn.h"

using namespace std;

vector<string> senders;

void findSensitivePath(vector<vector <int> > connections,
		vector<vector <string> > methods, vector<int> sensitive, char *user, char *password, char *path)
{
	vector<vector <string> > receivers = receiverIC3Query(user, password);
	for (unsigned s = 0; s < sensitive.size(); ++s)
	{
		int test = sensitive[s];
		for (unsigned c = 0; c < connections[test].size(); ++c)
		{
			int num = connections[test][c];
			senders.push_back(methods[num+1][0]);
		}
	}
}

string replaceAll(string input, string x, string y)
{
	size_t poistion = 0;
	while(poistion < input.size())
	{
		poistion = input.find(x, poistion);
		if (poistion > input.size())
		{
			break;
		}
		input.replace(poistion, size_t(1), y);
	}
	return input;
}


vector<vector <string> > isSensitive(vector<vector <string> > apps)
{
	for (unsigned a = 0; a < apps.size(); ++a)
	{
		//string application = replaceAll(apps[a][1], ".", "/");
		for (unsigned s = 0; s < senders.size(); ++s)
		{
			size_t inApp = senders[s].find(apps[a][4]);
			if (inApp >= 100)
			{
				inApp = apps[a][4].find(senders[s]);
			}

			if (inApp < 100)
			{
				apps[a].push_back("(SENSITIVE)");
			}
		}
	}
	return apps;
}


#endif /* SINGLEMETHODCONNECTION_H_ */
