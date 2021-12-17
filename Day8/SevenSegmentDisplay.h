// AdventOfCode2021.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <bitset>
#include <sstream>
#include <set>
#include <unordered_map>
#include <sstream>


using std::string;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
using std::ifstream;
using std::vector;
using std::stringstream;
//using std::wstring;
using std::set;
using std::bitset;
using std::unordered_map;

typedef bitset<7> bs;


// need to learn a mapping
// from S = { a,b,c,d,e,f,g } -> S

class SignalPattern
{

	enum class Wires {
		a, b, c, d, e, f, g
	}; 
	
	string input_string{};
	string unique_signal_patterns{};
	string four_digit_output_value{};
	
	unordered_map<bs, bs> wireDecoded;
	unordered_map<bs, int> decodedValue;

	// for each letter we'll need a set of candidates
	unordered_map<bs, vector<bs>> candidates;

public:
	friend istream& operator>>(istream& is, SignalPattern &sp)
	{
		string str;

		getline(is, str);
		if (!str.empty())
		{
			sp.input_string = str;
			sp.ParseInput();
		}
		return is;
	}
	void LoadInput(string inputFilename)
	{
		ifstream input(inputFilename);
		if (!(input >> *this))
		{
			cout << "couldn't read data!" << endl;
		}
		input.close();

	}
	void ParseInput() 
	{
		if (input_string.empty())
		{
			return;
		}
		size_t pos = 0;
		size_t it = input_string.find('|');
		unique_signal_patterns = input_string.substr(pos, it);
		four_digit_output_value = input_string.substr(it+2, string::npos);
#ifdef DEBUGINPUT
		cout << "Unique signal patterns: " << endl;
		cout << unique_signal_patterns << endl;
		cout << "Four digit output values " << endl;
		cout << four_digit_output_value << endl;
#endif
	}
	vector<string> TokenizeString(string str)
	{
		vector<string> tokens{};
		size_t pos = 0;
		stringstream ss(str);
		string s;
		while (ss >> s) {
			tokens.push_back(s);
		}
		return tokens;
	}
	bs StringToBitset(string str) {
		bs sum{};
		for (auto c : str) 
		{
			cout << static_cast<int>(Wires(c)) << endl;
			bs next = bs(static_cast<int>(Wires(c)));
			sum.operator|=(next);
		}
		cout << sum << endl;
		return sum;
	}
	string BitsetToString(bs b)
	{
		stringstream ss;
		for (int i=0; i < b.size(); i++)
		{
			if (b[i])
			{
				ss << i;
			}
		}
		return ss.str();
	}
	
	unordered_map<string, int> IdentifySignalPatterns() 
	{
		unordered_map<string, int> signalMap{};

		if (unique_signal_patterns.empty() || four_digit_output_value.empty())
		{
			cout << "Error identifying patterns";
			return signalMap;
		}

		vector<string> unidentifiedSignals = TokenizeString(unique_signal_patterns);
		vector<string> digits = TokenizeString(four_digit_output_value);

#ifdef DEBUG
		cout << "Extracted unidentified signals" << endl;
		for (auto s : unidentifiedSignals)
		{
			cout << s << endl;
		}

		cout << "Extracted four digits" << endl;
		for (auto s : digits)
		{
			cout << s << endl;
		}
#endif

		vector<bs> all_possible(7);
		std::iota(all_possible.begin(), all_possible.end(), 0);

		for (string signal : unidentifiedSignals) 
		{
			candidates[StringToBitset(signal)] = all_possible;
 		}
		return signalMap;
	}


	// decode the final 4 digit output value using signal patterns
	void decode(string word) {}
};


class SevenSegmentDisplay
{
private:
	string inputFilename;
	
	int _n; // decimal value to display
	std::bitset<7> _bitset; 
	
	//bool a, b, c, d, e, f, g;

public:
	static const unordered_map<int, std::bitset<7>> segmentMap;

	static unordered_map<int, std::bitset<7>> create_map() {
		unordered_map<int, std::bitset<7>> m;
		m[0] = std::bitset<7>{ "1110111" };
		m[1] = std::bitset<7>{ "0100100" };
		m[2] = std::bitset<7>{"1011101"};
		m[3] = std::bitset<7>{"1101101"};
		m[4] = std::bitset<7>{"0101110"};
		m[5] = std::bitset<7>{"1101011"};
		m[6] = std::bitset<7>{"1111011"};
		m[7] = std::bitset<7>{"0100101"};
		m[8] = std::bitset<7>{"1111111"};
		m[9] = std::bitset<7>{"1101111"};
		return m;
	}

	SevenSegmentDisplay(int n) 
	{ 
		cout << "Constructing with " << n << " " << std::abs(n % 10) << endl;
		_n = std::abs(n % 10);
		auto it = segmentMap.find(_n);
		if (it != segmentMap.end())
		{
			_bitset = it->second;
		}
	}
	
	bitset<7> GetBitSet() {
		return _bitset;
	}
	
	//SevenSegmentDisplay(string str) : inputFilename(str) {}
	//void LoadInput();

	friend ostream& operator<<(ostream& os, SevenSegmentDisplay& ssd)
	{
		std::stringstream ss;
		char a = ssd._bitset[0] ? 'a' : '.';
		char b = ssd._bitset[1] ? 'b' : '.';
		char c = ssd._bitset[2] ? 'c' : '.';;
		char d = ssd._bitset[3] ? 'd' : '.';;
		char e = ssd._bitset[4] ? 'e' : '.';;
		char f = ssd._bitset[5] ? 'f' : '.';;
		char g = ssd._bitset[6] ? 'g' : '.';;

		ss << " " << a << a << a << a << " " << endl;
		ss << b << " " << " " << " " << " " << c << endl;
		ss << b << " " << " " << " " << " " << c << endl;
		ss << " " << d << d << d << d << " " << endl;
		ss << e << " " << " " << " " << " " << f << endl;
		ss << e << " " << " " << " " << " " << f << endl;
		ss << " " << g << g << g << g << " " << endl;
		
		return os << ss.str();
	}
};