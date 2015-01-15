/**
*	Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
*	ParseFromJson
*	Purpose: It's a Parser which take the JSON message we receive 
*		from the server and extracts all the data 
*		to store them in a DataFromJson object.
*
*  @author Julie Djeffal & Fabien Zellweger
**/

#pragma once
#include<string>
#include "DataFromJson.h"
#include "libjson.h"
#include "JSONOptions.h"

class ParseFromJson
{
private:

	//A string containing our JSON message
	std::string json;

public:

	/* Constructor and Destructor*/
	ParseFromJson();
	ParseFromJson(std::string json);
	~ParseFromJson();

	/*
	* Parse one or multiples JSON, and 
	* @return an Array of parsed messages
	*/
	std::vector<DataFromJson> ParseJSON();

};
