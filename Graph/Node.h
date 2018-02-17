#pragma once
#include <string>
#include <memory>

class CNode
{
private:
	std::string m_strName;
	int m_nDegreeSortant;
	int m_nDegreeEntrant;

public:
	CNode(std::string strName = "") : m_strName(strName), m_nDegreeEntrant(0), m_nDegreeSortant(0) {}

	std::string GetName() const;

	int GetDegreeEntrant() const;
	int GetDegreeSortant() const;

	void UpDegreeEntrant();
	void DownDegreeSortant();

	void UpDegreeSortant();
	void DownDegreeEntrant();
};
std::ostream& operator<< (std::ostream& os, std::shared_ptr<CNode> node);