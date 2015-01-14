#include "stdafx.h"

#include <fstream>
#include <msclr/marshal_cppstd.h>

#include "FutureMarketApi.h"
#include "FutureMarketSpi.h"
#include "FutureMetaInfo.h"
#include "..\database\DBManager.h"

using namespace std;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Runtime::InteropServices;
using namespace CTP_Ingestion;

FutureMarketSpi::FutureMarketSpi(String^ ctp_ip, String^ ctp_broker, String^ ctp_userID, String^ ctp_passwd, String^ ctp_port_m, String^ ctp_port_t, 
			 String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd, FutureMarketApi* m_api, BackgroundWorker^ worker)
{
	this->ctp_ip = (char*)(void*)Marshal::StringToHGlobalAnsi(ctp_ip);
	this->ctp_broker = (char*)(void*)Marshal::StringToHGlobalAnsi(ctp_broker);
	this->ctp_userID = (char*)(void*)Marshal::StringToHGlobalAnsi(ctp_userID);
	this->ctp_passwd = (char*)(void*)Marshal::StringToHGlobalAnsi(ctp_passwd);
	this->ctp_port_m = (char*)(void*)Marshal::StringToHGlobalAnsi(ctp_port_m);
	this->ctp_port_t = (char*)(void*)Marshal::StringToHGlobalAnsi(ctp_port_t);
	
	this->sql_ip = sql_ip;
	this->sql_port = sql_port;
	this->sql_userID = sql_userID;
	this->sql_passwd = sql_passwd;

	this->m_api = m_api;
	this->worker = worker;
}

FutureMarketSpi::~FutureMarketSpi()
{
	Marshal::FreeHGlobal((System::IntPtr)(void*)ctp_ip);
	Marshal::FreeHGlobal((System::IntPtr)(void*)ctp_port_m);
	Marshal::FreeHGlobal((System::IntPtr)(void*)ctp_port_t);
	Marshal::FreeHGlobal((System::IntPtr)(void*)ctp_userID);
	Marshal::FreeHGlobal((System::IntPtr)(void*)ctp_passwd);
	Marshal::FreeHGlobal((System::IntPtr)(void*)ctp_broker);

	if (m_api)
	{
		m_api->RegisterSpi(NULL);
		m_api->Release();
		m_api = NULL;
	}
}

void FutureMarketSpi::Init()
{
	char frontUrl[100];
	sprintf_s(frontUrl, "tcp://%s:%s", ctp_ip, ctp_port_m);

	m_api->RegisterSpi(this);
	//m_api->SubscribePublicTopic(ZQTHOST_TERT_QUICK);
	//m_api->SubscribePrivateTopic(ZQTHOST_TERT_QUICK);
	m_api->RegisterFront(frontUrl);
	m_api->Init();
}

void FutureMarketSpi::OnFrontConnected()
{
	printf("I am in OnFrontConnected!\n");

	CThostFtdcReqUserLoginField reqUserLogin;
	memset(&reqUserLogin,0,sizeof(reqUserLogin));

	strcpy_s(reqUserLogin.BrokerID, ctp_broker);
	strcpy_s(reqUserLogin.UserID, ctp_userID);
	strcpy_s(reqUserLogin.Password, ctp_passwd);
	// 发出登陆请求  不登录也可查询行情
	m_api->ReqUserLogin(&reqUserLogin,1);
}

void FutureMarketSpi::OnFrontDisconnected(int nReason)
{
	printf("I am in OnFrontDisconnected!\n");
}

void FutureMarketSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{
	printf("I am in OnRspUserLogin!\n");
	
	m_api->SubscribeAllFutureMarketData(sql_ip, sql_port, sql_userID, sql_passwd);
}

void FutureMarketSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	printf("I am in OnRspError!\n");

	printf("%s\n", pRspInfo->ErrorMsg);
}

void FutureMarketSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) 
{
	printf("行情---证券代码：%s:[数量:%d] [交易所:%s] [最新价:%f] [时间:%s]\n",pDepthMarketData->InstrumentID,pDepthMarketData->Volume,pDepthMarketData->ExchangeID,pDepthMarketData->LastPrice,pDepthMarketData->UpdateTime);

	FutureMarketData^ marketData = gcnew FutureMarketData(pDepthMarketData->InstrumentID, pDepthMarketData->ExchangeID, pDepthMarketData->Volume, pDepthMarketData->LastPrice, pDepthMarketData->OpenPrice, 
		pDepthMarketData->ClosePrice, pDepthMarketData->PreClosePrice, pDepthMarketData->HighestPrice, pDepthMarketData->LowestPrice, m_api->GetTradingDay(), pDepthMarketData->UpdateTime);
	
	worker->ReportProgress(1, marketData);
	
	// Filter the first incoming market data as it may be several days ago. The GetTradingDay() method not working, workaround is to get current system date.
	string ID = msclr::interop::marshal_as<std::string>(String::Concat(marketData->getCode(), "_", marketData->getExchange()));
	if (regMap.count(ID) == 0)
	{
		regMap[ID] = 0;
	}
	else
	{
		DBManager^ db = gcnew DBManager(sql_ip, sql_port, sql_userID, sql_passwd);

		db->logFuturePrice(marketData);
	}
}
