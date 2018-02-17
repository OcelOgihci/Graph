#include "Node.h"
std::string CNode::GetName() const
{
	return m_strName;
}

int CNode::GetDegreeEntrant() const
{
	return m_nDegreeEntrant;
}

int CNode::GetDegreeSortant() const
{
	return m_nDegreeSortant;
}

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
