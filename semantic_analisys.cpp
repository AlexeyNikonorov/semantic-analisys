#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "wordstream.hpp"
#include "vocabulary.hpp"
#include "mnb.hpp"

int main() {	
	cout << "Training...\n";
	string data_path("movies_data.txt");
	string target_path("movies_target.txt");

	vector<string> data;
	vector<int> target;
	
	ifstream ifs1(data_path);
	string text;
	while (getline(ifs1, text))
		data.push_back(text);
	ifs1.close();
	
	ifstream ifs2(target_path);
	int y;
	while (ifs2 >> y)
		target.push_back(y);
	ifs2.close();
	
	int ntrain = data.size();
	
	Vocabulary v;
	for (int i = 0; i < ntrain; i++)
		v.feed(data[i], target[i]);
	cout << "Done\n";
	
	cout << "Enter text: ";
	while (getline(cin, text)) {
		switch (MNB::predict(text, v)) {
			case 0:
				cout << "\n\"Negative\"\n";
				break;
			case 1:
				cout << "\n\"Positive\"\n";
				break;
		}
		cout << "Enter text: ";
	}
	return 0;
}
