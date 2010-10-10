#ifndef IMPDUNGEON_LOGIC_NETWORK_NETWORKERROR_H_
#define IMPDUNGEON_LOGIC_NETWORK_NETWORKERROR_H_

#include <stdexcept>

namespace impdungeon {

class NetworkError : public std::runtime_error {
 public:
  explicit NetworkError(const std::string &what_arg);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_NETWORKERROR_H_

