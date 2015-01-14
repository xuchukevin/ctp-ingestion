#include "stdafx.h"

#include <fstream>

#include "FutureMarketApi.h"
#include "FutureMetaInfo.h"
#include "..\database\DBManager.h"

using namespace std;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace CTP_Ingestion;

FutureMarketApi::FutureMarketApi()
{
}

FutureMarketApi::~FutureMarketApi()
{
}

void FutureMarketApi::SubscribeAllFutureMarketData(String^ sql_ip, String^ sql_port, String^ sql_userID, String^ sql_passwd)
{
	DBManager^ db = gcnew DBManager(sql_ip, sql_port, sql_userID, sql_passwd);

	ArrayList^ list = db->getFutureWatchList();

	for (int i = 0; i < list->Count; i++)
	{
		FutureMetaInfo^ futureMetaInfo = (FutureMetaInfo^) list[i];

		char* code = (char*)(void*)Marshal::StringToHGlobalAnsi(futureMetaInfo->getCode());
		char* exchange = (char*)(void*)Marshal::StringToHGlobalAnsi(futureMetaInfo->getExchange());

		char* Instruments[1];
		memset(Instruments,0,sizeof(Instruments));
		Instruments[0] = code;

		//int a = SubscribeMarketData(Instruments, 1,exchange);
		int a = SubscribeMarketData(Instruments, 1);
		printf("%d\n", a);

		Marshal::FreeHGlobal((System::IntPtr)(void*)code);
		Marshal::FreeHGlobal((System::IntPtr)(void*)exchange);
	}
}