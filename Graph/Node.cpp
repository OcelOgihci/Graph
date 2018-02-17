#include "Node.h"
std::string CNode::GetName()
{
	return m_strName;
}

std::ostream & operator<<(std::ostream & os, std::shared_ptr<CNode> node)
{
	os << node->GetName();
	return os;
}
