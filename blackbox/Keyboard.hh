#ifndef KEYBOARD_HH
#define KEYBOARD_HH

/////////////////////////////////////////////////////////////////////////////////////////////////////
// External Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Keyboard Interface
/////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Keyboard {

  bool IsKeyPressed(SDL_Keycode p_keycode);
  bool IsKeyPressed(SDL_Scancode p_scancode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // KEYBOARD
