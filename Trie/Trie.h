#pragma once
#include <map>
#include <vector>

using namespace std;

class Trie
{
	class TrieNode;

	typedef map<char, TrieNode*> TrieMap;
	typedef map<char, TrieNode*>::iterator TrieMapIter;

	// Internal TrieNode class - not relevant outside Trie
	class TrieNode
	{
	public:
		TrieNode(char c = '\0', bool cw = false, TrieNode* p = nullptr) :
			val(c), parent(p), completesWord(cw)
		{
			children.clear();
		}

		char val;
		TrieNode* parent;
		bool completesWord;
		TrieMap children;
	};



public:
	Trie()
	{
		root = new TrieNode('\0', true);
	}


	~Trie()
	{
		clear(root);
	}


	void insert(string str) const
	{
		TrieNode* cur = root;

		unsigned int n = findPrefixEnd(str, cur);

		// Insert new nodes containing rest of str (if necessary)
		for (; n < str.length(); n++)
		{
			cur->children[str[n]] = new TrieNode(str[n], false, cur);
			cur = cur->children[str[n]];
		}

		// Finally, mark cur as completing a word
		cur->completesWord = true;
	}


	bool search(string str) const
	{
		TrieNode* end = nullptr;
		unsigned int n =  findPrefixEnd(str, end);
		return n == str.length() && end->completesWord;
	}


	bool remove(string str) const
	{
		TrieNode* cur = root;

		unsigned int n = findPrefixEnd(str, cur);
		if (! (n == str.length() && cur->completesWord)) return false;	// str not found
		
		// INV: str is in Trie. Remove word completion (in any case)
		cur->completesWord = false;
		
		// Remove nodes up the branch as far as possible
		while(cur != root)
		{
			if (cur->completesWord || cur->children.size() > 0) 	// Cannot remove any more nodes
				break;

			// Can remove cur from Trie. Do so and move up the branch
			TrieNode* toDie = cur;
			cur->parent->children.erase(cur->val);
			cur = cur->parent;
			delete toDie;
		}

		return true;
	}

	void findAllWithPrefix(string prefix, vector<string>& strings)
	{
		strings.clear();
		TrieNode* prefixEnd = nullptr;
		if (findPrefixEnd(prefix, prefixEnd) != prefix.length()) return;	// Prefix="prefix" found

		// Prefix found - find all words beginning with prefix
		findWords(prefix, prefixEnd, strings);
	}


private:

	void findWords(string prefix, TrieNode* node, vector<string>& strings) const
	{
		if (node->completesWord)
			strings.push_back(prefix);

		for (TrieMapIter child = node->children.begin(); child != node->children.end(); ++child)
		{
			findWords(prefix + child->second->val, child->second, strings);
		}

	}

	// findPrefixEnd: Returns pointer to the last node in the prefix of str
	unsigned int findPrefixEnd(string str, TrieNode*& end) const
	{
		TrieNode* cur = root;
		TrieMapIter res;
		unsigned int i = 0;

		// Find (part of) key already in trie
		for (; i < str.length(); i++)
		{
			if ((res = cur->children.find(str[i])) != cur->children.end())
			{
				cur = res->second;
			}
			else break;
		}

		end = cur;
		return i;

	}

	void clear(TrieNode* node)
	{
		for (TrieMapIter child = node->children.begin(); child != node->children.end(); ++child)
		{
			clear(child->second);
		}
		delete node;
	}

	TrieNode* root;
};
