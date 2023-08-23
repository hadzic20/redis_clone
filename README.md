# REDIS CLONE

Redis (**RE**mote **DI**ctionary **S**ervice) is a popular open-source in-memory storage which is used by well-known companies such as Twitter, Amazon and Yahoo. It supports a wide range of data types and is great for usage as cache or message broker.

Redis was firstly implemented in C language, and I tried to make a mini edition of Redis using c++. I implemented many different topics that I theoretically learned in school such as:
- basic algorithm design
- data structures
- OOP bacics encapsulation and inheritence
- socket programming

In this project, [ASIO](https://think-async.com/Asio/index.html) library was used for networking. In order to being able to run the project, ASIO library must be downloaded and set up first.

This project creates three executables:
* ```redis```: Executable that works standalone, does not require ASIO and does not contain networking.
* ```server```: Executable that works as the server of storage, the part that performs the commands.
* ```client```: Executable that end user uses, only provides an interface and displays informations coming from server.

Once ASIO is set up, Makefile may be used to easily build and run the project. Here are the commands and respective functions of them:
* ```make```, ```make all```: Build executables ```redis```, ```server``` and ```client```.
* ```make server```: Build executable ```server```.
* ```make client```: Build executable ```client```.
* ```make clean```: Remove executable ```redis```.
* ```make cleancs```: Remove executables ```server``` and ```client```.
* ```make fclean```: Remove all executables.
* ```make re```: Remove executable ```redis``` and build it again.
* ```make recs```: Remove executables ```server``` and ```client``` and build them again.


In this project, only two data types were implemented: string and list. Here are the commands used to manipulate them:
* ```set```: A string command that sets a value to a key if it does not exist or changes the value of key if it exists. Takes two parameters: key and value.

  Example: set best_employee a
* ```get```: A string command that returns the value stored in a key. Takes one parameter: key.

  Example: get best_employee
* ```del```: A string and list command that deletes the key. Takes one parameter: key.

  Example: del best_employee
* ```lpush```: A list command that pushs the value to the front of the list. Takes two or more parameters: a list name and one or more values.

  Example: lpush employees a b c
* ```rpush```: A list command that pushs the value to the back of the list. Takes two or more parameters: a list name and one or more values.

  Example: rpush employees a b c
* ```lpop```: A list command that returns the value on the front of the list and discards it. Takes one parameter: list name.

  Example: lpop employees
* ```rpop```: A list command that returns the value on the back of the list and discards it. Takes one parameter: list name.

  Example: rpop employees
* ```lindex```: A list command that return the value stored on the given index of list. Takes two parameters: list name and index.

  Example: lindex employees 1
* ```lset```: A list command that sets the given value to given index of list. Takes three parameters: list name, index and value.

  Example: lset employees 2 a
* ```llen```: A list command that returns the number of elements stored in the list. Takes one parameter: list name.

  Example: llen employees
* ```lrange```: A list command that returns values stored in each index of list between given indices. Takes three parameters: list name, start index and end index.

  Example: lrange employees 1 3
