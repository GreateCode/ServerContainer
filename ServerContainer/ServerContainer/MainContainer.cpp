#include "stdafx.h"
#include "MainContainer.h"
#include "boost/assign.hpp"

CMainContainer::CMainContainer()
{
	m_bThreadMainRun = false;
}


CMainContainer::~CMainContainer()
{
}

bool CMainContainer::SendContainerMsg(int nMsg, void* In, void* Out, void* pOwerner)
{
	boost::shared_ptr<IBean> spBean(nullptr);
	guling_tools::R_LOCK readLock(m_rwmutexRigsterMsgBean);
	auto itFindBean = m_mapRigsterMsgBean.find(nMsg);
	if (itFindBean == m_mapRigsterMsgBean.end())
		return false;
	if (itFindBean->second.size() < 0 || itFindBean->second.size() >= 2)
		return false;
	spBean = itFindBean->second[0];
	readLock.unlock();
	return spBean->OnContainerMsg(nMsg, In, Out, pOwerner) == -1 ? false : true;
}

bool CMainContainer::PostContainerMsg(int nMsg, void* In, void* Out, void* pOwerner)
{
	guling_tools::R_LOCK readLock(m_rwmutexRigsterMsgBean);
	auto itFindBean = m_mapRigsterMsgBean.find(nMsg);
	if (m_mapRigsterMsgBean.end() == itFindBean)
		return false;
	readLock.unlock();
	MSG_INFO msg;
	msg.nMsg = nMsg;
	msg.pInData = In;
	msg.pOutData = Out;
	msg.pOwerner = pOwerner;
	m_safequeueMsgInfo.push(msg);
	return true;
}

void CMainContainer::ThreadMain()
{
	while (m_bThreadMainRun)
	{
		MSG_INFO msg_info;
		m_safequeueMsgInfo.wait_and_pop(msg_info);
		boost::thread(boost::bind(&ThreadWork, this, msg_info));
	}
}

void CMainContainer::ThreadWork(const MSG_INFO& msg_info)
{
	boost::shared_ptr<IBean> spBean(nullptr);
	guling_tools::R_LOCK readLock(m_rwmutexRigsterMsgBean);
	auto itFindBean = m_mapRigsterMsgBean.find(msg_info.nMsg);
	if (m_mapRigsterMsgBean.end() == itFindBean)
	{
		assert(false);
		return;
	}
	std::vector<boost::shared_ptr<IBean>>queueMsgBean = itFindBean->second;
	readLock.unlock();
	for (auto& itVectorBean : queueMsgBean)
	{
		boost::shared_ptr<IBean> spTemp = itVectorBean;
		if (nullptr == spTemp)
			continue;
		spTemp->OnContainerMsg(msg_info.nMsg, msg_info.pInData, msg_info.pOutData, msg_info.pOwerner);
	}
}

bool CMainContainer::InitContainer()
{
	//////////////////////////////////////////////////////////////////////////
	//�ȼ����ʼ���������
	boost::assign::insert(m_mapBeanInitInfo)
		(1, BEAN_INIT_INFO("gl_communicate.dll", "ͨ��ģ��", "ʵ��������ͨ�ŵĹ���", 0))
		(2, BEAN_INIT_INFO("gl_brokerlogic.dll", "ȯ���߼�ģ��", "ʵ��ȯ�̲㹫�õ��߼�����", 0))
		(3, BEAN_INIT_INFO("gl_broker.dll", "ȯ��ģ��", "ʵ��ȯ�̲���ȯ�̵����ӹ���", 0));
	//////////////////////////////////////////////////////////////////////////

}
