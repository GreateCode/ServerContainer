#include "stdafx.h"
#include "BeanProxy.h"


CBeanProxy::CBeanProxy()
{
	m_pResourceBean = nullptr;
}


CBeanProxy::~CBeanProxy()
{
}

bool CBeanProxy::InitBean()
{
	return m_spBean->InitBean();
}

bool CBeanProxy::Release()
{
	if (!m_pResourceBean)
		return false;
	bool bRet = m_spBean->Release();
	if (bRet)
		return m_pResourceBean->Uninstall();
	return bRet;
}

int CBeanProxy::Status()
{
	return m_spBean->Status();
}

int CBeanProxy::OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner)
{
	return m_spBean->OnContainerMsg(nMsg, pIn, pOut, pOwerner);
}

bool CBeanProxy::CreateBean()
{
	if (!m_pResourceBean)
		return false;
	auto pBean = m_pResourceBean->GetBean();
	if (!pBean)
		return false;
	m_spBean.swap(boost::shared_ptr<IBean>(pBean));
	return true;
}

bool CBeanProxy::BeanEnable()
{
	return m_spBean == nullptr ? true : false;
}

void CBeanProxy::BindResource(CBeanStaticResource* pResource)
{
	m_pResourceBean = pResource;
}

IBean::BeanType CBeanProxy::Type()
{
	return m_spBean->Type();
}

bool CBeanProxy::DoMission(int nMsg, void* In, void* Out, void* pOwerner)
{
	return m_spBean->DoMission(nMsg, In, Out, pOwerner);
}

bool CBeanProxy::RequestMission(int nMsg, void* In, void* Out, void* pOwerner)
{
	return m_spBean->RequestMission(nMsg, In, Out, pOwerner);
}
