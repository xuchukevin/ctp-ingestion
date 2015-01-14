#pragma once

#include <vcclr.h>

#include "..\future_library\ThostFtdcMdApi.h"

using namespace System;

public class FutureMarketApi : public CThostFtdcMdApi  
{
public:
	FutureMarketApi();
	virtual ~FutureMarketApi();
	void SubscribeAllFutureMarketData(String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd);
};
