#pragma once
#include "IRoot.h"
__interface IBean : public IRoot
{
	virtual bool InitBean() = 0;

	virtual bool Release() = 0;
};

extern "C" typedef IBean* (*__stdcall CreateBean)(int);