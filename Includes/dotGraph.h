/*
 * dotGraph.h
 *
 *  Created on: Jul 20, 2017
 *      Author: andrew
 */

#ifndef DOTGRAPH_H_
#define DOTGRAPH_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


//Structure app to save connections.
//Currently only used in this header file.
struct app{
	string application;
	vector<int> send;
	vector<int> receive;
};

//Vector of struct App above.
static vector <app> applications;
//String vector.
static vector <string> connections;


//Changes the fillColor so their is some variety.
//Will need to be changed or not used if you want specific colors
//   for senders, receivers, etc.
int fillColorChange(int fillcolor)
{
	if (fillcolor == 9)
	{
		fillcolor = 0;
	}
	else
	{
		++fillcolor;
	}
	return fillcolor;
}


void separateInput(vector<vector <string> > input)
{
	//Function to seperate information from input.
	//Ran in the dotCreation function below.

	//Going through input to check position 1 of input.
	//Have to run through this first to create initial list of senders.
	for (unsigned s = 0; s < input.size(); ++s)
	{
		//Boolean to check for duplicates.
		bool alreadyIn = false;
		for (unsigned t = 0; t < applications.size(); ++t)
		{
			//Checks to see if input is already within the applications
			//   list.  Sets boolean true if it is.  Adds to the sender
			//   side if true.
			if (input[s][1] == applications[t].application)
			{
				applications[t].send.push_back(s);
				alreadyIn = true;
			}
		}
		//Checks to see if boolean has been changed.
		//If not, makes app struct and adds information info into the
		//   vector of apps.
		if (!alreadyIn)
		{
			app object;
			object.application = input[s][1];
			object.send.push_back(s);
			applications.push_back(object);
		}

	}
	//Runs through input again but searching position 3, receiver side.
	for (unsigned r = 0; r < input.size(); ++r)
	{
		//Boolean to check if it is already in.
		bool alreadyIn = false;
		for (unsigned g = 0; g < applications.size(); ++g)
		{
			//If it is already inside of applications list, set true.
			if (input[r][3] == applications[g].application)
			{
				alreadyIn = true;
			}
		}
		//If not in application list, adds application to bottom of
		//    vector of apps.
		if (!alreadyIn)
		{
			app object;
			object.application = input[r][3];
			applications.push_back(object);
		}
	}
	//After creating the initial list, this for loop will make lines
	//    of each connection and add them to string vector to be used
	//    later.
	for (unsigned c = 0; c < input.size(); ++c)
	{
		//gets intent from input
		string intent = input[c][2];
		int send, receive;

		//Looks through applications vector for the id numbers for
		//   where they will be input into graph.  Save these numbers
		//   to add to line.
		for (unsigned s = 0; s < applications.size(); ++s)
		{
			if (input[c][1] == applications[s].application)
			{
				send = s;
			}
			if (input[c][3] == applications[s].application)
			{
				receive = s;
			}
		}
		//makes stream to add numbers to string line.
		ostringstream stream;
		stream << send << "->" << receive;

		//Creates line to be added to graph.
		string line = stream.str() + " [label=\"" + intent;
		line += "\", fontcolor=darkgreen, color=darkgreen];";

		//Saves line for future use.
		connections.push_back(line);
	}
}

void receiversEntered(vector<vector <string> > receivers)
{
	//This fills in the receiver side of the struct app
	//Input comes from receiver query to IC3.
	for (unsigned a = 0; a < applications.size(); ++a)
	{
		for (unsigned r = 0; r < receivers.size(); ++r)
		{
			if (applications[a].application == receivers[r][2])
			{
				applications[a].receive.push_back(r);
			}
		}
	}
}

void dotCreation(vector<vector <string> > input, vector<vector <string> >receivers )
{
	//starting fillcolor.
	int fillcolor = 1;

	// Starting output of graph with ofstream.
	ofstream output ("Output/graph.dot");
	output << "digraph G {\nrankdir=RL;\n";

	//Running input and receiver in respective functions written above.
	separateInput(input);
	receiversEntered(receivers);

	//Runs through the application vector.
	for (unsigned a = 0; a < applications.size(); ++a)
	{
		//Booleans to verify that send and receive additions aren't
		//   added to the line more ten once.
		bool sendOnce = false;
		bool receiveOnce = false;

		//Beginning of line for applications.
		output << a << "[label=\"{" << a << "|" << applications[a].application  << "}|";

		//Adds sender information to line.
		for (unsigned s = 0; s < applications[a].send.size(); ++s)
		{
			//Prints for the first Send.
			if (sendOnce == false)
			{
				output << "{Jitana-IAC Send}|";
				sendOnce = true;
			}

			//Adds related information with breaks.
			output << input[applications[a].send[s]][2] << "\\l-  ";
			output << input[applications[a].send[s]][4] << "\\l-  ";
			output << input[applications[a].send[s]][5] << "\\l-  ";
			output << input[applications[a].send[s]][0];

			//Ends specific send information.
			if (s != applications[a].send.size() - 1)
			{
				output << "\\l";
			}
		}
		if (sendOnce == true)
		{
			output << "\\l";
		}
		//Adds receiver information to line.
		for (unsigned r = 0; r <applications[a].receive.size(); ++r)
		{
			//Different receive counting on if it has send side.
			//Adds to line once.
			if (sendOnce == false && receiveOnce == false)
			{
				output << "{IC3 - Receive}|";
				receiveOnce = true;
			}
			else if(sendOnce == true && receiveOnce == false)
			{
				output << "|{IC3 - Receive}|";
				receiveOnce = true;
			}

			//Adds receiver information.
			output << receivers[applications[a].receive[r]][0] << "\\l-  ";
			output << receivers[applications[a].receive[r]][1];
			if (r != applications[a].receive.size() - 1)
			{
				output << "\\l";
			}
		}

		//Ends line, adding color, style, scheme, etc.
		output << "\\l\",shape=record,colorscheme=pastel19, style=filled, fillcolor=";
		output << fillcolor << "];\n";
		fillcolor = fillColorChange(fillcolor);
	}

	//Adds the connection lines that were saved earlier.
	for (unsigned c = 0; c < connections.size(); ++c)
	{
		output << connections[c] << "\n";
	}

	//Ends and closes graph.
	output << "}";
	output.close();
}

#endif /* DOTGRAPH_H_ */
