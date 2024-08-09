#ifndef LITERALH
#define LITERALH

#include <iostream>
#include <string>

class LiteralData {
public:
  enum DataType {
    INT,
    STRING,
    EMPTY
  };

  DataType type;
  void* value;

  LiteralData(void* value, DataType type): value(value), type(type) {}
  LiteralData(): value(NULL), type(EMPTY) {}
};

#endif
