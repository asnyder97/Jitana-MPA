using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Includes/dbFunctions.h"
#include "Includes/dotGraph.h"
#include "Includes/blackListCheck.h"
#include "Includes/methodConnections.h"
#include "Includes/singleMethodConnection.h"
#include "Includes/parseInsn.h"

//Static multi-dimensional vectors that save data
//	that is used multiple times.
static vector<vector <string> > methodVector;
static vector<vector <string> > insnVector;
static vector<vector <string> > insnCombined;
static vector<vector <string> > final;
static vector<vector <string> > iacVector;

void parseMethods(char *path)
{
	//Parses through Method Graph of jitana-travis.

	//Opens ifstream to allow program to go through file.
	ifstream methodGraph;
	methodGraph.open((string(path) + "/method_graph.dot").c_str());
	int count = 0;
	string line;
	//While loop that goes line by line.
	while (!methodGraph.eof())
	{
		//Separates each line to be used.
		getline(methodGraph, line);

		//Temporary stores strings needed.
		vector<string> results (3);

		//Looks for code that will end the while loop.
		//	Breaks is true.
		size_t check = line.find("[dir=");
		if (check < 100)
		{
			break;
		}
		size_t checkTwo = line.find("[color=");
		if (checkTwo < 100)
		{
			break;
		}

		//Parses through line till it finds the Application class.
		//	Saves string to position 0.
		size_t first = line.find("|L");
		size_t second = line.find(";", first);
		if (first < line.size())
		{
			results[0] = line.substr(first + 2, second - first - 2);
		}

		//Parses through rest of line till it finds function.
		//  Saves string to position 1.
		size_t third = line.find('"', second);
		if (third < line.size())
		{
			results[1] = line.substr(second + 2, third - second - 2);
		}

		//Parses through rest of line till it finds URL.
		//  Saves string to position 2.
		size_t fourth = line.find("URL=", third);
		size_t fifth = line.find('"', fourth+6);
		if (fourth < line.size())
		{
			results[2] = line.substr(fourth + 5, fifth - fourth - 5);
		}

		//Pushes results into multi-dimensional array.
		methodVector.push_back(results);
		++count;
	}
	//From the current size of methodVector, changes another vector size.
	//This allows us to use the various numbers as IDs in connection with
	//    the methodVector.
	reSizeConnectionsVector(methodVector.size());

	//Runs through current line into methodConnections.h
	addConnectionFromLine(line);

	//Runs rest of the file.
	while (!methodGraph.eof())
	{
		//Streams through rest of lines.
		getline(methodGraph, line);

		//Verifying if it is last line.
		size_t num = line.find("}");
		if (num < 2)
		{
			break;
		}

		//Runs through current line into methodConnections.h
		addConnectionFromLine(line);
	}
	//Closes ifstream.
	methodGraph.close();
}

void parseInsn(char *path)
{
	//Parses through insn files and adds them to a
	//static vector<vector <string> >
	//Creates a large vector with many const-strings.

	//Going through each insn from the methodVector.
	for (unsigned i = 1; i < methodVector.size(); ++i)
	{
		//Starts stream of insn file.
		ifstream insn;
		string filename = (string)path + "/" + (string)methodVector[i][2];
		insn.open(filename.c_str());
		ifstream file(filename.c_str());

		//Runs while loop till end of single Insn file.
		while(!insn.eof())
		{
			//Checks if insn file is there, breaks loop if isn't.
			if ((bool)insn == false)
			{
				break;
			}

			//Creates variables to be used.
			string line;
			string constString;
			vector <string> output (3);
			stringstream methodNum;

			//Inserts insn name into output.
			output[0] = methodVector[i][2];

			//Inserts the methodVectors ID into the output.
			//Allows you to easily reference back to methodVector.
			methodNum << i;
			output[2] = methodNum.str();

			//Parse through line to find Const-Strings.
			//Const-Strings is where Intents are located.
			getline(insn, line);
			size_t first = line.find("const-string");
			size_t second = line.find("[", first);
			size_t third = line.find("]", second);

			//Adds string to output.
			if (first < 100)
			{
				output[1] = line.substr(second + 1, third - second - 1);
			}

			//Pushes entire ouput onto insnVector.
			insnVector.push_back(output);
		}

		//Closes stream.
		insn.close();
	}
}


void parseIACIntent(char *path)
{
	//Parses through Intent Graph for Information.

	//Opens up connection to Stream.
	//NEED TO CHANGE THE PATHING.
	ifstream IAC;
	IAC.open((string(path) + "/intent_graph.dot").c_str());
	vector<vector <string> > applications;

	//Runs stream of Intent Graph till End of File.
	while(!IAC.eof())
	{
		//Grabs string from stream.
		string line;
		getline(IAC, line);

		//Looks to see if this line is a connector Line.
		size_t connection = line.find("->");

		//Used to keep track of last input in iacVector.
		int count = 0;

		//If this is a small number then it is a connector line.
		//Runs through this If statement to extract information.
		if (connection < 100)
		{
			//Finds the sender and receiver and makes them integers.
			int sender = atoi(line.substr(0, connection).c_str());
			size_t one = line.find(" ", connection);
			int receiver = atoi(line.substr(connection + 2, one - connection - 2).c_str());

			//Verifies that they are not the same number.
			//Not looking for Component Communications.
			if (sender != receiver)
			{
				//Grabbing the intent string in the line.
				string intent;
				size_t two = line.find('"', one);
				//Runs different lines counting if string has quotation
				//    marks around it or not.
				if (two < 1000)
				{
					size_t three = line.find('"', two + 1);
					intent = line.substr(two + 1, three - two - 1);
				}
				else
				{
					two = line.find("[label=");
					size_t three = line.find(",", two +7);
					intent = line.substr(two + 7, three - two - 7);
				}

				//Makes a vector string with the path.
				//Uses the integers as IDs in the applications vector
				vector<string> path;
				path.push_back(applications[sender][1]);
				path.push_back(intent);
				path.push_back(applications[receiver][1]);

				//Checks to see is iacVector is empty.
				if (iacVector.size() > 0)
				{
					//Verifies that the path is not already inside of the vector by
					//    checking the path above it.  Uses count to determine location
					//    of last input into Vector.
					if (path[0] != iacVector[count][0] || path[2] != iacVector[count][2])
					{
						iacVector.push_back(path);
						++count;
					}
				}
				//If empty, puts first path into vector.
				else
				{
					iacVector.push_back(path);
				}
			}
		}
		//Grabs application name from graph.
		else
		{
			//Grabs information from Intent_Graph and puts information
			//    into temporary vector called applications.  Contains
			//    ID number at position 0 and Application name at
			//    position 1.
			vector<string> app;
			size_t first = line.find("[");
			if (first < 100)
			{
				app.push_back(line.substr(0, first));
				size_t second = line.find("|");
				size_t third = line.find("}", second);
				app.push_back(line.substr(second + 1, third - second - 1));
				applications.push_back(app);
			}

		}
	}
}

vector<vector <string> > combine()
{
	//Method to combine the information from the various vectors.
	vector<vector <string> > results;

	//Combining the insn and iac Vectors.
	for (unsigned n = 0; n < insnVector.size(); ++n)
	{
		for (unsigned m = 0; m < iacVector.size(); ++m)
		{
			//The connection point is the Intent which is in
			//   position 1 for both vectors.
			if (iacVector[m][1] == insnVector[n][1])
			{
				//combines information into temp vector string.
				vector <string> combined (4);
				combined[0] = insnVector[n][0];
				combined[1] = iacVector[m][0];
				combined[2] = iacVector[m][1];
				combined[3] = iacVector[m][2];
				//Pushes temp vector onto multi-dimensional vector.
				results.push_back(combined);
			}
		}
	}
	//Combines the method graph with the results of the first combine.
	for (unsigned r = 0; r < results.size(); ++r)
	{
		for (unsigned h = 0; h < methodVector.size(); ++h)
		{
			//The insn URL is the combination point.
			if (results[r][0] == methodVector[h][2])
			{
				//Pushes information into results at specific point in
				//    multi-dimensional vector.
				results[r].push_back(methodVector[h][0]);
				results[r].push_back(methodVector[h][1]);
			}
		}
	}
	return results;
}



void printFinal()
{
	//Print function to look at the full vector combination.
	for (unsigned u = 0; u < final.size(); ++u)
	{
		cout << "URL = " << final[u][0] << "\n";
		cout << "Sender = " << final[u][1] << "\n";
		cout << "Intent = " << final[u][2] << "\n";
		cout << "Receiver = " << final[u][3] << "\n";
		cout << "Application Class = " << final[u][4] << "\n";
		cout << "Function = " << final[u][5] << "\n\n";
	}
}

int main(int argc, char *argv[])
{
	//Main function that runs all the various functions in a specific
	//     order.
	parseMethods( argv[2] );
	parseInsn( argv[2] );
	parseIACIntent( argv[1] );
	vector<vector <string> > receivers = receiverIC3Query( argv[3], argv[4]);
	final = combine();
	dotCreation(final, receivers);
	vector<int> blackListID = blackListCheck(methodVector);
	vector<vector <int> > connections = returnConnections();
	vector<string> path = findSensitivePath(connections, methodVector, blackListID,  argv[3], argv[4], argv[2]);

	printFinal();
	return 0;
}
