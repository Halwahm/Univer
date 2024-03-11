#include <iostream>
#include "OS12.h"
#pragma comment(lib, "D:\\My Files\\Univer\\3 COURSE\\6 sem\\СП\\Lab33\\OS12\\Debug\\OS12.lib")

using namespace std;

int main()
{
	try
	{
		OS12HANDLE h1 = OS12::Init();
		OS12HANDLE h2 = OS12::Init();

		cout << "OS12:Adder::Add(h1, 2, 3) = " << OS12::Adder::Add(h1, 2, 3) << endl;
		cout << "OS12:Adder::Add(h2, 2, 3) = " << OS12::Adder::Add(h2, 2, 3) << endl;
		
		cout << "OS12:Adder::Sub(h1, 2, 3) = " << OS12::Adder::Sub(h1, 2, 3) << endl;
		cout << "OS12:Adder::Sub(h2, 2, 3) = " << OS12::Adder::Sub(h2, 2, 3) << endl;

		cout << "OS12:Multiplier::Mul(h1, 2, 3) = " << OS12::Multiplier::Mul(h1, 2, 3) << endl;
		cout << "OS12:Multiplier::Mul(h1, 2, 3) = " << OS12::Multiplier::Mul(h2, 2, 3) << endl;

		cout << "OS12:Multiplier::Div(h1, 2, 0) = " << OS12::Multiplier::Div(h1, 2, 0) << endl;
		cout << "OS12:Multiplier::Div(h1, 2, 3) = " << OS12::Multiplier::Div(h2, 2, 3) << endl;

		OS12::Dispose(h1);
		OS12::Dispose(h2);
	}
	catch (char* message)
	{
		cout << "OS12: error " << message << endl;
	}
}

