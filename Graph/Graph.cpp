#include "Graph.h"
#include <iostream>
#include "ColorMod.h"// namespace Color

std::list<std::shared_ptr<CNode>> CGraph::GetNodes() const
{
	return m_lNodes;
}

std::list<std::shared_ptr<CEdge>> CGraph::GetEdges() const
{
	return m_lEdges;
}



void CGraph::AddNode(const std::string& strName)
{
	if (!countainsNode(strName)) {

		m_lNodes.push_back(std::make_shared<CNode>(strName));
		std::cout << green << " Sommet " << strName << " créé." << white << std::endl;
	}
	else
		std::cerr << red << " #ERREUR : Le sommet existe déjà!" << white << std::endl;
}



void CGraph::AddEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2, double dPoids)
{
	if (!countainsEdge(n1, n2) ){
		if (countainsNode(n1->GetName()) && countainsNode(n2->GetName())) {
			m_lEdges.push_back(std::make_shared<CEdge>(n1, n2, dPoids));
			n1->UpDegreeSortant();
			n2->UpDegreeEntrant();
			std::cout << green << " Arc " << n1->GetName() << n2->GetName() << " ("<< dPoids << ")" << " créé." << white << std::endl;
		}else
			std::cerr << red << " #ERREUR : Un des points n'existe pas!" << white << std::endl;
	}
	else
		std::cerr << red << " #ERREUR : L'arc existe déjà!" << white << std::endl;

}



void CGraph::RemoveNode(std::shared_ptr<CNode> n)
{
	if (countainsNode(n->GetName())) {
		for (std::shared_ptr<CEdge> e : GetEdges())
		{
			auto tempE = e;
			if (tempE->GetFirstNode() == n) {
				std::cout << green << " Arc " << tempE->GetFirstNode()->GetName() << tempE->GetSecNode()->GetName() << " removed" << white << std::endl;
				tempE->GetSecNode()->DownDegreeEntrant();
				m_lEdges.remove(tempE);
			}
			else if (tempE->GetSecNode() == n) {
				std::cout << green << " Arc " << tempE->GetFirstNode()->GetName() << tempE->GetSecNode()->GetName() << " removed" << white << std::endl;
				(tempE)->GetFirstNode()->DownDegreeSortant();
				m_lEdges.remove(tempE);
			}
		}
		for (std::shared_ptr<CNode> n1 : GetNodes())
			if (n1 == n)
				m_lNodes.remove(n1);
		std::cout << green << " Node : " << n->GetName() << " removed" << white << std::endl;
	}else
		std::cerr << red << " #ERREUR : Le sommet n'existe pas!" << white << std::endl;

}


void CGraph::RemoveEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2)
{
	for (std::shared_ptr<CEdge> e : GetEdges())
	{
		if (e->GetFirstNode() == n1 && e->GetSecNode() == n2) {
			n1->DownDegreeSortant();
			n2->DownDegreeEntrant();
			std::cout << green << " Arc " << n1->GetName() << n2->GetName() << " removed" << white << std::endl;
			m_lEdges.remove(e);
			return;
		}
	}
	std::cerr << red << " #ERREUR : Cet arc n'existe pas!" << white << std::endl;
}

void CGraph::AddPoids(std::string s1, std::string s2, double d) {
	std::shared_ptr<CNode> n1 = FindNode(s1);
	std::shared_ptr<CNode> n2 = FindNode(s2);

	for (std::shared_ptr<CEdge> e : GetEdges())
	{
		if (e->GetFirstNode() == n1 && e->GetSecNode() == n2) 
			e->SetPoids(d);
	}
		
	std::cerr << red << " #ERREUR : Cet arc n'existe pas!" << white << std::endl;
	std::cerr << blue << " Voulez vous le créer? [y/n]" << white << std::endl;
	char choice;
	std::cin >> choice;
	if (choice == 'y') {
		if (n1) 
			std::cout << green << " " << n1->GetName() << " : OK" << white << std::endl;
		else {
			std::cerr << red << " #ERREUR : Le sommet " << s1 << " n'existe pas!" << white << std::endl;
			std::cerr << blue << " Voulez vous le créer? [y/n]" << white << std::endl;
			std::cin >> choice;
			if (choice == 'y') {
				AddNode(s1);
				n1 = FindNode(s1);
			}
			else
				return;
		}
		if (n2) 
			std::cout << green << " " << n2->GetName() << " : OK" << white << std::endl;
		else {
			std::cerr << red << " #ERREUR : Le sommet " << s2 << " n'existe pas!" << white << std::endl;
			std::cerr << blue << " Voulez vous le créer? [y/n]" << white << std::endl;

			std::cin >> choice;
			if (choice == 'y') {
				AddNode(s2);
				n2 = FindNode(s2);
			}
			else
				return;
		}
		AddEdge(n1, n2, d);
	}
			
}

std::shared_ptr<CNode> CGraph::FindNode(std::shared_ptr<CNode> n) const
{
	std::shared_ptr<CNode> node;
	for (const std::shared_ptr<CNode>& n1 : m_lNodes)
	{
		if (n1 == n)
			node = n;
	}

	return node;
}

std::shared_ptr<CNode> CGraph::FindNode(std::string strName) const
{

	std::shared_ptr<CNode> node;
	for(std::shared_ptr<CNode> n : m_lNodes)
	{
		if (n->GetName() == strName)
			node = n;
	}

	return node;
}

bool CGraph::countainsEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2) const
{
	for (std::shared_ptr<CEdge> e1 : m_lEdges)
	{
		
		if (e1->GetFirstNode() == n1 && e1->GetSecNode() == n2)
			return true;
	}

	return false;
}

bool CGraph::countainsNode(std::string strName) const
{
	for (std::shared_ptr<CNode> n : m_lNodes)
	{
		if (n->GetName() == strName)
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
	os << "Degres sortant :  ";

	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		os << n->GetDegreeSortant() << " ";
	}
	os << std::endl;
	os << "Degres entrant :  ";

	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		os << n->GetDegreeEntrant() << " ";
	}
	os << std::endl;
	os << "*******************************************" << std::endl;



	return os;
}

