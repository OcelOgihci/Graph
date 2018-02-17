#pragma once
#include "Node.h"
#include <memory>

class CEdge
{
private:
	std::shared_ptr<CNode> m_pFirstNode, m_pSecNode;
	double m_dPoids = 0;


public:
	CEdge(std::shared_ptr<CNode> firstNode = nullptr, std::shared_ptr<CNode> secNode = nullptr, double dPoids = 0);
	std::shared_ptr<CNode> GetFirstNode() const;
	std::shared_ptr<CNode> GetSecNode() const;

	bool operator== (const CEdge&);
};


std::ostream& operator<< (std::ostream& os, std::shared_ptr<CEdge> edge);


