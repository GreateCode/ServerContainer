#pragma once
#include "../../Interfaces/IBean.h"
#include "../../Interfaces/IContainer.h"
#include "SafeQueue.h"
#include "boost/timer.hpp"

typedef struct tagMsgInfo
{
	int nMsg;			//��Ϣ
	void* pInData;		//���
	void* pOutData;		//����
	void* pOwerner;		//ԭ��
	boost::timer t;		//��ʱ��
}MSG_INFO,*LPMSG_INFO;

typedef struct tagBeanInitInfo
{
	tagBeanInitInfo(const std::string& strDllPath, const std::string& strBeanName, const std::string& strBeanDesci, int nCreateMode)
	{
		this->strDllPath = strDllPath;
		this->strBeanName = strBeanName;
		this->strBeanDesci = strBeanDesci;
		this->nCreateMode = nCreateMode;
	}

	std::string strDllPath;		//dll·��
	std::string strBeanName;	//�������
	std::string strBeanDesci;	//���˵��
	int nCreateMode;			//���ط�ʽ�������Ҫ
}BEAN_INIT_INFO, *LPBEAN_INIT_INFO;

class CMainContainer : public IContainer
{
public:
	CMainContainer();
	virtual ~CMainContainer();

	bool InitContainer();

	//ͬ������Ҫ��
	virtual bool SendContainerMsg(int nMsg, void* In, void* Out, void* pOwerner);
	//�첽����Ҫ��
	virtual bool PostContainerMsg(int nMsg, void* In, void* Out, void* pOwerner);

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
};

