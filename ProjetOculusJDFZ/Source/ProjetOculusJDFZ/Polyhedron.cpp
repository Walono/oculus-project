#include "Polyhedron.h"


Polyhedron::Polyhedron(std::list<int> facesId, int polyhedronId):
facesId(facesId), polyhedronId(polyhedronId) {}


Polyhedron::~Polyhedron()
{
}

std::list<int> Polyhedron::getFaces() {
	return facesId;
}

int Polyhedron::getPolyhedronId() {
	return polyhedronId;
}