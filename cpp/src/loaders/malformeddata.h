#ifndef IMPDUNGEON_LOADER_MALFORMEDDATA_H_
#define IMPDUNGEON_LOADER_MALFORMEDDATA_H_

#include <stdexcept>

namespace impdungeon {

class MalformedData : public std::runtime_error {
 public:
  explicit MalformedData(const std::string &what_arg);
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOADER_MALFORMEDDATA_H_
