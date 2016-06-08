#pragma once
#include "IRoot.h"
__interface IBean : public IRoot
{
	//初始化组件
	virtual bool InitBean() = 0;
	//卸载该组件
	virtual bool Release() = 0;
	//组件运行状态
	virtual int Status() = 0;
	//卸载组件资源
	virtual bool Uninstall() = 0;
};

extern "C" typedef IBean* (*__stdcall CreateBean)(int);