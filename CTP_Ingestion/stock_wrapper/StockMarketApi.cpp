#include "stdafx.h"

#include <fstream>

#include "StockMarketApi.h"
#include "StockMetaInfo.h"
#include "..\database\DBManager.h"

using namespace std;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace CTP_Ingestion;

StockMarketApi::StockMarketApi()
{
}

StockMarketApi::~StockMarketApi()
{
}

void StockMarketApi::SubscribeAllStockMarketData(String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd)
{
	DBManager^ db = gcnew DBManager(sql_ip, sql_port, sql_userID, sql_passwd);

	ArrayList^ list = db->getStockWatchList();

	for (int i = 0; i < list->Count; i++)
	{
		StockMetaInfo^ stockMetaInfo = (StockMetaInfo^) list[i];

		char* code = (char*)(void*)Marshal::StringToHGlobalAnsi(stockMetaInfo->getCode());
		char* exchange = (char*)(void*)Marshal::StringToHGlobalAnsi(stockMetaInfo->getExchange());

		char* Instruments[1];
		memset(Instruments,0,sizeof(Instruments));
		Instruments[0] = code;

		int a = SubscribeMarketData(Instruments, 1,exchange);
		printf("%d\n", a);

		Marshal::FreeHGlobal((System::IntPtr)(void*)code);
		Marshal::FreeHGlobal((System::IntPtr)(void*)exchange);
	}
}

//订阅行情
//char * Instruments[10];
//memset(Instruments,0,sizeof(Instruments));
//Instruments[0] = "150019";
//Instruments[0] = "000001";
//Instruments[0] = "AG1406";

//SZE	深圳股票交易所
//SSE   上海证券交易所
//CFFEX 中国金融交易所 中金所 J
//CZCE  郑州商品交易所 郑商所 Z
//DCE   大连商品交易所 大商所 D
//SHFE  上海期货交易所 上期所 S
//m_pMdApi->SubscribeMarketData (Instruments,10,"SSE");
//m_pMdApi->SubscribeMarketData(Instruments,1,"SZE");
