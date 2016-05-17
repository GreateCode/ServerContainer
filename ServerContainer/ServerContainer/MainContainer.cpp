#include "stdafx.h"
#include "MainContainer.h"


CMainContainer::CMainContainer()
{
}


CMainContainer::~CMainContainer()
{
}

bool CMainContainer::SendContainerMsg(int nMsg, void* In, void* Out, void* pOwerner)
{
	IBean* pBean = nullptr;
	guling_tools::R_LOCK readLock(m_rwmutexRigsterMsgBean);
	auto itFindBean = m_mapRigsterMsgBean.find(nMsg);
	if (itFindBean == m_mapRigsterMsgBean.end())
		return false;
	if (itFindBean->second.size() < 0 || itFindBean->second.size() >= 2)
		return false;
	pBean = itFindBean->second[0];
	readLock.unlock();
	return pBean->OnContainerMsg(nMsg, In, Out, pOwerner) == -1 ? false : true;
}

bool CMainContainer::PostContainerMsg(int nMsg, void* In, void* Out, void* pOwerner)
{
	MSG_INFO msg;
	msg.nMsg = nMsg;
	msg.pInData = In;
	msg.pOutData = Out;
	msg.pOwerner = pOwerner;
	m_safequeueMsgInfo.push(msg);
	return true;
}
