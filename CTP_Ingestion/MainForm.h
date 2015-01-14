#pragma once

#include "stdafx.h"

#include "database\DBManager.h"
#include "stock_wrapper\StockMetaInfo.h"
#include "stock_wrapper\StockMarketData.h"
#include "stock_wrapper\StockMarketApi.h"
#include "stock_wrapper\StockMarketSpi.h"
#include "future_wrapper\FutureMetaInfo.h"
#include "future_wrapper\FutureMarketData.h"
#include "future_wrapper\FutureMarketApi.h"
#include "future_wrapper\FutureMarketSpi.h"

namespace CTP_Ingestion {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &MainForm::FormClosingEventCancle_Closing);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (stock_bgWorker)
			{
				stock_bgWorker->CancelAsync();

				delete stock_m_spi;

				stock_m_spi = NULL;
			}
			if (future_bgWorker)
			{
				future_bgWorker->CancelAsync();

				delete future_m_spi;

				future_m_spi = NULL;
			}
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::GroupBox^  gb_db;
	private: System::Windows::Forms::RadioButton^  tb_db_cat1;
	private: System::Windows::Forms::Label^  lb_db_serverip;
	private: System::Windows::Forms::TextBox^  tb_db_serverip;
	private: System::Windows::Forms::Label^  lb_db_port;
	private: System::Windows::Forms::TextBox^  tb_db_port;
	private: System::Windows::Forms::Label^  lb_db_username;
	private: System::Windows::Forms::TextBox^  tb_db_username;
	private: System::Windows::Forms::Label^  lb_db_password;
	private: System::Windows::Forms::TextBox^  tb_db_password;

	private: System::Windows::Forms::GroupBox^  gb_stock;

	private: System::Windows::Forms::GroupBox^  gb_stock_prop;
	private: System::Windows::Forms::RadioButton^  rb_stock_prop_cat1;
	private: System::Windows::Forms::Label^  lb_stock_prop_serverip;
	private: System::Windows::Forms::TextBox^  tb_stock_prop_serverip;
	private: System::Windows::Forms::Label^  lb_stock_prop_brokerid;
	private: System::Windows::Forms::TextBox^  tb_stock_prop_brokerid;
	private: System::Windows::Forms::Label^  lb_stock_prop_userid;
	private: System::Windows::Forms::TextBox^  tb_stock_prop_userid;
	private: System::Windows::Forms::Label^  lb_stock_prop_password;
	private: System::Windows::Forms::TextBox^  tb_stock_prop_password;
	private: System::Windows::Forms::Label^  lb_stock_prop_portm;
	private: System::Windows::Forms::TextBox^  tb_stock_prop_portm;
	private: System::Windows::Forms::Label^  lb_stock_prop_portt;
	private: System::Windows::Forms::TextBox^  tb_stock_prop_portt;

	private: System::Windows::Forms::GroupBox^  gb_stock_ctrl;
	private: System::Windows::Forms::RadioButton^  rb_stock_ctrl_cat1;
	private: System::Windows::Forms::RadioButton^  rb_stock_ctrl_cat2;
	private: System::Windows::Forms::Button^  bt_stock_ctrl_start;
	private: System::Windows::Forms::Button^  bt_stock_ctrl_stop;

	private: System::Windows::Forms::GroupBox^  gb_stock_list;
	private: System::Windows::Forms::ListView^  lv_stock_list;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader4;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader5;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader6;
	private: System::Windows::Forms::ColumnHeader^  stock_columnHeader7;

	private: System::Windows::Forms::GroupBox^  gb_future;

	private: System::Windows::Forms::GroupBox^  gb_future_prop;
	private: System::Windows::Forms::RadioButton^  rb_future_prop_cat1;
	private: System::Windows::Forms::Label^  lb_future_prop_serverip;
	private: System::Windows::Forms::TextBox^  tb_future_prop_serverip;
	private: System::Windows::Forms::Label^  lb_future_prop_brokerid;
	private: System::Windows::Forms::TextBox^  tb_future_prop_brokerid;
	private: System::Windows::Forms::Label^  lb_future_prop_userid;
	private: System::Windows::Forms::TextBox^  tb_future_prop_userid;
	private: System::Windows::Forms::Label^  lb_future_prop_password;
	private: System::Windows::Forms::TextBox^  tb_future_prop_password;
	private: System::Windows::Forms::Label^  lb_future_prop_portm;
	private: System::Windows::Forms::TextBox^  tb_future_prop_portm;
	private: System::Windows::Forms::Label^  lb_future_prop_portt;
	private: System::Windows::Forms::TextBox^  tb_future_prop_portt;

	private: System::Windows::Forms::GroupBox^  gb_future_ctrl;
	private: System::Windows::Forms::RadioButton^  rb_future_ctrl_cat1;
	private: System::Windows::Forms::RadioButton^  rb_future_ctrl_cat2;
	private: System::Windows::Forms::Button^  bt_future_ctrl_start;
	private: System::Windows::Forms::Button^  bt_future_ctrl_stop;

	private: System::Windows::Forms::GroupBox^  gb_future_list;
	private: System::Windows::Forms::ListView^  lv_future_list;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader4;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader5;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader6;
	private: System::Windows::Forms::ColumnHeader^  future_columnHeader7;

	private: System::ComponentModel::BackgroundWorker^ stock_bgWorker;
	private: System::ComponentModel::BackgroundWorker^ future_bgWorker;

	private: StockMarketApi* stock_m_api;
	private: StockMarketSpi* stock_m_spi;
	private: FutureMarketApi* future_m_api;
	private: FutureMarketSpi* future_m_spi;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->gb_db = (gcnew System::Windows::Forms::GroupBox());
			this->tb_db_cat1 = (gcnew System::Windows::Forms::RadioButton());
			this->lb_db_serverip = (gcnew System::Windows::Forms::Label());
			this->tb_db_serverip = (gcnew System::Windows::Forms::TextBox());
			this->lb_db_port = (gcnew System::Windows::Forms::Label());
			this->tb_db_port = (gcnew System::Windows::Forms::TextBox());
			this->lb_db_username = (gcnew System::Windows::Forms::Label());
			this->tb_db_username = (gcnew System::Windows::Forms::TextBox());
			this->lb_db_password = (gcnew System::Windows::Forms::Label());
			this->tb_db_password = (gcnew System::Windows::Forms::TextBox());
			this->gb_stock = (gcnew System::Windows::Forms::GroupBox());
			this->gb_stock_prop = (gcnew System::Windows::Forms::GroupBox());
			this->rb_stock_prop_cat1 = (gcnew System::Windows::Forms::RadioButton());
			this->lb_stock_prop_serverip = (gcnew System::Windows::Forms::Label());
			this->tb_stock_prop_serverip = (gcnew System::Windows::Forms::TextBox());
			this->lb_stock_prop_brokerid = (gcnew System::Windows::Forms::Label());
			this->tb_stock_prop_brokerid = (gcnew System::Windows::Forms::TextBox());
			this->lb_stock_prop_userid = (gcnew System::Windows::Forms::Label());
			this->tb_stock_prop_userid = (gcnew System::Windows::Forms::TextBox());
			this->lb_stock_prop_password = (gcnew System::Windows::Forms::Label());
			this->tb_stock_prop_password = (gcnew System::Windows::Forms::TextBox());
			this->lb_stock_prop_portm = (gcnew System::Windows::Forms::Label());
			this->tb_stock_prop_portm = (gcnew System::Windows::Forms::TextBox());
			this->lb_stock_prop_portt = (gcnew System::Windows::Forms::Label());
			this->tb_stock_prop_portt = (gcnew System::Windows::Forms::TextBox());
			this->gb_stock_ctrl = (gcnew System::Windows::Forms::GroupBox());
			this->rb_stock_ctrl_cat1 = (gcnew System::Windows::Forms::RadioButton());
			this->rb_stock_ctrl_cat2 = (gcnew System::Windows::Forms::RadioButton());
			this->bt_stock_ctrl_start = (gcnew System::Windows::Forms::Button());
			this->bt_stock_ctrl_stop = (gcnew System::Windows::Forms::Button());
			this->gb_stock_list = (gcnew System::Windows::Forms::GroupBox());
			this->lv_stock_list = (gcnew System::Windows::Forms::ListView());
			this->stock_columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stock_columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stock_columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stock_columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stock_columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stock_columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->stock_columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());

			this->gb_future = (gcnew System::Windows::Forms::GroupBox());
			this->gb_future_prop = (gcnew System::Windows::Forms::GroupBox());
			this->rb_future_prop_cat1 = (gcnew System::Windows::Forms::RadioButton());
			this->lb_future_prop_serverip = (gcnew System::Windows::Forms::Label());
			this->tb_future_prop_serverip = (gcnew System::Windows::Forms::TextBox());
			this->lb_future_prop_brokerid = (gcnew System::Windows::Forms::Label());
			this->tb_future_prop_brokerid = (gcnew System::Windows::Forms::TextBox());
			this->lb_future_prop_userid = (gcnew System::Windows::Forms::Label());
			this->tb_future_prop_userid = (gcnew System::Windows::Forms::TextBox());
			this->lb_future_prop_password = (gcnew System::Windows::Forms::Label());
			this->tb_future_prop_password = (gcnew System::Windows::Forms::TextBox());
			this->lb_future_prop_portm = (gcnew System::Windows::Forms::Label());
			this->tb_future_prop_portm = (gcnew System::Windows::Forms::TextBox());
			this->lb_future_prop_portt = (gcnew System::Windows::Forms::Label());
			this->tb_future_prop_portt = (gcnew System::Windows::Forms::TextBox());
			this->gb_future_ctrl = (gcnew System::Windows::Forms::GroupBox());
			this->rb_future_ctrl_cat1 = (gcnew System::Windows::Forms::RadioButton());
			this->rb_future_ctrl_cat2 = (gcnew System::Windows::Forms::RadioButton());
			this->bt_future_ctrl_start = (gcnew System::Windows::Forms::Button());
			this->bt_future_ctrl_stop = (gcnew System::Windows::Forms::Button());
			this->gb_future_list = (gcnew System::Windows::Forms::GroupBox());
			this->lv_future_list = (gcnew System::Windows::Forms::ListView());
			this->future_columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->future_columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->future_columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->future_columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->future_columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
			this->future_columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
			this->future_columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());

			this->gb_db->SuspendLayout();
			this->gb_stock->SuspendLayout();
			this->gb_stock_prop->SuspendLayout();
			this->gb_stock_ctrl->SuspendLayout();
			this->gb_stock_list->SuspendLayout();
			this->gb_future->SuspendLayout();
			this->gb_future_prop->SuspendLayout();
			this->gb_future_ctrl->SuspendLayout();
			this->gb_future_list->SuspendLayout();
			this->SuspendLayout();
			// 
			// gb_db
			// 
			this->gb_db->Controls->Add(this->tb_db_cat1);
			this->gb_db->Controls->Add(this->lb_db_serverip);
			this->gb_db->Controls->Add(this->tb_db_serverip);
			this->gb_db->Controls->Add(this->lb_db_port);
			this->gb_db->Controls->Add(this->tb_db_port);
			this->gb_db->Controls->Add(this->lb_db_username);
			this->gb_db->Controls->Add(this->tb_db_username);
			this->gb_db->Controls->Add(this->lb_db_password);
			this->gb_db->Controls->Add(this->tb_db_password);
			this->gb_db->Location = System::Drawing::Point(10, 12);
			this->gb_db->Name = L"gb_db";
			this->gb_db->Size = System::Drawing::Size(996, 79);
			this->gb_db->TabIndex = 0;
			this->gb_db->TabStop = false;
			this->gb_db->Text = L"Database Connection";
			// 
			// tb_db_cat1
			// 
			this->tb_db_cat1->AutoSize = true;
			this->tb_db_cat1->Checked = true;
			this->tb_db_cat1->Location = System::Drawing::Point(10, 20);
			this->tb_db_cat1->Name = L"tb_db_cat1";
			this->tb_db_cat1->Size = System::Drawing::Size(54, 17);
			this->tb_db_cat1->TabIndex = 1;
			this->tb_db_cat1->TabStop = true;
			this->tb_db_cat1->Text = L"MySql";
			this->tb_db_cat1->UseVisualStyleBackColor = true;
			// 
			// lb_db_serverip
			// 
			this->lb_db_serverip->AutoSize = true;
			this->lb_db_serverip->Location = System::Drawing::Point(10, 50);
			this->lb_db_serverip->Name = L"lb_db_serverip";
			this->lb_db_serverip->Size = System::Drawing::Size(51, 13);
			this->lb_db_serverip->TabIndex = 2;
			this->lb_db_serverip->Text = L"Server IP";
			// 
			// tb_db_serverip
			// 
			this->tb_db_serverip->Location = System::Drawing::Point(80, 47);
			this->tb_db_serverip->Name = L"tb_db_serverip";
			this->tb_db_serverip->Size = System::Drawing::Size(80, 20);
			this->tb_db_serverip->TabIndex = 3;
			this->tb_db_serverip->Text = L"127.0.0.1";
			// 
			// lb_db_port
			// 
			this->lb_db_port->AutoSize = true;
			this->lb_db_port->Location = System::Drawing::Point(180, 50);
			this->lb_db_port->Name = L"lb_db_port";
			this->lb_db_port->Size = System::Drawing::Size(60, 13);
			this->lb_db_port->TabIndex = 4;
			this->lb_db_port->Text = L"Server Port";
			// 
			// tb_db_port
			// 
			this->tb_db_port->Location = System::Drawing::Point(250, 47);
			this->tb_db_port->Name = L"tb_db_port";
			this->tb_db_port->Size = System::Drawing::Size(80, 20);
			this->tb_db_port->TabIndex = 5;
			this->tb_db_port->Text = L"3306";
			// 
			// lb_db_username
			// 
			this->lb_db_username->AutoSize = true;
			this->lb_db_username->Location = System::Drawing::Point(350, 50);
			this->lb_db_username->Name = L"lb_db_username";
			this->lb_db_username->Size = System::Drawing::Size(55, 13);
			this->lb_db_username->TabIndex = 6;
			this->lb_db_username->Text = L"Username";
			// 
			// tb_db_username
			// 
			this->tb_db_username->Location = System::Drawing::Point(420, 47);
			this->tb_db_username->Name = L"tb_db_username";
			this->tb_db_username->Size = System::Drawing::Size(80, 20);
			this->tb_db_username->TabIndex = 7;
			this->tb_db_username->Text = L"root";
			// 
			// lb_db_password
			// 
			this->lb_db_password->AutoSize = true;
			this->lb_db_password->Location = System::Drawing::Point(520, 50);
			this->lb_db_password->Name = L"lb_db_password";
			this->lb_db_password->Size = System::Drawing::Size(53, 13);
			this->lb_db_password->TabIndex = 8;
			this->lb_db_password->Text = L"Password";
			// 
			// tb_db_password
			// 
			this->tb_db_password->Location = System::Drawing::Point(590, 47);
			this->tb_db_password->Name = L"tb_db_password";
			this->tb_db_password->Size = System::Drawing::Size(80, 20);
			this->tb_db_password->TabIndex = 9;
			this->tb_db_password->Text = L"1qaz2wsx";
			// 
			// gb_stock
			// 
			this->gb_stock->Controls->Add(this->gb_stock_prop);
			this->gb_stock->Controls->Add(this->gb_stock_ctrl);
			this->gb_stock->Controls->Add(this->gb_stock_list);
			this->gb_stock->Location = System::Drawing::Point(10, 97);
			this->gb_stock->Name = L"gb_stock";
			this->gb_stock->Size = System::Drawing::Size(495, 593);
			this->gb_stock->TabIndex = 10;
			this->gb_stock->TabStop = false;
			this->gb_stock->Text = L"CTP Stock";
			// 
			// gb_stock_prop
			// 
			this->gb_stock_prop->Controls->Add(this->rb_stock_prop_cat1);
			this->gb_stock_prop->Controls->Add(this->lb_stock_prop_serverip);
			this->gb_stock_prop->Controls->Add(this->tb_stock_prop_serverip);
			this->gb_stock_prop->Controls->Add(this->lb_stock_prop_brokerid);
			this->gb_stock_prop->Controls->Add(this->tb_stock_prop_brokerid);
			this->gb_stock_prop->Controls->Add(this->lb_stock_prop_userid);
			this->gb_stock_prop->Controls->Add(this->tb_stock_prop_userid);
			this->gb_stock_prop->Controls->Add(this->lb_stock_prop_password);
			this->gb_stock_prop->Controls->Add(this->tb_stock_prop_password);
			this->gb_stock_prop->Controls->Add(this->lb_stock_prop_portm);
			this->gb_stock_prop->Controls->Add(this->tb_stock_prop_portm);
			this->gb_stock_prop->Controls->Add(this->lb_stock_prop_portt);
			this->gb_stock_prop->Controls->Add(this->tb_stock_prop_portt);
			this->gb_stock_prop->Location = System::Drawing::Point(10, 19);
			this->gb_stock_prop->Name = L"gb_stock_prop";
			this->gb_stock_prop->Size = System::Drawing::Size(330, 166);
			this->gb_stock_prop->TabIndex = 11;
			this->gb_stock_prop->TabStop = false;
			this->gb_stock_prop->Text = L"Server Connection";
			// 
			// rb_stock_prop_cat1
			// 
			this->rb_stock_prop_cat1->AutoSize = true;
			this->rb_stock_prop_cat1->Checked = true;
			this->rb_stock_prop_cat1->Location = System::Drawing::Point(10, 20);
			this->rb_stock_prop_cat1->Name = L"rb_stock_prop_cat1";
			this->rb_stock_prop_cat1->Size = System::Drawing::Size(61, 17);
			this->rb_stock_prop_cat1->TabIndex = 12;
			this->rb_stock_prop_cat1->TabStop = true;
			this->rb_stock_prop_cat1->Text = L"Staging";
			this->rb_stock_prop_cat1->UseVisualStyleBackColor = true;
			// 
			// lb_stock_prop_serverip
			// 
			this->lb_stock_prop_serverip->AutoSize = true;
			this->lb_stock_prop_serverip->Location = System::Drawing::Point(10, 50);
			this->lb_stock_prop_serverip->Name = L"lb_stock_prop_serverip";
			this->lb_stock_prop_serverip->Size = System::Drawing::Size(51, 13);
			this->lb_stock_prop_serverip->TabIndex = 13;
			this->lb_stock_prop_serverip->Text = L"Server IP";
			// 
			// tb_stock_prop_serverip
			// 
			this->tb_stock_prop_serverip->Location = System::Drawing::Point(70, 47);
			this->tb_stock_prop_serverip->Name = L"tb_stock_prop_serverip";
			this->tb_stock_prop_serverip->Size = System::Drawing::Size(94, 20);
			this->tb_stock_prop_serverip->TabIndex = 14;
			this->tb_stock_prop_serverip->Text = L"180.166.11.40";
			// 
			// lb_stock_prop_brokerid
			// 
			this->lb_stock_prop_brokerid->AutoSize = true;
			this->lb_stock_prop_brokerid->Location = System::Drawing::Point(171, 51);
			this->lb_stock_prop_brokerid->Name = L"lb_stock_prop_brokerid";
			this->lb_stock_prop_brokerid->Size = System::Drawing::Size(52, 13);
			this->lb_stock_prop_brokerid->TabIndex = 15;
			this->lb_stock_prop_brokerid->Text = L"Broker ID";
			// 
			// tb_stock_prop_brokerid
			// 
			this->tb_stock_prop_brokerid->Location = System::Drawing::Point(240, 47);
			this->tb_stock_prop_brokerid->Name = L"tb_stock_prop_brokerid";
			this->tb_stock_prop_brokerid->Size = System::Drawing::Size(80, 20);
			this->tb_stock_prop_brokerid->TabIndex = 16;
			this->tb_stock_prop_brokerid->Text = L"2011";
			// 
			// lb_stock_prop_userid
			// 
			this->lb_stock_prop_userid->AutoSize = true;
			this->lb_stock_prop_userid->Location = System::Drawing::Point(10, 80);
			this->lb_stock_prop_userid->Name = L"lb_stock_prop_userid";
			this->lb_stock_prop_userid->Size = System::Drawing::Size(43, 13);
			this->lb_stock_prop_userid->TabIndex = 17;
			this->lb_stock_prop_userid->Text = L"User ID";
			// 
			// tb_stock_prop_userid
			// 
			this->tb_stock_prop_userid->Location = System::Drawing::Point(70, 77);
			this->tb_stock_prop_userid->Name = L"tb_stock_prop_userid";
			this->tb_stock_prop_userid->Size = System::Drawing::Size(94, 20);
			this->tb_stock_prop_userid->TabIndex = 18;
			this->tb_stock_prop_userid->Text = L"20000084";
			// 
			// lb_stock_prop_password
			// 
			this->lb_stock_prop_password->AutoSize = true;
			this->lb_stock_prop_password->Location = System::Drawing::Point(170, 80);
			this->lb_stock_prop_password->Name = L"lb_stock_prop_password";
			this->lb_stock_prop_password->Size = System::Drawing::Size(53, 13);
			this->lb_stock_prop_password->TabIndex = 19;
			this->lb_stock_prop_password->Text = L"Password";
			// 
			// tb_stock_prop_password
			// 
			this->tb_stock_prop_password->Location = System::Drawing::Point(240, 77);
			this->tb_stock_prop_password->Name = L"tb_stock_prop_password";
			this->tb_stock_prop_password->Size = System::Drawing::Size(80, 20);
			this->tb_stock_prop_password->TabIndex = 20;
			this->tb_stock_prop_password->Text = L"112233";
			// 
			// lb_stock_prop_portm
			// 
			this->lb_stock_prop_portm->AutoSize = true;
			this->lb_stock_prop_portm->Location = System::Drawing::Point(10, 114);
			this->lb_stock_prop_portm->Name = L"lb_stock_prop_portm";
			this->lb_stock_prop_portm->Size = System::Drawing::Size(68, 13);
			this->lb_stock_prop_portm->TabIndex = 21;
			this->lb_stock_prop_portm->Text = L"Port (Market)";
			// 
			// tb_stock_prop_portm
			// 
			this->tb_stock_prop_portm->Location = System::Drawing::Point(84, 107);
			this->tb_stock_prop_portm->Name = L"tb_stock_prop_portm";
			this->tb_stock_prop_portm->Size = System::Drawing::Size(80, 20);
			this->tb_stock_prop_portm->TabIndex = 22;
			this->tb_stock_prop_portm->Text = L"41213";
			// 
			// lb_stock_prop_portt
			// 
			this->lb_stock_prop_portt->AutoSize = true;
			this->lb_stock_prop_portt->Location = System::Drawing::Point(170, 110);
			this->lb_stock_prop_portt->Name = L"lb_stock_prop_portt";
			this->lb_stock_prop_portt->Size = System::Drawing::Size(63, 13);
			this->lb_stock_prop_portt->TabIndex = 23;
			this->lb_stock_prop_portt->Text = L"Port (Trade)";
			// 
			// tb_stock_prop_portt
			// 
			this->tb_stock_prop_portt->Location = System::Drawing::Point(239, 107);
			this->tb_stock_prop_portt->Name = L"tb_stock_prop_portt";
			this->tb_stock_prop_portt->Size = System::Drawing::Size(81, 20);
			this->tb_stock_prop_portt->TabIndex = 24;
			this->tb_stock_prop_portt->Text = L"41205";
			// 
			// gb_stock_ctrl
			// 
			this->gb_stock_ctrl->Controls->Add(this->rb_stock_ctrl_cat1);
			this->gb_stock_ctrl->Controls->Add(this->rb_stock_ctrl_cat2);
			this->gb_stock_ctrl->Controls->Add(this->bt_stock_ctrl_start);
			this->gb_stock_ctrl->Controls->Add(this->bt_stock_ctrl_stop);
			this->gb_stock_ctrl->Location = System::Drawing::Point(346, 19);
			this->gb_stock_ctrl->Name = L"gb_stock_ctrl";
			this->gb_stock_ctrl->Size = System::Drawing::Size(140, 166);
			this->gb_stock_ctrl->TabIndex = 25;
			this->gb_stock_ctrl->TabStop = false;
			this->gb_stock_ctrl->Text = L"Data Ingestion";
			// 
			// rb_stock_ctrl_cat1
			// 
			this->rb_stock_ctrl_cat1->AutoSize = true;
			this->rb_stock_ctrl_cat1->Checked = true;
			this->rb_stock_ctrl_cat1->Location = System::Drawing::Point(10, 20);
			this->rb_stock_ctrl_cat1->Name = L"rb_stock_ctrl_cat1";
			this->rb_stock_ctrl_cat1->Size = System::Drawing::Size(55, 17);
			this->rb_stock_ctrl_cat1->TabIndex = 26;
			this->rb_stock_ctrl_cat1->TabStop = true;
			this->rb_stock_ctrl_cat1->Text = L"Online";
			this->rb_stock_ctrl_cat1->UseVisualStyleBackColor = true;
			// 
			// rb_stock_ctrl_cat2
			// 
			this->rb_stock_ctrl_cat2->AutoSize = true;
			this->rb_stock_ctrl_cat2->Location = System::Drawing::Point(71, 20);
			this->rb_stock_ctrl_cat2->Name = L"rb_stock_ctrl_cat2";
			this->rb_stock_ctrl_cat2->Size = System::Drawing::Size(55, 17);
			this->rb_stock_ctrl_cat2->TabIndex = 27;
			this->rb_stock_ctrl_cat2->TabStop = true;
			this->rb_stock_ctrl_cat2->Text = L"Offline";
			this->rb_stock_ctrl_cat2->UseVisualStyleBackColor = true;
			// 
			// bt_stock_ctrl_start
			// 
			this->bt_stock_ctrl_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bt_stock_ctrl_start->ForeColor = System::Drawing::Color::Green;
			this->bt_stock_ctrl_start->Location = System::Drawing::Point(10, 47);
			this->bt_stock_ctrl_start->Name = L"bt_stock_ctrl_start";
			this->bt_stock_ctrl_start->Size = System::Drawing::Size(120, 50);
			this->bt_stock_ctrl_start->TabIndex = 28;
			this->bt_stock_ctrl_start->Text = L"Start";
			this->bt_stock_ctrl_start->UseVisualStyleBackColor = true;
			this->bt_stock_ctrl_start->Click += gcnew System::EventHandler(this, &MainForm::bt_stock_ctrl_start_Click);
			// 
			// bt_stock_ctrl_stop
			// 
			this->bt_stock_ctrl_stop->Enabled = false;
			this->bt_stock_ctrl_stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bt_stock_ctrl_stop->ForeColor = System::Drawing::Color::Red;
			this->bt_stock_ctrl_stop->Location = System::Drawing::Point(10, 103);
			this->bt_stock_ctrl_stop->Name = L"bt_stock_ctrl_stop";
			this->bt_stock_ctrl_stop->Size = System::Drawing::Size(120, 50);
			this->bt_stock_ctrl_stop->TabIndex = 29;
			this->bt_stock_ctrl_stop->Text = L"Stop";
			this->bt_stock_ctrl_stop->UseVisualStyleBackColor = true;
			this->bt_stock_ctrl_stop->Click += gcnew System::EventHandler(this, &MainForm::bt_stock_ctrl_stop_Click);
			// 
			// gb_stock_list
			// 
			this->gb_stock_list->Controls->Add(this->lv_stock_list);
			this->gb_stock_list->Location = System::Drawing::Point(10, 191);
			this->gb_stock_list->Name = L"gb_stock_list";
			this->gb_stock_list->Size = System::Drawing::Size(476, 396);
			this->gb_stock_list->TabIndex = 30;
			this->gb_stock_list->TabStop = false;
			this->gb_stock_list->Text = L"List of Stocks";
			// 
			// lv_stock_list
			// 
			this->lv_stock_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(7) {this->stock_columnHeader1, 
				this->stock_columnHeader2, this->stock_columnHeader3, this->stock_columnHeader4, this->stock_columnHeader5, this->stock_columnHeader6, 
				this->stock_columnHeader7});
			this->lv_stock_list->GridLines = true;
			this->lv_stock_list->Location = System::Drawing::Point(0, 21);
			this->lv_stock_list->Name = L"lv_stock_list";
			this->lv_stock_list->Size = System::Drawing::Size(476, 375);
			this->lv_stock_list->TabIndex = 31;
			this->lv_stock_list->UseCompatibleStateImageBehavior = false;
			this->lv_stock_list->View = System::Windows::Forms::View::Details;
			// 
			// stock_columnHeader1
			// 
			this->stock_columnHeader1->Text = L"NO.";
			this->stock_columnHeader1->Width = 40;
			// 
			// stock_columnHeader2
			// 
			this->stock_columnHeader2->Text = L"Code";
			// 
			// stock_columnHeader3
			// 
			this->stock_columnHeader3->Text = L"Exc.";
			this->stock_columnHeader3->Width = 40;
			// 
			// stock_columnHeader4
			// 
			this->stock_columnHeader4->Text = L"Last Udt Time";
			this->stock_columnHeader4->Width = 85;
			// 
			// stock_columnHeader5
			// 
			this->stock_columnHeader5->Text = L"Last Udt Vol.";
			this->stock_columnHeader5->Width = 80;
			// 
			// stock_columnHeader6
			// 
			this->stock_columnHeader6->Text = L"Last Udt Price";
			this->stock_columnHeader6->Width = 85;
			// 
			// stock_columnHeader7
			// 
			this->stock_columnHeader7->Text = L"Last Rsp Time";
			this->stock_columnHeader7->Width = 115;
			// 
			// gb_future
			// 
			this->gb_future->Controls->Add(this->gb_future_prop);
			this->gb_future->Controls->Add(this->gb_future_ctrl);
			this->gb_future->Controls->Add(this->gb_future_list);
			this->gb_future->Location = System::Drawing::Point(511, 97);
			this->gb_future->Name = L"gb_future";
			this->gb_future->Size = System::Drawing::Size(495, 593);
			this->gb_future->TabIndex = 32;
			this->gb_future->TabStop = false;
			this->gb_future->Text = L"CTP Future";
			// 
			// gb_future_prop
			// 
			this->gb_future_prop->Controls->Add(this->rb_future_prop_cat1);
			this->gb_future_prop->Controls->Add(this->lb_future_prop_serverip);
			this->gb_future_prop->Controls->Add(this->tb_future_prop_serverip);
			this->gb_future_prop->Controls->Add(this->lb_future_prop_brokerid);
			this->gb_future_prop->Controls->Add(this->tb_future_prop_brokerid);
			this->gb_future_prop->Controls->Add(this->lb_future_prop_userid);
			this->gb_future_prop->Controls->Add(this->tb_future_prop_userid);
			this->gb_future_prop->Controls->Add(this->lb_future_prop_password);
			this->gb_future_prop->Controls->Add(this->tb_future_prop_password);
			this->gb_future_prop->Controls->Add(this->lb_future_prop_portm);
			this->gb_future_prop->Controls->Add(this->tb_future_prop_portm);
			this->gb_future_prop->Controls->Add(this->lb_future_prop_portt);
			this->gb_future_prop->Controls->Add(this->tb_future_prop_portt);
			this->gb_future_prop->Location = System::Drawing::Point(10, 19);
			this->gb_future_prop->Name = L"gb_future_prop";
			this->gb_future_prop->Size = System::Drawing::Size(330, 166);
			this->gb_future_prop->TabIndex = 33;
			this->gb_future_prop->TabStop = false;
			this->gb_future_prop->Text = L"Server Connection";
			// 
			// rb_future_prop_cat1
			// 
			this->rb_future_prop_cat1->AutoSize = true;
			this->rb_future_prop_cat1->Checked = true;
			this->rb_future_prop_cat1->Location = System::Drawing::Point(10, 20);
			this->rb_future_prop_cat1->Name = L"rb_future_prop_cat1";
			this->rb_future_prop_cat1->Size = System::Drawing::Size(61, 17);
			this->rb_future_prop_cat1->TabIndex = 34;
			this->rb_future_prop_cat1->TabStop = true;
			this->rb_future_prop_cat1->Text = L"Staging";
			this->rb_future_prop_cat1->UseVisualStyleBackColor = true;
			// 
			// lb_future_prop_serverip
			// 
			this->lb_future_prop_serverip->AutoSize = true;
			this->lb_future_prop_serverip->Location = System::Drawing::Point(10, 50);
			this->lb_future_prop_serverip->Name = L"lb_future_prop_serverip";
			this->lb_future_prop_serverip->Size = System::Drawing::Size(51, 13);
			this->lb_future_prop_serverip->TabIndex = 35;
			this->lb_future_prop_serverip->Text = L"Server IP";
			// 
			// tb_future_prop_serverip
			// 
			this->tb_future_prop_serverip->Location = System::Drawing::Point(67, 47);
			this->tb_future_prop_serverip->Name = L"tb_future_prop_serverip";
			this->tb_future_prop_serverip->Size = System::Drawing::Size(97, 20);
			this->tb_future_prop_serverip->TabIndex = 36;
			this->tb_future_prop_serverip->Text = L"116.236.213.178";
			// 
			// lb_future_prop_brokerid
			// 
			this->lb_future_prop_brokerid->AutoSize = true;
			this->lb_future_prop_brokerid->Location = System::Drawing::Point(171, 51);
			this->lb_future_prop_brokerid->Name = L"lb_future_prop_brokerid";
			this->lb_future_prop_brokerid->Size = System::Drawing::Size(52, 13);
			this->lb_future_prop_brokerid->TabIndex = 37;
			this->lb_future_prop_brokerid->Text = L"Broker ID";
			// 
			// tb_future_prop_brokerid
			// 
			this->tb_future_prop_brokerid->Location = System::Drawing::Point(240, 47);
			this->tb_future_prop_brokerid->Name = L"tb_future_prop_brokerid";
			this->tb_future_prop_brokerid->Size = System::Drawing::Size(80, 20);
			this->tb_future_prop_brokerid->TabIndex = 38;
			this->tb_future_prop_brokerid->Text = L"4200";
			// 
			// lb_future_prop_userid
			// 
			this->lb_future_prop_userid->AutoSize = true;
			this->lb_future_prop_userid->Location = System::Drawing::Point(10, 80);
			this->lb_future_prop_userid->Name = L"lb_future_prop_userid";
			this->lb_future_prop_userid->Size = System::Drawing::Size(43, 13);
			this->lb_future_prop_userid->TabIndex = 39;
			this->lb_future_prop_userid->Text = L"User ID";
			// 
			// tb_future_prop_userid
			// 
			this->tb_future_prop_userid->Location = System::Drawing::Point(67, 77);
			this->tb_future_prop_userid->Name = L"tb_future_prop_userid";
			this->tb_future_prop_userid->Size = System::Drawing::Size(97, 20);
			this->tb_future_prop_userid->TabIndex = 40;
			this->tb_future_prop_userid->Text = L"20000173";
			// 
			// lb_future_prop_password
			// 
			this->lb_future_prop_password->AutoSize = true;
			this->lb_future_prop_password->Location = System::Drawing::Point(170, 80);
			this->lb_future_prop_password->Name = L"lb_future_prop_password";
			this->lb_future_prop_password->Size = System::Drawing::Size(53, 13);
			this->lb_future_prop_password->TabIndex = 41;
			this->lb_future_prop_password->Text = L"Password";
			// 
			// tb_future_prop_password
			// 
			this->tb_future_prop_password->Location = System::Drawing::Point(240, 77);
			this->tb_future_prop_password->Name = L"tb_future_prop_password";
			this->tb_future_prop_password->Size = System::Drawing::Size(80, 20);
			this->tb_future_prop_password->TabIndex = 42;
			this->tb_future_prop_password->Text = L"112233";
			// 
			// lb_future_prop_portm
			// 
			this->lb_future_prop_portm->AutoSize = true;
			this->lb_future_prop_portm->Location = System::Drawing::Point(10, 114);
			this->lb_future_prop_portm->Name = L"lb_future_prop_portm";
			this->lb_future_prop_portm->Size = System::Drawing::Size(68, 13);
			this->lb_future_prop_portm->TabIndex = 43;
			this->lb_future_prop_portm->Text = L"Port (Market)";
			// 
			// tb_future_prop_portm
			// 
			this->tb_future_prop_portm->Location = System::Drawing::Point(84, 107);
			this->tb_future_prop_portm->Name = L"tb_future_prop_portm";
			this->tb_future_prop_portm->Size = System::Drawing::Size(80, 20);
			this->tb_future_prop_portm->TabIndex = 44;
			this->tb_future_prop_portm->Text = L"21213";
			// 
			// lb_future_prop_portt
			// 
			this->lb_future_prop_portt->AutoSize = true;
			this->lb_future_prop_portt->Location = System::Drawing::Point(170, 110);
			this->lb_future_prop_portt->Name = L"lb_future_prop_portt";
			this->lb_future_prop_portt->Size = System::Drawing::Size(63, 13);
			this->lb_future_prop_portt->TabIndex = 45;
			this->lb_future_prop_portt->Text = L"Port (Trade)";
			// 
			// tb_future_prop_portt
			// 
			this->tb_future_prop_portt->Location = System::Drawing::Point(239, 107);
			this->tb_future_prop_portt->Name = L"tb_future_prop_portt";
			this->tb_future_prop_portt->Size = System::Drawing::Size(81, 20);
			this->tb_future_prop_portt->TabIndex = 46;
			this->tb_future_prop_portt->Text = L"41205";
			// 
			// gb_future_ctrl
			// 
			this->gb_future_ctrl->Controls->Add(this->rb_future_ctrl_cat1);
			this->gb_future_ctrl->Controls->Add(this->rb_future_ctrl_cat2);
			this->gb_future_ctrl->Controls->Add(this->bt_future_ctrl_start);
			this->gb_future_ctrl->Controls->Add(this->bt_future_ctrl_stop);
			this->gb_future_ctrl->Location = System::Drawing::Point(346, 19);
			this->gb_future_ctrl->Name = L"gb_future_ctrl";
			this->gb_future_ctrl->Size = System::Drawing::Size(140, 166);
			this->gb_future_ctrl->TabIndex = 47;
			this->gb_future_ctrl->TabStop = false;
			this->gb_future_ctrl->Text = L"Data Ingestion";
			// 
			// rb_future_ctrl_cat1
			// 
			this->rb_future_ctrl_cat1->AutoSize = true;
			this->rb_future_ctrl_cat1->Checked = true;
			this->rb_future_ctrl_cat1->Location = System::Drawing::Point(10, 20);
			this->rb_future_ctrl_cat1->Name = L"rb_future_ctrl_cat1";
			this->rb_future_ctrl_cat1->Size = System::Drawing::Size(55, 17);
			this->rb_future_ctrl_cat1->TabIndex = 48;
			this->rb_future_ctrl_cat1->TabStop = true;
			this->rb_future_ctrl_cat1->Text = L"Online";
			this->rb_future_ctrl_cat1->UseVisualStyleBackColor = true;
			// 
			// rb_future_ctrl_cat2
			// 
			this->rb_future_ctrl_cat2->AutoSize = true;
			this->rb_future_ctrl_cat2->Location = System::Drawing::Point(71, 20);
			this->rb_future_ctrl_cat2->Name = L"rb_future_ctrl_cat2";
			this->rb_future_ctrl_cat2->Size = System::Drawing::Size(55, 17);
			this->rb_future_ctrl_cat2->TabIndex = 49;
			this->rb_future_ctrl_cat2->TabStop = true;
			this->rb_future_ctrl_cat2->Text = L"Offline";
			this->rb_future_ctrl_cat2->UseVisualStyleBackColor = true;
			// 
			// bt_future_ctrl_start
			// 
			this->bt_future_ctrl_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bt_future_ctrl_start->ForeColor = System::Drawing::Color::Green;
			this->bt_future_ctrl_start->Location = System::Drawing::Point(10, 47);
			this->bt_future_ctrl_start->Name = L"bt_future_ctrl_start";
			this->bt_future_ctrl_start->Size = System::Drawing::Size(120, 50);
			this->bt_future_ctrl_start->TabIndex = 50;
			this->bt_future_ctrl_start->Text = L"Start";
			this->bt_future_ctrl_start->UseVisualStyleBackColor = true;
			this->bt_future_ctrl_start->Click += gcnew System::EventHandler(this, &MainForm::bt_future_ctrl_start_Click);
			// 
			// bt_future_ctrl_stop
			// 
			this->bt_future_ctrl_stop->Enabled = false;
			this->bt_future_ctrl_stop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->bt_future_ctrl_stop->ForeColor = System::Drawing::Color::Red;
			this->bt_future_ctrl_stop->Location = System::Drawing::Point(10, 103);
			this->bt_future_ctrl_stop->Name = L"bt_future_ctrl_stop";
			this->bt_future_ctrl_stop->Size = System::Drawing::Size(120, 50);
			this->bt_future_ctrl_stop->TabIndex = 51;
			this->bt_future_ctrl_stop->Text = L"Stop";
			this->bt_future_ctrl_stop->UseVisualStyleBackColor = true;
			this->bt_future_ctrl_stop->Click += gcnew System::EventHandler(this, &MainForm::bt_future_ctrl_stop_Click);
			// 
			// gb_future_list
			// 
			this->gb_future_list->Controls->Add(this->lv_future_list);
			this->gb_future_list->Location = System::Drawing::Point(10, 191);
			this->gb_future_list->Name = L"gb_future_list";
			this->gb_future_list->Size = System::Drawing::Size(476, 396);
			this->gb_future_list->TabIndex = 52;
			this->gb_future_list->TabStop = false;
			this->gb_future_list->Text = L"List of Futures";
			// 
			// lv_future_list
			// 
			this->lv_future_list->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(7) {this->future_columnHeader1, 
				this->future_columnHeader2, this->future_columnHeader3, this->future_columnHeader4, this->future_columnHeader5, this->future_columnHeader6, 
				this->future_columnHeader7});
			this->lv_future_list->GridLines = true;
			this->lv_future_list->Location = System::Drawing::Point(0, 21);
			this->lv_future_list->Name = L"lv_future_list";
			this->lv_future_list->Size = System::Drawing::Size(475, 375);
			this->lv_future_list->TabIndex = 53;
			this->lv_future_list->UseCompatibleStateImageBehavior = false;
			this->lv_future_list->View = System::Windows::Forms::View::Details;
			// 
			// future_columnHeader1
			// 
			this->future_columnHeader1->Text = L"NO.";
			this->future_columnHeader1->Width = 40;
			// 
			// future_columnHeader2
			// 
			this->future_columnHeader2->Text = L"Code";
			// 
			// future_columnHeader3
			// 
			this->future_columnHeader3->Text = L"Exc.";
			this->future_columnHeader3->Width = 40;
			// 
			// future_columnHeader4
			// 
			this->future_columnHeader4->Text = L"Last Udt Time";
			this->future_columnHeader4->Width = 85;
			// 
			// future_columnHeader5
			// 
			this->future_columnHeader5->Text = L"Last Udt Vol.";
			this->future_columnHeader5->Width = 80;
			// 
			// future_columnHeader6
			// 
			this->future_columnHeader6->Text = L"Last Udt Price";
			this->future_columnHeader6->Width = 85;
			// 
			// future_columnHeader7
			// 
			this->future_columnHeader7->Text = L"Last Rsp Time";
			this->future_columnHeader7->Width = 115;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1015, 697);
			this->Controls->Add(this->gb_db);
			this->Controls->Add(this->gb_stock);
			this->Controls->Add(this->gb_future);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"CTP Data Ingestion Module v1.1";
			this->gb_db->ResumeLayout(false);
			this->gb_db->PerformLayout();
			this->gb_stock->ResumeLayout(false);
			this->gb_stock_prop->ResumeLayout(false);
			this->gb_stock_prop->PerformLayout();
			this->gb_stock_ctrl->ResumeLayout(false);
			this->gb_stock_ctrl->PerformLayout();
			this->gb_stock_list->ResumeLayout(false);
			this->gb_future->ResumeLayout(false);
			this->gb_future_prop->ResumeLayout(false);
			this->gb_future_prop->PerformLayout();
			this->gb_future_ctrl->ResumeLayout(false);
			this->gb_future_ctrl->PerformLayout();
			this->gb_future_list->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
		System::Void FormClosingEventCancle_Closing(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show(this, L"Do you really want to quit application?", 
				L"Quit Application", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation);

			if (result == System::Windows::Forms::DialogResult::No)
			{
				e->Cancel = true;
			}
		}

	private: 
		System::Void bt_stock_ctrl_start_Click(System::Object^ sender, System::EventArgs^ e)
		{
			tb_db_serverip->Enabled = false;
			tb_db_port->Enabled = false;
			tb_db_username->Enabled = false;
			tb_db_password->Enabled = false;

			tb_stock_prop_serverip->Enabled = false;
			tb_stock_prop_brokerid->Enabled = false;
			tb_stock_prop_portm->Enabled = false;
			tb_stock_prop_portt->Enabled = false;
			tb_stock_prop_userid->Enabled = false;
			tb_stock_prop_password->Enabled = false;

			bt_stock_ctrl_start->Enabled = false;
			bt_stock_ctrl_stop->Enabled = true;

			if (stock_bgWorker)
			{
				stock_bgWorker->CancelAsync();

				delete stock_m_spi;

				stock_m_spi = NULL;
			}

			stock_bgWorker = gcnew System::ComponentModel::BackgroundWorker;
			stock_bgWorker->WorkerReportsProgress = true;
			stock_bgWorker->WorkerSupportsCancellation = true;
			stock_bgWorker->DoWork += gcnew DoWorkEventHandler(this, &MainForm::stock_bgWorker_DoWork);
			stock_bgWorker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(this, &MainForm::stock_bgWorker_RunWorkerCompleted);
			stock_bgWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &MainForm::stock_bgWorker_ProgressChanged);
			
			stock_m_api = (StockMarketApi*) StockMarketApi::CreateFtdcMdApi();
			stock_m_spi = new StockMarketSpi(tb_stock_prop_serverip->Text, tb_stock_prop_brokerid->Text, tb_stock_prop_userid->Text, tb_stock_prop_password->Text, 
				tb_stock_prop_portm->Text, tb_stock_prop_portt->Text, tb_db_serverip->Text, tb_db_port->Text, tb_db_username->Text, tb_db_password->Text, stock_m_api, stock_bgWorker);

			stock_bgWorker->RunWorkerAsync();
		}

	private: 
		System::Void bt_future_ctrl_start_Click(System::Object^ sender, System::EventArgs^ e)
		{
			tb_db_serverip->Enabled = false;
			tb_db_port->Enabled = false;
			tb_db_username->Enabled = false;
			tb_db_password->Enabled = false;

			tb_future_prop_serverip->Enabled = false;
			tb_future_prop_brokerid->Enabled = false;
			tb_future_prop_portm->Enabled = false;
			tb_future_prop_portt->Enabled = false;
			tb_future_prop_userid->Enabled = false;
			tb_future_prop_password->Enabled = false;

			bt_future_ctrl_start->Enabled = false;
			bt_future_ctrl_stop->Enabled = true;

			if (future_bgWorker)
			{
				future_bgWorker->CancelAsync();

				delete future_m_spi;

				future_m_spi = NULL;
			}

			future_bgWorker = gcnew System::ComponentModel::BackgroundWorker;
			future_bgWorker->WorkerReportsProgress = true;
			future_bgWorker->WorkerSupportsCancellation = true;
			future_bgWorker->DoWork += gcnew DoWorkEventHandler(this, &MainForm::future_bgWorker_DoWork);
			future_bgWorker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(this, &MainForm::future_bgWorker_RunWorkerCompleted);
			future_bgWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &MainForm::future_bgWorker_ProgressChanged);
			
			future_m_api = (FutureMarketApi*) FutureMarketApi::CreateFtdcMdApi();
			future_m_spi = new FutureMarketSpi(tb_future_prop_serverip->Text, tb_future_prop_brokerid->Text, tb_future_prop_userid->Text, tb_future_prop_password->Text, 
				tb_future_prop_portm->Text, tb_future_prop_portt->Text, tb_db_serverip->Text, tb_db_port->Text, tb_db_username->Text, tb_db_password->Text, future_m_api, future_bgWorker);

			future_bgWorker->RunWorkerAsync();
		}

	private:
		System::Void bt_stock_ctrl_stop_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show(this, L"Do you really want to stop data ingestion?", 
				L"Stop Ingestion", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation);

			if (result == System::Windows::Forms::DialogResult::No)
			{
				return;
			}
			
			tb_stock_prop_serverip->Enabled = true;
			tb_stock_prop_brokerid->Enabled = true;
			tb_stock_prop_portm->Enabled = true;
			tb_stock_prop_portt->Enabled = true;
			tb_stock_prop_userid->Enabled = true;
			tb_stock_prop_password->Enabled = true;

			tb_db_serverip->Enabled = true;
			tb_db_port->Enabled = true;
			tb_db_username->Enabled = true;
			tb_db_password->Enabled = true;

			bt_stock_ctrl_start->Enabled = true;
			bt_stock_ctrl_stop->Enabled = false;

			if (stock_bgWorker)
			{
				stock_bgWorker->CancelAsync();

				delete stock_m_spi;

				stock_m_spi = NULL;
			}
		}

	private: 
		System::Void bt_future_ctrl_stop_Click(System::Object^ sender, System::EventArgs^ e)
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show(this, L"Do you really want to stop data ingestion?", 
				L"Stop Ingestion", MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation);

			if (result == System::Windows::Forms::DialogResult::No)
			{
				return;
			}
			
			tb_future_prop_serverip->Enabled = true;
			tb_future_prop_brokerid->Enabled = true;
			tb_future_prop_portm->Enabled = true;
			tb_future_prop_portt->Enabled = true;
			tb_future_prop_userid->Enabled = true;
			tb_future_prop_password->Enabled = true;

			tb_db_serverip->Enabled = true;
			tb_db_port->Enabled = true;
			tb_db_username->Enabled = true;
			tb_db_password->Enabled = true;

			bt_future_ctrl_start->Enabled = true;
			bt_future_ctrl_stop->Enabled = false;

			if (future_bgWorker)
			{
				future_bgWorker->CancelAsync();

				delete future_m_spi;

				future_m_spi = NULL;
			}
		}

		System::Void stock_bgWorker_DoWork(Object^ sender, DoWorkEventArgs^ e)
		{
			DBManager^ db = gcnew DBManager(tb_db_serverip->Text, tb_db_port->Text, tb_db_username->Text, tb_db_password->Text);

			ArrayList^ list = db->getStockWatchList();

			stock_bgWorker->ReportProgress(0, list);

			stock_m_spi->Init();

			HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);
			WaitForSingleObject(g_hEvent, INFINITE);
		}

		System::Void future_bgWorker_DoWork(Object^ sender, DoWorkEventArgs^ e)
		{
			DBManager^ db = gcnew DBManager(tb_db_serverip->Text, tb_db_port->Text, tb_db_username->Text, tb_db_password->Text);

			ArrayList^ list = db->getFutureWatchList();

			future_bgWorker->ReportProgress(0, list);

			future_m_spi->Init();

			HANDLE g_hEvent = CreateEvent(NULL, true, false, NULL);
			WaitForSingleObject(g_hEvent, INFINITE);
		}

		System::Void stock_bgWorker_ProgressChanged(Object^ /*sender*/, ProgressChangedEventArgs^ e)
		{
			if (e->ProgressPercentage == 0)
			{
				ArrayList^ list = (ArrayList^) e->UserState;

				lv_stock_list->Items->Clear();

				for (int i = 0; i < list->Count; i++)
				{
					StockMetaInfo^ stockMetaInfo = (StockMetaInfo^) list[i];

					ListViewItem^ item = lv_stock_list->Items->Add((i+1).ToString());
					item->SubItems->Add(stockMetaInfo->getCode());
					item->SubItems->Add(stockMetaInfo->getExchange());
					item->SubItems->Add(L"");
					item->SubItems->Add(L"");
					item->SubItems->Add(L"");
					item->SubItems->Add(L"");
				}
			}
			else if (e->ProgressPercentage == 1)
			{
				StockMarketData^ marketData = (StockMarketData^) e->UserState;

				for (int i = 0; i < lv_stock_list->Items->Count; i++)
				{
					ListViewItem^ item = lv_stock_list->Items[i];

					if (item->SubItems[1]->Text->Equals(marketData->getCode()) && item->SubItems[2]->Text->Equals(marketData->getExchange()))
					{
						item->SubItems[3]->Text = marketData->getUpdateTime();
						item->SubItems[4]->Text = Convert::ToString(marketData->getVolume());
						item->SubItems[5]->Text = Convert::ToString(marketData->getLastPrice());
						item->SubItems[6]->Text = marketData->getResponseTime();
					}
				}
			}
		}

		System::Void future_bgWorker_ProgressChanged(Object^ /*sender*/, ProgressChangedEventArgs^ e)
		{
			if (e->ProgressPercentage == 0)
			{
				ArrayList^ list = (ArrayList^) e->UserState;

				lv_future_list->Items->Clear();

				for (int i = 0; i < list->Count; i++)
				{
					FutureMetaInfo^ futureMetaInfo = (FutureMetaInfo^) list[i];

					ListViewItem^ item = lv_future_list->Items->Add((i+1).ToString());
					item->SubItems->Add(futureMetaInfo->getCode());
					item->SubItems->Add(futureMetaInfo->getExchange());
					item->SubItems->Add(L"");
					item->SubItems->Add(L"");
					item->SubItems->Add(L"");
					item->SubItems->Add(L"");
				}
			}
			else if (e->ProgressPercentage == 1)
			{
				FutureMarketData^ marketData = (FutureMarketData^) e->UserState;

				for (int i = 0; i < lv_future_list->Items->Count; i++)
				{
					ListViewItem^ item = lv_future_list->Items[i];

					if (item->SubItems[1]->Text->Equals(marketData->getCode()))
					{
						item->SubItems[3]->Text = marketData->getUpdateTime();
						item->SubItems[4]->Text = Convert::ToString(marketData->getVolume());
						item->SubItems[5]->Text = Convert::ToString(marketData->getLastPrice());
						item->SubItems[6]->Text = marketData->getResponseTime();
					}
				}
			}
		}

		System::Void stock_bgWorker_RunWorkerCompleted(Object^ /*sender*/, RunWorkerCompletedEventArgs^ e)
		{
		}

		System::Void future_bgWorker_RunWorkerCompleted(Object^ /*sender*/, RunWorkerCompletedEventArgs^ e)
		{
		}

	};
}
