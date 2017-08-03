#ifndef MNB_HPP
#define MNB_HPP

#include <string>
#include <unordered_map>
#include <cmath>
#include <stdexcept>
#include "wordstream.hpp"
#include "vocabulary.hpp"

struct MNB {	
	static int predict(const string& text, const Vocabulary& v) {
		WordStream ws(text);
		unordered_map<string, double[2]> x;
		string word;
		while (ws.iterate(word)) {
			x[word][0] = 1.0;
			x[word][1] = 1.0;
		}
		if (x.empty()) return -1;
		double alpha = 1.0, Ny[2] = { 0.0, 0.0 };
		for (auto& item : x) {
			try {
				auto& i = v._dict.at(item.first);
				double idf = log((v._total + 1.0) / (i.df + 1.0)) + 1.0;
				item.second[0] = i.tf[0] * idf;
				item.second[1] = i.tf[1] * idf;
				Ny[0] += item.second[0];
				Ny[1] += item.second[1];
			} catch (out_of_range& err) {}
		}
		double py[2] = { log(v.dist(0)), log(v.dist(1)) };
		double dnom[2] = { Ny[0] + v.size() * alpha, Ny[1] + v.size() * alpha };
		for (auto& item : x) {
			py[0] += log((item.second[0] + alpha) / dnom[0]);
			py[1] += log((item.second[1] + alpha) / dnom[1]);
		}
		return py[0] < py[1] ? 1 : 0;
	}
};

#endif
