#pragma once
#include "IRoot.h"
__interface IBean : public IRoot
{
	//��ʼ�����
	virtual bool InitBean() = 0;
	//ж�ظ����
	virtual bool Release() = 0;
	//�������״̬
	virtual int Status() = 0;
	//ж�������Դ
	virtual bool Uninstall() = 0;
};

extern "C" typedef IBean* (*__stdcall CreateBean)(int);