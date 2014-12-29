#pragma once
#include<vector>
#include<list>
#include<string>

class Sound
{
public:
	Sound(std::string name, std::list<float> position,
		std::vector<float> viewDirection,
		std::vector<float> upDirection, int sourceId);

	Sound(const Sound& other);

	~Sound();

	std::string getName();
	std::list<float> getPosition();
	std::vector<float> getViewDirection();
	std::vector<float> getUpDirection();
	int getSourceId();

private:

	std::string name;
	std::list<float> position;
	std::vector<float> viewDirection;
	std::vector<float> upDirection; 
	int sourceId;
};

