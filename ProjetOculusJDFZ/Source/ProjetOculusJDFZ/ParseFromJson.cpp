// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjetOculusJDFZ.h"
#include "ParseFromJson.h"

ParseFromJson::ParseFromJson()
{
}

ParseFromJson::ParseFromJson(std::string json) : json(json) {}

ParseFromJson::~ParseFromJson()
{
}

std::vector<DataFromJson> ParseFromJson::ParseJSON(){

	std::vector<DataFromJson> allData;
	JSONNode node = libjson::parse(libjson::to_json_string(json));


	for (auto& message : node)
	{
		DataFromJson parsedMessage;

		auto& type = message.at(JSON_TEXT("type"));
		auto& remove = message.at(JSON_TEXT("remove"));
		auto& set = message.at(JSON_TEXT("set"));
	

		for (auto& face : set)
		{
			auto& id = face.at(JSON_TEXT("id"));
			auto& material = face.at(JSON_TEXT("material"));
			auto& normal = face.at(JSON_TEXT("normal"));
			auto& vertices = face.at(JSON_TEXT("vertices"));
			auto is_triangulated = face.find(JSON_TEXT("is_triangulated"));

			std::string typeString = libjson::to_std_string(type.as_string());
			std::string materialString =
				libjson::to_std_string(material.as_string());
			parsedMessage.setType(typeString);
			parsedMessage.setId(id.as_int());
			parsedMessage.setMaterial(materialString);

			if (is_triangulated != message.end() &&
				is_triangulated->as_bool()) {
				parsedMessage.setIsTriangulated(true);
			}
			else{
				parsedMessage.setIsTriangulated(false);
			}


			for (auto &r : remove) {

				parsedMessage.addIdToRemove(r.as_int());
			}


			parsedMessage.setNormal(normal[0].as_float(),
				normal[1].as_float(), normal[2].as_float());


			for (auto &v : vertices)
			{
				DataFromJson::coordinates3D vertice;
				vertice.push_back(v[0].as_float());
				vertice.push_back(v[1].as_float());
				vertice.push_back(v[2].as_float());
				parsedMessage.addVertice(vertice);
			}

			allData.push_back(parsedMessage);
		}
	}

	return allData;
}
