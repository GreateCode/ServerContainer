#pragma once
#include "../../Interfaces/IContainer.h"

#include "BeanProxy.h"

class CMainContainer: public IContainer
{
public:
	CMainContainer();
	virtual ~CMainContainer();

	virtual int OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner);

protected:
	//Ĭ����Ϣ�������
	CBeanProxy* m_pDefaultMsgCore;
	//�����
	std::map<int, CBeanProxy*>m_mapBean;
	//����Զ����
	std::map<std::string, CBeanProxy*>m_mapUserDefBean;
	//��Ϣ�������
	std::vector<int>m_vectorMsgCoreBeanId;
	//��ͨӦ�����
	std::vector<int>m_vectorAppBean;
};

