#pragma once

#include "../utils/myutils.h"
#include <cassert>

typedef vector<string> string_vec;
typedef vector<char> opStack;


struct NavigationLogEntry
{
	opStack stack;
	int corruptScore = 0;
	int64_t autoCompleteScore = 0;
	bool corrupt = false;
	bool incomplete = false;
	const static unordered_map<char, int> corruptPointsMap;
	const static unordered_map<char, int> incompletePointsMap;
	friend istream& operator>>(istream& is, NavigationLogEntry& entry)
	{
		char c;
		while (is >> c)
		{
			entry.stack.push_back(c);
		}
		return is;
	}

	// lookup map for scoring delimiter
	static unordered_map<char, int> create_corrupt_points_map()
	{
		unordered_map<char, int> map{};
		map[')'] = 3;
		map[']'] = 57;
		map['}'] = 1197;
		map['>'] = 25137;
		return map;
	}
	static unordered_map<char, int> create_incomplete_points_map()
	{
		unordered_map<char, int> map{};
		map[')'] = 1;
		map[']'] = 2;
		map['}'] = 3;
		map['>'] = 4;
		return map;
	}
	struct opposite_delimiter {
		char operator()(const char& a) {
			{
				switch (a) {
				case '<':
					return '>';
				case '{':
					return '}';
				case '[':
					return ']';
				case '(':
					return ')';
				case '>':
					return '<';
				case '}':
					return '{';
				case ']':
					return '[';
				case ')':
					return '(';
				default:
					return false;
				}
			}
		}
	};
	struct open_delimiter {
		bool operator()(const char& a)
		{
			return a == '<' || a == '[' || a == '{' || a == '(';
		}
	};
	struct close_delimiter {
		bool operator()(const char& a)
		{
			return a == '>' || a == ']' || a == '}' || a == ')';
		}
	};
	struct pair_delimiter {
		bool operator() (char& a, char& b)
		{
			switch (a) {
			case '<':
				return b == '>';
			case '{':
				return b == '}';
			case '[':
				return b == ']';
			case '(':
				return b == ')';
			case '>':
				return b == '<';
			case '}':
				return b == '{';
			case ']':
				return b == '[';
			case ')':
				return b == '(';
			default:
				return false;
			}
		}
	};
	int CorruptScore() 
	{
		corruptScore = 0;
		if (stack.empty())
			return -1;
		opStack parser;
		open_delimiter is_open{};
		close_delimiter is_close{};
		pair_delimiter is_pair{};
		for (char& e : stack)
		{
			if (is_open(e))
			{
				parser.push_back(e);
				continue;
			}
			if (is_close(e))
			{
				if (is_pair(e, parser.back())) {
					parser.pop_back();
				}
				else {
					corrupt = true;
					auto val = corruptPointsMap.find(e);
					if (val == corruptPointsMap.end()) {
						//cout << "corrupt / invalid points for this end character" << endl;
						return 0;
					}
					// cout << "Score: " << val->second << "! Mismatch: " << parser.back() << " and " << e << endl;
					return val->second;
				}
			}
		}
		if (!parser.empty())
		{
			// cout << "Incomplete!?" << endl;
			incomplete = true;
			return 0;
		}
		return corruptScore;
	}

	int64_t AutoCompleteScore() 
	{
		autoCompleteScore = 0;
		if (stack.empty())
			return -1;
		opStack parser;
		opposite_delimiter get_opposite{};
		open_delimiter is_open{};
		close_delimiter is_close{};
		pair_delimiter is_pair{};
		for (char& e : stack)
		{
			if (is_open(e))
			{
				parser.push_back(e);
				continue;
			}
			if (is_close(e))
			{
				if (is_pair(e, parser.back())) 
				{
					parser.pop_back();
				}
				else 
				{
					corrupt = true;
					return 0;
				}
			}
		}
		if (!parser.empty())
		{
			// cout << "Incomplete!?" << endl;
			incomplete = true;
			autoCompleteScore = 0;
			for (auto it = parser.rbegin(); it != parser.rend(); it++)
			{
				autoCompleteScore *= 5;
				char opposite = get_opposite(*it);
				auto val = incompletePointsMap.find(opposite);
				if (val == incompletePointsMap.end())
				{
					cout << "Error! Couldn't score auto complete character? " << endl;
					return 0;
				}
				autoCompleteScore += val->second;
			}
			return autoCompleteScore;
		}
		//cout << " Complete? " << endl;
		return 0;
	}
};

typedef NavigationLogEntry entry;

struct NavigationLog
{
	string_vec log;
	vector<entry> parser;

	friend istream& operator>>(istream& is, NavigationLog& nl)
	{
		string line;
		while (getline(is, line)) {
			nl.log.push_back(line);
		}
		return is;
	}

	friend ostream& operator<<(ostream& os, const NavigationLog& nl)
	{
		int i = 0;
		for (string line : nl.log)
		{
			os << i++ << " " << line << endl;
		}
		return os;
	}

	bool empty() {
		return log.empty();
	}

	vector<entry>::iterator begin(){ return parser.begin(); }
	vector<entry>::iterator end() { return parser.end(); }

	int CorruptLines() {
		int count = 0; // could be std::count_if instead lazy
		for (const auto &e : parser)
		{
			if (e.corrupt)
			{
				count++;
			}
		}
		return count;
	}

	int IncompleteLines() {
		int count = 0;
		for (const auto &e : parser)
		{
			if (e.incomplete)
			{
				count++;
			}
		}
		return count;
	}

	int CorruptScoreLog() {
		int corruptScore = 0;
		parser.clear();
		for (string line : log)
		{
			entry e;
			stringstream(line) >> e;
			parser.push_back(e);
		}
		for (entry &e : parser)
		{
			corruptScore += e.CorruptScore();
		}
		return corruptScore;
	}
	int64_t IncompleteScoreLog() {
		int incompleteScore = 0;
		parser.clear();
		for (string line : log)
		{
			entry e;
			stringstream(line) >> e;
			parser.push_back(e);
		}
		vector<int64_t> scores{};
		for (entry& e : parser)
		{
			int64_t score = e.AutoCompleteScore();
			if (e.incomplete) {
				scores.push_back(score);
			}
		}
		scores.erase(std::remove_if(scores.begin(), scores.end(), [](const int& a) { return a == 0; }), scores.end());
		std::sort(scores.begin(), scores.end());
		
		auto mid = scores.begin() + (scores.size() / 2);
		return *mid;
	}
};
