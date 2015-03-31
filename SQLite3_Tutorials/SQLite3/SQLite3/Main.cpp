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

	sqlite3* myDatabase = NULL;    //This is our database object

	#pragma sqlite3_open("TestDabase.db", &myDatabase); //Opens and creates database 
	//if it doesn't exist

	char* errorMsg = NULL;
	string sqlStatement;            //SQL Statement

	sqlStatement = "CREATE TABLE TEST(" \
		"NAME   TEXT," \
		"AGE    INT);";

	//Execute Query(myDatabase, SQL Statement, Callback func, ??, Error Msg)
	#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error message: " << errorMsg << endl;

	}

	errorMsg = NULL;
	sqlStatement = "REPLACE INTO TEST(NAME, AGE)" \
		"VALUES ('Jason', 99);";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error message: " << errorMsg << endl;
	}

	errorMsg = NULL;
	sqlStatement = "SELECT * from TEST order by AGE desc;";

#pragma sqlite3_exec(myDatabase, sqlStatement.c_str(), Callback, 0, &errorMsg);

	if (errorMsg != NULL)
	{
		cout << "Error message: " << errorMsg << endl;
	}

#pragma sqlite3_close(myDatabase);  //Closes the database after we're finished

	system("pause");

	return 0;
}