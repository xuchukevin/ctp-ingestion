#include "stdafx.h"

#include "DBManager.h"
#include "..\stock_wrapper\StockMetaInfo.h"
#include "..\future_wrapper\FutureMetaInfo.h"

using namespace std;

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace MySql::Data::MySqlClient;

namespace CTP_Ingestion
{
	DBManager::DBManager(String^ ip, String^ port, String^ username, String^ password)
	{
		this->ip = ip;
		this->port = port;
		this->username = username;
		this->password = password;
	}

	ArrayList^ DBManager::getStockWatchList()
	{
		ArrayList^ list = gcnew ArrayList();

		String^ connString;
		MySqlConnection^ connection;
		MySqlCommand^ command;
		MySqlDataReader^ reader;

		try
		{
			connString = String::Concat("datasource=", ip, ";port=", port, ";username=", username, ";password=", password);
			connection = gcnew MySqlConnection(connString);
			connection->Open();

			command = gcnew MySqlCommand("SELECT * FROM ctp.stock_watchlist;", connection);

			reader = command->ExecuteReader();
			while (reader->Read())
			{
				int id = reader->GetInt32(0);
				String^ code = reader["Code"]->ToString();
				String^ exchange = reader["Exchange"]->ToString();
				StockMetaInfo^ stockMetaInfo = gcnew StockMetaInfo(id, code, exchange);
				list->Add(stockMetaInfo);
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message);
		}
		finally
		{
			if (reader)
			{
				try
				{
					reader->Close();
					delete reader;
				}
				catch (...)
				{
				}
			}

			if (connection)
			{
				try
				{
					connection->Close();	
				}
				catch (...)
				{
				}
			}
		}

		return list;
	}

	ArrayList^ DBManager::getFutureWatchList()
	{
		ArrayList^ list = gcnew ArrayList();

		String^ connString;
		MySqlConnection^ connection;
		MySqlCommand^ command;
		MySqlDataReader^ reader;

		try
		{
			connString = String::Concat("datasource=", ip, ";port=", port, ";username=", username, ";password=", password);
			connection = gcnew MySqlConnection(connString);
			connection->Open();

			command = gcnew MySqlCommand("SELECT * FROM ctp.future_watchlist;", connection);

			reader = command->ExecuteReader();
			while (reader->Read())
			{
				int id = reader->GetInt32(0);
				String^ code = reader["Code"]->ToString();
				String^ exchange = reader["Exchange"]->ToString();
				FutureMetaInfo^ futureMetaInfo = gcnew FutureMetaInfo(id, code, exchange);
				list->Add(futureMetaInfo);
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message);
		}
		finally
		{
			if (reader)
			{
				try
				{
					reader->Close();
					delete reader;
				}
				catch (...)
				{
				}
			}

			if (connection)
			{
				try
				{
					connection->Close();	
				}
				catch (...)
				{
				}
			}
		}

		return list;
	}

	void DBManager::logStockPrice(StockMarketData^ marketData)
	{
		String^ connString;
		MySqlConnection^ connection;
		MySqlCommand^ command;

		try
		{
			connString = String::Concat("datasource=", ip, ";port=", port, ";username=", username, ";password=", password);
			connection = gcnew MySqlConnection(connString);
			connection->Open();

			command = gcnew MySqlCommand("INSERT INTO ctp.stock_quotes (Code, Exchange, Timestamp, Volume, LastPrice, OpenPrice, ClosePrice, PreClosePrice, HighestPrice, LowestPrice)" + 
				"VALUES (@Code, @Exchange, @Timestamp, @Volume, @LastPrice, @OpenPrice, @ClosePrice, @PreClosePrice, @HighestPrice, @LowestPrice);", connection);
			command->Parameters->AddWithValue("@Code", marketData->getCode());
			command->Parameters->AddWithValue("@Exchange", marketData->getExchange());
			command->Parameters->AddWithValue("@Timestamp", marketData->getTimestamp());
			command->Parameters->AddWithValue("@Volume", marketData->getVolume());
			command->Parameters->AddWithValue("@LastPrice", marketData->getLastPrice());
			command->Parameters->AddWithValue("@OpenPrice", marketData->getOpenPrice());
			command->Parameters->AddWithValue("@ClosePrice", marketData->getClosePrice());
			command->Parameters->AddWithValue("@PreClosePrice", marketData->getPreClosePrice());
			command->Parameters->AddWithValue("@HighestPrice", marketData->getHighestPrice());
			command->Parameters->AddWithValue("@LowestPrice", marketData->getLowestPrice());
			
			command->ExecuteNonQuery();
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message);
		}
		finally
		{
			if (connection)
			{
				try
				{
					connection->Close();	
				}
				catch (...)
				{
				}
			}
		}
	}

	void DBManager::logFuturePrice(FutureMarketData^ marketData)
	{
		String^ connString;
		MySqlConnection^ connection;
		MySqlCommand^ command;

		try
		{
			connString = String::Concat("datasource=", ip, ";port=", port, ";username=", username, ";password=", password);
			connection = gcnew MySqlConnection(connString);
			connection->Open();

			command = gcnew MySqlCommand("INSERT INTO ctp.future_quotes (Code, Exchange, Timestamp, Volume, LastPrice, OpenPrice, ClosePrice, PreClosePrice, HighestPrice, LowestPrice)" + 
				"VALUES (@Code, @Exchange, @Timestamp, @Volume, @LastPrice, @OpenPrice, @ClosePrice, @PreClosePrice, @HighestPrice, @LowestPrice);", connection);
			command->Parameters->AddWithValue("@Code", marketData->getCode());
			command->Parameters->AddWithValue("@Exchange", marketData->getExchange());
			command->Parameters->AddWithValue("@Timestamp", marketData->getTimestamp());
			command->Parameters->AddWithValue("@Volume", marketData->getVolume());
			command->Parameters->AddWithValue("@LastPrice", marketData->getLastPrice());
			command->Parameters->AddWithValue("@OpenPrice", marketData->getOpenPrice());
			command->Parameters->AddWithValue("@ClosePrice", marketData->getClosePrice());
			command->Parameters->AddWithValue("@PreClosePrice", marketData->getPreClosePrice());
			command->Parameters->AddWithValue("@HighestPrice", marketData->getHighestPrice());
			command->Parameters->AddWithValue("@LowestPrice", marketData->getLowestPrice());
			
			command->ExecuteNonQuery();
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message);
		}
		finally
		{
			if (connection)
			{
				try
				{
					connection->Close();	
				}
				catch (...)
				{
				}
			}
		}
	}
}
