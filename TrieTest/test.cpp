#include "pch.h"
#include "../Trie/Trie.h"
#include <list>

class TrieUnitTest : public testing::Test
{
public:
	TrieUnitTest() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); strings.clear(); }
	void TearDown() override {	delete uut;			}
	Trie* uut;
	vector<string> strings;
};



TEST_F(TrieUnitTest, Search_StringInsertedTwice_StringFound) {
	uut->insert("SUN");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}


TEST_F(TrieUnitTest, Search_StringInsertedTwiceRemovedOnce_StringNotFound) {
	uut->insert("SUN");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, Search_VanillaTrie_EmptyStringFound) {
	ASSERT_TRUE(uut->search(""));
}

TEST_F(TrieUnitTest, Search_VanillaTrie_StringNotFound) {
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, Search_StringInserted_StringFound) {
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}


TEST_F(TrieUnitTest, Search_StringInserted_PrefixNotFound) {
	uut->insert("SUNDAY");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, Search_PrefixStringInserted_StringFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, Search_PrefixStringInserted_OriginalStringFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}


TEST_F(TrieUnitTest, Remove_OnlyWordInTrie_WordNotFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
}

TEST_F(TrieUnitTest, Remove_OnlyWordInTrie_EmptyStringStillFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	ASSERT_TRUE(uut->search(""));
}

TEST_F(TrieUnitTest, Remove_WordReInserted_WordFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	uut->insert("SUNDAY");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieUnitTest, Remove_NonPresentPrefixRemoved_WordStillFound) {
	uut->insert("SUNDAY");
	uut->remove("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieUnitTest, Remove_PrefixRemoved_CompleteWordStillFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieUnitTest, Remove_PrefixRemoved_PrefixNotFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, Remove_LongWordRemoved_PrefixStillFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUNDAY");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, Remove_LongWordRemoved_LongWordFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
}

TEST_F(TrieUnitTest, Remove_MoreWordsInTrieOneRemoved_OtherWordsFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
	ASSERT_TRUE(uut->search("SUNDANCE"));
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieUnitTest, FindAllWithPrefix_EmptyTrieEmptyPrefix_EmptyStringReturned) {
	uut->findAllWithPrefix("", strings);
	ASSERT_EQ(strings.size(), 1);
}

TEST_F(TrieUnitTest, FindAllWithPrefix_EmptyTrieNonEmptyPrefix_NoStringReturned) {
	uut->findAllWithPrefix("FOO", strings);
	ASSERT_EQ(strings.size(), 0);
}

TEST_F(TrieUnitTest, FindAllWithPrefix_NoStringsWithPrefix_NoStringsReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("BAD", strings);
	ASSERT_EQ(strings.size(), 0);
}

TEST_F(TrieUnitTest, FindAllWithPrefix_OneStringsWithPrefix_OneStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUNDANCE", strings);
	ASSERT_EQ(strings.size(), 1);
}

TEST_F(TrieUnitTest, FindAllWithPrefix_OneStringsWithPrefix_CorrectStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUNDANCE", strings);
	ASSERT_EQ(strings[0], "SUNDANCE");
}


TEST_F(TrieUnitTest, FindAllWithPrefix_ThreeStringsWithPrefix_ThreeStringReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUN", strings);
	ASSERT_EQ(strings.size(), 3);
}

TEST_F(TrieUnitTest, FindAllWithPrefix_ThreeStringsWithPrefix_CorrectStringsReturned) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->findAllWithPrefix("SUN", strings);

	ASSERT_TRUE(
		find(strings.begin(), strings.end(), "SUNDAY") != strings.end() &&
		find(strings.begin(), strings.end(), "SUN") != strings.end() &&
		find(strings.begin(), strings.end(), "SUNDANCE") != strings.end());
}

TEST_F(TrieUnitTest, FindAllWithPrefix_ManyStringsInsertedThreeStringsWithPrefix_CorrectStringsReturned) {
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

TEST_F(TrieUnitTest, FindAllWithPrefix_ManyStringsInsertedEmptyPrefix_AllStringsReturned) {
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

	ASSERT_EQ(strings.size(), 14+1);	// Empty string always in Trie
}