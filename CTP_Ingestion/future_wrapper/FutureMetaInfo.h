#pragma once

#include <stdlib.h>
#include <iostream>

#include "..\MetaInfo.h"

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	public ref class FutureMetaInfo : public MetaInfo
	{	
	public:
		FutureMetaInfo(int id, String^, String^);
	};
}