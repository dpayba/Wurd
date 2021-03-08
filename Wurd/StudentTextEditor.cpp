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
<<<<<<< HEAD
    : TextEditor(undo) {
=======
 : TextEditor(undo) {
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    m_currCol = 0;
    m_currRow = 0;
    m_wordList.push_back("");
    m_currRowIterator = m_wordList.begin();
}

StudentTextEditor::~StudentTextEditor()
{
    std::list<std::string>::iterator it = m_wordList.begin();
    while (it != m_wordList.end())
        it = m_wordList.erase(it);
}

bool StudentTextEditor::load(std::string file) {
<<<<<<< HEAD

    // clear screen
    std::ifstream infile(file);

=======
    
    // clear screen
    std::ifstream infile(file);
    
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    if (!infile) {
        std::cerr << "Error Opening File" << std::endl;
        return false;
    }
<<<<<<< HEAD

    std::list<std::string>::iterator clear = m_wordList.begin();
    while (clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }

=======
    
    std::list<std::string>::iterator clear = m_wordList.begin();
    while(clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }
    
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
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
<<<<<<< HEAD

    m_currRowIterator = m_wordList.begin();
    m_currRow = 0;
    m_currCol = 0;

=======
    
    m_currRowIterator = m_wordList.begin();
    m_currRow = 0;
    m_currCol = 0;
  
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    return true;  // TODO
}

bool StudentTextEditor::save(std::string file) {
    std::ofstream outfile(file);
    if (!outfile)
        return false;

    std::list<std::string>::iterator it = m_wordList.begin();
    while (it != m_wordList.end()) {
        outfile << (*it) << '\n';
        it++;
    }

<<<<<<< HEAD
    return true;
=======
    return true; 
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
}

void StudentTextEditor::reset() {
    std::list<std::string>::iterator clear = m_wordList.begin();
    while (clear != m_wordList.end()) {
        clear = m_wordList.erase(clear);
    }
}

void StudentTextEditor::move(Dir dir) {
    switch (dir) {
<<<<<<< HEAD
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
        m_currCol = (*m_currRowIterator).length() + 1;
        break;
=======
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
            if (m_currRow == m_wordList.size()-1)
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
            if (m_currRow == m_wordList.size()-1 && m_currCol == (*m_currRowIterator).length())
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
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    }

}

void StudentTextEditor::del() {
    std::list<std::string>::iterator last = m_wordList.end();
    last--;
<<<<<<< HEAD
    if (m_currRow == m_wordList.size() - 1 && m_currCol == (*last).length())
=======
    if (m_currRow == m_wordList.size()-1 && m_currCol == (*last).length())
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
        return;

    std::string s = *(m_currRowIterator);
    if (m_currCol == (*m_currRowIterator).length()) {
        m_currRowIterator++;
        std::string stringToCopy = *(m_currRowIterator);
        m_currRowIterator = m_wordList.erase(m_currRowIterator);
        m_currRowIterator--;
        s = s + stringToCopy;
        getUndo()->submit(Undo::Action::JOIN, m_currRow, m_currCol);
    }
    else {
        char chDelete = s.at(m_currCol);
        s = s.substr(0, m_currCol) + s.substr(m_currCol + 1);
        getUndo()->submit(Undo::Action::DELETE, m_currRow, m_currCol, chDelete);
    }
    *(m_currRowIterator) = s;

}

void StudentTextEditor::backspace() {
    std::string s = *(m_currRowIterator);
    if (m_currCol == 0 || *(m_currRowIterator) == "") {
        m_currRowIterator = m_wordList.erase(m_currRowIterator);
        m_currRowIterator--;
        m_currRow--;
        m_currCol = (*m_currRowIterator).length();
<<<<<<< HEAD
        s = *(m_currRowIterator)+s;
        getUndo()->submit(Undo::Action::JOIN, m_currRow, m_currCol);
    }
    else {
        char chDelete = s.at(m_currCol - 1);
=======
        s = *(m_currRowIterator) + s;
        getUndo()->submit(Undo::Action::JOIN, m_currRow, m_currCol);
    }
    else {
        char chDelete = s.at(m_currCol-1);
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
        s = s.substr(0, m_currCol - 1) + s.substr(m_currCol);
        m_currCol--;
        getUndo()->submit(Undo::Action::DELETE, m_currRow, m_currCol, chDelete);
    }
    *(m_currRowIterator) = s;
}

void StudentTextEditor::insert(char ch) {
    std::string s = *(m_currRowIterator);
    if (ch == '\t') {
        s = s.substr(0, m_currCol) + "    " + s.substr(m_currCol);
        m_currCol += 4;
        *(m_currRowIterator) = s;
        getUndo()->submit(Undo::Action::INSERT, m_currRow, m_currCol, ch);
        return;
    }
    s = s.substr(0, m_currCol) + ch + s.substr(m_currCol);
    *(m_currRowIterator) = s;
    m_currCol++;
    getUndo()->submit(Undo::Action::INSERT, m_currRow, m_currCol, ch);
}

void StudentTextEditor::enter() {
    getUndo()->submit(Undo::Action::SPLIT, m_currRow, m_currCol);
    std::string s = (*m_currRowIterator).substr(m_currCol);
    (*m_currRowIterator) = (*m_currRowIterator).substr(0, m_currCol);
    m_currRowIterator++;
    m_wordList.insert(m_currRowIterator, s);
    m_currRowIterator--;
    m_currRow++;
    m_currCol = 0;
    // TODO
}

void StudentTextEditor::getPos(int& row, int& col) const {
    row = m_currRow;
    col = m_currCol;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    if (startRow < 0 || numRows < 0 || startRow > lines.size())
        return -1;
<<<<<<< HEAD

    int linesAdded = 0;

    std::vector<std::string>::iterator clear = lines.begin();
    while (clear != lines.end()) {
        clear = lines.erase(clear);
    }

    int adjustPosition = startRow - m_currRow;
    std::list<std::string>::iterator it = m_currRowIterator;

=======
    
    int linesAdded = 0;
    
    std::vector<std::string>::iterator clear = lines.begin();
    while(clear != lines.end()) {
        clear = lines.erase(clear);
    }
    
    int adjustPosition = startRow - m_currRow;
    std::list<std::string>::iterator it = m_currRowIterator;
    
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    // set it to startrow
    if (adjustPosition > 0) {
        for (int i = 0; i != adjustPosition; i++)
            it++;
    }
    if (adjustPosition < 0) {
        for (int i = 0; i != adjustPosition; i--)
            it--;
    }
<<<<<<< HEAD

=======
    
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    while (startRow != numRows) {
        if (it == m_wordList.end())
            break;
        lines.push_back(*it);
<<<<<<< HEAD
        startRow++;
        it++;
        linesAdded++;
    }

=======
        startRow++; 
        it++; 
        linesAdded++;
    }
    
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    return linesAdded;
}

void StudentTextEditor::undo() {
    int undoRow;
    int undoCol;
    int numUndo;
    std::string strUndo;
    Undo::Action action = getUndo()->get(undoRow, undoCol, numUndo, strUndo);

    if (action == Undo::Action::ERROR)
        return;

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
<<<<<<< HEAD
    case Undo::Action::INSERT: {
        (*m_currRowIterator) = (*m_currRowIterator).substr(0, m_currCol) + strUndo + (*m_currRowIterator).substr(m_currCol);
        break;
    }
    case Undo::Action::DELETE: {
        (*m_currRowIterator) = (*m_currRowIterator).substr(0, undoCol - numUndo) + (*m_currRowIterator).substr(undoCol);
        m_currCol = undoCol - numUndo;
        break;
    }
    case Undo::Action::SPLIT: {
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
=======
        case Undo::Action::INSERT: {
            (*m_currRowIterator) = (*m_currRowIterator).substr(0, m_currCol) + strUndo + (*m_currRowIterator).substr(m_currCol);
            break;
        }
        case Undo::Action::DELETE: {
            (*m_currRowIterator) = (*m_currRowIterator).substr(0, undoCol - numUndo) + (*m_currRowIterator).substr(undoCol);
            m_currCol = undoCol - numUndo;
            break;
        }
        case Undo::Action::SPLIT: {
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
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
    }

}

