#include "stdafx.h"
#include "MainContainer.h"


CMainContainer::CMainContainer()
{
	m_pDefaultMsgCore = nullptr;
}


CMainContainer::~CMainContainer()
{
}

int CMainContainer::OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner)
{
	return -1;
}

