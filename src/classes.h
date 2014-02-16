
#include <vector>
#include <cstddef>
#include <SFML/Graphics.hpp>

#ifndef _CLASSES_
#define _CLASSES_

#define TILE_SIZE 64
#define BOARD_SIZE 10

using namespace std;

class Game;
class Board;
class Tile;
class Worker;
class Resource;
class Base;
class PathSegment;
class Pos;
class Assets;
class Mouse;

extern Assets * assets;
extern Game * game;

class Pos
{
public:
	int x;
	int y;
};


class Game
{
public:
	Game(Board * board);
	~Game();
	bool Active();
	void Animate();
	void Reset();
	void ResetPaths();
	int priority;
	int speed;
	bool paused;
private:
	Board * board;
	int frame;

};

class GameMouse
{
public:
	GameMouse(Tile *** tiles_);
	~GameMouse();
	void Click();
	void Release();
	void NewFrame();
	void draw();
private:
	void CreateTempPathSegment(bool replace);
	void MakeTempPathSegmentReal();
	Tile * GetTileFromMouse();
	Tile * GetTileFromPix(int pix_x, int pix_y);
	bool MouseOnScreen();

	Tile *** tiles;
	Tile * last_locked_tile;
	Tile * current_tile;
	PathSegment * tempPathSegment;
	bool drawing;
};

class Assets
{
public:
	Assets();
	~Assets();
	void setWindow(sf::RenderWindow * window_);
	sf::Texture * tile_texture;
	sf::Texture * arrow_texture;
	sf::Texture * diagonal_arrow_texture;
	sf::Texture * worker_texture;
	sf::Texture * base_texture;
	sf::Texture * resource_texture;
	sf::Texture * resource_depleted_texture;
	sf::Texture * stop_texture;
	sf::Texture * pause_texture;
	sf::Texture * play_texture;
	sf::Texture * fast_texture;
	sf::Texture * delete_texture;
	sf::RenderWindow * window;
};

class Board
{
public:
	Board(int seed, bool tutorial);
	~Board();
	void draw();
	void MoveWorkers();
	void ResetWorkers();
	void ResetResources();
	void DeletePaths();
	Tile *** tiles;
private:
	vector<Worker *> workers;
	vector<Base *> bases;
	vector<Resource *> resources;
};

class Tile
{
public:
	Tile(int x, int y, Tile *** tiles_);
	~Tile();
	void draw();
	void draw_arrows();
	void draw_base();
	void draw_worker();
	void draw_resource();
	Tile * PathForward();
	Tile * PathBackward();
	bool empty();
	void addResource(Resource * to_add);
	void addBase(Base * to_add);
	void addWorker(Worker * to_add);
	void removeWorker();
	void clearPathFrom(int priority);
	void clearPathTo(int priority);
	Pos pos;
	PathSegment ** dirs;
	Base * base;
	Resource * resource;
	Worker * worker;
private:
	Tile *** tiles;
	sf::Sprite sprite;
};

class PathSegment
{
public:
	PathSegment(Tile * from_, Tile * to_, int priority_);
	~PathSegment();
	void draw();
	int priority;
	Tile * from;
	Tile * to;
private:
	sf::Sprite sprite;
};

class Worker
{
public:
	Worker(int x, int y, Tile *** tiles);
	~Worker();
	void draw();
	void Move();
	void Reset();
private:
	bool empty;
	float lerp;
	Tile * start_pos;
	Tile * from;
	Tile * to;
	Tile *** tiles;
	float speed;
	sf::Sprite sprite;

};

class Resource
{
public:
	Resource(int x, int y, Tile *** tiles);
	~Resource();
	bool Depleted();
	void draw();
	void Mine();
	void Reset();
private:
	Tile * tile;
	float drag;
	Tile *** tiles;
	int loads;
	sf::Sprite sprite_normal;
	sf::Sprite sprite_depleted;
};

class Base
{
public:
	Base(int x, int y, Tile *** tiles_);
	~Base();
	void draw();
private:
	Tile * tile;
	Tile *** tiles;
	sf::Sprite sprite;
};

class UI
{
public:
	UI();
	~UI();
	void draw();
	void click();
private:
	void PressStop();
	void PressPause();
	void PressPlay();
	void PressFast();
	void PressPriority1();
	void PressPriority2();
	void PressPriority3();
	void PressDelete();
	sf::Sprite stop;
	sf::Sprite pause;
	sf::Sprite play;
	sf::Sprite fast;

	sf::Sprite priority1;
	sf::Sprite priority2;
	sf::Sprite priority3;

	sf::Sprite deletebutton;
};

#endif