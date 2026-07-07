#include <cstdint>
#include <functional>
#include <raylib.h>
#include <vector>
#include <map>

static const int screenWidth = 720;
static const int screenHeight = 720;

static RenderTexture2D target = { 0 };  // Render texture to render our game
static int frameCounter = 0;

using DescriptorType = const uint64_t;

struct Game;

extern Game *g_global;

struct State
{
	void handle_input();
	void update();
	void draw();
};

struct GameState : State
{
	void handle_input();
	void update(float dt);
	void draw();
};

struct MenuState : State
{
	void handle_input();
	void update(float dt);
	void draw();
};

struct LogoState : State
{
	void handle_input();
	void update(float dt);
	void draw();
};

struct Game
{
	void init();
	void handle_input();
	void update(float dt);
	void draw();
	void deinit();
};

struct Event
{
	virtual ~Event();
	virtual DescriptorType type() = 0;
};

using SlotType = std::function<const Event&>;

struct Dispatcher
{
	void subscribe(const DescriptorType &descriptor, SlotType &&slot);
	void post(const Event& event) const;

	std::map<DescriptorType, std::vector<SlotType>> observers;
};
