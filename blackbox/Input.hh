#ifndef INPUT_HH
#define INPUT_HH

/////////////////////////////////////////////////////////////////////////////////////////////////////
// External Headers
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>
#include <glm/glm.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Keyboard Interface
/////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Keyboard {

  enum class Key {
    // Number Line
    Num0 = SDLK_0, Num1 = SDLK_1, Num2 = SDLK_2, Num3 = SDLK_3, Num4 = SDLK_4,
    Num5 = SDLK_5, Num6 = SDLK_6, Num7 = SDLK_7, Num8 = SDLK_8, Num9 = SDLK_9,
    // Characters
    A = SDLK_a, B = SDLK_b, C = SDLK_c, D = SDLK_d, E = SDLK_e, F = SDLK_f, G = SDLK_g,
    H = SDLK_h, I = SDLK_i, J = SDLK_j, K = SDLK_k, L = SDLK_l, M = SDLK_m, N = SDLK_n,
    O = SDLK_o, P = SDLK_p, Q = SDLK_q, R = SDLK_r, S = SDLK_s, T = SDLK_t, U = SDLK_u,
    V = SDLK_v, W = SDLK_w, X = SDLK_x, Y = SDLK_y, Z = SDLK_z,
    // Arrows
    Down = SDLK_DOWN, Left = SDLK_LEFT, Right = SDLK_RIGHT, Up = SDLK_UP,
    // Function Keys
    F1 = SDLK_F1, F2 = SDLK_F2, F3 = SDLK_F3, F4 = SDLK_F4, F5 = SDLK_F5, F6 = SDLK_F6,
    F7 = SDLK_F7, F8 = SDLK_F8, F9 = SDLK_F9, F10 = SDLK_F10, F11 = SDLK_F11, F12 = SDLK_F12,
    // Miscellaneous Keys
    Backslash = SDLK_BACKSLASH, Backspace = SDLK_BACKSPACE, Capslock = SDLK_CAPSLOCK,
    Delete = SDLK_DELETE, End = SDLK_END, Equals = SDLK_EQUALS, Escape = SDLK_ESCAPE,
    Backquote = SDLK_BACKQUOTE, Home = SDLK_HOME, LeftAlt = SDLK_LALT, LeftControl = SDLK_LCTRL,
    LeftBracket = SDLK_LEFTBRACKET, LeftShift = SDLK_LSHIFT, Minus = SDLK_MINUS,
    PageDown = SDLK_PAGEDOWN, PageUp = SDLK_PAGEUP, Period = SDLK_PERIOD, RightAlt = SDLK_RALT,
    RightControl = SDLK_RCTRL, Return = SDLK_RETURN, RightBracket = SDLK_RIGHTBRACKET,
    RightShift = SDLK_RSHIFT, SemiColon = SDLK_SEMICOLON, Slash = SDLK_SLASH, Space = SDLK_SPACE,
    Tab = SDLK_TAB
  };

  bool                   IsKeyPressed(Key p_key);
  bool                   IsKeyPressed(SDL_Scancode p_scancode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Mouse Interface
/////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Mouse {

  enum class Button {
    Left   = SDL_BUTTON_LEFT,
    Middle = SDL_BUTTON_MIDDLE,
    Right  = SDL_BUTTON_RIGHT,
    Extra1 = SDL_BUTTON_X1,
    Extra2 = SDL_BUTTON_X2
  };

  bool                   IsButtonPressed(Button p_button);

  glm::ivec2             GetPosition();
  glm::ivec2             GetRelativePosition();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // INPUT
