#include <iostream>
#include <sstream>
#include <map>
#include <cstring>

using namespace std;

class Store {
	map<string, string> dictionary;
	
public:
	void set_key_value(string key, string value) {
		if (!dictionary.insert(pair<string, string>(key, value)).second)
			dictionary.find(key)->second = value;
		cout << "OK" << endl;
	}
	void get_key(string key) {
		auto itr = dictionary.find(key);
		if (itr != dictionary.end())
			cout << ("\"" + itr->second + "\"") << endl;
		else
			cout << ("(nil)") << endl;
	}

	void del_key(string key) {
		if (dictionary.find(key) != dictionary.end()) {
			dictionary.erase(key);
			cout << "(integer) 1" << endl;
		}
		else {
			cout << "(nil)" << endl;
		}
	}
};

int function_mapper(Store *store, string query, string key, string value) {
	if (!query.compare("q"))
		return (1);
	else if (!query.compare(""))
		return (2);
	else {
		if (!query.compare("set"))
			store->set_key_value(key, value);
		else if (!query.compare("get"))
			store->get_key(key);
		else if (!query.compare("del"))
			store->del_key(key);
		else
			cout << "(error) I'm sorry, I don't recognize that command" << endl;
		return (0);
	}
}

void repl() {
	Store store;
	while (1) {
		string line;
		string query;
		string key;
		string value;
		string temp;
		stringstream buff;
		cout << "> ";
		getline(cin, line);
		buff << line;
		buff >> query >> key >> value;
		int tmp = function_mapper(&store, query, key, value);
		if (tmp == 1)
			break;
		if (tmp == 2)
			continue;
		if (value[0] != '"' && buff >> temp)
			cout << "(error) ERR Syntax error" << endl;
		
	}
}

int main() {
	repl();
}