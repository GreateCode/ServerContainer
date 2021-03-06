#pragma once
#include "../../Interfaces/IBean.h"
#include "gl_tools.h"
#include "boost/timer.hpp"

typedef struct tagMsgInfo
{
	tagMsgInfo()
	{
		nMsg = -1;
		pInData = nullptr;
		pOutData = nullptr;
		pOwerner = nullptr;
	}

	int nMsg;			//消息
	void* pInData;		//入参
	void* pOutData;		//出参
	void* pOwerner;		//原型
	boost::timer t;		//计时器
}MSG_INFO, *LPMSG_INFO;

typedef struct tagBeanInitInfo
{
	tagBeanInitInfo(const std::string& strDllPath, const std::string& strBeanName, const std::string& strBeanDesci, int nCreateMode)
	{
		this->strDllPath = strDllPath;
		this->strBeanName = strBeanName;
		this->strBeanDesci = strBeanDesci;
		this->nCreateMode = nCreateMode;
	}

	std::string strDllPath;		//dll路径
	std::string strBeanName;	//组件名称
	std::string strBeanDesci;	//组件说明
	int nCreateMode;			//加载方式，如果需要
}BEAN_INIT_INFO, *LPBEAN_INIT_INFO;

class CMessageCore :public IBean
{
public:
	CMessageCore();
	virtual ~CMessageCore();

	//同步任务要求
	virtual bool DoMission(int nMsg, void* In, void* Out, void* pOwerner);
	//异步任务要求
	virtual bool RequestMission(int nMsg, void* In, void* Out, void* pOwerner);
protected:
	//////////////////////////////////////////////////////////////////////////
	guling_tools::R_W_MUTEX m_rwmutexRigsterMsgBean;
	std::map<int, std::vector<boost::shared_ptr<IBean>>>m_mapRigsterMsgBean;
	//////////////////////////////////////////////////////////////////////////

	guling_tools::queue_s<MSG_INFO>	m_safequeueMsgInfo;

	std::map<int, BEAN_INIT_INFO>m_mapBeanInitInfo;
private:
	bool m_bThreadMainRun;
	void ThreadMain();
	void ThreadWork(const MSG_INFO& msg_info);

	virtual bool InitBean();

	virtual bool Release();

	virtual int Status();

	virtual BeanType Type();

	virtual int OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner);

};

