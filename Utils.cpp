#include "stdafx.h"
#include "Utils.h"


Utils::Utils()
{
}


Utils::~Utils()
{
}

int Utils::getRandomIndex(int maxIndex)
{
	int index = rand() % (maxIndex + 1);
	return index;
}
