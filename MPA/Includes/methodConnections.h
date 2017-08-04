/*
 * methodConnections.h
 *
 *  Created on: Jul 28, 2017
 *      Author: andrew
 */
using namespace std;

#ifndef METHODCONNECTIONS_H_
#define METHODCONNECTIONS_H_

#include <iostream>
#include <string>
#include <vector>

static vector<vector <int> > receiverConnections;

void reSizeConnectionsVector(int num)
{
	//Resizes the static vector in this header file.
	receiverConnections.resize(num);
}

void addConnectionFromLine(string line)
{
	//Parses through a single line to find connections.

	//Separates the numbers from the beginning of the line.
	size_t pointOne = line.find("->");
	string sender = line.substr(0, pointOne);
	size_t pointTwo = line.find(" ", pointOne);
	string receiver = line.substr(pointOne + 2, pointTwo - pointOne - 2);

	//Changes these string numbers into integers.
	//receiverID is used as an ID for place inside of vector.
	int senderID = atoi(sender.c_str());
	int receiverID = atoi(receiver.c_str());

	//boolean to see if the number is already inside of the vector.
	bool alreadyIn = false;

	//Goes through the vector at the receiverID.
	for (unsigned i = 0; i < receiverConnections[receiverID].size(); ++i)
	{
		//Checks to see if sender is already connected to the receiver.
		if (senderID == receiverConnections[receiverID][i])
		{
			alreadyIn = true;
			break;
		}
	}
	//If not already inside of vector, the sender is added to the vector
	//    at the receiverID.
	if (alreadyIn == false)
	{
		receiverConnections[receiverID].push_back(senderID);
	}
}

vector<vector <int> > returnConnections()
{
	//returns the Connections vector when needed.
	return receiverConnections;
}

void  printConnections()
{
	//Prints the Connections into Console.
	for (unsigned k = 0; k < receiverConnections.size(); ++k)
	{
		cout << "Receiver Number:  " << k << "   ";
		cout << "Senders:  ";
		for (unsigned l = 0; l < receiverConnections[k].size(); ++l)
		{
			cout << receiverConnections[k][l] << "  ";
		}
		cout << "\n";
	}
}

#endif /* METHODCONNECTIONS_H_ */
