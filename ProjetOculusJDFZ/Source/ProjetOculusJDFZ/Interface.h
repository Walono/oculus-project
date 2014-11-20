/*
Author: Julie Djeffal (julied20)

Class: Interface
*/

#pragma once
#include "DataFromJson.h"
#include "Object.h"
#include<list>
#include<vector>
#include<string>



class Interface {

	public:

		// add a face 
		// a texture is represented by is id (int)
		virtual void add_face(std::list<float> position, 
			int texture, int faceId) = 0;
		
		// Remove a face from the Environment
		virtual void remove_face(int faceId) = 0;
		
		//Move a face in the Environment
		virtual void move_face(int faceId) = 0;
		
		//Add a sound source to the environment
		virtual void add_sound_source(std::string name, 
			std::list<float> position, 
			std::list<std::vector<float>> viewDirection, 
			std::list<std::vector<float>> upDirection, int sourceId) = 0;
		
		// Remove a sound source from the environment
		virtual void remove_sound_source(int sourceId) = 0;
		
		// Move a source sound from the environment
		virtual void move_source(int sourceId) = 0;
		
		// Enable or disable the sound of a source sound
		virtual void enable_sound(bool enable) = 0;
		
		// Set the initial position 
		virtual void set_initial_position(std::list<float> position) = 0;

		// Reset the position to the initial position
		virtual void reset_position() = 0;



};