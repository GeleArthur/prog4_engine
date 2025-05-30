#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <SoundSystem/SoundSystemLocator.h>
#include <SoundSystem/SoundSystemLogger.h>
#include <SoundSystem/SoundSystemSDL3_Mixer.h>
#include <StumpEngine.h>

#include <Component/FpsShowCase.h>
#include "Component/TextDisplay.h"
#include "Component/Texture2D.h"
#include "Component/Transform.h"
#include "Components/Digger.h"
#include "Components/DirtDrawer.h"
#include "Components/GridWalls.h"
#include "GameObject.h"
#include "Components/GoldBag.h"
#include "Components/GridTransform.h"

#if defined(WIN32)
#include <windows.h>
#endif

void AllocateConsole()
{
#if defined(WIN32)
    if (AllocConsole()) // Allocate a new console for the application
    {
        FILE* fp; // Redirect STDOUT to the console
        freopen_s(&fp, "CONOUT$", "w", stdout);
        setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering for stdout

        freopen_s(&fp, "CONOUT$", "w", stderr); // Redirect STDERR to the console
        setvbuf(stderr, NULL, _IONBF, 0);       // Disable buffering for stderr

        freopen_s(&fp, "CONIN$", "r", stdin); // Redirect STDIN to the console
        setvbuf(stdin, NULL, _IONBF, 0);      // Disable buffering for stdin

        std::ios::sync_with_stdio(true); // Sync C++ streams with the console
    }
#endif
}

static void init_game(StumpEngine& engine)
{
    GameObject& fps_display = engine.add_game_object();
    fps_display.get_transform().set_local_position(glm::vec2{ 0, 0 });
    fps_display.add_component<TextDisplay>("data/Lingua.otf", "", 10.0f);
    fps_display.add_component<FpsShowcase>();

    GameObject& gird = engine.add_game_object();
    gird.add_component<DirtDrawer>();
    auto& grid_handler = gird.add_component<GridWalls>();

    GameObject& gold_bag = engine.add_game_object();
    gold_bag.add_component<Texture2D>("data/money.png").draw_center(true).draw_size(3);
    GridTransform& gold_pos = gold_bag.add_component<GridTransform>(glm::ivec2{ 3, 0 });
    gold_bag.add_component<GoldBag>(grid_handler);

    GameObject& digger = engine.add_game_object();
    digger.add_component<Texture2D>("data/driller.png").draw_center(true);
    digger.add_component<GridTransform>();
    digger.add_component<Digger>(gold_pos);

    SoundSystemLocator::register_sound_system(
        std::make_unique<SoundSystemLogger>(std::make_unique<SoundSystemSDL3_Mixer>()));
}

int main(int, char*[])
{
    AllocateConsole();
    auto engine = StumpEngine{ init_game };
    engine.run();

    return 0;
}
