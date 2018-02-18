#include "Node.h"

void CNode::UpDegreeEntrant()
{
	m_nDegreeEntrant++;
}

void CNode::DownDegreeEntrant()
{
	m_nDegreeEntrant--;
}

void CNode::UpDegreeSortant()
{
	m_nDegreeSortant++;
}

void CNode::DownDegreeSortant()
{
	m_nDegreeSortant--;
}



std::ostream & operator<<(std::ostream & os, std::shared_ptr<CNode> node)
{
	os << node->GetName();
	return os;
}
