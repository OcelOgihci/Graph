#include "Edge.h"

CEdge::CEdge(std::shared_ptr<CNode> firstNode, std::shared_ptr<CNode> secNode, double dPoids)
	: m_pFirstNode(firstNode),
	m_pSecNode(secNode),
	m_dPoids(dPoids)
{
}

std::shared_ptr<CNode> CEdge::GetFirstNode() const
{
	return m_pFirstNode;
}

std::shared_ptr<CNode> CEdge::GetSecNode() const
{
	return m_pSecNode;
}

bool CEdge::operator==(const CEdge & e)
{
	if (this->m_dPoids == e.m_dPoids && this->m_pFirstNode == e.GetFirstNode() && this->m_pSecNode == e.m_pSecNode)
		return true;
	else
		return false;
}

std::ostream & operator<<(std::ostream & os, std::shared_ptr<CEdge> edge)
{
	os << "Un arc joint les sommets : " + edge->GetFirstNode()->GetName() + " et " + edge->GetSecNode()->GetName() << std::endl;
	return os;
}
