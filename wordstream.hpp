#ifndef WORDSTREAM_HPP
#define WORDSTREAM_HPP

#include <iostream>
#include <string>

using namespace std;

class WordStream {
	string _text;
	const char *_cur;

public:
	WordStream() : _cur(nullptr) {}
	WordStream(const string& text) : _text(text), _cur(text.data()) {}

	bool iterate(string& word) {
		_cur = next_word(_cur);
		if (!_cur) return false;
		_cur = read_word(_cur, word);
		//if (is_stopword(word)) return iterate(word);
		return true;
	}

private:
	static const char *read_word(const char *p, string& word) {
		word.clear();
		while (char c = to_charset(*(p++))) {
			word.push_back(c);
		}
		return p;
	}
	
	static const char *next_word(const char *p) {
		while (!is_letter(*p)) {
			if (*p == '\0') return nullptr;
			else p++;
		}
		return p;
	}
	
	static bool is_letter(char c) {
		return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
	}

	static char to_charset(char c) {
		if ('a' <= c && c <= 'z') return c;
		if ('A' <= c && c <= 'Z') return c + ('a' - 'A');
		if (c == '\'') return c;
		return '\0';
	}
	
	static bool is_stopword(const string& word) {
		static const vector<string> stopwords = {
			"in", "is", "a", "the", "i", "i'm", "he", "she",
			"of", "it", "this", "that", "on", "and", "you",
		};
		for (auto& sw : stopwords)
			if (word == sw) return true;
		return false;
	}
};

#endif
