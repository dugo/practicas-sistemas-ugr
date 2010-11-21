#include <fstream>
#include <cassert>
#include "VTio.hh"

void loadCrossroads(const std::string &file, std::map<std::string, Crossroads> &crossroads)
{
	std::ifstream f(file.c_str());
	assert(f);
	
	Crossroads c;
	while(f && !f.eof())
	{
		f>>c;
		assert(f);
		crossroads[c.getName()] = c;
	}
	f.close();
}

void loadStretch(const std::string &file, std::vector<Stretch> &stretchs)
{
	std::ifstream f(file.c_str());
	assert(f);
	
	Stretch t;
	while(f && !f.eof())
	{
		f>>t;
		assert(f);
		stretchs.push_back(t);
	}
	f.close();	
}

void buildMap(std::map<std::string, Crossroads> &crossroads, std::vector<Stretch> &stretchs, CGraph<Crossroads> &mymap)
{
	for (unsigned int i=0;i<stretchs.size();i++)
	{
		mymap.addNeighbourgs(crossroads[stretchs[i].get1()],crossroads[stretchs[i].get2()]);
	}
}

void writePath(const std::string &file, const std::vector<Crossroads> &way)
{
	std::ofstream f(file.c_str());
	assert(f);
	
	f.setf(std::ios::fixed,std::ios::floatfield);
	for (unsigned int i=0;i<way.size();i++)
		f<<way[i].getN()<<','<<way[i].getX()<<','<<way[i].getY()<<std::endl;
	
	f.close();
}

std::string getCrossName(std::map<std::string, Crossroads> cross, const int &id)
{
	std::map<std::string, Crossroads>::const_iterator it;
	for (it=cross.begin();it!=cross.end() && (*it).second.getN()!=id;it++);
	
	if (it!=cross.end())
		return (*it).second.getName();
	else return "";
}

#include "CGraph.cc"
