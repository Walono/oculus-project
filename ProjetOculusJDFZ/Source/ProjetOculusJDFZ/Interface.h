/**
 * Bachelor Project: Development and Implementation of 
 * an Oculus Rift Frontend for Audio-Visual VR Applications
 *  Interface
 *  Purpose: The Interface contains all the method we need to generate
 *  our environment in the engine
 *  @author Julie Djeffal & Fabien Zellweger
*/

#pragma once
#include<list>
#include<vector>
#include<string>

class Interface {

	public:
		
		virtual ~Interface() {};

		/**
     		* Add a Face to the Library
     		* @param The caracteristics of a Face
     		*/
		virtual void add_face(std::list<float> position, 
			std::list<std::list<float>> coordinates, 
			int texture, int faceId) = 0;
		
		/**
     		* Remove a Face from the Library
     		* @param The id of the Face
     		*/
		virtual void remove_face(int faceId) = 0;
		
		/**
     		* Modifiy the position of a Face in the Library
     		* @param The new position and rotation of a Face and its ID
     		*/
		virtual void move_face(std::list<float> translationVector, 
			std::list<float> rotation, int faceId) = 0;
		
		/**
     		* Add a Sound source to the Library
     		* @param The caracteristic of a Sound source
     		*/
		//Add a sound source to the environment
		virtual void add_sound_source(std::string name, 
			std::list<float> position, 
			std::vector<float> viewDirection, 
			std::vector<float> upDirection, int sourceId) = 0;
		
		/**
     		* Remove a Sound source from the Library
     		* @param The Sound source ID
     		*/
		virtual void remove_sound_source(int sourceId) = 0;
		
		/**
     		* Move a Sound source in the Library
     		* @param The new positions caracteristics 
			* of the Sounf source and its ID
     		*/
		virtual void move_source(std::list<float> translationVector,
			std::vector<float> newViewDirection,
			std::vector<float> newUpDirection, int sourceId) = 0;
		
		/**
     		* Enable or disable the sound of a source sound
     		* @param The Sound source ID
     		*/
		virtual void enable_sound(bool enable, int sourceId) = 0;
		
		/**
     		* Set the initial position of the player
     		* @param the position
     		*/
		virtual void set_initial_position(std::list<float> position) = 0;

		/**
     		* Reset the position to the initial position
     		*/
		virtual void reset_position() = 0;

};
