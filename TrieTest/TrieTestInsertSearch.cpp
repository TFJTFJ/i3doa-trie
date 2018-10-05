#include "pch.h"
#include "../Trie/Trie.h"
#include <list>

class TrieTestInsertSearch : public testing::Test
{
public:
	TrieTestInsertSearch() : uut(nullptr) {}

protected:
	void SetUp() override { uut = new Trie(); }
	void TearDown() override {	delete uut;			}
	Trie* uut;

};



TEST_F(TrieTestInsertSearch, Search_StringInsertedTwice_StringFound) {
	uut->insert("SUN");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}



TEST_F(TrieTestInsertSearch, Search_VanillaTrie_EmptyStringFound) {
	ASSERT_TRUE(uut->search(""));
}

TEST_F(TrieTestInsertSearch, Search_VanillaTrie_StringNotFound) {
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_StringInserted_StringFound) {
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}


TEST_F(TrieTestInsertSearch, Search_StringInserted_PrefixNotFound) {
	uut->insert("SUNDAY");
	ASSERT_FALSE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_PrefixStringInserted_StringFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUN"));
}

TEST_F(TrieTestInsertSearch, Search_PrefixStringInserted_OriginalStringFound) {
	uut->insert("SUNDAY");
	uut->insert("SUN");
	ASSERT_TRUE(uut->search("SUNDAY"));
}


