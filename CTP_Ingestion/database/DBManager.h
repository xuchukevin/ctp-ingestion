#pragma once

#include <stdlib.h>
#include <iostream>

#include "..\stock_wrapper\StockMarketData.h"
#include "..\future_wrapper\FutureMarketData.h"

using namespace std;

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;

namespace CTP_Ingestion
{
	public ref class DBManager
	{
	private:
		String^ ip;
		String^ port;
		String^ username;
		String^ password;

	public:
		DBManager(String^, String^, String^, String^);
		ArrayList^ getStockWatchList();
		ArrayList^ getFutureWatchList();
		void logStockPrice(StockMarketData^ marketData);
		void logFuturePrice(FutureMarketData^ marketData);
	};
}