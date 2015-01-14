#include "stdafx.h"

#include "StockMetaInfo.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	StockMetaInfo::StockMetaInfo(int id, String^ code, String^ exchange) : MetaInfo(id, code, exchange)
	{
	}
}
