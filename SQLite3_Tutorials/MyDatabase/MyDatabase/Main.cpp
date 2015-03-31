#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

static int Callback(void* notUsed, int numArgs, char **data, char **columnName)
{

	float myFloat = 4.0;

	for (int i = 0; i < numArgs; i++)
	{
		cout << columnName[i] << ": " << data[i] << endl;
	}

	return 0;
}

int main()
{
	sqlite3* myDatabase = NULL;

	#pragma sqlite3_open("Test", &myDatabase);

	char* errorMsg = NULL;
	string sqlStatement;

	sqlStatement = "CREATE TABLE SERVER("\
		"ServerNumber	int,"\
		"Location		string,"\
		"Type			string);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error Message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "INSERT INTO TEST(ServerNumber, Location, Type)" \
		"VALUES(1, 'Spawn', PvE);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error Message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "INSERT INTO TEST(ServerNumber, Location, Type)" \
		"VALUES(1, 'Feild_1', PvE);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error Message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "INSERT INTO TEST(ServerNumber, Location, Type)" \
		"VALUES(1, 'Arena', PvP);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error Message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "INSERT INTO TEST(ServerNumber, Location, Type)" \
		"VALUES(3, 'Spawn', PvP);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error Message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "INSERT INTO TEST(ServerNumber, Location, Type)" \
		"VALUES(2, 'Boss_1', PvE);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error Message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "SELECT * from TEST ServerNumber = 1;";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	system("pause");
	return 0;
}