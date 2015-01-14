#pragma once

#include "ThostFtdcUserApiStructSSE.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

class CZQThostFtdcMdSpi
{
public:
	///6.4.1 当客户端与交易托管系统建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected() {};
	
	///6.4.2 当客户端与交易托管系统通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。自动重连地址，可能是原来注册的地址，也可能是系统支持的其它可用的通信地址，它由程序自动选择。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason) {};
	
	///6.4.3 心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse) {};
	
	///6.4.4 当客户端发出登录请求之后，交易托管系统返回响应时，该方法会被调用，通知客户端登录是否成功。
	virtual void OnRspUserLogin(CZQThostFtdcRspUserLoginField *pRspUserLogin, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.5 当客户端发出退出请求之后，交易托管系统返回响应时，该方法会被调用，通知客户端退出是否成功。
	virtual void OnRspUserLogout(CZQThostFtdcUserLogoutField *pUserLogout, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.6 用户密码修改应答。当客户端发出用户密码修改指令后，交易托管系统返回响应时，该方法会被调用。
	//virtual void OnRspUserPasswordUpdate(CZQThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.7 资金账户口令更新应答。当客户端发出资金账户口令更新指令后，交易托管系统返回响应时，该方法会被调用。
	//virtual void OnRspTradingAccountPasswordUpdate(CZQThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.8 针对用户请求的出错通知。
	virtual void OnRspError(CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	/*///6.4.9 报单录入应答。当客户端发出过报单录入指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspOrderInsert(CZQThostFtdcInputOrderField *pInputOrder, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.10 报单操作应答。报单操作包括报单的撤销、报单的挂起、报单的激活、报单的修改。当客户端发出过报单操作指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspOrderAction(CZQThostFtdcOrderActionField *pOrderAction,CZQThostFtdcRspInfoField *pRspInfo,int nRequestID,bool bIsLast) {};

	///6.4.11 查询最大报单数量应答。当客户端发出查询最大报单数量指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQueryMaxOrderVolume(CZQThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.12 投资者结算结果确认应答。当客户端发出投资者结算结果确认指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspSettlementInfoConfirm(CZQThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.13 请求银行资金转期货响应。当客户端发出请求银行资金转期货指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspTransferBankToFuture(CZQThostFtdcTransferBankToFutureRspField *pTransferBankToFutureRsp, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.14 请求期货资金转银行响应。当客户端发出请求期货资金转银行指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspTransferFutureToBank(CZQThostFtdcTransferFutureToBankRspField *pTransferFutureToBankRsp, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.15 请求查询银行资金响应。当客户端发出请求查询银行资金指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspTransferQryBank(CZQThostFtdcTransferQryBankRspField *pTransferQryBankRsp, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.16 请求查询银行交易明细响应。当客户端发出请求查询银行交易明细指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspTransferQryDetail(CZQThostFtdcTransferQryDetailRspField *pTransferQryDetailRsp, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.17 报单查询请求。当客户端发出报单查询指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryOrder(CZQThostFtdcOrderField *pOrder, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.18 成交单查询应答。当客户端发出成交单查询指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryTrade(CZQThostFtdcTradeField *pTrade, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.19 会员客户查询应答。当客户端发出会员客户查询指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryInvestor(CZQThostFtdcInvestorField *pInvestor, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.20 投资者持仓查询应答。当客户端发出投资者持仓查询指令后，后交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryInvestorPosition(CZQThostFtdcInvestorPositionField *pInvestorPosition, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.21 请求查询资金账户响应。当客户端发出请求查询资金账户指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryTradingAccount(CZQThostFtdcTradingAccountField *pTradingAccount, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.22 请求查询交易编码响应。当客户端发出请求查询交易编码指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryTradingCode(CZQThostFtdcTradingCodeField *pTradingCode, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.23 请求查询交易所响应。当客户端发出请求查询交易所指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryExchange(CZQThostFtdcExchangeField *pExchange, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.24 请求查询合约响应。当客户端发出请求查询合约指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryInstrument(CZQThostFtdcInstrumentField *pInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};*/

	///6.4.25 请求查询行情响应。当客户端发出请求查询行情指令后，交易托管系统返回响应时，该方法会被调用。
	//virtual void OnRspQryDepthMarketData(CZQThostFtdcDepthMarketDataField *pDepthMarketData, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	/*///6.4.26 请求查询投资者结算结果响应。当客户端发出请求查询投资者结算结果指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQrySettlementInfo(CZQThostFtdcSettlementInfoField *pSettlementInfo, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.27 请求查询转帐银行响应。当客户端发出请求查询转帐银行指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryTransferBank(CZQThostFtdcTransferBankField *pTransferBank, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.28 请求查询投资者持仓明细响应。当客户端发出请求请求查询投资者持仓明细指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryInvestorPositionDetail(CZQThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.29 请求查询客户通知响应。当客户端发出请求查询客户通知指令后，交易托管系统返回响应时，该方法会被调用。
	virtual void OnRspQryNotice(CZQThostFtdcNoticeField *pNotice, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.30 合约查询应答。当客户端发出合约查询指令后，交易托管系统返回响应时，该方法会被调用。 --- Duplicate of 6.4.24
	//virtual void OnRspQryInstrument(CZQThostFtdcInstrumentField *pInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.31 成交回报。当发生成交时交易托管系统会通知客户端，该方法会被调用。 --- Can not found
	//virtual void OnRtnTrade(CZQThostFtdcTradeField *pTrade);

	///6.4.32 报单回报。当客户端进行报单录入、报单操作及其它原因（如部分成交）导致报单状态发生变化时，交易托管系统会主动通知客户端，该方法会被调用。 --- Can not found
	//virtual void OnRtnOrder(CZQThostFtdcOrderField *pOrder);

	///6.4.33 报单录入错误回报。由交易托管系统主动通知客户端，该方法会被调用。
	virtual void OnErrRtnOrderInsert(CZQThostFtdcInputOrderField *pInputOrder, CZQThostFtdcRspInfoField *pRspInfo) {};

	///6.4.34 报价操作错误回报。由交易托管系统主动通知客户端，该方法会被调用。
	virtual void OnErrRtnOrderAction (CZQThostFtdcOrderActionField *pOrderAction, CZQThostFtdcRspInfoField *pRspInfo) {};

	///6.4.35 查询结算确认响应。由交易托管系统主动通知客户端，该方法会被调用。
	virtual void OnRspQrySettlementInfoConfirm(CZQThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.36 请求查询签约银行响应。
	virtual void OnRspQryContractBank(CZQThostFtdcContractBankField *pContractBank, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.37 请求查询预埋单响应。
	virtual void OnRspQryParkedOrder(CZQThostFtdcParkedOrderField *pParkedOrder, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.38 请求查询预埋撤单响应。
	virtual void OnRspQryParkedOrderAction(CZQThostFtdcParkedOrderActionField *pParkedOrderAction, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.39 请求查询投资者持仓明细响应。
	virtual void OnRspQryInvestorPositionCombineDetail(CZQThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.40 预埋单录入请求响应。
	virtual void OnRspParkedOrderInsert(CZQThostFtdcParkedOrderField *pParkedOrder, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.41 预埋撤单录入请求响应。
	virtual void OnRspParkedOrderAction(CZQThostFtdcParkedOrderActionField *pParkedOrderAction, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.42 删除预埋单响应。
	virtual void OnRspRemoveParkedOrder(CZQThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///6.4.43 删除预埋撤单响应。
	virtual void OnRspRemoveParkedOrderAction(CZQThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};*/

	///订阅行情应答
	virtual void OnRspSubMarketData(CZQThostFtdcSpecificInstrumentField *pSpecificInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CZQThostFtdcSpecificInstrumentField *pSpecificInstrument, CZQThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CZQThostFtdcDepthMarketDataField *pDepthMarketData) {};
};

class MD_API_EXPORT CZQThostFtdcMdApi
{
public:
	///6.5.1 产生一个CZQThostFtdcTradeApi的一个实例，不能通过new来产生。
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	///modify for udp marketdata
	static CZQThostFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false);
	
	///6.5.2 释放一个CZQThostFtdcTradeApi实例。不能使用delete方法
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///6.5.3 使客户端开始与交易托管系统建立连接，连接成功后可以进行登陆。
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///6.5.4 客户端等待一个接口实例线程的结束。
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///6.5.5 获得当前交易日。只有当与交易托管系统连接建立后才会取到正确的值。
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///6.5.6 注册一个派生自CZQThostFtdcTraderSpi接口类的实例，该实例将完成事件处理。
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///6.5.7 设置交易托管系统的网络通讯地址，交易托管系统拥有多个通信地址，但用户只需要选择一个通信地址。
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CZQThostFtdcMdSpi *pSpi) = 0;
	
	///6.5.8 订阅私有流。该方法要在Init 方法前调用。若不调用则不会收到私有流的数据。
	///@param nResumeType： 私有流重传方式
	///        TERT_RESTART 从本交易日开始重传
	///        TERT_RESUME 从上次收到的续传
	///        TERT_QUICK 只传送登录后私有流的内容
	//virtual void SubscribePrivateTopic(ZQTHOST_TE_RESUME_TYPE nResumeType) = 0;

	///6.5.9 订阅公共流。该方法要在Init 方法前调用。若不调用则不会收到公共流的数据。
	//virtual void SubscribePublicTopic(ZQTHOST_TE_RESUME_TYPE nResumeType) = 0;

	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount, char* pExchageID) = 0;

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount, char* pExchageID) = 0;

	///6.5.10 用户发出登陆请求。
	virtual int ReqUserLogin(CZQThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	///6.5.11 用户发出登出请求。
	virtual int ReqUserLogout(CZQThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	/*///6.5.12 用户密码修改请求。
	virtual int ReqUserPasswordUpdate(CZQThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///6.5.13 资金账户口令更新请求。
	virtual int ReqTradingAccountPasswordUpdate(CZQThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID) = 0;

	///6.5.14 客户端发出报单录入请求。
	virtual int ReqOrderInsert(CZQThostFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///6.5.15 客户端发出报单操作请求，包括报单的撤销、报单的挂起、报单的激活、报单的修改。
	virtual int ReqOrderAction(CZQThostFtdcOrderActionField *pOrderAction, int nRequestID) = 0;

	///6.5.16 查询最大报单数量请求。
	virtual int ReqQueryMaxOrderVolume(CZQThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID) = 0;

	///6.5.17 投资者结算结果确认。
	virtual int ReqSettlementInfoConfirm(CZQThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) = 0;

	///6.5.18 请求银行资金转期货。
	virtual int ReqTransferBankToFuture(CZQThostFtdcTransferHeaderField *pTransferHeader, CZQThostFtdcTransferBankToFutureReqField *pTransferBankToFutureReq, int nRequestID) = 0;

	///6.5.19 请求期货资金转银行。
	virtual int ReqTransferFutureToBank(CZQThostFtdcTransferHeaderField *pTransferHeader, CZQThostFtdcTransferFutureToBankReqField *pTransferFutureToBankReq, int nRequestID) = 0;

	///6.5.20 请求查询银行资金。
	virtual int ReqTransferQryBank(CZQThostFtdcTransferHeaderField *pTransferHeader, CZQThostFtdcTransferQryBankReqField *pTransferQryBankReq, int nRequestID) = 0;

	///6.5.21 请求查询银行交易明细。
	virtual int ReqTransferQryDetail(CZQThostFtdcTransferHeaderField *pTransferHeader, CZQThostFtdcTransferQryDetailReqField *pTransferQryDetailReq, int nRequestID) = 0;

	///6.5.22 报单查询请求。
	virtual int ReqQryOrder(CZQThostFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///6.5.23 成交单查询请求。
	virtual int ReqQryTrade(CZQThostFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///6.5.24 会员客户查询请求。
	virtual int ReqQryInvestor(CZQThostFtdcQryInvestorField *pQryInvestor, int nRequestID) = 0;

	///6.5.25 会员持仓查询请求。
	virtual int ReqQryInvestorPosition(CZQThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///6.5.26 请求查询资金账户。
	virtual int ReqQryTradingAccount(CZQThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///6.5.27 请求查询交易编码。
	virtual int ReqQryTradingCode(CZQThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///6.5.28 请求查询交易所。
	virtual int ReqQryExchange(CZQThostFtdcQryExchangeField *pQryExchange, int nRequestID) = 0;

	///6.5.29 请求查询合约。
	virtual int ReqQryInstrument(CZQThostFtdcQryInstrumentField *pQryInstrument,int nRequestID) = 0;*/

	///6.5.30 请求查询行情。
	//virtual int ReqQryDepthMarketData(CZQThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) = 0;

	/*///6.5.31 请求查询投资者结算结果。
	virtual int ReqQrySettlementInfo(CZQThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID) = 0;

	///6.5.32 请求查询转帐银行。
	virtual int ReqQryTransferBank(CZQThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID) = 0;

	///6.5.33 请求查询投资者持仓明细。
	virtual int ReqQryInvestorPositionDetail(CZQThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;

	///6.5.34 请求查询客户通知。
	virtual int ReqQryNotice(CZQThostFtdcQryNoticeField *pQryNotice, int nRequestID) = 0;

	///6.5.35 查询结算信息确认。
	virtual int ReqQrySettlementInfoConfirm(CZQThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID) = 0;

	///6.5.36 请求查询签约银行。
	virtual int ReqQryContractBank(CZQThostFtdcQryContractBankField *pQryContractBank, int nRequestID) = 0;

	///6.5.37 请求查询预埋单。
	virtual int ReqQryParkedOrder(CZQThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID) = 0;

	///6.5.38 请求查询预埋撤单。
	virtual int ReqQryParkedOrderAction(CZQThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID) = 0;

	///6.5.39 请求查询投资者组合持仓明细。
	virtual int ReqQryInvestorPositionCombineDetail(CZQThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID) = 0;

	///6.5.40 预埋单录入请求。
	virtual int ReqParkedOrderInsert (CZQThostFtdcParkedOrderField *pParkedOrder, int nRequestID) = 0;

	///6.5.41 预埋撤单录入请求。
	virtual int ReqParkedOrderAction(CZQThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID) = 0;

	///6.5.42 请求删除预埋单。
	virtual int ReqRemoveParkedOrder(CZQThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID) = 0;

	///6.5.43 请求删除预埋撤单。
	virtual int ReqRemoveParkedOrderAction(CZQThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID) = 0;*/

protected:
	~CZQThostFtdcMdApi(){};
};

