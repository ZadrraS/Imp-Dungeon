#ifndef IMPDUNGEON_LOGIC_NETWORK_EVENTS_VIEWUPDATEEVENT_H_
#define IMPDUNGEON_LOGIC_NETWORK_EVENTS_VIEWUPDATEEVENT_H_

#include "logic/network/events/playerevent.h"

namespace impdungeon {

class ViewUpdateEvent : public PlayerEvent {
 public:
  ViewUpdateEvent(boost::uuids::uuid &source, int width, int height);
  virtual ~ViewUpdateEvent();

  void Accept(EventVisitorInterface &event_visitor);

  int width() const;
  int height() const;

 private:
  int width_;
  int height_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_EVENTS_VIEWUPDATEEVENT_H_
