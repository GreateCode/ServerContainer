#pragma once
#include "../../Interfaces/IBean.h"
#include "boost\dll.hpp"
#include "boost\noncopyable.hpp"
#include "gl_tools.h"
//组件静态资源
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
	//资源句柄
	boost::dll::shared_library m_resourceHandle;
	//资源路径
	std::string m_strResourcePath;
	//资源说明
	std::string m_strResourceDes;
	//错误
	std::string m_strLastError;
	//出口函数
	CreateBean m_pfuncBean;

	//设置错误 
	bool SetLastError(const std::string& strLastError, bool bWantReturn = false);

	boost::mutex m_mutexResource;
	int m_nRef;
};

