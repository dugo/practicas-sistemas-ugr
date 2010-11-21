#ifndef __VT_CROSSROADS_HH__
#define __VT_CROSSROADS_HH__

#include <istream>
#include "MapItem.hh"

/**
@brief Representa un cruce en el mapa
*/
class Crossroads : public MapItem
{
	public:
		Crossroads();
		Crossroads(const int &n, const std::string &name, const float &x, const float &y);
		Crossroads(const Crossroads &c);
		Crossroads& operator=(const Crossroads &c);
		bool operator==(const Crossroads &c) const;
		bool operator!=(const Crossroads &c) const;
		bool operator<(const Crossroads &c) const;
		bool null() const;
		~Crossroads();
		float& getX();
		float& getY();
		float getX() const;
		float getY() const;
		friend std::istream& operator>>(std::istream &s, Crossroads &c);
	
	private:
		float x,y;
};

#endif
