#ifndef __VT_STRETCH_HH__
#define __VT_STRETCH_HH__

#include <string>
#include "MapItem.hh"

/**
@brief Representa un tramo entre dos cruces del mapa.
*/
class Stretch : public MapItem
{
	public:
		Stretch();
		Stretch(const int &n, const std::string &name, const std::string &street, const std::string &c1, const std::string &c2);
		Stretch(const Stretch &s);
		Stretch& operator=(const Stretch &s);
		~Stretch();
		std::string& get1();
		std::string& get2();
		std::string& getStreet();
		friend std::istream& operator>>(std::istream &s, Stretch &c);
			
	private:
		std::string c1,c2,street;
};

#endif
