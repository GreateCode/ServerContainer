#include "stdafx.h"
#include "BeanStaticResource.h"


CBeanStaticResource::CBeanStaticResource()
{
	m_pfuncBean = nullptr;
	m_nRef = 0;
}


CBeanStaticResource::~CBeanStaticResource()
{
}

bool CBeanStaticResource::Init()
{
	if (m_strResourcePath.empty())
	{
		m_strLastError = "资源路径不能为空";
		return false;
	}
	assert(!m_resourceHandle.is_loaded());
	if (m_resourceHandle.is_loaded())
		return SetLastError("静态资源未清除");
	try
	{
		m_resourceHandle.load(m_strResourcePath);
	}
	catch (std::exception& e)
	{
		return SetLastError("加载静态资源失败:" + std::string(e.what()));
	}
	if (!m_resourceHandle.has(BEAN_EXPORT_FUNC_NAME))
	{
		m_resourceHandle.unload();
		assert(!m_resourceHandle.is_loaded());
		return SetLastError("找不到资源的出口函数");
	}
	m_pfuncBean = m_resourceHandle.get<IBean* _stdcall(int)>(BEAN_EXPORT_FUNC_NAME);
	assert(!m_pfuncBean);
	return true;
}

bool CBeanStaticResource::Init(const std::string& strPath, const std::string& strDes)
{
	m_strResourcePath = strPath;
	m_strResourceDes = strDes;
	return Init();
}

bool CBeanStaticResource::Uninstall()
{
	boost::mutex::scoped_lock lock(m_mutexResource);
	int nTempRef = m_nRef;
	if (1 < nTempRef)
	{
		SubRef();
		return true;
	}

	try
	{
		m_resourceHandle.unload();
	}
	catch (std::exception& e)
	{
		return SetLastError("卸载资源失败:" + std::string(e.what()));
	}

	m_pfuncBean = nullptr;
	return true;
}



bool CBeanStaticResource::SetLastError(const std::string& strLastError, bool bWantReturn)
{
	m_strLastError = strLastError;
	return bWantReturn;
}

bool CBeanStaticResource::SetPath(const std::string& strPath)
{
	if (m_resourceHandle.is_loaded())
		return SetLastError("当前资源已加载，设置路径无效");
	m_strResourcePath = strPath;
	return true;
}

void CBeanStaticResource::SetDescription(const std::string& strDes)
{
	m_strResourceDes = strDes;
}

const std::string& CBeanStaticResource::Path() const
{
	return m_strResourcePath;
}

const std::string& CBeanStaticResource::Desription() const
{
	return m_strResourceDes;
}

const std::string& CBeanStaticResource::GetLastError() const
{
	return m_strLastError;
}

IBean* CBeanStaticResource::GetBean()
{
	boost::mutex::scoped_lock lock(m_mutexResource);
	if (m_resourceHandle.is_loaded())
		return GetBeanByExport();
	bool bRet = Init();
	if (!bRet)
		return nullptr;
	return GetBeanByExport();
}

void CBeanStaticResource::AddRef()
{
	m_nRef++;
}

void CBeanStaticResource::SubRef()
{
	m_nRef--;
}

IBean* CBeanStaticResource::GetBeanByExport()
{
	if (m_pfuncBean)
	{
		AddRef();
		return (*m_pfuncBean)(0);
	}
	SetLastError("无法获取资源的导出函数");
	return nullptr;
}

void CBeanStaticResource::Ref(int& ref)
{
	boost::mutex::scoped_lock lock(m_mutexResource);
	ref = m_nRef;
}


