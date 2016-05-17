#pragma once
#include "../../Interfaces/IBean.h"
#include "SafeQueue.h"

typedef struct tagMsgInfo
{
	int nMsg;			//消息
	void* pInData;		//入参
	void* pOutData;		//出参
	void* pOwerner;		//原型
}MSG_INFO,*LPMSG_INFO;

class CMainContainer
{
public:
	CMainContainer();
	virtual ~CMainContainer();

	//同步任务要求
	virtual bool SendContainerMsg(int nMsg, void* In, void* Out, void* pOwerner);
	//异步任务要求
	virtual bool PostContainerMsg(int nMsg, void* In, void* Out, void* pOwerner);
protected:
	//////////////////////////////////////////////////////////////////////////
	guling_tools::R_W_MUTEX m_rwmutexRigsterMsgBean;
	std::map<int, std::vector<IBean*>>m_mapRigsterMsgBean;
	//////////////////////////////////////////////////////////////////////////

	guling_tools::queue_s<MSG_INFO>	m_safequeueMsgInfo;
};

