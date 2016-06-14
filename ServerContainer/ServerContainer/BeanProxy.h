#pragma once
#include "boost/smart_ptr.hpp"
#include "boost/thread.hpp"
#include "BeanStaticResource.h"
class CBeanProxy : public IBean
{
public:
	CBeanProxy();
	virtual ~CBeanProxy();

	bool CreateBean();

	virtual bool InitBean();

	virtual bool Release();

	virtual int Status();

	virtual int OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner);

	bool BeanEnable();

	void BindResource(CBeanStaticResource* pResource);

	virtual IBean::BeanType Type();

	virtual bool DoMission(int nMsg, void* In, void* Out, void* pOwerner);

	virtual bool RequestMission(int nMsg, void* In, void* Out, void* pOwerner);

private:
	boost::shared_ptr<IBean> m_spBean;
	CBeanStaticResource* m_pResourceBean;
};

