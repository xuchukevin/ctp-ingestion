#pragma once

#include <map>

#include "StockMarketApi.h"
#include "..\stock_library\ThostFtdcMdApiSSE.h"

using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;

public class StockMarketSpi : public CZQThostFtdcMdSpi  
{
	char* ctp_ip;
	char* ctp_port_m;
	char* ctp_port_t;
	char* ctp_userID;
	char* ctp_passwd;
	char* ctp_broker;

	gcroot<String^> sql_ip;
	gcroot<String^> sql_port;
	gcroot<String^> sql_userID;
	gcroot<String^> sql_passwd;

	StockMarketApi* m_api;

	gcroot<BackgroundWorker^> worker;

	map<string, int> regMap;

public:
	StockMarketSpi(String^ ctp_ip, String^ ctp_broker, String^ ctp_userID, String^ ctp_passwd, String^ ctp_port_m, String^ ctp_port_t, 
		String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd, StockMarketApi* m_api, BackgroundWorker^ worker);
	virtual ~StockMarketSpi();
	void Init();
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	void OnRspError(CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspUserLogin(CZQThostFtdcRspUserLoginField *pRspUserLogin, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRtnDepthMarketData(CZQThostFtdcDepthMarketDataField *pDepthMarketData);
};
