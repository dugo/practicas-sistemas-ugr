#include "Stretch.hh"

Stretch::Stretch() : MapItem(0, "")
{
	c1 = c2 = street = "";
}

Stretch::Stretch(const int &n, const std::string &name, const std::string &street, const std::string &c1, const std::string &c2) : MapItem(n, name)
{
	this->c1 = c1;
	this->c2 = c2;
	this->street = street;
}

Stretch::Stretch(const Stretch &s) : MapItem(s.getN(), s.getName())
{
	c1 = s.c1;
	c2 = s.c2;
	street = s.street;
}

Stretch&
Stretch::operator=(const Stretch &s)
{
	if (&s!=this)
	{
		MapItem::operator=(s);
		c1 = s.c1;
		c2 = s.c2;
		street = s.street;
	}
	return *this;
}

Stretch::~Stretch()
{

}

std::string&
Stretch::get1()
{
	return c1;
}

std::string&
Stretch::get2()
{
	return c2;
}

std::string&
Stretch::getStreet()
{
	return street;
}

std::istream&
operator>>(std::istream &s, Stretch &c)
{
	MapItem m(0,"");
	s>>m;
		
	if (!s) return s;
	
	std::string str,c1;
	char buffer[256];
	
	s.getline(buffer, 255, ',');
	if (*buffer==0)
	{
		s.setstate(std::ios::badbit);
		return s;
	}
	str = buffer;
	
	s.getline(buffer, 255, ',');
	if (*buffer==0)
	{
		s.setstate(std::ios::badbit);
		return s;
	}
	c1 = buffer;

	s.getline(buffer, 255, '\n');
	if (*buffer==0)
	{
		s.setstate(std::ios::badbit);
		return s;
	}
	c.c2 = buffer;
	
	c.MapItem::operator=(m);
	c.street = str;
	c.c1 = c1;
	
	return s;
}


