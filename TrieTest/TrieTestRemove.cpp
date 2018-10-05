#include "pch.h"
#include "../Trie/Trie.h"
#include <list>

class TrieTestRemove : public testing::Test
{
public:
	TrieTestRemove() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); }
	void TearDown() override { delete uut; }
	Trie* uut;

};



TEST_F(TrieTestRemove, Search_StringInsertedTwiceRemovedOnce_StringNotFound) {
	uut->insert("SUN");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_FALSE(uut->search("SUN"));
}


TEST_F(TrieTestRemove, Remove_OnlyWordInTrie_WordNotFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_OnlyWordInTrie_EmptyStringStillFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	ASSERT_TRUE(uut->search(""));
}

TEST_F(TrieTestRemove, Remove_WordReInserted_WordFound) {
	uut->insert("SUNDAY");
	uut->remove("SUNDAY");
	uut->insert("SUNDAY");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_NonPresentPrefixRemoved_WordStillFound) {
	uut->insert("SUNDAY");
	uut->remove("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_PrefixRemoved_CompleteWordStillFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_PrefixRemoved_PrefixNotFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUN");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieTestRemove, Remove_LongWordRemoved_PrefixStillFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUNDAY");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieTestRemove, Remove_LongWordRemoved_LongWordFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
}

TEST_F(TrieTestRemove, Remove_MoreWordsInTrieOneRemoved_OtherWordsFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	uut->insert("SUNDANCE");

	uut->remove("SUNDAY");
	ASSERT_FALSE(uut->search("SUNDAY"));
	ASSERT_TRUE(uut->search("SUNDANCE"));
	ASSERT_TRUE(uut->search("SUN"));
}