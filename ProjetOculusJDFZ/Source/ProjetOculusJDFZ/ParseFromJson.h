/*
Author: Julie Djeffal (julied20)

Class: ParseFromJson
*/
#pragma once
#include<string>
#include "DataFromJson.h"
#include "libjson.h"
#include "JSONOptions.h"

class ParseFromJson
{
private:

	//A string containong our JSON
	std::string json;

public:

	/* Constructor and Destructor*/
	ParseFromJson();
	ParseFromJson(std::string json);
	~ParseFromJson();

	/*
	* Parse a or some JSON, and return the datas into an array
	*/
	std::vector<DataFromJson> ParseJSON();

};