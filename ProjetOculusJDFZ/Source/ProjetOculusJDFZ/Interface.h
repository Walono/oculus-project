/*
Author: Julie Djeffal (julied20)

Class: Interface
*/

#pragma once
#include<list>
#include<vector>
#include<string>

class Interface {

	public:

		virtual ~Interface() {};

		// add a face 
		// a texture is represented by is id (int)
		virtual void add_face(std::list<float> position, 
			std::list<std::list<float>> coordinates, int texture, int faceId) = 0;
		
		// Remove a face from the Environment
		virtual void remove_face(int faceId) = 0;
		
		/**Move a face in the Environment with translation of position */
		//rotation list with (Pitch, Yaw, Roll)
		virtual void move_face(std::list<float> translationVector, std::list<float> rotation, int faceId) = 0;
		
		//Add a sound source to the environment
		virtual void add_sound_source(std::string name, 
			std::list<float> position, 
			std::vector<float> viewDirection, 
			std::vector<float> upDirection, int sourceId) = 0;
		
		// Remove a sound source from the environment
		virtual void remove_sound_source(int sourceId) = 0;
		
		// Move a source sound from the environment
		virtual void move_source(std::list<float> translationVector,
			std::vector<float> newViewDirection,
			std::vector<float> newUpDirection, int sourceId) = 0;
		
		// Enable or disable the sound of a source sound
		virtual void enable_sound(bool enable, int sourceId) = 0;
		
		// Set the initial position 
		virtual void set_initial_position(std::list<float> position) = 0;

		// Reset the position to the initial position
		virtual void reset_position() = 0;

};