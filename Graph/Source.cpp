#include "Edge.h"
#include "Graph.h"
#include "Node.h"

#include <iostream>
#include <conio.h>
using namespace std;

#define menu() 	cout << endl << " -m : Retourner au menu principal" << endl; \
				cout << " -n : Pour Ajouter un sommet" << endl; \
				cout << " -e : Pour Ajouter un arc" << endl; \
				cout << " -p : Pour Ajouter un poids � un arc" << endl; \
				cout << " -a : Pour Afficher le graphe" << endl; \
				cout << " -r : Pour Supprimer un sommet" << endl; \
				cout << " -t : Pour Supprimer un arc" << endl;\
				cout << "************************************************" << endl; \
				cin >> choice; 

int main() {
	system("chcp 1252>NUL");
	char choice = 'm';
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
		case 'm':
			system("cls");
			cout << "*********** [Mod�lisateur de Graphe]*************" << endl;
			cout << "************************************************" << endl;
			menu();
			cin >> choice;
			break;
		case 'n':
			system("cls");
			cout << "Entrez le nom du sommet : ";
			cin >> sNameDep;
			graph.AddNode(sNameDep);
			cout << endl << " -m : Retourner au menu principal" << endl;
			menu();
			break;
		case 'e':
			system("cls");
			cout << "Entrez le sommet de d�part : ";
			cin >> sNameDep;
			cout << "Entrez le sommet d'arriv�e : ";
			cin >> sNameArr;
			graph.AddEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr));

			menu();
			break;
		case 'a':
			system("cls");
			cout << graph;
			menu();
			_getch();
			break;
		case 'r':
			system("cls");
			cout << "Entrez le nom du sommet : ";
			cin >> sNameDep;
			graph.RemoveNode(graph.FindNode(sNameDep));
			menu();
			break;
		case 't':
			system("cls");
			cout << "Entrez le sommet de d�part : ";
			cin >> sNameDep;
			cout << "Entrez le sommet d'arriv�e : ";
			cin >> sNameArr;
			graph.RemoveEdge(graph.FindNode(sNameDep), graph.FindNode(sNameArr));
			menu();
			break;
		case 'p':
			int nPoids;
			system("cls");
			cout << "Entrez le sommet de d�part : ";
			cin >> sNameDep;
			cout << "Entrez le sommet d'arriv�e : ";
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