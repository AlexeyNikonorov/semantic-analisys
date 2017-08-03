#ifndef VOCABULARY_HPP
#define VOCABULARY_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <unordered_map>
#include <stdexcept>
#include "wordstream.hpp"

using namespace std;

class Vocabulary {
public:
	struct Item {
		size_t occ[2];
		double tf[2];
		size_t df;
		Item() { occ[0] = occ[1] = 0; tf[0] = tf[1] = 0.0; df = 0; }
	};
	unordered_map<string, Item> _dict;
	size_t _y_dist[2];
	size_t _total;
	
public:
	Vocabulary() {
		_y_dist[0] = _y_dist[1] = 0;
		_total = 0;
	}
	
	void feed(const string& text, int cls) {
		WordStream ws(text);
		unordered_map<string, int> occurrence;
		int total = 0;
		string word;
		while (ws.iterate(word)) {
			occurrence[word]++;
			total++;
		}
		for (auto& item : occurrence) {
			auto& i = _dict[item.first];
			i.occ[cls] += item.second;
			i.tf[cls] += (double) item.second / total;
			i.df++;
		}
		_y_dist[cls]++;
		_total++;
	}
	
	double tfidf(const string& word, int cls) const {
		try {
			auto& item = _dict.at(word);
			double idf = log((_total + 1.0) / (item.df + 1.0)) + 1.0;
			return item.tf[cls] * idf;
		} catch (out_of_range& err) {
			return 0.0;
		}
	}
	
	double dist(int cls) const { return (double) _y_dist[cls] / _total; }
	
	int size() const { return _dict.size(); }
	
	const unordered_map<string, Item>& dict() const { return _dict; }
};

#endif
