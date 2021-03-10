#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>

class StudentSpellCheck : public SpellCheck {
public:
	StudentSpellCheck() { }
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:
	struct Trie {
		bool isLeaf;
		Trie* children[27];

		// Constructor
		Trie()
		{
			this->isLeaf = false;

			for (int i = 0; i < 27; i++) {
				this->children[i] = nullptr;
			}
		}

		void insert(std::string key) {
			// start from root
			Trie* curr = this;

			for (int i = 0; i < key.length(); i++) { // loop through characters in string
				if (key[i] == '\'') {
					if (curr->children[26] == nullptr) {
						curr->children[26] = new Trie();
					}
					curr = curr->children[26];
				}
				else if (isalpha(key[i])) { // use only letters and '
					char c = tolower(key[i]);

					// create new node if no path
					if (curr->children[c - 'a'] == nullptr) {
						curr->children[c - 'a'] = new Trie();
					}

					// go to next node
					curr = curr->children[c - 'a'];
				}
			}
			// mark end of word
			curr->isLeaf = true;
		}

		bool search(std::string key) {
			if (this == nullptr) {
				return false;
			}

			Trie* curr = this;
			for (int i = 0; i < key.length(); i++) {
				if (key[i] == '\'') {
					curr = curr->children[26];

					if (curr == nullptr) {
						return false;
					}
				}
				else if (isalpha(key[i])) { // use only letters and '
					char c = tolower(key[i]);

					curr = curr->children[c - 'a'];

					if (curr == nullptr) {
						return false;
					}
				}
			}
			return curr->isLeaf;
		}

		void destroy(Trie *curr) {
			if (curr == nullptr) {
				return;
			}

			for (int i = 0; i < 27; i++) 
				destroy(children[i]);

			delete curr;
		}
	
	};
	Trie* m_trie;
};

#endif  // STUDENTSPELLCHECK_H_
