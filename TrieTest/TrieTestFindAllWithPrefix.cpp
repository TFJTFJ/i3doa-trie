#include "pch.h"
#include "../Trie/Trie.h"
#include <list>

class TrieTestFindAllWithPrefix : public testing::Test
{
public:
	TrieTestFindAllWithPrefix() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); strings.clear(); }
	void TearDown() override { delete uut; }
	Trie* uut;
	vector<string> strings;
};


TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_EmptyTrieEmptyPrefix_EmptyStringReturned) {
	uut->findAllWithPrefix("", strings);
	ASSERT_EQ(strings.size(), 1);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_EmptyTrieNonEmptyPrefix_NoStringReturned) {
	uut->findAllWithPrefix("FOO", strings);
	ASSERT_EQ(strings.size(), 0);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_NoStringsWithPrefix_NoStringsReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("BAD", strings);
	ASSERT_EQ(strings.size(), 0);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_OneStringsWithPrefix_OneStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUNDANCE", strings);
	ASSERT_EQ(strings.size(), 1);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_OneStringsWithPrefix_CorrectStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUNDANCE", strings);
	ASSERT_EQ(strings[0], "SUNDANCE");
}


TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ThreeStringsWithPrefix_ThreeStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUN", strings);
	ASSERT_EQ(strings.size(), 3);
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ThreeStringsWithPrefix_CorrectStringsReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUN", strings);

	ASSERT_TRUE(
		find(strings.begin(), strings.end(), "SUNDAY") != strings.end() &&
		find(strings.begin(), strings.end(), "SUN") != strings.end() &&
		find(strings.begin(), strings.end(), "SUNDANCE") != strings.end());
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ManyStringsInsertedThreeStringsWithPrefix_CorrectStringsReturned) {
	uut->insert("BRAVOUR");
	uut->insert("BRAVO");
	uut->insert("BRAVE");
	uut->insert("BAD");

	uut->insert("SUNDAY");
	uut->insert("SU");
	uut->insert("SUN");
	uut->insert("SUNDANCE");
	uut->insert("SO");
	uut->insert("SAM");

	uut->insert("FIX");
	uut->insert("FINISH");
	uut->insert("FINNISH");
	uut->insert("FILE");


	uut->findAllWithPrefix("SUN", strings);

	ASSERT_TRUE(
		find(strings.begin(), strings.end(), "SUNDAY") != strings.end() &&
		find(strings.begin(), strings.end(), "SUN") != strings.end() &&
		find(strings.begin(), strings.end(), "SUNDANCE") != strings.end());
}

TEST_F(TrieTestFindAllWithPrefix, FindAllWithPrefix_ManyStringsInsertedEmptyPrefix_AllStringsReturned) {
	uut->insert("BRAVOUR");
	uut->insert("BRAVO");
	uut->insert("BRAVE");
	uut->insert("BAD");

	uut->insert("SUNDAY");
	uut->insert("SU");
	uut->insert("SUN");
	uut->insert("SUNDANCE");
	uut->insert("SO");
	uut->insert("SAM");

	uut->insert("FIX");
	uut->insert("FINISH");
	uut->insert("FINNISH");
	uut->insert("FILE");


	uut->findAllWithPrefix("", strings);

	ASSERT_EQ(strings.size(), 14 + 1);	// Empty string always in Trie
}