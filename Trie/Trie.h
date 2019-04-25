#pragma once
#include <map>
#include <vector>

using namespace std;

class Trie
{
	class Node;	// Forward declaration will allow Children definition in class Node

	typedef map<char, Node*> Children;
	typedef Children::iterator ChildrenIter;

	// Internal Node class - not relevant outside Trie
	class Node
	{
	public:
		Node(char c = '\0', bool cw = false, Node* p = nullptr) :
			val(c), parent(p), completesWord(cw)
		{
			children.clear();
		}

		char val;
		Node* parent;
		bool completesWord;
		Children children;
	};


	Node* root;

public:
	Trie()
	{
		root = new Node('\0', true);
	}


	~Trie()
	{
		clear(root);
	}


	void insert(string str) const
	{
		Node* cur = root;

		unsigned int n = findPrefixEnd(str, cur);

		// Insert new nodes containing rest of str (if necessary)
		for (; n < str.length(); n++)
		{
			cur->children[str[n]] = new Node(str[n], false, cur);
			cur = cur->children[str[n]];
		}

		// Finally, mark cur as completing a word
		cur->completesWord = true;
	}


	bool search(string str) const
	{
		Node* end = nullptr;
		unsigned int n =  findPrefixEnd(str, end);
		return n == str.length() && end->completesWord;
	}


	void remove(string str) const
	{
		Node* cur = root;

		unsigned int n = findPrefixEnd(str, cur);
		if (! (n == str.length() && cur->completesWord)) return;	// str not found
		
		// INV: str is in Trie. Remove word completion (in any case)
		cur->completesWord = false;
		
		// Remove nodes up the branch as far as possible
		while(cur != root)
		{
			if (cur->completesWord || cur->children.size() > 0) 	// Cannot remove any more nodes
				break;

			// Can remove cur from Trie. Do so and move up the branch
			Node* toDie = cur;
			cur->parent->children.erase(cur->val);
			cur = cur->parent;
			delete toDie;
		}
	}

	void findAllWithPrefix(string prefix, vector<string>& strings) const
	{
		strings.clear();
		Node* prefixEnd = nullptr;
		if (findPrefixEnd(prefix, prefixEnd) != prefix.length()) return;	// Prefix="prefix" found

		// Prefix found - find all words beginning with prefix
		findWords(prefix, prefixEnd, strings);
	}


private:

	void findWords(string prefix, Node* node, vector<string>& strings) const
	{
		if (node->completesWord)
			strings.push_back(prefix);

		for (ChildrenIter child = node->children.begin(); child != node->children.end(); ++child)
		{
			findWords(prefix + child->second->val, child->second, strings);
		}

	}

	// findPrefixEnd: 
	// Sets the parameter end to the last node in the prefix of str and returns the length of the prefix
	unsigned int findPrefixEnd(string str, Node*& end) const
	{
		Node* cur = root;
		ChildrenIter res;
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

	void clear(Node* node) const
	{
		for (ChildrenIter child = node->children.begin(); child != node->children.end(); ++child)
			clear(child->second);

		delete node;
	}

	
};
