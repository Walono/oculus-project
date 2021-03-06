/**
* Bachelor Project: Development and Implementation of 
* an Oculus Rift Frontend for Audio-Visual VR Applications
* Sound
* Purpose: Represent a sound source
* 
* @author Julie Djeffal & Fabien Zellweger
*/
#pragma once
#include<vector>
#include<list>
#include<string>

class Sound
{
	
/* Constructors and Desctructor */
public:
	Sound(std::string name, std::list<float> position,
		std::vector<float> viewDirection,
		std::vector<float> upDirection, int sourceId);

	Sound();

	Sound(const Sound& other);

	~Sound();

/* Getter and Setter */

	std::string getName();
	std::list<float> getPosition();
	std::vector<float> getViewDirection();
	std::vector<float> getUpDirection();
	int getSourceId();
	bool getSoundActivity();
	std::list<float> getTranslationVector();

	void setPosition(std::list<float> newPosition);
	void setViewDirecton(std::vector<float> newViewDirection);
	void setUpDirection(std::vector<float> newUpDirection);
	void setSoundSpawned(bool isSpawned);
	void setSoundActive(bool isNewActive);
	void setSoundTranslationVector(std::list<float> newTranslationVector);

	bool hasProceduralFaceActor;

private:

	std::string name;
	std::list<float> position;
	std::vector<float> viewDirection;
	std::vector<float> upDirection; 
	int sourceId;
	bool isActive;
	std::list<float> translationVector;
};

