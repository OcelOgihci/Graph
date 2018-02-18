#include "Graph.h"
#include <iostream>
std::list<std::shared_ptr<CNode>> CGraph::GetNodes() const
{
	return m_sNodes;
}

std::list<std::shared_ptr<CEdge>> CGraph::GetEdges() const
{
	return m_sEdges;
}



void CGraph::AddNode(const std::string& strName)
{
	if (!countainsNode(strName)) {

		m_sNodes.push_back(std::make_shared<CNode>(strName));
		std::cout << "Sommet " << strName << " créé." << std::endl;
	}
	else
		std::cerr << "ERREUR : Le sommet existe déjà!" << std::endl;
}

void CGraph::AddEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2)
{
	if (!countainsEdge(n1, n2)) {
		m_sEdges.push_back(std::make_shared<CEdge>(n1, n2));
		n1->UpDegreeSortant();
		n2->UpDegreeEntrant();
		std::cout << "Arc " << n1->GetName() << n2->GetName() << " créé." << std::endl;
	}
	else
		std::cerr << "ERREUR : L'arc existe déjà!" << std::endl;

}



void CGraph::RemoveNode(std::shared_ptr<CNode> n)
{
	if (countainsNode(n->GetName())) {
		for (std::shared_ptr<CEdge> e : GetEdges())
		{
			auto tempE = e;
			if (tempE->GetFirstNode() == n) {
				std::cout << "Arc " << tempE->GetFirstNode()->GetName() << tempE->GetSecNode()->GetName() << " removed" << std::endl;
				tempE->GetSecNode()->DownDegreeEntrant();
				m_sEdges.remove(tempE);
			}
			else if (tempE->GetSecNode() == n) {
				std::cout << "Arc " << tempE->GetFirstNode()->GetName() << tempE->GetSecNode()->GetName() << " removed" << std::endl;
				(tempE)->GetFirstNode()->DownDegreeSortant();
				m_sEdges.remove(tempE);
			}
		}
		for (std::shared_ptr<CNode> n1 : GetNodes())
			if (n1 == n)
				m_sNodes.remove(n1);
		std::cout << "Node : " << n->GetName() << " removed" << std::endl;
	}else
		std::cerr << "ERREUR : Le sommet n'existe pas!" << std::endl;

}


void CGraph::RemoveEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2)
{
	for (std::shared_ptr<CEdge> e : GetEdges())
	{
		if (e->GetFirstNode() == n1 && e->GetSecNode() == n2) {
			n1->DownDegreeSortant();
			n2->DownDegreeEntrant();
			std::cout << "Arete " << n1->GetName() << n2->GetName() << " removed" << std::endl;
			m_sEdges.remove(e);
			return;
		}
	}
	std::cerr << "ERREUR : L'arete n'existe pas!";
}

void CGraph::AddPoids(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2, double d) {
	for (std::shared_ptr<CEdge> e : GetEdges())
	{
		if (e->GetFirstNode() == n1 && e->GetSecNode() == n2) {
			e->SetPoids(d);
		}
	}
}

std::shared_ptr<CNode> CGraph::FindNode(std::shared_ptr<CNode> n) const
{
	std::shared_ptr<CNode> node;
	for (const std::shared_ptr<CNode>& n1 : m_sNodes)
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
	for (const std::shared_ptr<CEdge>& e : graph.GetEdges()) {
		os << "    " << e;
	}
	os << std::endl;
	os << "Sommets :======== ";
	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		os << n << " ";
	}
	os << std::endl;

	os << "Matrice :         ";
	for (size_t i = 0; i < graph.GetNodes().size()*2; ++i) {
		if(i % 2 == 0)
			os << "_";
		else
			os << " ";
	}
	os << std::endl;

	char bit = 0;
	for (const std::shared_ptr<CNode>& n : graph.GetNodes())
	{
		os << "                " << n->GetName() << "|";
		for (const std::shared_ptr<CNode>& no : graph.GetNodes())
		{
			if (graph.countainsEdge(n, no))
				bit = '1';
			else
				bit = '0';

			os << bit << " ";
		}
		os << std::endl;
	}

	os << "                  ";
	for (size_t i = 0; i < graph.GetNodes().size() * 2; ++i) {
		if (i % 2 == 0)
			os << "—";
		else
			os << " ";
	}
	os << std::endl;
	os << "Degrees sortant : ";

	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		os << n->GetDegreeSortant() << " ";
	}
	os << std::endl;
	os << "Degrees entrant : ";

	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		os << n->GetDegreeEntrant() << " ";
	}
	os << std::endl;
	os << "*******************************************" << std::endl;



	return os;
}

