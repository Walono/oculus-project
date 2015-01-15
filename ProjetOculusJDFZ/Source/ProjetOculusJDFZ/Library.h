
/**
* Bachelor Project: Development and Implementation of an Oculus Rift Frontend for Audio-Visual VR Applications
* FakeServer
* Purpose: It's a storage manager for all our environment. 
* Every Objects, Scene, Sound sources created, deleted or 
* moved are stored in the Library.  
* It also contains all the information about the status 
* of the object in the engine: if they have been spawned 
* or not in the level
* 
* @author Julie Djeffal & Fabien Zellweger
*/

#pragma once
#include"Interface.h"
#include"Face.h"
#include"Polyhedron.h"
#include"Scene.h"
#include"Sound.h"
#include<list>
#include<vector>
#include<string>
#include<map>
#include"Runtime/Core/Public/Containers/Array.h"

class Library : public virtual Interface
{
public:
	/* Get the Library */
	static Library * getLibrary();

	virtual void add_face(std::list<float> position,
		std::list<std::list<float>> coordinates, int texture, int faceId);

	virtual void remove_face(int faceId);

	virtual void move_face(std::list<float> translationVector, std::list<float> rotation, int faceId);

	virtual void add_sound_source(std::string name,
		std::list<float> position,
		std::vector<float> viewDirection,
		std::vector<float> upDirection, int sourceId);

	virtual void remove_sound_source(int sourceId);

	virtual void move_source(std::list<float> translationVector,
		std::vector<float> newViewDirection,
		std::vector<float> newUpDirection, int sourceId);

	virtual void enable_sound(bool enable, int sourceId);

	virtual void set_initial_position(std::list<float> position);

	virtual std::list<float> getInitialPosition();

	
	virtual void reset_position();
	
	/*
	* Set isResetActive
	* @param resetActivity the new status of isResetActive	
	*/
	void setResetActivity(bool resetActivity);
	
	/* Get isResetActive
	* return isResetActive
	*/
	bool getResetActivity();

	/*
	* Add a Polyhedron to the Library
	* @param the Polyhedron ID and the ID of its Faces
	*/
	void addPolyhedron(std::list<int> facesId, int polyhedronId);

	/*
	* Remove a Polyhedron from the Library
	* @param the Polyhedron ID 
	*/
	void removePolyhedron(int polyhedronId);

	/*
	* Add a Scene to the Library
	* @param the Scene ID and the ID of its Objects
	*/
	void addScene(int sceneId, std::list<int> objectsId);

	/*
	* Remove a Scene from the Library
	* @param the Scene ID 
	*/
	void removeScene(int sceneId);
	
	/*
	* Get the next Face to be Spwaned from facesToSPawn
	* @return a pointer to the Face
	*/
	Face* getNextFaceToSpawn();
	
	/*
	* Verify if the array facesToSpawn is empty
	* @return true if it's empty
	*/
	bool isFacesToSpawnEmpty();
	
	/*
	* Delete the Face spawned from facesToSpawn
	*/
	void deleteFaceSpawned();
	
	/*
	* Get the next Face to be moved from facesToMove
	* @return a pointer to the Face
	*/
	Face* getNextFaceToMove();
	
	/*
	* Verify if the array facesToMove is empty
	* @return true if it's empty
	*/
	bool isFacesToMoveEmpty();
	
	/*
	* Delete the Face moved from facesToMove
	*/
	void deleteFaceMoved();
	
	/*
	* Verify if a Face is in a Array
	* @param The id of the Face we want to verify 
	* and the Array we need to verify in
	* @return true if the Face is in the Array
	*/
	bool isInTArray(TArray<int> faces, int id);
	
	/*
	* Get the next Face ID to be deleted from facesToDelete
	* @return the ID of the Face
	*/
	int getNextFaceIdToDelete();
	
	/*
	* Verify if the array facesToDelete is empty
	* @return true if it's empty
	*/
	bool isFacesToDeleteEmpty();
	
	/*
	* Delete the Face deleted from facesToDelete
	*/
	void deleteFaceDeleted();


	/*
	* Get the next Sound to be spawned from soundToSPawn
	* @return a pointer to the Sound
	*/
	Sound* getNextSoundToSpawn();

	/*
	* Verify if the array soundToSpawn is empty
	* @return true if it's empty
	*/
	bool isSoundToSpawnEmpty();
	
		
	/*
	* Delete the Sound spawned from soundToSpawn
	*/
	void deleteSoundSpawned();
	
	/*
	* Get the next Sound to be moved from soundToMove
	* @return a pointer to the Sound
	*/
	Sound* getNextSoundToMove();
	
	/*
	* Verify if the array soundToMove is empty
	* @return true if it's empty
	*/
	bool isSoundToMoveEmpty();
	
	/*
	* Delete the Sound moved from soundToMove
	*/
	void deleteSoundMoved();
	
	
	/*
	* Get the next sound ID to be deleted from soundToDelete
	* @return the ID of the sound
	*/
	int getNextSoundIdToDelete();
	
	/*
	* Verify if the array soundToDelete is empty
	* @return true if it's empty
	*/
	bool isSoundToDeleteEmpty();
		
	/*
	* Delete the Sound deleted from soundToDelete
	*/
	void deleteSoundDeleted();
	
	/*
	* Get the next sound to be enable from soundToEnable
	* @return the sound
	*/
	Sound* getNextSoundIdToEnable();
	
	/*
	* Verify if the array soundToEnable is empty
	* @return true if it's empty
	*/
	bool isSoundToEnableEmpty();
	
	/*
	* Delete the Sound enabled from soundToEnable
	*/
	void deleteSoundEnabled();


private:

	static Library * _singletonInst;
	Library() {}
	Library(Library const&);
	void operator=(Library const&);

	std::list<float> initialPosition;
	// Set to false by the GameMode with BeginPlay()
	bool isResetActive;

	std::map<int, Scene> scenes;
	std::map<int, Polyhedron> polyhedrons;
	std::map<int, Face> faces;
	std::map<int, Sound> sounds;
	TArray<int> facesToSpawn;
	TArray<int> facesToMove;
	TArray<int> facesToDelete;
	TArray<int> soundToSpawn;
	TArray<int> soundToMove;
	TArray<int> soundToDelete;
	TArray<int> soundToEnable;

};

