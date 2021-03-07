#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

TextEditor* createTextEditor(Undo* un)
{
    return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
    m_currCol = 0;
    m_currRow = 0;

    // TODO
}

StudentTextEditor::~StudentTextEditor()
{
    // TODO
}

bool StudentTextEditor::load(std::string file) {
    
    // clear screen
    std::ifstream infile(file);
    
    if (!infile) {
        std::cerr << "Error Opening File" << std::endl;
        return false;
    }
    
    std::list<std::string>::iterator clear = m_wordList.begin();
    while(clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }
    
    std::string s;
    while (getline(infile, s)) {
        if (!s.empty() && s.back() == 'r') {
            char backChar = 'r';
            s.pop_back();
            if (s.back() == '\\')
                s.pop_back();
            else
                s.push_back(backChar);
        }
        m_wordList.push_back(s);
    }
    
    m_currRowIterator = m_wordList.begin();
    m_currRow = 0;
    m_currCol = 0;
    
    return true;  // TODO
}

bool StudentTextEditor::save(std::string file) {
    return false;  // TODO
}

void StudentTextEditor::reset() {
    std::list<std::string>::iterator clear = m_wordList.begin();
    while (clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }
}

void StudentTextEditor::move(Dir dir) {
    switch (dir) {
        case Dir::UP:
            if (m_currRow == 0)
                break;
            else {
                m_currRowIterator--;
                if ((*m_currRowIterator).length() < m_currCol) {
                    m_currCol = (*m_currRowIterator).length();
                    m_currRow--;
                }
                else
                    m_currRow--;
            }
            break;
        case Dir::DOWN:
            if (m_currRow == m_wordList.size())
                break;
            else {
                m_currRowIterator++;
                if ((*m_currRowIterator).length() < m_currCol) {
                    m_currCol = (*m_currRowIterator).length();
                    m_currRow++;
                }
                else
                    m_currRow++;
            }
            break;
        case Dir::LEFT:
            if (m_currCol == 0 && m_currRow == 0)
                break;
            else if (m_currCol == 0) {
                m_currRow--;
                m_currRowIterator--;
                m_currCol = (*m_currRowIterator).length();
            }
            else 
                m_currCol--;
            break;
        case Dir::RIGHT:
            if (m_currRow == m_wordList.size() && m_currCol == (*m_currRowIterator).length())
                break;
            else if (m_currCol == (*m_currRowIterator).length()) {
                m_currRow++;
                m_currRowIterator++;
                m_currCol = 0;
            }
            else
                m_currCol++;
            break;
        case Dir::HOME:
            m_currCol = 0;
            break;
        case Dir::END:
            m_currCol = (*m_currRowIterator).length() + 1;
            break;
    }

}

void StudentTextEditor::del() {
    std::string s = *(m_currRowIterator);
    s = s.substr(0, m_currCol) + s.substr(m_currCol+1);
    *(m_currRowIterator) = s;
    if (m_currCol = (*m_currRowIterator).length()1)
        exit(1);
    // TODO
}

void StudentTextEditor::backspace() {
    std::string s = *(m_currRowIterator);
    s = s.substr(0, m_currCol-1) + s.substr(m_currCol);
    *(m_currRowIterator) = s;
    if (m_currCol == 0 || *(m_currRowIterator) == "") {
        m_currRowIterator = m_wordList.erase(m_currRowIterator);
        m_currRowIterator--;
        m_currRow--;
        m_currCol = (*m_currRowIterator).length();
    }
    else
        m_currCol--;
}

void StudentTextEditor::insert(char ch) {
    std::string s = *(m_currRowIterator);
    s = s.substr(0, m_currCol) + ch + s.substr(m_currCol);
    *(m_currRowIterator) = s;
    m_currCol++;
}

void StudentTextEditor::enter() {
    // TODO
}

void StudentTextEditor::getPos(int& row, int& col) const {
    row = m_currRow;
    col = m_currCol;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    if (startRow < 0 || numRows < 0 || startRow > lines.size())
        return -1;
    
    int linesAdded = 0;
    
    std::vector<std::string>::iterator clear = lines.begin();
    while(clear != lines.end()) {
        clear = lines.erase(clear);
    }
    
    int adjustPosition = startRow - m_currRow;
    std::list<std::string>::iterator it = m_currRowIterator;
    
    // set it to startrow
    if (adjustPosition > 0) {
        for (int i = 0; i != adjustPosition; i++)
            it++;
    }
    if (adjustPosition < 0) {
        for (int i = 0; i != adjustPosition; i--)
            it--;
    }
    
    while (startRow != numRows) {
        if (it == m_wordList.end())
            break;
        lines.push_back(*it);
        startRow++; 
        it++; 
        linesAdded++;
    }
    
    return linesAdded;
}

void StudentTextEditor::undo() {
    // TODO
}

