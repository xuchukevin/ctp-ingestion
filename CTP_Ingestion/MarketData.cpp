#include "stdafx.h"

#include "MarketData.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	MarketData::MarketData(char* code, char* exchange, int volume, double lastPrice, double openPrice, double closePrice, 
		double preClosePrice, double highestPrice, double lowestPrice, const char* updateDate, char* updateTime)
	{
		this->code = gcnew String(code);
		this->exchange = gcnew String(exchange);
		this->volume = volume;
		this->lastPrice = lastPrice;
		this->openPrice = openPrice;
		this->closePrice = closePrice;
		this->preClosePrice = preClosePrice;
		this->highestPrice = highestPrice;
		this->lowestPrice = lowestPrice;
		//this->updateDate = gcnew String(updateDate);

		char buf2[20];
		struct tm now2;
		time_t t2 = time(0);
		localtime_s(&now2, &t2);
		strftime(buf2, sizeof(buf2), "%Y-%m-%d", &now2);
		this->updateDate = gcnew String(buf2);

		this->updateTime = gcnew String(updateTime);
		this->timestamp = String::Concat(this->updateDate, " ", this->updateTime);

		char buf[20];
		struct tm now;
		time_t t = time(0);
		localtime_s(&now, &t);
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &now);
		this->responseTime = gcnew String(buf);
	}

	String^ MarketData::getCode()
	{
		return code;
	}

	String^ MarketData::getExchange()
	{
		return exchange;
	}

	int MarketData::getVolume()
	{
		return volume;
	}

	double MarketData::getLastPrice()
	{
		return lastPrice;
	}

	double MarketData::getOpenPrice()
	{
		return openPrice;
	}

	double MarketData::getClosePrice()
	{
		return closePrice;
	}

	double MarketData::getPreClosePrice()
	{
		return preClosePrice;
	}

	double MarketData::getHighestPrice()
	{
		return highestPrice;
	}
	
	double MarketData::getLowestPrice()
	{
		return lowestPrice;
	}

	String^ MarketData::getUpdateDate()
	{
		return updateDate;
	}

	String^ MarketData::getUpdateTime()
	{
		return updateTime;
	}

	String^ MarketData::getTimestamp()
	{
		return timestamp;
	}

	String^ MarketData::getResponseTime()
	{
		return responseTime;
	}
}
