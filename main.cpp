#include <iostream>
#include <map>
#include <cstring>

using namespace std;

map<string, string> dictionary;

void set_key_value(string key, string value) {
	if (!dictionary.insert(pair<string, string>(key, value)).second)
		dictionary.find(key)->second = value;
	cout << "OK" << endl;
}

string get_key(string key) {
	auto itr = dictionary.find(key);
	if (itr != dictionary.end())
		return ("\"" + itr->second + "\"");
	else
		return ("(nil)");
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

int main() {
	cout << "set-get-del functions" << endl;
}