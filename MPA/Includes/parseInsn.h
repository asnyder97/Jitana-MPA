/*
 * parseInsn.h
 *
 *  Created on: Jul 28, 2017
 *      Author: andrew
 */

#ifndef PARSEINSN_H_
#define PARSEINSN_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string>  parseInsnFile(int id, string filename, vector<vector <string> > methodVector, char *path)
{
	//Parses through single INSN File and returns vector<string> results.

	//creates temporary vector.
	vector <string> output;

	//opens and streams insn file.
	ifstream insn;
	filename = (string)path + "/" + filename;
	insn.open(filename.c_str());
	ifstream file(filename.c_str());

	//runs while loop till end of file.
	while(!insn.eof())
	{
		//Checks to see if the insn file exists and has anything inside of it.
		if ((bool)insn == false)
		{
			break;
		}

		//Runs a line of the file.
		string line;
		getline(insn, line);

		//parses through the file for cons-string.
		size_t first = line.find("const-string");
		size_t second = line.find("[", first);
		size_t third = line.find("]", second);

		//If found it extracts information inside and pushes string
		//    onto vector.
		if (first < 100)
		{
			string extract = line.substr(second + 1, third - second - 1);
			output.push_back(extract);
		}

	}

	//closese INSN file and returns vector.
	insn.close();
	return output;
}



#endif /* PARSEINSN_H_ */
