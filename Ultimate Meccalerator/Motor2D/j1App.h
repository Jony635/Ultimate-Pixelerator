#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2SString.h"
#include "SDL\include\SDL_rect.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"


// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1FileSystem;
class j1Scene;
class j1Map;
class j1Player;
class j1PathFinding;
class j1Enemies;



struct j1Rect
{
	SDL_Rect rec;
	bool Collides(j1Rect);
};

enum Levels
{
	FIRST_LEVEL = 0,
	SECOND_LEVEL
};

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(p2List<p2SString>& list_to_fill) const;

	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	void RestartScene()const;
	char* GetBoolString(const bool b) const;

private:

	// Load config file
	

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;



public:

	// Modules
	j1Window*			win				=	nullptr;
	j1Input*			input			=	nullptr;
	j1Render*			render			=	nullptr;
	j1Textures*			tex				=	nullptr;
	j1Audio*			audio			=	nullptr;
	j1Scene*			scene			=	nullptr;
	j1FileSystem*		fs				=	nullptr;
	j1Map*				map				=	nullptr;
	j1Player*			player			=	nullptr;
	j1PathFinding*		pathfinding		=	nullptr;
	j1Enemies*			enemies			=	nullptr;

private:

	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	p2SString			load_game;
	mutable p2SString	save_game;

	j1Timer				last_sec_frame_time;
	uint32				prev_last_sec_frame_count = 0;
	uint32				last_sec_frame_count = 0;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1PerfTimer			dt_timer;

	uint32				framerate_cap;

	bool				cap_on = false;
	bool				vsync_on = false;

public:
	Levels actual_lvl = Levels::FIRST_LEVEL;
};

extern j1App* App; // No student is asking me about that ... odd :-S

#endif