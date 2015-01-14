#pragma once

#include <stdlib.h>
#include <iostream>

#include "..\MetaInfo.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	public ref class StockMetaInfo : public MetaInfo
	{
	public:
		StockMetaInfo(int id, String^, String^);
	};
}