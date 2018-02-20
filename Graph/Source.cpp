#include "Edge.h"
#include "Graph.h"
#include "Node.h"
#include <iostream>
#include <conio.h>
#include "ColorMod.h"// namespace Color
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name  
using namespace std::experimental::filesystem::v1;


#define MENU 	std::cout << std::endl << yellow << "************************************************" << white <<	std::endl; \
				std::cout << " -1 : Retourner au menu principal" <<							std::endl; \
				std::cout << " -2 : Ajouter un sommet" <<								std::endl; \
				std::cout << " -3 : Ajouter un arc" <<									std::endl; \
				std::cout << " -4 : Ajouter un poids à un arc" <<						std::endl; \
				std::cout << " -5 : Afficher le graphe" <<								std::endl; \
				std::cout << " -6 : Supprimer un sommet" <<							std::endl; \
				std::cout << " -7 : Supprimer un arc" <<								std::endl; \
				std::cout << " -s : Sauvegarder le graphe" <<							std::endl; \
				std::cout << " -l : Charger un graphe" <<								std::endl; \
				std::cout << " -9 : Quitter" <<										std::endl; \
				std::cout << yellow << "************************************************" << white <<	std::endl; \
				std::cin >> choice; 

#define GRAPH_LIST 	std::cout << "|Liste des différents graphs existants: " << std::endl;		\
					for (auto & p : directory_iterator("Graphs/"))							\
					std::cout << blue << "-" << p.path().filename() << std::endl;

#define ASK_FOR_EDGE 			std::cout << yellow << "|Entrez le sommet de départ : ";		  \
								std::cin >> sNameDep;								  \
								std::cout << yellow << "|Entrez le sommet d'arrivée : ";		  \
								std::cin >> sNameArr;								  \
								std::cout << yellow << "|Entrez le poids : ";					  \
								std::cin >> dPoids;

int main() {
	system("chcp 1252>NUL");
	char choice = '1';
	CGraph graph;
	std::string sNameDep, sNameArr;
	double dPoids;
	std::string strName;

	graph.loadGraph("GraphFini");

	do {

		switch (choice)
		{
		case '1':
			system("cls");
			std::cout << yellow << "*********** [Modélisateur de Graphe]*************" << white << std::endl;
			MENU;
			break;
		case '2':
			system("cls");
			std::cout << " Entrez le nom du sommet : ";
			std::cin >> sNameDep;
			graph.AddNode(sNameDep);
			MENU;
			break;
		case '3':
			system("cls");
			ASK_FOR_EDGE;
			graph.AddEdge(sNameDep,sNameArr, dPoids);

			MENU;
			break;
		case '5':
			system("cls");
			std::cout << graph;
			MENU;
			break;
		case '6':
			system(" cls");
			std::cout << yellow << "|Entrez le nom du sommet : ";
			std::cin >> sNameDep;
			graph.RemoveNode(graph.FindNode(sNameDep));
			MENU;
			break;
		case '7':
			system("cls");
			ASK_FOR_EDGE;
			graph.RemoveEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr), dPoids);
			MENU;
			break;
		case '4':
			int nPoids;
			system("cls");

			ASK_FOR_EDGE;
			graph.AddPoids(sNameDep, sNameArr, dPoids);
			MENU;
			break;
		case 's':
			system("cls"); 
			GRAPH_LIST;

			std::cout << std::endl << yellow << "|Entrez le nom du fichier (sans extension!) :" << std::endl;
			std::cout << "|'q' pour annuler et revenir au menu principal." << std::endl;
			std::cin >> strName;
			if (strName == "q") { choice = 1; break; }
			
			graph.saveGraph(strName);
			MENU;
			break;
		case 'l':
			system("cls");

			GRAPH_LIST;
			std::cout << yellow << std::endl << "|Entrez le nom du fichier (sans extension!) :" << std::endl;

			std::cout << "|'q' pour annuler et revenir au menu principal." << std::endl;
			std::cout << red << "[/!\ TOUT GRAPHE NON SAUVEGARDÉ SERA PERDU /!\]" << white << std::endl;
			std::cin >> strName;
			if (strName == "q") { choice = 1; break; }
			graph.loadGraph(strName);
			MENU;
			break;
		default:
			choice = '1';
			break;
		}
	} while (choice != '9');

	return 0;
}


