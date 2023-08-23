#pragma once
#include <string>

using namespace std;

class ReturnValue {
 protected:
  string kind;
  string message;

 public:
  string getMessage() { return (message); }
  virtual string form_message() { return (NULL); }
};

class Error : public ReturnValue {
 public:
  Error(string value) {
    kind = "error";
    message = value;
  }
  string form_message() {
    string return_message = "";
    return_message += "-";
    return_message += message;
    return_message += "\r\n";
    return (return_message);
  }
};

class MyString : public ReturnValue {
 public:
  MyString(string value) {
    kind = "string";
    message = value;
  }
  string form_message() {
    string return_message = "";
    return_message += "+";
    return_message += message;
    return_message += "\r\n";
    return (return_message);
  }
};

class Integer : public ReturnValue {
 public:
  Integer(string value) {
    kind = "integer";
    message = value;
  }
  string form_message() {
    string return_message = "";
    return_message += ":";
    return_message += message;
    return_message += "\r\n";
    return (return_message);
  }
};

class Array : public ReturnValue {
 public:
  Array(string value) {
    kind = "array";
    message = value;
  }
  string form_message() {
    string return_message = "";
    return_message += "*";
    return_message += message;
    return_message += "\r\n";
    return (return_message);
  }
};

class BulkString : public ReturnValue {
 public:
  BulkString(string value) {
    kind = "bulk_string";
    message = value;
  }
  string form_message() {
    string return_message = "";
    return_message += "$";
    return_message += message;
    return_message += "\r\n";
    return (return_message);
  }
};