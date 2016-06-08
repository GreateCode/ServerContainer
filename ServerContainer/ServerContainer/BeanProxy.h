#pragma once
#include "../../Interfaces/IBean.h"
#include "boost/smart_ptr.hpp"
class CBeanProxy
{
public:
	CBeanProxy();
	virtual ~CBeanProxy();

private:
	boost::shared_ptr<IBean> m_spBean;
};

