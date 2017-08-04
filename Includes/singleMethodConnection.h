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

#include "../Includes/parseInsn.h"

using namespace std;

vector<string> findSensitivePath(vector<vector <int> > connections,
		vector<vector <string> > methods, vector<int> sensitive, char *user, char *password, char *path)
{
	vector<string> pathOf;
	vector<vector <string> > receivers = receiverIC3Query(user, password);
	for (unsigned s = 0; s < sensitive.size(); ++s)
	{
		int test = sensitive[s];
		for (unsigned c = 0; c < connections[test].size(); ++c)
		{
			//parseInsnFile(connetions[test][c]], )
			cout << test << "\n";
			cout << methods[test+1][0] << "\n";
			cout << methods[test+1][1] << "\n";
			cout << methods[test+1][2] << "\n";
			int num = connections[test][c];
			cout << num << "\n";
			cout << methods[num+1][0] << "\n";
			cout << methods[num+1][1] << "\n";
			cout << methods[num+1][2] << "\n";
			vector<string> insnOutput = parseInsnFile(num+1, methods[num+1][2], methods, path);
			cout << "INSN:\n";
			for (unsigned i = 0; i < insnOutput.size(); ++i)
			{
				cout << insnOutput[i] << "\n";
			}
			cout << "\n";
		}
	}
	return pathOf;
}



#endif /* SINGLEMETHODCONNECTION_H_ */
