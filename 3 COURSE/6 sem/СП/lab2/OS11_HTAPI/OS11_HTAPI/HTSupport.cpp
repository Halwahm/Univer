#include "pch.h"
#include "HTSupport.h"
#include <Windows.h>
#include <stdlib.h>
#include <Math.h>

int BuildHash(const void* key, int keylength)
{
	int hash = 0;

	char* slider = (char*)key;
	for (int i = 0; i < keylength - 1; i++)
	{
		hash += (div(slider[i + 1] + slider[i], abs(255 - i)).rem) << keylength / (24 * (i + 1));
	}

	return abs(hash);
}