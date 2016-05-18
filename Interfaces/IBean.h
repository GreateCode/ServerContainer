#pragma once
#include "IRoot.h"
__interface IBean : public IRoot
{
	virtual bool InitBean() = 0;

	virtual int OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner) = 0;
};

extern "C" typedef IBean* (*__stdcall CreateBean)(int);