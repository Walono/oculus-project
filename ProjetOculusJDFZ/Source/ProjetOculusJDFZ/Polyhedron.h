

/**
* Bachelor Project: Development and Implementation of 
* an Oculus Rift Frontend for Audio-Visual VR Applications
* Polyhedron
* Purpose: Represent a set of face
* 
* @author Julie Djeffal & Fabien Zellweger
*/

#pragma once
#include<list>


class Polyhedron
{
public:

/* Constructors and Destructor */
	Polyhedron(std::list<int> facesId, int polyhedronId);
	Polyhedron();
	~Polyhedron();

/* Getter */

	std::list<int> getFaces();
	int getPolyhedronId();



private:

	std::list<int> facesId;
	int polyhedronId;

};

