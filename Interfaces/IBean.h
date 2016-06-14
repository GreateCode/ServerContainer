#pragma once
#include "IRoot.h"
__interface IBean : public IRoot
{
	enum BeanType
	{
		BEAN_MSGCORE,
		BEAN_NORMAL
	};
	//初始化组件
	virtual bool InitBean() = 0;
	//组件内部资源释放
	virtual bool Release() = 0;
	//组件状态	返回0表示已准备好
	virtual int Status() = 0;
	//组件类型
	virtual BeanType Type() = 0;

	//同步任务要求
	virtual bool DoMission(int nMsg, void* In, void* Out, void* pOwerner) = 0;
	//异步任务要求
	virtual bool RequestMission(int nMsg, void* In, void* Out, void* pOwerner) = 0;
};

#define BEAN_EXPORT_FUNC_NAME	"CreateBean"
extern "C" typedef IBean* (__stdcall *CreateBean)(int);