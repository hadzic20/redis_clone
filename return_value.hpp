#pragma once
#include <string>

using namespace std;

class ReturnValue {
 protected:
  string kind;
  string message;

 public:
    string form_message() {
    string return_message = "";
    if (kind == "error") {
      return_message += "-";
    } else if (kind == "string") {
      return_message += "+";
    } else if (kind == "integer") {
      return_message += ":";
    } else if (kind == "array") {
      return_message += "*";
    } else if (kind == "bulk_string") {
      return_message += "$";
    }
    return_message += message;
    return_message += "\r\n";
    return (return_message);
  }
};

class Error : public ReturnValue {
 public:
  Error(string value) {
    kind = "error";
    message = value;
  }

};

class MyString : public ReturnValue {
 public:
  MyString(string value) {
    kind = "string";
    message = value;
  }
};

class Integer : public ReturnValue {
 public:
  Integer(string value) {
    kind = "integer";
    message = value;
  }
};

class Array : public ReturnValue {
 public:
  Array(string value) {
    kind = "array";
    message = value;
  }
};

class BulkString : public ReturnValue {
 public:
  BulkString(string value) {
    kind = "bulk_string";
    message = value;
  }
};