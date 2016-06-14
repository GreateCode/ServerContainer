#include "stdafx.h"
#include "MessageCore.h"
#include "boost/assign.hpp"

CMessageCore::CMessageCore()
{
	m_bThreadMainRun = false;
}


CMessageCore::~CMessageCore()
{
}

bool CMessageCore::DoMission(int nMsg, void* In, void* Out, void* pOwerner)
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

bool CMessageCore::RequestMission(int nMsg, void* In, void* Out, void* pOwerner)
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

void CMessageCore::ThreadMain()
{
	while (m_bThreadMainRun)
	{
		MSG_INFO msg_info;
		m_safequeueMsgInfo.wait_and_pop(msg_info);
		boost::thread(boost::bind(&CMessageCore::ThreadWork, this, msg_info));
	}
}

void CMessageCore::ThreadWork(const MSG_INFO& msg_info)
{
	boost::shared_ptr<IBean> spBean(nullptr);
	guling_tools::R_LOCK readLock(m_rwmutexRigsterMsgBean);
	auto itFindBean = m_mapRigsterMsgBean.find(msg_info.nMsg);
	if (m_mapRigsterMsgBean.end() == itFindBean)
		return;
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

bool CMessageCore::InitBean()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CMessageCore::Release()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CMessageCore::Status()
{
	throw std::logic_error("The method or operation is not implemented.");
}

IBean::BeanType CMessageCore::Type()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CMessageCore::OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner)
{
	throw std::logic_error("The method or operation is not implemented.");
}
