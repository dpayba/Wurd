#include "StudentUndo.h"

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
	if (m_undoStack.empty()) {
		std::string s;
		s.push_back(ch);
		m_undoStack.push(UndoActions(action, row, col, s));
		return;
	}
	Action topAction = m_undoStack.top().getActions();
	int topRow = m_undoStack.top().getRow();
	int topCol = m_undoStack.top().getCol();
	std::string topString = m_undoStack.top().getStr();

	std::string s;
	s.push_back(ch);

	if (action == Action::DELETE && topRow == row && topCol == col) { // consecutive deletes
		m_undoStack.pop();
		topString += s;
		m_undoStack.push(UndoActions(action, row, col, topString));
		return;
	}
	else if (action == Action::DELETE && topRow == row && topCol-1 == col) { // consecutive backspaces
		m_undoStack.pop();
		s += topString;
		m_undoStack.push(UndoActions(action, row, col, s));
		return;
	}
	else if (action == Action::INSERT && topRow == row && topCol + 1 == col) { // consecutive letters typed
		m_charactersInvolved++;
		m_undoStack.pop();
		topString += s;
		m_undoStack.push(UndoActions(action, row, col, topString));
		return;
	}
	m_undoStack.push(UndoActions(action, row, col, s));
	
	// TODO
}

StudentUndo::Action StudentUndo::get(int &row, int &col, int& count, std::string& text) {
	if (m_undoStack.empty())
		return Action::ERROR;

	Action topAction = m_undoStack.top().getActions();
	row = m_undoStack.top().getRow();
	col = m_undoStack.top().getCol();
	if (topAction == Action::INSERT) {
		count = m_charactersInvolved;
		m_charactersInvolved = 1;
	}
	else {
		count = 1;
	}

	if (topAction == Action::DELETE)
		text = m_undoStack.top().getStr();
	else
		text = "";
	m_undoStack.pop();

	switch (topAction) {
		case Action::INSERT:
			return Action::DELETE;
		case Action::DELETE:
			return Action::INSERT;
		case Action::SPLIT:
			return Action::JOIN;
		case Action::JOIN:
			return Action::SPLIT;
	}
	// TODO
}

void StudentUndo::clear() {
	while (m_undoStack.empty())
		m_undoStack.pop();
}
