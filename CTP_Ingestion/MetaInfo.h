#pragma once

#include <stdlib.h>
#include <iostream>

using namespace std;

using namespace System;

namespace CTP_Ingestion
{
	public ref class MetaInfo
	{
		int id;
		String^ code;
		String^ exchange;
		
	public:
		MetaInfo(int id, String^, String^);
		int getId();
		String^ getCode();
		String^ getExchange();
	};
}