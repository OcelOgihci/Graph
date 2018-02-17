#include "Graph.h"
#include <iostream>
std::vector<std::shared_ptr<CNode>> CGraph::GetNodes() const
{
	return m_sNodes;
}

std::vector<std::shared_ptr<CEdge>> CGraph::GetEdges() const
{
	return m_sEdges;
}



void CGraph::AddNode(std::string strName)
{
	if (!countainsNode(strName)) {
		m_sNodes.push_back(std::make_shared<CNode>(strName));
		std::cout << "Sommet " << strName << " créé." << std::endl;
	}
	else
		std::cerr << "ERROR : Le sommet existe déjà!" << std::endl;
}

void CGraph::AddEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2)
{
	if (!countainsEdge(n1, n2)) {
		m_sEdges.push_back(std::make_shared<CEdge>(n1, n2));
		std::cout << "Arc " << n1->GetName() << n2->GetName() << " créé." << std::endl;
	}
	else
		std::cerr << "ERREUR : L'arc existe déjà!" << std::endl;

}



void CGraph::RemoveNode(std::shared_ptr<CNode> n)
{
	if (countainsNode(n->GetName())) {
		for (auto e = m_sEdges.begin(); e != m_sEdges.end();)
		{
			if (e->get()->GetFirstNode() == n || e->get()->GetSecNode() == n) {
				auto tempE = e;
				e++;
				std::cout << "Arc " << tempE->get()->GetFirstNode()->GetName() << tempE->get()->GetSecNode()->GetName() << " removed" << std::endl;
				m_sEdges.erase(tempE);
			}
			else
				e++;
		}
		for (auto n1 = m_sNodes.begin(); n1 != m_sNodes.end();)
			if (*n1 == n)
				n1 = m_sNodes.erase(n1);
		std::cout << "Node : " << n->GetName() << " removed" << std::endl;
	}else
		std::cerr << "ERREUR : Le sommet n'existe pas!" << std::endl;

}


void CGraph::RemoveEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2)
{
	for (auto e = m_sEdges.begin(); e != m_sEdges.end(); ++e)
	{
		if (e->get()->GetFirstNode() == n1 && e->get()->GetSecNode() == n2) {
			std::cout << "Arete " << n1->GetName() << n2->GetName() << " removed" << std::endl;
			m_sEdges.erase(e);
			return;
		}
	}
	std::cout << "L'arete n'existe pas!";
}



std::shared_ptr<CNode> CGraph::FindNode(std::shared_ptr<CNode> n) const
{
	std::shared_ptr<CNode> node;
	for (std::shared_ptr<CNode> n1 : m_sNodes)
	{
		if (n1 == n)
			node = n;
	}

	return node;
}

std::shared_ptr<CNode> CGraph::FindNode(std::string strName) const
{

	std::shared_ptr<CNode> node;
	for(std::shared_ptr<CNode> n : m_sNodes)
	{
		if (n->GetName() == strName)
			node = n;
	}

	return node;
}

bool CGraph::countainsEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2) const
{
	for (std::shared_ptr<CEdge> e1 : m_sEdges)
	{
		
		if (e1->GetFirstNode() == n1 && e1->GetSecNode() == n2)
			return true;
	}

	return false;
}

bool CGraph::countainsNode(std::string strName) const
{
	for (std::shared_ptr<CNode> n1 : m_sNodes)
	{

		if (n1->GetName() == strName)
			return true;
	}

	return false;
}


std::ostream & operator<<(std::ostream & os, const CGraph & graph)
{
	os << "*******************************************" << std::endl;
	os << "[Structure du Graphe]" << std::endl;
	os << "Nombre de Sommet : " << graph.GetNodes().size() << ", Nombre d'Arc : " << graph.GetEdges().size() << std::endl;

	os << "Liens : " << std::endl;
	for (std::shared_ptr<CEdge> e : graph.GetEdges()) {
		os << "    " << e;
	}
	os << std::endl;
	os << "Sommets : ";
	for (std::shared_ptr<CNode> n : graph.GetNodes()) {
		os << n << " ";
	}
	os << std::endl;

	os << "Matrice : ";
	for (int i = 0; i < graph.GetNodes().size()*2; ++i) {
		if(i % 2 == 0)
			os << "_";
		else
			os << " ";
	}
	os << std::endl;

	char bit = 0;
	for (std::shared_ptr<CNode> n : graph.GetNodes())
	{
		os << "        " << n->GetName() << "|";
		for (std::shared_ptr<CNode> no : graph.GetNodes())
		{
			if (graph.countainsEdge(n, no))
				bit = '1';
			else
				bit = '0';

			os << bit << " ";
		}
		os << std::endl;
	}
	os << "*******************************************" << std::endl;



	return os;
}

