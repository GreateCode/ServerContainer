#pragma once
#include "boost/noncopyable.hpp"
class CContainerDirManager : public boost::noncopyable
{
public:
	CContainerDirManager();
	virtual ~CContainerDirManager();
	//设置根目录
	void SetContainerRoot(const std::string& strContainerRoot);
	//添加工作目录 如果添加的目录开头以!开始，则为相对路径
	bool AddDir(const std::string& strDes, const std::string& strDir);
	//删除工作目录
	bool DelDir(const std::string& strDes);
	//清空
	void ClearDir();
private:
	//工作目录表
	std::map<std::string, std::string>m_mapDir;
	//当前工作目录
	std::string m_strCurrentDir;
	//容器的根目录
	std::string m_strContainerRoot;
};

