#include "Crossroads.hh"
#include <istream>
#include <cmath>
#include <cstdlib>

Crossroads::Crossroads() : MapItem(0, "")
{
	x = y = 0.0;
}

Crossroads::Crossroads(const int &n, const std::string &name, const float &x, const float &y) : MapItem(n , name)
{
	this->x = x;
	this->y = y;
}

Crossroads::Crossroads(const Crossroads &c) : MapItem(c.getN(), c.getName())
{
	x = c.x;
	y = c.y;
}

Crossroads&
Crossroads::operator=(const Crossroads &c)
{
	if (&c!=this)
	{
		MapItem::operator=(c);
		x = c.x;
		y = c.y;
	}
	return *this;
}

Crossroads::~Crossroads()
{

}

bool
Crossroads::operator==(const Crossroads &c) const
{
	return (getName()==c.getName());
}

bool
Crossroads::operator!=(const Crossroads &c) const
{
	return !(getName()==c.getName());
}

bool
Crossroads::null() const
{
	return (getName()=="");
}

bool
Crossroads::operator<(const Crossroads &c) const
{
	// Puede haber otros criterios pero no es relevante
	return ((x*x+y*y)<(c.x*c.x+c.y*c.y));
}

float&
Crossroads::getX()
{
	return x;
}

float&
Crossroads::getY()
{
	return y;
}

float
Crossroads::getX() const
{
	return x;
}

float
Crossroads::getY() const
{
	return y;
}

std::istream&
operator>>(std::istream &s, Crossroads &c)
{
	MapItem m(0,"");
	s>>m;
	
	if (!s) return s;
	
	char buffer[256];
	float x,y;
	
	s.getline(buffer, 255, ',');
	x = atof(buffer);
	if (x==HUGE_VAL || x==-HUGE_VAL)
	{
		s.setstate(std::ios::badbit);
		return s;
	}

	s.getline(buffer, 255);
	y = atof(buffer);
	if (y==HUGE_VAL || y==-HUGE_VAL)
	{
		s.setstate(std::ios::badbit);
		return s;
	}

	c.MapItem::operator=(m);
	c.x = x;
	c.y = y;
	
	return s;
}
