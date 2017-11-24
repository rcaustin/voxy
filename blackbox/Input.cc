#include "Input.hh"


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Keyboard Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Keyboard {

  bool IsKeyPressed(Key p_key) {

    SDL_Scancode scancode = SDL_GetScancodeFromKey((SDL_Keycode)p_key);
    return (SDL_GetKeyboardState(NULL))[scancode];
  }

  bool IsKeyPressed(SDL_Scancode p_scancode) {

    return (SDL_GetKeyboardState(NULL))[p_scancode];
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Mouse Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Mouse {

  bool IsButtonPressed(Button p_button) {

    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON((Uint8)p_button);
  }

  glm::ivec2 GetPosition() {

    int x, y;
    SDL_GetGlobalMouseState(&x, &y);
    return {x, y};
  }

  glm::ivec2 GetRelativePosition() {

    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    return {x, y};
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////