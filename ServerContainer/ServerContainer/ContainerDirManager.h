#pragma once
#include "boost/noncopyable.hpp"
class CContainerDirManager : public boost::noncopyable
{
public:
	CContainerDirManager();
	virtual ~CContainerDirManager();
	//���ø�Ŀ¼
	void SetContainerRoot(const std::string& strContainerRoot);
	//��ӹ���Ŀ¼ �����ӵ�Ŀ¼��ͷ��!��ʼ����Ϊ���·��
	bool AddDir(const std::string& strDes, const std::string& strDir);
	//ɾ������Ŀ¼
	bool DelDir(const std::string& strDes);
	//���
	void ClearDir();
private:
	//����Ŀ¼��
	std::map<std::string, std::string>m_mapDir;
	//��ǰ����Ŀ¼
	std::string m_strCurrentDir;
	//�����ĸ�Ŀ¼
	std::string m_strContainerRoot;
};

