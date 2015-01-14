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

	/* Concerning the faces */
	virtual void add_face(std::list<float> position,
		std::list<std::list<float>> coordinates, int texture, int faceId);

	// Remove a face from the Environment
	virtual void remove_face(int faceId);

	/**Move a face in the Environment with translation of position */
	//rotation list with (Pitch, Yaw, Roll)
	virtual void move_face(std::list<float> translationVector, std::list<float> rotation, int faceId);

	 /* Concerning the sound sources */ 
	//Add a sound source to the environment
	virtual void add_sound_source(std::string name,
		std::list<float> position,
		std::vector<float> viewDirection,
		std::vector<float> upDirection, int sourceId);

	// Remove a sound source from the environment
	virtual void remove_sound_source(int sourceId);

	// Move a source sound from the environment
	virtual void move_source(std::list<float> translationVector,
		std::vector<float> newViewDirection,
		std::vector<float> newUpDirection, int sourceId);

	// Enable or disable the sound of a source sound
	virtual void enable_sound(bool enable, int sourceId);

	 /* Concerning the global environment*/
	// Set the initial position 
	virtual void set_initial_position(std::list<float> position);

	// Get the initial position
	virtual std::list<float> getInitialPosition();

	// Reset the position to the initial position
	virtual void reset_position();
	void setResetActivity(bool resetActivity);
	bool getResetActivity();

	/* Concerning a Polyhedron */

	void addPolyhedron(std::list<int> facesId, int polyhedronId);

	void removePolyhedron(int polyhedronId);

	/* Concerning a scene */

	void addScene(int sceneId, std::list<int> objectsId);

	void removeScene(int sceneId);

	/* Concerning the Faces*/

	Face* getNextFaceToSpawn();
	bool isFacesToSpawnEmpty();
	void deleteFaceSpawned();
	Face* getNextFaceToMove();
	bool isFacesToMoveEmpty();
	void deleteFaceMoved();
	bool isInTArray(TArray<int> faces, int id);
	int getNextFaceIdToDelete();
	bool isFacesToDeleteEmpty();
	void deleteFaceDeleted();

	/* Concerning the Sound*/

	Sound* getNextSoundToSpawn();
	bool isSoundToSpawnEmpty();
	void deleteSoundSpawned();
	Sound* getNextSoundToMove();
	bool isSoundToMoveEmpty();
	void deleteSoundMoved();
	int getNextSoundIdToDelete();
	bool isSoundToDeleteEmpty();
	void deleteSoundDeleted();
	Sound* getNextSoundIdToEnable();
	bool isSoundToEnableEmpty();
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

