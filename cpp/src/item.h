#ifndef IMPDUNGEON_ITEM_H_
#define IMPDUNGEON_ITEM_H_

#include <boost/uuid/uuid.hpp>

#include "entity.h"

namespace impdungeon {

/*-------------------
* The Item class is the base class for all items in the game.
---------------------*/
class Item {
  public:
    Item(const boost::uuids::uuid &id, const std::string &name, int value, 
         bool equipable, bool usable);
    virtual ~Item();

    virtual void Equip(Entity &entity) = 0;
    virtual void Use(Entity &entity) = 0;

    const boost::uuids::uuid &id() const;
    const std::string &name() const;
    int value() const;
    bool equipable() const;
    bool usable() const;
    
  private:
    boost::uuids::uuid id_;
    std::string name_;
    int value_;

    bool equipable_;
    bool usable_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_ITEM_H_
