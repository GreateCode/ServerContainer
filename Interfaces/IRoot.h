#pragma once
//���ӿ�
__interface IRoot
{
	virtual int OnContainerMsg(int nMsg, void* pIn, void* pOut, void* pOwerner) = 0;
};