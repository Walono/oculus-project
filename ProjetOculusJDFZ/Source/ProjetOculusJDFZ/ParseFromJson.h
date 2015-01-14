/*
Class: ParseFromJson

It's a Parser which take the JSON message we receive 
fromthe server and extracts all the data 
to store them in a DataFromJson object.

*/
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
