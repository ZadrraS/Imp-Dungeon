#ifndef IMPDUNGEON_LOGIC_LOADERS_MALFORMEDDATA_H_
#define IMPDUNGEON_LOGIC_LOADERS_MALFORMEDDATA_H_

#include <stdexcept>

namespace impdungeon {

class MalformedData : public std::runtime_error {
 public:
  explicit MalformedData(const std::string &what_arg);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_LOADERS_MALFORMEDDATA_H_
