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
    m_wordList.push_back("");
    m_currRowIterator = m_wordList.begin();
}

StudentTextEditor::~StudentTextEditor()
{
    // O(N)
    std::list<std::string>::iterator it = m_wordList.begin();
    while (it != m_wordList.end())
        it = m_wordList.erase(it);
}

bool StudentTextEditor::load(std::string file) {

    // clear screen
    std::ifstream infile(file);

    if (!infile) {
        std::cerr << "Error Opening File" << std::endl;
        return false;
    }

    // O(M)
    std::list<std::string>::iterator clear = m_wordList.begin(); 
    while (clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }

    std::string s;
    // O(N)
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

    return true;
}

bool StudentTextEditor::save(std::string file) {
    std::ofstream outfile(file);
    if (!outfile)
        return false;

    // O(M)
    std::list<std::string>::iterator it = m_wordList.begin();
    while (it != m_wordList.end()) {
        outfile << (*it) << '\n';
        it++;
    }

    return true;
}

void StudentTextEditor::reset() {
    // O(N)
    std::list<std::string>::iterator clear = m_wordList.begin();
    while (clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }

    // O(U)
    getUndo()->clear();
}

void StudentTextEditor::move(Dir dir) {
    // O(1)
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
        if (m_currRow == m_wordList.size() - 1)
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
        if (m_currRow == m_wordList.size() - 1 && m_currCol == (*m_currRowIterator).length())
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
        m_currCol = (*m_currRowIterator).length();
        break;
    }

}

void StudentTextEditor::del() {
    std::list<std::string>::iterator last = m_wordList.end();
    last--;
    // just after last character on last line
    if (m_currRow == m_wordList.size() - 1 && m_currCol == (*last).length())
        return;

    // current line string
    std::string s = *(m_currRowIterator);
    // last character on the line
    if (m_currCol == (*m_currRowIterator).length()) {
        // copy string to merge
        m_currRowIterator++; 
        std::string stringToCopy = *(m_currRowIterator);
        // get rid of string to join
        m_currRowIterator = m_wordList.erase(m_currRowIterator);
        // reset iterator to line to join
        m_currRowIterator--;
        s = s + stringToCopy;
        getUndo()->submit(Undo::Action::JOIN, m_currRow, m_currCol);
    }
    else {
        char chDelete = s.at(m_currCol);
        // O(L)
        s = s.substr(0, m_currCol) + s.substr(m_currCol + 1);
        getUndo()->submit(Undo::Action::DELETE, m_currRow, m_currCol, chDelete);
    }
    *(m_currRowIterator) = s;

}

void StudentTextEditor::backspace() {
    std::string s = *(m_currRowIterator);
    // first character first row
    if (m_currCol == 0 && m_currRow == 0)
        return;

    // first character of line or line empty
    if (m_currCol == 0 || *(m_currRowIterator) == "") {
        // O(L1+L2)
        m_currRowIterator = m_wordList.erase(m_currRowIterator);
        // reset iterator to line join
        m_currRowIterator--;
        m_currRow--;
        m_currCol = (*m_currRowIterator).length();
        s = *(m_currRowIterator)+s;
        getUndo()->submit(Undo::Action::JOIN, m_currRow, m_currCol);
    }
    else {
        char chDelete = s.at(m_currCol - 1);
        // O(L)
        s = s.substr(0, m_currCol - 1) + s.substr(m_currCol);
        m_currCol--;
        getUndo()->submit(Undo::Action::DELETE, m_currRow, m_currCol, chDelete);
    }
    *(m_currRowIterator) = s;
}

void StudentTextEditor::insert(char ch) {
    std::string s = *(m_currRowIterator);
    // O(L)
    if (ch == '\t') { // tab is pressed
        s = s.substr(0, m_currCol) + "    " + s.substr(m_currCol);
        m_currCol += 4;
        *(m_currRowIterator) = s;
        getUndo()->submit(Undo::Action::INSERT, m_currRow, m_currCol, ch);
        return;
    }
    // O(L)
    std::string character;
    character.push_back(ch);
    s = s.insert(m_currCol, character); // insert character to line
    *(m_currRowIterator) = s;
    m_currCol++;
    getUndo()->submit(Undo::Action::INSERT, m_currRow, m_currCol, ch);
}

void StudentTextEditor::enter() {
    // O(L)
    getUndo()->submit(Undo::Action::SPLIT, m_currRow, m_currCol);
    // rest of line
    std::string s = (*m_currRowIterator).substr(m_currCol);
    // line before enter key
    (*m_currRowIterator) = (*m_currRowIterator).substr(0, m_currCol);
    // move iterator forward, insert before
    m_currRowIterator++;
    m_wordList.insert(m_currRowIterator, s);
    // move positions to new line
    m_currRowIterator--;
    m_currRow++;
    m_currCol = 0;
}

void StudentTextEditor::getPos(int& row, int& col) const {
    // O(1)
    row = m_currRow;
    col = m_currCol;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    if (startRow < 0 || numRows < 0 || startRow > lines.size())
        return -1;

    int linesAdded = 0;

    // clear previous lines data
    // O(oldR)
    std::vector<std::string>::iterator clear = lines.begin();
    while (clear != lines.end()) {
        clear = lines.erase(clear);
    }

    // abs(current row number - startRow)
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

    // numRows*L
    while (startRow != numRows) { // loop from startRow to numRows or until list empty
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
    int undoRow;
    int undoCol;
    int numUndo;
    std::string strUndo;
    Undo::Action action = getUndo()->get(undoRow, undoCol, numUndo, strUndo);

    // stack is empty
    if (action == Undo::Action::ERROR)
        return;

    // adjust positions to place of undo
    int adjustPosition = undoRow - m_currRow;
    if (adjustPosition > 0) {
        for (int i = 0; i != adjustPosition; i++)
            m_currRowIterator++;
    }
    if (adjustPosition < 0) {
        for (int i = 0; i != adjustPosition; i--)
            m_currRowIterator--;
    }
    m_currCol = undoCol;
    m_currRow = undoRow;

    switch (action) {
    case Undo::Action::INSERT: {
        (*m_currRowIterator) = (*m_currRowIterator).insert(m_currCol, strUndo);
        break;
    }
    case Undo::Action::DELETE: {
        (*m_currRowIterator) = (*m_currRowIterator).substr(0, undoCol - numUndo) + (*m_currRowIterator).substr(undoCol);
        m_currCol = undoCol - numUndo;
        break;
    }
    case Undo::Action::SPLIT: {
        //
        std::string s = (*m_currRowIterator).substr(m_currCol);
        (*m_currRowIterator) = (*m_currRowIterator).substr(0, m_currCol);
        m_currRowIterator++;
        m_wordList.insert(m_currRowIterator, s);
        m_currRowIterator--;
        m_currRowIterator--;
        break;
    }
    case Undo::Action::JOIN: {
        m_currRowIterator++;
        std::string s = (*m_currRowIterator);
        m_currRowIterator = m_wordList.erase(m_currRowIterator);
        m_currRowIterator--;
        (*m_currRowIterator) += s;
        break;
    }
    }

}

