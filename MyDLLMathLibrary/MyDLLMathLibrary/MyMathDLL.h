#ifdef DLL
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif#include <string>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;namespace MyDLL{}