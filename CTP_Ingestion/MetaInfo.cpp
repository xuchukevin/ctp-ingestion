#include "stdafx.h"

#include "MetaInfo.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	MetaInfo::MetaInfo(int id, String^ code, String^ exchange)
	{
		this->id = id;
		this->code = code;
		this->exchange = exchange;
	}

	int MetaInfo::getId()
	{
		return id;
	}

	String^ MetaInfo::getCode()
	{
		return code;
	}

	String^ MetaInfo::getExchange()
	{
		return exchange;
	}
}
