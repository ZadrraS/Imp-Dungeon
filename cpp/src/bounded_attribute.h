#ifndef IMPDUNGEON_BOUNDED_ATTRIBUTE_H_
#define IMPDUNGEON_BOUNDED_ATTRIBUTE_H_

namespace impdungeon {

/*-------------------
* Used to represent entity statistics like health.
---------------------*/
class BoundedAttribute {
  public:
    explicit BoundedAttribute(int value);
    BoundedAttribute(int value, int bound);
    virtual ~BoundedAttribute();

    int value();
    int bound();

    BoundedAttribute operator+(int arg);
    BoundedAttribute operator-(int arg);
    BoundedAttribute &operator+=(int arg);
    BoundedAttribute &operator-=(int arg);
    BoundedAttribute &operator=(int arg);

  private:
    int value_;
    int bound_;
};

}  // namespace impdungeon

#endif  // IMPDUNGEON_BOUNDEDATTRIBUTE_H_

