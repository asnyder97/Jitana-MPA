/*
 * dbFunctions.h
 *
 *  Created on: Jul 14, 2017
 *      Author: andrew
 */

#ifndef DBFUNCTIONS_H_
#define DBFUNCTIONS_H_

#include <mysql++.h>
#include <mysql.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace mysqlpp;

Connection connectionDB(char *user, char *password)
{
	//WARNING!
	//Connection to DB  - need to change the input information - Password
	//   should not be in this file.
	Connection conn(true);

	//Attempts to connect to local database.
	try
	{
		conn.connect("cc", "localhost", string(user).c_str(), string(password).c_str(), 3306);
		cout << "Connected to database\n\n";

	}
	//Catches if the database cannot be connected to.
	catch (mysqlpp::Exception &e)
	{
		cout << e.what() << "\n";
	}

	return conn;
}

vector<vector <string> > queryDB(string request, char *user, char *password)
{
	//Input is a query string.

	//Temporary multi-dimensional vector to return results.
	vector<vector <string> > queryResults;

	//Runs connection function.
	Connection conn = connectionDB(user, password);

	//Attempts to run query with requested query.
	Query attempt = conn.query(request);

	//Stores results and runs iterator through it.
	StoreQueryResult storeRequest = attempt.store();
	StoreQueryResult::iterator it;
	it = storeRequest.begin();

	//Runs iterator till the end of stored Results.
	//Pushes information onto temp vector.
	while (it != storeRequest.end())
	{
		Row row = *it;
		vector <string> singleRow;
		for (unsigned i = 0; i < row.size(); ++i)
		{
			singleRow.push_back(row[i].c_str());
		}
		if (singleRow[0] != "android.intent.action.MAIN")
		{
			queryResults.push_back(singleRow);
		}
		++it;
	}

	//Return temp vector.
	return queryResults;
}

vector<vector <string> > receiverIC3Query(char *user, char *password)
{
	//Receiver information query.
	//Runs queryDB function with specific query and returns results.
	vector<vector <string> > results;
	string query = "select ActionStrings.st, Classes.class, "
			"Applications.app  from IFActions join IntentFilters "
			"on (IFActions.filter_id = IntentFilters.id) join "
			"ActionStrings on (ActionStrings.id = IFActions.action) "
			"join Components on (IntentFilters.component_id = "
			"Components.id) join Classes on (Components.class_id = "
			"Classes.id) join Applications on (Classes.app_id = "
			"Applications.id);";
	results = queryDB(query, user, password);
	return results;
}



#endif /* DBFUNCTIONS_H_ */
