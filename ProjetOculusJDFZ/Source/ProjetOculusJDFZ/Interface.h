/*
Author: Julie Djeffal (julied20)

Class: Interface
*/

#pragma once
#include "DataFromJson.h"
#include "Object.h"
#include<list>



class Interface {

	public:

		// add a face 
		// a texture is represented by is id (int)
		virtual Object add_object(std::list<float> position, 
			std::list<int> textures) = 0;
		// Remove an object from the Environment
		virtual void remove_object(std::list<float> position,
			std::list<int> textures) = 0;
		virtual Object add_sound_source(std::list<float> position, 
			std::list<float> directionVector, int sourceId) = 0;
		// Remove a sound source from the environment
		virtual void remove_sound_source(std::list<float> position,
			int sourceId) = 0;
		virtual void move_object(std::list<float> position,
			std::list<int> textures) = 0;
		// Move a source sound from the environment
		virtual void move_source(std::list<float> position,
			std::list<float> directionVector, int sourceId) = 0;
		// enable or disable the sound of a source sound
		virtual void enable_sound(bool enable) = 0;
		// Set the initial position and view of the receiver
		// Equal to reset_position()?
		virtual void set_initial_position() = 0;
		virtual void set_position(std::list<float> position) = 0;




};