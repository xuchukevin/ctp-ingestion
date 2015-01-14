#pragma once

#include <stdlib.h>
#include <iostream>

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	public ref class MarketData
	{
		String^ code;
		String^ exchange;
		
		int volume;
		double lastPrice;
		double openPrice;
		double closePrice;
		double preClosePrice;
		double highestPrice;
		double lowestPrice;

		String^ updateDate;
		String^ updateTime;
		String^ timestamp;
		String^ responseTime;

	public:
		MarketData(char*, char*, int, double, double, double, double, double, double, const char*, char*);
		String^ getCode();
		String^ getExchange();
		int getVolume();
		double getLastPrice();
		double getOpenPrice();
		double getClosePrice();
		double getPreClosePrice();
		double getHighestPrice();
		double getLowestPrice();
		String^ getUpdateDate();
		String^ getUpdateTime();
		String^ getTimestamp();
		String^ getResponseTime();
	};
}