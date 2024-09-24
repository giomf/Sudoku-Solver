#ifndef FIELD_H
#define FIELD_H

class Field {
 private:
  int value;

 public:
  Field() : value(0) {};
  Field(const int value) : value(value) {};
  int getValue() const { return value; };
};

#endif  // FIELD_H
