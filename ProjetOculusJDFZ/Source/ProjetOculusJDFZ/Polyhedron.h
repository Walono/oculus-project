#pragma once
#include<list>


class Polyhedron
{
public:
	Polyhedron(std::list<int> facesId, int polyhedronId);
	~Polyhedron();

	std::list<int> getFaces();
	int getPolyhedronId();



private:

	std::list<int> facesId;
	int polyhedronId;

};

