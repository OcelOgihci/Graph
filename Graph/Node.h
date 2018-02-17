#pragma once
#include <string>
#include <memory>

class CNode
{
private:
	std::string m_strName;

public:
	CNode(std::string strName = "") : m_strName(strName) {}


	std::string GetName();
};
std::ostream& operator<< (std::ostream& os, std::shared_ptr<CNode> node);