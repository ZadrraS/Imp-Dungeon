#include "logic/loaders/malformeddata.h"

namespace impdungeon {

MalformedData::MalformedData(const std::string &what_arg)
  : std::runtime_error(what_arg) {
  
}

}  // namespace impdungeon
