#pragma once
__interface IBean
{
	virtual int OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner) = 0;
};