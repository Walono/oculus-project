#pragma once
#include<list>
#include<vector>
#include<string>

class AProceduralFaceActor;

class Face
{
public:
	Face(std::list<float> position, std::list<std::list<float>> coordinates, 
		int texture, int faceId);
	Face();
	~Face();
	Face(const Face& other);

	std::list<float> getPosition();
	std::list<std::list<float>> getCoordinates();
	int getTexture();
	int getFaceId();
	AProceduralFaceActor* getProceduralFaceActor();

	void setPosition(std::list<float> position);
	void setCoordinates(std::list<std::list<float>> coordinates);
	void setTexture(int texture);
	void setfaceId(int faceId);
	void setFaceSpawned(bool isSpawned);

	bool hasProceduralFaceActor;
	

private:

	std::list<float> position;
	std::list<std::list<float>> coordinates;
	int texture; 
	int faceId;
	
};

