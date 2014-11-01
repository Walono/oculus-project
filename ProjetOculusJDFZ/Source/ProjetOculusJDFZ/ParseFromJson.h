// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include<string>
#include "DataFromJson.h"
#include "libjson.h"
#include "JSONOptions.h"

class ParseFromJson
{
private:

	std::string json;

public:
	ParseFromJson();
	ParseFromJson(std::string json);
	~ParseFromJson();
	std::vector<DataFromJson> ParseJSON();
	//DataFromJson parseFromJson();

};