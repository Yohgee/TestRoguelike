#include <SDL.h>
#include <libtcod.hpp>
#include "Engine.hpp"
#include "Actor.hpp"
#include "Map.hpp"

auto get_data_dir() -> std::filesystem::path {
  static auto root_directory = std::filesystem::path{"."};  // Begin at the working directory.
  while (!std::filesystem::exists(root_directory / "data")) {
    // If the current working directory is missing the data dir then it will assume it exists in any parent directory.
    root_directory /= "..";
    if (!std::filesystem::exists(root_directory)) {
      throw std::runtime_error("Could not find the data directory.");
    }
  }
  return root_directory / "data";
};

Engine engine;

int main(int argc, char* argv[]) {
  auto console = tcod::Console{80, 64};  // Main console.

  // Configure the context.
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;  // This is required.
  params.console = console.get();  // Derive the window size from the console size.
  params.window_title = "Roguelike";
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.vsync = true;
  params.argc = argc;  // This allows some user-control of the context.
  params.argv = argv;

  // Tileset example using a Code Page 437 font.
  // "terminal8x8_gs_ro.png" must be in the working directory.
  auto tileset = tcod::load_tilesheet(get_data_dir() / "terminal8x8_gs_ro.png", {16, 16}, tcod::CHARMAP_CP437);
  params.tileset = tileset.get();

  auto context = tcod::Context(params);

  std::printf("begin");

  while (true) {  // Game loop.
    console.clear();
    
    tcod::print(console, {0, 0}, "UNYUN", std::nullopt, std::nullopt);
    engine.update();
    engine.render(console.get());

    context.present(console);  // Updates the visible display.

    

    SDL_Event event;
    SDL_WaitEvent(nullptr);  // Optional, sleep until events are available.
    while (SDL_PollEvent(&event)) {
      context.convert_event_coordinates(event);  // Optional, converts pixel coordinates into tile coordinates.
      SDL_PushEvent(&event);
      switch (event.type) {
        case SDL_QUIT:
          return 0;  // Exit.
      }
    }
  }
}