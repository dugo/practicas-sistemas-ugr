#ifndef __VT_MAPITEM_HH__
#define __VT_MAPITEM_HH__

#include <string>
#include <istream>

/**
@brief Representacion generica de un elemento en el mapa.

Esta formada por un numero identificador y un nombre.
*/
class MapItem
{
	public:
		MapItem(const int &n, const std::string &name);
		MapItem(const MapItem &src);
		MapItem& operator=(const MapItem &src);
		~MapItem();
		int getN() const;
		std::string getName() const;
		friend std::istream& operator>>(std::istream &s, MapItem &m);
		
	private:
		int n;
		std::string name;
};

#endif
