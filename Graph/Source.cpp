#include "Edge.h"
#include "Graph.h"
#include "Node.h"

#include <iostream>
#include <conio.h>
using namespace std;

#define menu() 	cout << endl << "************************************************" << endl; \
				cout << " -1 : Retourner au menu principal" << endl; \
				cout << " -2 : Pour Ajouter un sommet" << endl; \
				cout << " -3 : Pour Ajouter un arc" << endl; \
				cout << " -4 : Pour Ajouter un poids à un arc" << endl; \
				cout << " -5 : Pour Afficher le graphe" << endl; \
				cout << " -6 : Pour Supprimer un sommet" << endl; \
				cout << " -7 : Pour Supprimer un arc" << endl;\
				cout << "************************************************" << endl; \
				cin >> choice; 

int main() {
	system("chcp 1252>NUL");
	unsigned int choice = 1;
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
	graph.AddEdge(graph.FindNode("A"), graph.FindNode("B"));
	graph.AddEdge(graph.FindNode("A"), graph.FindNode("A"));
	graph.AddEdge(graph.FindNode("B"), graph.FindNode("C"));
	graph.AddEdge(graph.FindNode("C"), graph.FindNode("A"));
	graph.AddPoids(graph.FindNode("A"), graph.FindNode("B"), 10);
	graph.AddPoids(graph.FindNode("A"), graph.FindNode("A"), 2);
	graph.AddPoids(graph.FindNode("B"), graph.FindNode("C"), 12);
	graph.AddPoids(graph.FindNode("C"), graph.FindNode("A"), 2.5);
	//graph.AddEdge(graph.FindNode("E"), graph.FindNode("F"));
	//graph.AddEdge(graph.FindNode("F"), graph.FindNode("A"));
	//graph.AddEdge(graph.FindNode("C"), graph.FindNode("D"));
	//graph.AddEdge(graph.FindNode("A"), graph.FindNode("E"));
	//graph.AddEdge(graph.FindNode("B"), graph.FindNode("E"));
	//graph.AddEdge(graph.FindNode("A"), graph.FindNode("D"));

	//graph.RemoveNode(graph.FindNode("B"));
	//graph.RemoveEdge(graph.FindNode("C"), graph.FindNode("A"));
	
	string sNameDep, sNameArr;
	do {

		switch (choice)
		{
		case 1:
			system("cls");
			cout << "*********** [Modélisateur de Graphe]*************" << endl;
			menu();
			break;
		case 2:
			system("cls");
			cout << "Entrez le nom du sommet : ";
			cin >> sNameDep;
			graph.AddNode(sNameDep);
			menu();
			break;
		case 3:
			system("cls");
			cout << "Entrez le sommet de départ : ";
			cin >> sNameDep;
			cout << "Entrez le sommet d'arrivée : ";
			cin >> sNameArr;
			graph.AddEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr));

			menu();
			break;
		case 4:
			system("cls");
			cout << graph;
			menu();
			break;
		case 5:
			system("cls");
			cout << "Entrez le nom du sommet : ";
			cin >> sNameDep;
			graph.RemoveNode(graph.FindNode(sNameDep));
			menu();
			break;
		case 6:
			system("cls");
			cout << "Entrez le sommet de départ : ";
			cin >> sNameDep;
			cout << "Entrez le sommet d'arrivée : ";
			cin >> sNameArr;
			graph.RemoveEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr));
			menu();
			break;
		case 7:
			int nPoids;
			system("cls");
			cout << "Entrez le sommet de départ : ";
			cin >> sNameDep;
			cout << "Entrez le sommet d'arrivée : ";
			cin >> sNameArr;
			cout << "Entrez le poids : ";
			cin >> nPoids;
			graph.AddPoids(graph.FindNode(sNameDep), graph.FindNode(sNameArr), nPoids);
			menu();
			break;
		default:
			break;
		}
	} while (choice != 'q');


	//std::cout << graph << std::endl;
	_getch();

	return 0;
}