#pragma once
#include "IRoot.h"
__interface IBean : public IRoot
{
	enum BeanType
	{
		BEAN_MSGCORE,
		BEAN_NORMAL
	};
	//��ʼ�����
	virtual bool InitBean() = 0;
	//����ڲ���Դ�ͷ�
	virtual bool Release() = 0;
	//���״̬	����0��ʾ��׼����
	virtual int Status() = 0;
	//�������
	virtual BeanType Type() = 0;

	//ͬ������Ҫ��
	virtual bool DoMission(int nMsg, void* In, void* Out, void* pOwerner) = 0;
	//�첽����Ҫ��
	virtual bool RequestMission(int nMsg, void* In, void* Out, void* pOwerner) = 0;
};

#define BEAN_EXPORT_FUNC_NAME	"CreateBean"
extern "C" typedef IBean* (__stdcall *CreateBean)(int);