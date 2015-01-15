#include "ProjetOculusJDFZ.h"
#include "Polyhedron.h"


/* Constructors and Destructor */

Polyhedron::Polyhedron(std::list<int> facesId, int polyhedronId):
facesId(facesId), polyhedronId(polyhedronId) {}

Polyhedron::Polyhedron()
{
}


Polyhedron::~Polyhedron()
{
}

/* Getter */ 

std::list<int> Polyhedron::getFaces() {
	return facesId;
}

int Polyhedron::getPolyhedronId() {
	return polyhedronId;
}
