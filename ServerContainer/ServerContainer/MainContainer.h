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
	//默认消息核心组件
	CBeanProxy* m_pDefaultMsgCore;
	//组件库
	std::map<int, CBeanProxy*>m_mapBean;
	//组件自定义表
	std::map<std::string, CBeanProxy*>m_mapUserDefBean;
	//消息核心组件
	std::vector<int>m_vectorMsgCoreBeanId;
	//普通应用组件
	std::vector<int>m_vectorAppBean;
};

