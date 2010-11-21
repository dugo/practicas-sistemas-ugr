#include "MapItem.hh"
#include <istream>
#include <cstdlib>
#include <climits>

MapItem::MapItem(const int &n, const std::string &name)
{
	this->n = n;
	this->name = name;
}

MapItem::MapItem(const MapItem &src)
{
	this->n = src.n;
	this->name = src.name;
}

MapItem&
MapItem::operator=(const MapItem &src)
{
	if (this!=&src)
	{
		this->n = src.n;
		this->name = src.name;
	}
	
	return *this;
}

MapItem::~MapItem()
{

}

int
MapItem::getN() const
{
	return n;
}

std::string
MapItem::getName() const
{
	return name;
}

std::istream&
operator>>(std::istream &s, MapItem &m)
{
	char buffer[256];
	int n;
	
	s.getline(buffer, 255, ',');
	n = atoi(buffer);
	
	
	if (n==INT_MIN || n==INT_MAX)
	{
		s.setstate(std::ios::badbit);
		return s;
	}
	
	m.n = n;
	
	s.getline(buffer, 255, ',');
	m.name = buffer;
	
	return s;
}
