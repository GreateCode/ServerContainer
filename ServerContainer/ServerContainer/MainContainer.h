#pragma once
#include "../../Interfaces/IBean.h"
#include "SafeQueue.h"

typedef struct tagMsgInfo
{
	int nMsg;			//��Ϣ
	void* pInData;		//���
	void* pOutData;		//����
	void* pOwerner;		//ԭ��
}MSG_INFO,*LPMSG_INFO;

class CMainContainer
{
public:
	CMainContainer();
	virtual ~CMainContainer();

	//ͬ������Ҫ��
	virtual bool SendContainerMsg(int nMsg, void* In, void* Out, void* pOwerner);
	//�첽����Ҫ��
	virtual bool PostContainerMsg(int nMsg, void* In, void* Out, void* pOwerner);
protected:
	//////////////////////////////////////////////////////////////////////////
	guling_tools::R_W_MUTEX m_rwmutexRigsterMsgBean;
	std::map<int, std::vector<IBean*>>m_mapRigsterMsgBean;
	//////////////////////////////////////////////////////////////////////////

	guling_tools::queue_s<MSG_INFO>	m_safequeueMsgInfo;
};

