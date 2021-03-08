#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>

class StudentSpellCheck : public SpellCheck {
public:
<<<<<<< HEAD
	StudentSpellCheck() { }
=======
    StudentSpellCheck() { }
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:
	struct Trie {
		Trie* children[27];
		bool isEndOfWord;

		Trie() {
			this->isEndOfWord = false;

			for (int i = 0; i < 27; i++)
				this->children[i] = nullptr;
		}
<<<<<<< HEAD

=======
		
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
		void insert(std::string key) {
			Trie* curr = this;
			for (int i = 0; i < key.length(); i++) {
				if (isalpha(key[i]) || key[i] == '\'') {
					tolower(key[i]);
					int k = key[i] - 'a';
					if (!curr->children[k])
						curr->children[k] = new Trie();
<<<<<<< HEAD

=======
	
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
					curr = curr->children[k];
				}
			}
			curr->isEndOfWord = true;
		}

		bool search(std::string s) {
			Trie* curr = this;
			for (int i = 0; i < s.length(); i++) {
				int k = s[i] - 'a';
				if (curr->children[k] == nullptr)
					return false;
				curr = curr->children[k];
			}
			return (curr != nullptr && curr->isEndOfWord);
		}
	};
	Trie* m_trie;
};

#endif  // STUDENTSPELLCHECK_H_
