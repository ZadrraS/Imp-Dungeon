#include "client/inputmanager.h"

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

namespace impdungeon {
namespace client {

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

ActionType InputManager::GetInput() {
  struct termios old_terminal;
  struct termios new_terminal;
  tcgetattr(STDIN_FILENO, &old_terminal);
  new_terminal = old_terminal;
  new_terminal.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);
  char input = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
  
  ActionType action;
  switch (input) {
    case 'w': {
      action = kUp;
      break;
    }
    case 's': {
      action = kDown;
      break;
    }
    case 'd': {
      action = kRight;
      break;
    }
    case 'a': {
      action = kLeft;
      break;
    }
    case 'l': {
      action = kLook;
      break;
    }
    default: {
      action = kOther;
      break;
    }
  }

  return action;
}

}  // namespace client
}  // namespace impdungeon
