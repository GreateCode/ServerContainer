#include "stdafx.h"
#include "ContainerDirManager.h"


CContainerDirManager::CContainerDirManager()
{
}


CContainerDirManager::~CContainerDirManager()
{
}

void CContainerDirManager::SetContainerRoot(const std::string& strContainerRoot)
{
	m_strContainerRoot = strContainerRoot;
}

bool CContainerDirManager::AddDir(const std::string& strDes, const std::string& strDir)
{
	std::pair<std::map<std::string, std::string>::iterator, bool> pairCheckInsert =
		m_mapDir.insert(std::pair<std::string,std::string>(strDes, strDir));
	return pairCheckInsert.second;
}

bool CContainerDirManager::DelDir(const std::string& strDes)
{
	auto itFindDir = m_mapDir.find(strDes);
	if (m_mapDir.end() == itFindDir)
		return false;
}
