/**
* Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
* Face
* Purpose: Represent a polygon.  
* 
* @author Julie Djeffal & Fabien Zellweger
*/

#pragma once
#include<list>
#include<vector>
#include<string>

class Face
{
public:

/* Constructors and Destructor */

	Face(std::list<float> position, std::list<std::list<float>> coordinates, 
		int texture, int faceId);
	Face();
	~Face();
	Face(const Face& other);

/* Getter and Setter */

	std::list<float> getPosition();
	std::list<std::list<float>> getCoordinates();
	int getTexture();
	int getFaceId();
	std::list<float> getTranslationVector();
	std::list<float> getRotation();

	void setPosition(std::list<float> position);
	void setCoordinates(std::list<std::list<float>> coordinates);
	void setTexture(int texture);
	void setfaceId(int faceId);
	void setFaceSpawned(bool isSpawned);
	void setFaceTranslationVector(std::list<float> newTranslationVector);
	void setFaceRotation(std::list<float> newRotation);

	bool hasProceduralFaceActor;
	

private:

	std::list<float> position;
	std::list<std::list<float>> coordinates;
	int texture; 
	int faceId;
	std::list<float> translationVector;
	std::list<float> rotation;
	
};

