#include "logic/network/events/event.h"

namespace impdungeon {

Event::Event() : descriptor_(-1) {

}

Event::~Event() {

}

void Event::set_descriptor(int descriptor) {
  descriptor_ = descriptor;
}

int Event::descriptor() const {
  return descriptor_;
}

}  // namespace events

