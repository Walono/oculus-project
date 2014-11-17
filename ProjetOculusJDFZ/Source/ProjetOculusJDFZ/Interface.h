/*
Author: Julie Djeffal (julied20)

Class: Interface
*/

#pragma once
#include "DataFromJson.h"
#include "Object.h"
#include<vector>



class Interface {

	private:

		// Add an Object to the environment from the data we extract 
		//from the JSON
		virtual Object add_object(DataFromJson data) = 0;
		// Remove an object from the Environment
		virtual void remove_object(Object polygon) = 0;
		//Add a set of object to the environment
		virtual Object add_scene(std::vector<Object> polygons) = 0;
		// Remove a set of object from the environment
		virtual void remove_scene(std::vector<Object> polygons) = 0;
		// Add a sounf source to the environment
		virtual Object add_sound_source(DataFromJson data) = 0;
		// Remove a sound source from the environment
		virtual void remove_sound_source(Object sound) = 0;

	public:

		//Interprete the Data we extracted from the JSON in order 
		//to know wich method to call
		virtual void interpreteJSON(DataFromJson data) = 0;
		// Move an object from the environment
		virtual void move_object(Object polygon) = 0;
		// Move a source sound from the environment
		virtual void move_source(Object sound) = 0;
		// enable or disable the sound of a source sound
		virtual void enable_sound(bool enable, Object sound) = 0;
		// Set the initial position and view of the receiver
		virtual void set_initial_position() = 0;




};