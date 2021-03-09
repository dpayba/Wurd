#include "StudentSpellCheck.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

SpellCheck* createSpellCheck()
{
	return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck() {
	// TODO
}

bool StudentSpellCheck::load(std::string dictionaryFile) {
	std::ifstream infile(dictionaryFile);

	if (!infile) {
		std::cerr << "Error Opening File" << std::endl;
		return false;
	}

	std::string s;
	m_trie = new Trie();
	while (getline(infile, s)) {
		m_trie->insert(s);
	}

	return true; // TODO
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {
	for (int i = 0; i < word.length(); i++)
		tolower(word[i]);

	if (m_trie->search(word))
		return true;

	std::vector<std::string>::iterator it = suggestions.begin();
	while (it != suggestions.end()) {
		it = suggestions.erase(it);
	}

	int suggestionsCount = 0;
	for (int i = 0; i < word.length(); i++) {
		if (isalpha(word[i]) || word[i] == 39) {
			char original = word[i];

			// replace all characters with a-z
			for (char j = 'a'; j <= 'z'; j++) {
				word[i] = j;
				if (m_trie->search(word)) {
					suggestions.push_back(word);
					suggestionsCount++;
				}
			}

			if (suggestionsCount == max_suggestions)
				break;

			// check apostrophe
			word[i] = '\'';
			if (m_trie->search(word)) {
				suggestions.push_back(word);
				suggestionsCount++;
			}

			// reset word to original
			word[i] = original;
			if (suggestionsCount == max_suggestions)
				break;
		}
	}

	return false; // TODO
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
	// loop through string
	// if not alpha or apostrophe
	int startPos = 0;
	int i = 0;
	int length = 0;
	while (i < line.size()) {
		if (!isalpha(line[i]) || line[i] == 39) {
			if (i == line.size() - 1) // make sure not end of string
				break;
			else {
				while (!isalpha(line[i]) || line[i] == 39) { // loop through until letters again
					if (i == line.size() - 1)
						return;
					i++;
				}
			}
			startPos = i;
			length = 0;
		}
		else {
			i++;
			length++;
		}

		if (!m_trie->search(line.substr(startPos, length))) { // if not word
			Position position;
			position.start = startPos;
			position.end = length + startPos - 1;
			problems.push_back(position);
		}
	}
	// TODO
}
