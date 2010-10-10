#include "logic/network/networkerror.h"

namespace impdungeon {

NetworkError::NetworkError(const std::string &what_arg)
  : std::runtime_error(what_arg) {
  
}

}  // namespace impdungeon


