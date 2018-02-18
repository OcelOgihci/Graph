#include "Edge.h"
#include "Graph.h"
#include "Node.h"
#include "Tree.h"
#include <iostream>
#include "ColorMod.h"// namespace Color

#define menu() 	std::cout << std::endl << "************************************************" <<	std::endl; \
				std::cout << " -1 : Retourner au menu principal" <<							std::endl; \
				std::cout << " -2 : Pour Ajouter un sommet" <<								std::endl; \
				std::cout << " -3 : Pour Ajouter un arc" <<									std::endl; \
				std::cout << " -4 : Pour Ajouter un poids à un arc" <<						std::endl; \
				std::cout << " -5 : Pour Afficher le graphe" <<								std::endl; \
				std::cout << " -6 : Pour Supprimer un sommet" <<							std::endl; \
				std::cout << " -7 : Pour Supprimer un arc" <<								std::endl; \
				std::cout << " -9 : Pour quitter" <<										std::endl; \
				std::cout << "************************************************" <<			std::endl; \
				std::cin >> choice; 

int main() {
	system("chcp 1252>NUL");
	char choice = '1';
	CGraph graph;
	graph.AddNode("A");
	graph.AddNode("B");
	graph.AddNode("C");
	//graph.AddNode("D");
	//graph.AddNode("E");
	//graph.AddNode("F");
	//graph.AddNode("G");
	//graph.AddNode("H");
	//graph.AddNode("I");
	graph.AddEdge(graph.FindNode("A"), graph.FindNode("B"), 10);
	graph.AddEdge(graph.FindNode("A"), graph.FindNode("A"), 2);
	graph.AddEdge(graph.FindNode("B"), graph.FindNode("C"), 12);
	graph.AddEdge(graph.FindNode("C"), graph.FindNode("A"), 2.5);
	//graph.AddEdge(graph.FindNode("E"), graph.FindNode("F"));
	//graph.AddEdge(graph.FindNode("F"), graph.FindNode("A"));
	//graph.AddEdge(graph.FindNode("C"), graph.FindNode("D"));
	//graph.AddEdge(graph.FindNode("A"), graph.FindNode("E"));
	//graph.AddEdge(graph.FindNode("B"), graph.FindNode("E"));
	//graph.AddEdge(graph.FindNode("A"), graph.FindNode("D"));

	//graph.RemoveNode(graph.FindNode("B"));
	//graph.RemoveEdge(graph.FindNode("C"), graph.FindNode("A"));
	
	std::string sNameDep, sNameArr;
	double dPoids;
	do {

		switch (choice)
		{
		case '1':
			system("cls");
			std::cout << yellow << "*********** [Modélisateur de Graphe]*************" << white << std::endl;
			menu();
			break;
		case '2':
			system("cls");
			std::cout << " Entrez le nom du sommet : ";
			std::cin >> sNameDep;
			graph.AddNode(sNameDep);
			menu();
			break;
		case '3':
			system("cls");
			std::cout << "|Entrez le sommet de départ : ";
			std::cin >> sNameDep;
			std::cout << "|Entrez le sommet d'arrivée : ";
			std::cin >> sNameArr;
			std::cout << "|Entrez le poids de l'arc : ";
			std::cin >> dPoids;
			graph.AddEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr), dPoids);

			menu();
			break;
		case '5':
			system("cls");
			std::cout << graph;
			menu();
			break;
		case '6':
			system(" cls");
			std::cout << "|Entrez le nom du sommet : ";
			std::cin >> sNameDep;
			graph.RemoveNode(graph.FindNode(sNameDep));
			menu();
			break;
		case '7':
			system("cls");
			std::cout << "|Entrez le sommet de départ : ";
			std::cin >> sNameDep;
			std::cout << "|Entrez le sommet d'arrivée : ";
			std::cin >> sNameArr;
			graph.RemoveEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr));
			menu();
			break;
		case '4':
			int nPoids;
			system("cls");
			std::cout << "|Entrez le sommet de départ : ";
			std::cin >> sNameDep;
			std::cout << "|Entrez le sommet d'arrivée : ";
			std::cin >> sNameArr;
			std::cout << "|Entrez le poids : ";
			std::cin >> nPoids;
			graph.AddPoids(sNameDep, sNameArr, nPoids);
			menu();
			break;
		default:
			choice = '1';
			break;
		}
	} while (choice != '9');

	return 0;
}