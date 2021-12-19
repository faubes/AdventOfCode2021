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
#include <ranges>
#include <utility>

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

	enum Wires 
	{
		a, b, c, d, e, f, g
	}; 
	
	string input_string{};
	string unique_signal_patterns{};
	string four_digit_output_value{};
	
	unordered_map<string, int> decodedValue;
	vector<string> unidentifiedSignals;
	vector<string> digits;


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
		int sum = 0;
		int count = 0;
		while (input >> *this)
		{
			count++;
			sum += decode();
		}

		cout << "Count is: " << count << " and sum is " << sum << endl;
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

	static bs StringToBitset(string str) {
		bs sum{};
		for (auto c : str) 
		{
			bs next = WireToBitset(Wires(c - 'a'));
			sum.operator|=(next);
		}
		return sum;
	}

	static bs WireToBitset(Wires w) {
		bs result{};
		result[static_cast<int>(w)] = true; // flip the w'th bit
		return result;
	}

	static string BitsetToWire(bs b)
	{
		stringstream ss;
		for (int i = 0; i < b.size(); i++)
		{
			if (b[i])
			{
				ss << Wires(i);
			}
		}
		return ss.str();
	}

	static string BitsetToBinaryString(bs b)
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

	struct same_length {
		int n;
		bool operator()(const string& str) const { return str.length() == n; }
	};

	struct common_bits {
		int num_common_bits;
		bool operator()(const string& str1, const string& str2) const
		{
			bs bs1 = StringToBitset(str1);
			bs bs2 = StringToBitset(str2);
			bs common_bits = bs1 & bs2;
			return common_bits.count() == num_common_bits;
		}
	};

	unordered_map<string, int> IdentifySignalPatterns() 
	{
		unordered_map<string, int> signalMap{};

		if (unique_signal_patterns.empty() || four_digit_output_value.empty())
		{
			cout << "Error identifying patterns";
			return signalMap;
		}

		unidentifiedSignals = TokenizeString(unique_signal_patterns);
		digits = TokenizeString(four_digit_output_value);

#if DEBUG
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

		auto length2 = same_length{ 2 };
		auto length3 = same_length{ 3 };
		auto length4 = same_length{ 4 };
		auto length5 = same_length{ 5 };
		auto length6 = same_length{ 6 };
		auto length7 = same_length{ 7 };
		auto one_common_bit = common_bits{ 1 };
		auto two_common_bits = common_bits{ 2 };
		auto four_common_bits = common_bits{ 4 };

		auto one = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), length2 ); // should probably not crash if one = end()
		signalMap[*one] = 1;
		string one_string = *one;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *one));

		auto four = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), length4);
		signalMap[*four] = 4;
		string four_string = *four;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *four));

		auto seven = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), length3);
		signalMap[*seven] = 7;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *seven));

		auto eight = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), length7);
		signalMap[*eight] = 8;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *eight));

		auto must_be_nine_if = [length6, four_common_bits, four_string](const string& str) { return length6(str) && four_common_bits(str, four_string); };

		auto nine = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), must_be_nine_if);
		signalMap[*nine] = 9;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *nine));

		auto must_be_six_if = [length6, one_common_bit, one_string](const string& str) { return length6(str) && one_common_bit(str, one_string); };

		auto six = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), must_be_six_if);
		signalMap[*six] = 6;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *six));

		auto zero = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), length6);
		signalMap[*zero] = 0;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *zero));

		auto must_be_three_if = [length5, two_common_bits, one_string](const string& str) { return length5(str) && two_common_bits(str, one_string); };
		
		auto three = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), must_be_three_if);
		signalMap[*three] = 3;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *three));

		auto must_be_two_if = [length5, two_common_bits, four_string](const string& str) { return length5(str) && two_common_bits(str, four_string); };

		auto two = find_if(unidentifiedSignals.begin(), unidentifiedSignals.end(), must_be_two_if);
		signalMap[*two] = 2;
		unidentifiedSignals.erase(std::remove(unidentifiedSignals.begin(), unidentifiedSignals.end(), *two));

		if (unidentifiedSignals.size() == 1)
		{
			auto five = unidentifiedSignals.begin();
			signalMap[*five] = 5;
		}
		else 
		{
			cout << "Something went wrong decoding signals!! There should only be 5 left." << endl;
		}

		return signalMap;
	}

	// count number of 1,4,7,8 in digits
	int count() {
		decodedValue = IdentifySignalPatterns();

		unordered_map<bs, int> decodedBitMap{};
		for (auto& e : decodedValue)
		{
			decodedBitMap.insert(make_pair(StringToBitset(e.first), e.second)); 
		}

		int sum = 0;
		for (auto& s : digits)
		{
			bs asBitset = StringToBitset(s); // use conversion to Bitset to disregard ordering of letters
			// ie: cfbegad and fdgacbe are same up to permutation
			if (decodedBitMap[asBitset] == 1 ||
				decodedBitMap[asBitset] == 4 ||
				decodedBitMap[asBitset] == 7 ||
				decodedBitMap[asBitset] == 8)
			{
				sum++;
			}
		}
		return sum;
	}

	// decode and sum the final 4 digit output value using signal patterns
	int decode() 
	{
		decodedValue = IdentifySignalPatterns();

		unordered_map<bs, int> decodedBitMap{};
		for (auto& e : decodedValue)
		{
			decodedBitMap.insert(make_pair(StringToBitset(e.first), e.second));
		}

		int sum = 0;
		for (int i =0; i< 4; i++)
		{

			// use conversion to Bitset to drop ordering of letters
			bs asBitset = StringToBitset(digits[4-(i+1)]); 
			// ie: cfbegad and fdgacbe are same up to permutation
			// multiply by pow10 to get digits into right place
			sum += decodedBitMap[asBitset] * pow(10, i);
		}
		cout << "decoded: " << sum << endl;
		return sum;
	}
};


class SevenSegmentDisplay
{
private:
	string inputFilename;
	
	int _n; // decimal value to display
	std::bitset<7> _bitset; 

public:
	static const unordered_map<int, std::bitset<7>> segmentMap;

	static unordered_map<int, std::bitset<7>> create_map() {
		unordered_map<int, std::bitset<7>> m;
		m[0] = std::bitset<7>{"1110111"};
		m[1] = std::bitset<7>{"0100100"};
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