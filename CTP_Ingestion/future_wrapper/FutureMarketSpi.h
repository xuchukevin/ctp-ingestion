#pragma once

#include <map>

#include "FutureMarketApi.h"
#include "..\future_library\ThostFtdcMdApi.h"

using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;

public class FutureMarketSpi : public CThostFtdcMdSpi  
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

	FutureMarketApi* m_api;

	gcroot<BackgroundWorker^> worker;

	map<string, int> regMap;

public:
	FutureMarketSpi(String^ ctp_ip, String^ ctp_broker, String^ ctp_userID, String^ ctp_passwd, String^ ctp_port_m, String^ ctp_port_t, 
		String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd, FutureMarketApi* m_api, BackgroundWorker^ worker);
	virtual ~FutureMarketSpi();
	void Init();
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
};
