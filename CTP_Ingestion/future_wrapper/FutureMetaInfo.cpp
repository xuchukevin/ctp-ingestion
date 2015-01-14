#include "stdafx.h"

#include "FutureMetaInfo.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	FutureMetaInfo::FutureMetaInfo(int id, String^ code, String^ exchange) : MetaInfo(id, code, exchange)
	{
	}
}
