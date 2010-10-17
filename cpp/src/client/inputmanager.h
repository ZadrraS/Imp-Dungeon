#ifndef IMPDUNGEON_CLIENT_INPUTMANAGER_H_
#define IMPDUNGEON_CLIENT_INPUTMANAGER_H_

namespace impdungeon {
namespace client {

enum ActionType {
  kOther,
  kUp,
  kDown,
  kLeft,
  kRight,
  kLook,
  kAttack,
  kConfirm,
  kQuit
};

class InputManager {
 public:
  InputManager();
  virtual ~InputManager();

  ActionType GetInput();
};

}  // namespace client
}  // namespace impdungeon

#endif  // IMPDUNGEON_CLIENT_INPUTMANAGER_H_
