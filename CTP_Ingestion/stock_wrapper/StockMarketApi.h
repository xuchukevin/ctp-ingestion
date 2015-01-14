#pragma once

#include <vcclr.h>

#include "..\stock_library\ThostFtdcMdApiSSE.h"

using namespace System;

public class StockMarketApi : public CZQThostFtdcMdApi  
{
public:
	StockMarketApi();
	virtual ~StockMarketApi();
	void SubscribeAllStockMarketData(String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd);
};

