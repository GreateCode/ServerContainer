#pragma once
#include "../../Interfaces/IBean.h"
#include "boost\dll.hpp"
#include "boost\noncopyable.hpp"
#include "gl_tools.h"
//�����̬��Դ
class CBeanStaticResource : public boost::noncopyable
{
public:
	CBeanStaticResource();
	virtual ~CBeanStaticResource();
	IBean* GetBean();
	bool Uninstall();

	bool SetPath(const std::string& strPath);
	void SetDescription(const std::string& strDes);


	const std::string& Path() const;
	const std::string& Desription() const;
	const std::string& GetLastError() const;
	
	void Ref(int& ref);
protected:
	bool Init();
	bool Init(const std::string& strPath, const std::string& strDes);
	void AddRef();
	void SubRef();
	IBean* GetBeanByExport();
private:
	//��Դ���
	boost::dll::shared_library m_resourceHandle;
	//��Դ·��
	std::string m_strResourcePath;
	//��Դ˵��
	std::string m_strResourceDes;
	//����
	std::string m_strLastError;
	//���ں���
	CreateBean m_pfuncBean;

	//���ô��� 
	bool SetLastError(const std::string& strLastError, bool bWantReturn = false);

	boost::mutex m_mutexResource;
	int m_nRef;
};

