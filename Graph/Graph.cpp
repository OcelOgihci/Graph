#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "ColorMod.h"// namespace Color


std::vector<std::string>& explode(const std::string& str)
{
	//std::string str("abc:def:ghi:jkl"); -> exemple
	std::istringstream split(str); // flux d'exatraction sur un std::string
	std::vector<std::string> tokens;
	for (std::string each; std::getline(split, each, ':'); tokens.push_back(each));
	return tokens;
}


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
		std::cout << green << "|Sommet " << strName << " créé." << white << std::endl;
	}
	else
		std::cerr << red << "|#ERREUR : Le sommet existe déjà!" << white << std::endl;
}



void CGraph::AddEdge(std::string s1, std::string s2, double dPoids)
{
	std::shared_ptr<CNode> n1 = FindNode(s1);
	std::shared_ptr<CNode> n2 = FindNode(s2);

	if (!countainsEdge(n1, n2) ){

		char choice;
		if (n1) {
			n1->UpDegreeSortant();
		}
		else {
			std::cerr << red << "|#ERREUR : Le sommet " << s1 << " n'existe pas!" << white << std::endl;
			do {
				std::cerr << blue << "|Voulez vous le créer? [y/n]" << white << std::endl;

				std::cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					AddNode(s1);
					n1 = FindNode(s1);
				}
				else if (choice == 'n' || choice == 'N')
					return;
			} while (choice != 'y' || choice != 'Y' || choice != 'n' || choice != 'N');
		}
		if (n2) {
			n2->UpDegreeEntrant();
		}
		else {
			std::cerr << red << "|#ERREUR : Le sommet " << s2 << " n'existe pas!" << white << std::endl;
			do {
				std::cerr << blue << "|Voulez vous le créer? [y/n]" << white << std::endl;

				std::cin >> choice;
				if (choice == 'y' || choice == 'Y') {
					AddNode(s2);
					n2 = FindNode(s2);
				}
				else if (choice == 'n' || choice == 'N')
					return;
			} while (choice != 'y' || choice != 'Y' || choice != 'n' || choice != 'N');
		}
		m_lEdges.push_back(std::make_shared<CEdge>(n1, n2, dPoids));
		std::cout << green << "|Arc " << n1 << n2 << " (" << dPoids << ")" << " créé." << white << std::endl;
		
	}
	else 
		std::cerr << red << "|#ERREUR : L'arc existe déjà!" << white << std::endl;
}



void CGraph::RemoveNode(std::shared_ptr<CNode> n)
{
	if (countainsNode(n->GetName())) {
		for (std::shared_ptr<CEdge> e : GetEdges())
		{
			auto tempE = e;
			if (tempE->GetFirstNode() == n) {
				std::cout << green << "|Arc " << tempE->GetFirstNode() << tempE->GetSecNode() << " removed" << white << std::endl;
				tempE->GetSecNode()->DownDegreeEntrant();
				m_lEdges.remove(tempE);
			}
			else if (tempE->GetSecNode() == n) {
				std::cout << green << " Arc " << tempE->GetFirstNode() << tempE->GetSecNode() << " removed" << white << std::endl;
				(tempE)->GetFirstNode()->DownDegreeSortant();
				m_lEdges.remove(tempE);
			}
		}
		for (std::shared_ptr<CNode> n1 : GetNodes())
			if (n1 == n)
				m_lNodes.remove(n1);
		std::cout << green << "|Node : " << n << " removed" << white << std::endl;
	}else
		std::cerr << red << "|#ERREUR : Le sommet n'existe pas!" << white << std::endl;

}


void CGraph::RemoveEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2, double d)
{
	for (std::shared_ptr<CEdge> e : GetEdges())
	{
		if (e->GetFirstNode() == n1 && e->GetSecNode() == n2 && e->GetPoids() == d) {
			n1->DownDegreeSortant();
			n2->DownDegreeEntrant();
			std::cout << green << "|Arc " << n1 << n2 << " removed" << white << std::endl;
			m_lEdges.remove(e);
			return;
		}
	}
	std::cerr << red << "|#ERREUR : Cet arc n'existe pas!" << white << std::endl;
}

void CGraph::AddPoids(std::string s1, std::string s2, double d) {
	std::shared_ptr<CNode> n1 = FindNode(s1);
	std::shared_ptr<CNode> n2 = FindNode(s2);

	for (std::shared_ptr<CEdge> e : GetEdges())
	{
		if (e->GetFirstNode() == n1 && e->GetSecNode() == n2) {
			if (e->GetPoids() != d) {
				double PrecPoids = e->GetPoids();
				e->SetPoids(d);
				std::cout << green << "|Poids de " << n1->GetName() << n2->GetName() << " : " << PrecPoids << "-->" << d << white << std::endl;
				return;
			}
			else {
				std::cerr << red << "|#ERREUR : Poids identique au précédent! Arc " << n1->GetName() << n2->GetName() << " non modifié." << white << std::endl;
				return;
			}
		}
	
	}
		
	std::cerr << red << "|#ERREUR : Cet arc n'existe pas!" << white << std::endl;
	char choice;
	do{
	std::cerr << blue << "|Voulez vous le créer? [y/n]" << white << std::endl;

	std::cin >> choice;
	 
		if (choice == 'y' || choice == 'Y') {
			AddEdge(s1, s2, d);
		}
		else if(choice == 'n' || choice == 'N')
			return;
	} while (choice != 'y' || choice != 'Y' || choice != 'n' || choice != 'N');
	

			
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


void CGraph::saveGraph(const std::string& strName) {
	std::ofstream file;

	if (fileExist("Graphs/" + strName + ".graph")) {
		char choice;
		std::cerr << red << "|#ERREUR : Le fichier existe déjà!" << white << std::endl;
		return;
	}
		
		file.open("Graphs/" + strName + ".graph");
		file << "Sommets:" << std::endl;
		for (const std::shared_ptr<CNode>& n1 : m_lNodes) {
			file << n1 << " ";
		}
		file << std::endl;
		file << "Arcs:" << std::endl;
		for (const std::shared_ptr<CEdge>& e1 : m_lEdges) {
			std::shared_ptr<CNode> n1 = e1->GetFirstNode();
			std::shared_ptr<CNode> n2 = e1->GetSecNode();
			double d = e1->GetPoids();
			file << n1 << " "
				<< n2 << " " << d << std::endl;
		}

	if (file.is_open())
		file.close();

	std::cout << green << "|Graph saved!" << white << std::endl;

}

void CGraph::loadGraph(const std::string& strName) {
	std::ifstream file;
	std::string lineString;
	double lineDouble;
	file.open("Graphs/" + strName + ".graph");
	bool mode;

	if (file.is_open()) {
		clear();
		while (std::getline(file, lineString)) {
			if (lineString == "Sommets:") {
				mode = true;
				file.ignore(0,'\n');
			}
			else if (lineString == "Arcs:") {
				mode = false;
				file.ignore(0, '\n');
			}
			else {
				std::stringstream ss(lineString);

				if (mode) {
					while(ss >> lineString)
						AddNode(lineString);
				}
				else {
					std::shared_ptr<CNode> n1;
					std::shared_ptr<CNode> n2;
					double d;
					while (ss >> lineString) 
					{
						n1 = FindNode(lineString);
						ss >> lineString;
						n2 = FindNode(lineString);
						ss >> lineDouble;
						d = lineDouble;
					}
					AddEdge(n1->GetName(), n2->GetName(), d);
				}
			}
		}
		std::cout << green << "|Graph loaded!" << white << std::endl;
		file.close();
	}else
		std::cerr << red << "|#ERREUR : Le fichier n'existe pas!" << white << std::endl;

}


void CGraph::clear() {
	m_lEdges.clear();
	m_lNodes.clear();
	std::cout << yellow << "|Graphe nettoyé" << white << std::endl;
}


inline bool CGraph::fileExist(const std::string& strName) {
	struct stat buffer;
	return (stat(strName.c_str(), &buffer) == 0);
}




std::ostream & operator<<(std::ostream & os, const CGraph & graph)
{
	os << yellow << "************************************************" << std::endl;
	os << "[Structure du Graphe]" << white << std::endl;
	os << "Nombre de Sommet : " << graph.GetNodes().size() << ", Nombre d'Arc : " << graph.GetEdges().size() << std::endl;

	os << green << "Arcs : " << std::endl;
	for (const std::shared_ptr<CEdge>& e : graph.GetEdges()) {
		os << "    " << e;
	}
	os << std::endl;
	os << blue << "Sommets " << ":======== ";
	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		os << n << " ";
	}
	os << white << std::endl;

	os << yellow << "Matrice :         ";
	for (size_t i = 0; i < graph.GetNodes().size()*2; ++i) {
		if(i % 2 == 0)
			os << yellow << "_" << white;
		else
			os << " ";
	}
	os << std::endl;

	char bit = 0;
	for (const std::shared_ptr<CNode>& n : graph.GetNodes())
	{
		os << blue << "                " << n->GetName() << yellow << "|" << white;
		for (const std::shared_ptr<CNode>& no : graph.GetNodes())
		{
			if (graph.countainsEdge(n, no)) {
				bit = '1';
				os << green;
			}
			else {
				bit = '0';
				os << red;
			}

			os << bit << " " << white;
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
	os << green << "Degres sortants" << white << " : ";

	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		if (n->GetDegreeSortant() > 0)
			os << green << n->GetDegreeSortant() << " ";
		else
			os << red << n->GetDegreeSortant() << " ";
	}
	os << white << std::endl;
	os << blue << "Degres entrants" << white <<" : ";

	for (const std::shared_ptr<CNode>& n : graph.GetNodes()) {
		if (n->GetDegreeEntrant() > 0)
			os << green << n->GetDegreeEntrant() << " ";
		else
			os << red << n->GetDegreeEntrant() << " ";
	}
	os << std::endl;
	os << yellow << "************************************************" << white << std::endl;



	return os;
}

