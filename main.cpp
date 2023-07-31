#include <iostream>
#include <sstream>
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

void repl() {
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
		if (query == "q")
			break;
		if (query == "")
			continue;
		if (value[0] != '"' && buff >> temp)
			cout << "(error) ERR Syntax error" << endl;
		else if (!query.compare("set")) {
			if (value[0] == '"') {
				while (buff >> temp) {
					value += " ";
					value += temp;
				}
				value = value.substr(1, value.length() - 2);
			}
			set_key_value(key, value);
		}
		else if (!query.compare("get")) {
			cout << get_key(key) << endl;
		}
		else if (!query.compare("del")) {
			del_key(key);
		}
		else {
			cout << "(error) I'm sorry, I don't recognize that command" << endl;
		}
	}
}

int main() {
	repl();
}