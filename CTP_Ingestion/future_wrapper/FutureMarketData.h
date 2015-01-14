#pragma once

#include <stdlib.h>
#include <iostream>

#include "..\MarketData.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	public ref class FutureMarketData : public MarketData
	{
	public:
		FutureMarketData(char*, char*, int, double, double, double, double, double, double, const char*, char*);
	};
}