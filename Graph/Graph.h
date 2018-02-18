#pragma once
#include "Edge.h"
#include "Node.h"
#include <list>
#include <vector>
#include <memory>
#include <set>
class CGraph
{
private:
	std::list<std::shared_ptr<CNode>> m_sNodes;
	std::list<std::shared_ptr<CEdge>> m_sEdges;
public:

	std::list<std::shared_ptr<CNode>> GetNodes() const;
	std::list<std::shared_ptr<CEdge>> GetEdges() const;

	void AddNode(const std::string& strName);
	void AddEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2);

	void RemoveNode(std::shared_ptr<CNode> n);
	void RemoveEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2);

	void AddPoids(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2, double d);

	std::shared_ptr<CNode> FindNode(std::shared_ptr<CNode> n) const;
	std::shared_ptr<CNode> FindNode(std::string strName) const;

	bool countainsEdge(std::shared_ptr<CNode> n1, std::shared_ptr<CNode> n2) const;
	bool countainsNode(std::string strName) const;
};		 

std::ostream& operator<< (std::ostream& os, const CGraph& graph);