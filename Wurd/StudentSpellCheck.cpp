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



	return false; // TODO
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
	// TODO
}
