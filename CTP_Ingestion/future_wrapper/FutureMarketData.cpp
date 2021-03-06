#include "stdafx.h"

#include "FutureMarketData.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	FutureMarketData::FutureMarketData(char* code, char* exchange, int volume, double lastPrice, double openPrice, double closePrice, 
		double preClosePrice, double highestPrice, double lowestPrice, const char* updateDate, char* updateTime) 
		: MarketData(code, exchange, volume, lastPrice, openPrice, closePrice, preClosePrice, highestPrice, lowestPrice, updateDate, updateTime)
	{
	}
}
