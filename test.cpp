#include "catch.hpp"
#include "String.h"
#include "ArrayList.h"
#include <cstring>

TEST_CASE("String class", "[string]")
{
	String testBase = "testing";
	char testCS[] = "testingCS";

	SECTION("COPY CONSTRUCTOR")
	{
		String s = testBase;
		String t = s;
		REQUIRE(s == testBase);
		REQUIRE(t == s);
		REQUIRE(t == testBase);
	}

	SECTION("COPY CSTRING CONSTRUCTOR")
	{
		String s = testCS;
		String t = s.c_string();
		REQUIRE(s == testCS);
		REQUIRE(t == s);
		REQUIRE(t == String(testCS));
	}

	SECTION("ASSIGNMENT OPERATOR")
	{
		String s;
		String t;
		s = testBase;
		t = s;
		REQUIRE(s == testBase);
		REQUIRE(t == s);
		REQUIRE(t == testBase);
	}

	SECTION("CSTRING ASSIGNMENT OPERATOR")
	{
		String s;
		String t;
		s = testCS;
		t = s.c_string();
		REQUIRE(s == testCS);
		REQUIRE(t == s);
		REQUIRE(t == testCS);
	}

	SECTION("STRING STRING EQUALITY OPERATOR")
	{
		REQUIRE(String("a") == String("a"));
		REQUIRE(String("b") == String("b"));
		REQUIRE(String("c") == String("c"));
	}

	SECTION("LESS THAN OPERATOR")
	{
		REQUIRE(String("a") < String("ba"));
		REQUIRE(String("b") < String("be"));
		REQUIRE(!(String("a") < String("a")));
	}

	SECTION("GREATER THAN OPERATOR")
	{
		REQUIRE(String("ba") > String("a"));
		REQUIRE(String("be") > String("b"));
		REQUIRE(!(String("a") > String("a")));
	}

	SECTION("LESS THAN/EQUAL TO OPERATOR")
	{
		REQUIRE(String("a") <= String("a"));
		REQUIRE(String("b") <= String("be"));
		REQUIRE(!(String("b") <= String("a")));
	}

	SECTION("GREATER THAN/EQUAL TO OPERATOR")
	{
		REQUIRE(String("a") >= String("a"));
		REQUIRE(String("be") >= String("b"));
		REQUIRE(!(String("a") >= String("b")));
	}

	SECTION("STRING CSTRING EQUALITY OPERATOR")
	{
		REQUIRE(String("a") == "a");
		REQUIRE(String("b") == "b");
		REQUIRE(String("c") == "c");
	}

	SECTION("CSTRING STRING EQUALITY OPERATOR")
	{
		REQUIRE("a" == String("a"));
		REQUIRE("b" == String("b"));
		REQUIRE("c" == String("c"));
	}

	SECTION("STRING STRING INEQUALITY OPERATOR")
	{
		REQUIRE(String("a") != String("b"));
		REQUIRE(String("b") != String("c"));
		REQUIRE(String("c") != String("a"));
	}

	SECTION("STRING CSTRING INEQUALITY OPERATOR")
	{
		REQUIRE(String("a") != "b");
		REQUIRE(String("b") != "c");
		REQUIRE(String("c") != "a");
	}

	SECTION("CSTRING STRING INEQUALITY OPERATOR")
	{
		REQUIRE("a" != String("b"));
		REQUIRE("b" != String("c"));
		REQUIRE("c" != String("a"));
	}

	SECTION("STRING APPEND OPERATOR")
	{
		String base = "base";
		String a = "a";
		String b = "b";
		String c = "c";
		REQUIRE((base += a) == "basea");
		REQUIRE((base += b) == "baseab");
		REQUIRE((base += c) == "baseabc");
	}

	SECTION("CSTRING APPEND OPERATOR")
	{
		String base = "base";
		char a[] = "a";
		char b[] = "b";
		char c[] = "c";
		REQUIRE((base += a) == "basea");
		REQUIRE((base += b) == "baseab");
		REQUIRE((base += c) == "baseabc");
	}

	SECTION("CHAR APPEND OPERATOR")
	{
		String base = "base";
		char a = 'a';
		char b = 'b';
		char c = 'c';
		REQUIRE((base += a) == "basea");
		REQUIRE((base += b) == "baseab");
		REQUIRE((base += c) == "baseabc");
	}

	SECTION("CHAR AT INDEX OPERATOR")
	{
		String base = "test";
		REQUIRE(base[0] == 't');
		REQUIRE(base[1] == 'e');
		REQUIRE(base[2] == 's');
	}

	SECTION("STRING STRING ADDITION OPERATOR")
	{
		String left = "left";
		String right = "right";

		REQUIRE((left + right) == "leftright");
		REQUIRE((right + left) == "rightleft");
		REQUIRE((left + right + left) == "leftrightleft");
	}

	SECTION("STRING CSTRING ADDITION OPERATOR")
	{
		String left = "left";
		char right[] = "right";
		char mid[] = "mid";

		REQUIRE((left + right) == "leftright");
		REQUIRE((left + right + right) == "leftrightright");
		REQUIRE((left + mid) == "leftmid");
	}

	SECTION("STRING CHAR ADDITION OPERATOR")
	{
		String left = "left";
		char r = 'r';
		char s = 's';

		REQUIRE((left + r) == "leftr");
		REQUIRE((left + r + r) == "leftrr");
		REQUIRE((left + s) == "lefts");
	}

	SECTION("CSTRING STRING ADDITION OPERATOR")
	{
		char left[] = "left";
		String right = "right";
		String mid = "mid";

		REQUIRE((left + right) == "leftright");
		REQUIRE((left + (left + right)) == "leftleftright");
		REQUIRE((left + mid) == "leftmid");

	}

	SECTION("CHAR STRING ADDITION OPERATOR")
	{
		String left = "left";
		String right = "right";
		char s = 's';

		REQUIRE((s + left) == "sleft");
		REQUIRE((s + right) == "sright");
		REQUIRE((s + (s + right)) == "ssright");
	}

	SECTION("GETLENGTH")
	{
		REQUIRE(String("testing").getLength() == 7);
		REQUIRE(String("left").getLength() == 4);
		REQUIRE(String().getLength() == 0);
	}

	SECTION("SUBSTRING")
	{
		String base = "testing";
		REQUIRE(base.substring(1, 3) == "es");
		REQUIRE(base.substring(0, 1) == "t");
		REQUIRE(base.substring(1, base.getLength()) == "esting");
	}

	SECTION("SUBSTRINGLENGTH")
	{
		String base = "testing";
		REQUIRE(base.substringLength(1, 3) == "est");
		REQUIRE(base.substringLength(1, 1) == "e");
		REQUIRE(base.substringLength(1, 2) == "es");
	}

	SECTION("STRING SPLIT")
	{
		String split = "testing";
		String toSplit = "atestingbtestingctestingd";
		REQUIRE(toSplit.split(split).arrayLength() == 4);
		REQUIRE(toSplit.split(split)[0] == "a");
		REQUIRE(toSplit.split(split)[1] == "b");
	}

	SECTION("CSTRING SPLIT")
	{
		char split[] = "testingCS";
		String toSplit = "atestingCSbtestingCSctestingCSd";

		REQUIRE(toSplit.split(split).arrayLength() == 4);
		REQUIRE(toSplit.split(split)[0] == "a");
		REQUIRE(toSplit.split(split)[1] == "b");
	}

	SECTION("CHAR SPLIT")
	{
		String toSplit = "atbtctd";

		REQUIRE(toSplit.split('t').arrayLength() == 4);
		REQUIRE(toSplit.split('t')[0] == "a");
		REQUIRE(toSplit.split('t')[1] == "b");
	}

	SECTION("PREDICATE SPLIT")
	{
		String toSplit = "a.b?c!d";
        
		std::function<bool(char)> p = [](char c) -> bool
		{
			return ispunct(c);
		};
        
		REQUIRE(toSplit.split(p).arrayLength() == 4);
		REQUIRE(toSplit.split(p)[0] == "a");
		REQUIRE(toSplit.split(p)[1] == "b");
	}

	SECTION("STRING FIND")
	{
		String find = "testing";
		String toSearch = "hiTESTINGhilo";
		REQUIRE(toSearch.find(find, false) == 2);
		REQUIRE(toSearch.find(find, true) == toSearch.getLength());
		REQUIRE(toSearch.find(find, false, 4) == toSearch.getLength());
	}

	SECTION("CSTRING FIND")
	{
		char find[] = "testingCS";
		String toSearch = "hiTESTINGCShilo";
		REQUIRE(toSearch.find(find, false) == 2);
		REQUIRE(toSearch.find(find, true) == toSearch.getLength());
		REQUIRE(toSearch.find(find, false, 4) == toSearch.getLength());
	}

	SECTION("CHAR FIND")
	{
		String toSearch = "hiThilo";
		REQUIRE(toSearch.find('t', false) == 2);
		REQUIRE(toSearch.find('t', true) == toSearch.getLength());
		REQUIRE(toSearch.find('t', false, 4) == toSearch.getLength());
	}

	SECTION("GETHASHCODE")
	{
		REQUIRE(String().getHashCode() == 0);
		REQUIRE(String("a").getHashCode() == 97);
		REQUIRE(String("testing").getHashCode() == 105951736336);
	}

	SECTION("TRIM")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trim() == "ha");
		REQUIRE((' ' + String("testing") + ' ').trim() == "testing");
		REQUIRE(spaceOut.trim() == "t t");
	}

	SECTION("TRIMSTART")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trimStart() == "ha   ");
		REQUIRE((' ' + String("testing")).trimStart() == "testing");
		REQUIRE(spaceOut.trimStart() == "t t  ");
	}

	SECTION("TRIMEND")
	{
		String spaced = "   ha   ";
		String spaceOut = "  t t  ";
		REQUIRE(spaced.trimEnd() == "   ha");
		REQUIRE((String("testing") + ' ').trimEnd() == "testing");
		REQUIRE(spaceOut.trimEnd() == "  t t");
	}

	SECTION("STRIPCHARACTER CHAR")
	{
		String base = "abcbdBebfB";

		REQUIRE(base.stripCharacter('b') == "acdBefB");
		REQUIRE(base.stripCharacter('b', false) == "acdef");
		REQUIRE(String("b").stripCharacter('b') == "");
	}

	SECTION("STRIPCHARACTER PREDICATE")
	{
		String base = "abcbdBebfB";
        
		std::function<bool(char)> p1 = [](char c) -> bool
		{
			return c == 'b';
		};
        
		std::function<bool(char)> p2 = [](char c) -> bool
		{
			return tolower(c) == 'b';
		};

		REQUIRE(base.stripCharacter(p1) == "acdBefB");
		REQUIRE(base.stripCharacter(p2) == "acdef");
		REQUIRE(String("b").stripCharacter(p1) == "");
	}

	SECTION("TOLOWER")
	{
		REQUIRE(String("A").toLower() == "a");
		REQUIRE(String("TESTING").toLower() == "testing");
		REQUIRE(String("B").toLower() != "B");
	}

	SECTION("TOUPPER")
	{
		REQUIRE(String("a").toUpper() == "A");
		REQUIRE(String("testing").toUpper() == "TESTING");
		REQUIRE(String("b").toUpper() != "b");
	}

	SECTION("CLONE")
	{
		String base = "testing";
		String cloned = base.clone();
		REQUIRE(cloned == base);
		REQUIRE(cloned.getLength() == base.getLength());
		REQUIRE((cloned + 'a') == (base + 'a'));
	}

	SECTION("C_STRING")
	{
		REQUIRE(strcmp(String("testing").c_string(), "testing") == 0);
		REQUIRE(strcmp(String("a").c_string(), "a") == 0);
		REQUIRE(strcmp(String("b").c_string(), "b") == 0);
	}
}

TEST_CASE("ArrayList class", "[arraylist]")
{
	int numbers[] = {0, 1, 2, 3, 4, 5};

	SECTION("COPY CONSTRUCTOR")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		ArrayList<int> listTwo = listOne;

		REQUIRE(listOne.getSize() == listTwo.getSize());
		REQUIRE(listOne.at(0) == listTwo.at(0));
		REQUIRE(listOne.at(1) == listTwo.at(1));
	}

	SECTION("ASSIGNMENT OPERATOR")
	{
		ArrayList<int> listOne;
		ArrayList<int> listTwo;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		listTwo = listOne;

		REQUIRE(listOne.getSize() == listTwo.getSize());
		REQUIRE(listOne.at(0) == listTwo.at(0));
		REQUIRE(listOne.at(1) == listTwo.at(1));
	}

	SECTION("INDEX ACCESS OPERATOR")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);
		listOne.push_back(numbers[2]);

		REQUIRE(listOne[0] == numbers[0]);
		REQUIRE(listOne[1] == numbers[1]);
		REQUIRE(listOne[2] == numbers[2]);
	}

	SECTION("AT")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		REQUIRE(listOne.at(0) == numbers[0]);
		REQUIRE(listOne.at(1) == numbers[1]);
		REQUIRE(listOne.isSorted());
	}

	SECTION("GETSIZE")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);
		ArrayList<int> listTwo;
		listTwo.push_back(numbers[2]);

		REQUIRE(listOne.getSize() == 2);
		REQUIRE(listTwo.getSize() == 1);
		REQUIRE(ArrayList<int>().getSize() == 0);
	}

	SECTION("ISEMPTY")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		ArrayList<int> listTwo;
		listTwo.push_back(numbers[1]);

		REQUIRE(!listOne.isEmpty());
		REQUIRE(!listTwo.isEmpty());
		REQUIRE(ArrayList<int>().isEmpty());
	}

	SECTION("INDEXOF")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		REQUIRE(listOne.indexOf(numbers[0]) == 0);
		REQUIRE(listOne.indexOf(numbers[1]) == 1);
		REQUIRE(listOne.indexOf(numbers[2]) == listOne.getSize());
	}

	SECTION("ITERATOR")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);
		listOne.push_back(numbers[2]);

		int index = 0;
        
		for (int i : listOne)
		{
			REQUIRE(i == listOne.at(index++));
		}
        
		REQUIRE(index == listOne.getSize());
		bool cModThrown = false;
        
		try
		{
			for (int i : listOne)
			{
				listOne.pop_back();
				i++;
			}
		}
		catch (ConcurrentModificationException& ex)
		{
			cModThrown = true;
		}

		REQUIRE(cModThrown);
	}

	SECTION("INSERT")
	{
		ArrayList<int> listOne;
		listOne.insert(0, numbers[1]);
		listOne.insert(0, numbers[2]);
		listOne.insert(0, numbers[3]);

		REQUIRE(listOne.at(0) == numbers[3]);
		REQUIRE(listOne.at(1) == numbers[2]);
		REQUIRE(listOne.at(2) == numbers[1]);
	}

	SECTION("PUSH_BACK")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);
		listOne.push_back(numbers[2]);

		REQUIRE(listOne.at(0) == numbers[0]);
		REQUIRE(listOne.at(1) == numbers[1]);
		REQUIRE(listOne.at(2) == numbers[2]);
	}

	SECTION("POP")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		REQUIRE(listOne.pop() == numbers[0]);
		REQUIRE(listOne.pop() == numbers[1]);
		REQUIRE(listOne.isEmpty());
	}

	SECTION("POP_BACK")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		REQUIRE(listOne.pop_back() == numbers[1]);
		REQUIRE(listOne.pop_back() == numbers[0]);
		REQUIRE(listOne.isEmpty());
	}

	SECTION("REMOVE INDEX")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);

		listOne.remove(0);
		REQUIRE(listOne.at(0) == numbers[1]);
		listOne.remove(0);
		REQUIRE(listOne.isEmpty());
		bool indexOOBThrown = false;
        
		try
		{
			listOne.remove(0);
		}
		catch (IndexOutOfBoundsException& ex)
		{
			indexOOBThrown = true;
		}
        
		REQUIRE(indexOOBThrown);
	}

	SECTION("REMOVE ELEMENT")
	{
		char chars[] = {'a', 'b', 'c'};
		ArrayList<char> listOne;
		listOne.push_back(chars[0]);
		listOne.push_back(chars[1]);

		listOne.remove(chars[2]);
		REQUIRE(listOne.getSize() == 2);
		listOne.remove(chars[0]);
		REQUIRE(listOne.at(0) == chars[1]);
		listOne.remove(chars[1]);
		REQUIRE(listOne.isEmpty());
	}

	SECTION("ISSORTED")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[0]);
		listOne.push_back(numbers[1]);
		REQUIRE(listOne.isSorted());
		listOne.insert(0, numbers[2]);
		REQUIRE(!listOne.isSorted());
		REQUIRE(ArrayList<int>().isSorted());
	}

	SECTION("SORT")
	{
		ArrayList<int> listOne;
		listOne.push_back(numbers[3], false);
		listOne.push_back(numbers[1], false);
		listOne.push_back(numbers[5], false);
		listOne.push_back(numbers[4], false);
		listOne.push_back(numbers[2], false);
		listOne.push_back(numbers[0], false);

		listOne.sort();
		REQUIRE(listOne.isSorted());
		REQUIRE(listOne.at(0) == numbers[0]);
		REQUIRE(listOne.at(5) == numbers[5]);
	}
}
