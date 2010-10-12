#ifndef IMPDUNGEON_LOGIC_NETWORK_MESSAGES_MESSAGEVISITORINTERFACE_H_
#define IMPDUNGEON_LOGIC_NETWORK_MESSAGES_MESSAGEVISITORINTERFACE_H_

namespace impdungeon {

class OkMessage;
class ErrorMessage;
class EntityDataMessage;
class ItemDataMessage;
class ViewUpdateMessage;

class MessageVisitorInterface {
 public:
  virtual void Visit(OkMessage &ok_message) = 0;
  virtual void Visit(ErrorMessage &error_message) = 0;
  virtual void Visit(EntityDataMessage &entity_data_message) = 0;
  virtual void Visit(ItemDataMessage &item_data_message) = 0;
  virtual void Visit(ViewUpdateMessage &view_update_message) = 0;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_LOGIC_NETWORK_MESSAGES_MESSAGEVISITORINTERFACE_H_

