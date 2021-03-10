#include "StudentUndo.h"

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
	if (m_undoStack.empty()) {
		if (ch == '\t') {
			m_undoStack.push(UndoActions(action, row, col, "    "));
			return;
		}
		else {
			std::string s;
			s.push_back(ch);
			m_undoStack.push(UndoActions(action, row, col, s));
			return;
		}
	}

	// get values at top of stack to check for batching
	Action topAction = m_undoStack.top().m_actions;
	int topRow = m_undoStack.top().m_row;
	int topCol = m_undoStack.top().m_col;
	std::string topString = m_undoStack.top().m_str;

	if (ch == '\t') {
		m_undoStack.push(UndoActions(action, row, col, "    "));
		return;
	}

	// turn char into a string
	std::string s;
	s.push_back(ch);


	if (action == Action::DELETE && topRow == row && topCol == col && topAction == Action::DELETE) { // consecutive deletes
		m_undoStack.pop();
		topString += s;
		m_undoStack.push(UndoActions(action, row, col, topString));
		return;
	}
	else if (action == Action::DELETE && topRow == row && topCol - 1 == col && topAction == Action::DELETE) { // consecutive backspaces
		m_undoStack.pop();
		s += topString;
		m_undoStack.push(UndoActions(action, row, col, s));
		return;
	}
	else if (action == Action::INSERT && topRow == row && topCol + 1 == col && topAction == Action::INSERT) { // consecutive letters typed
		m_undoStack.pop();
		topString += s;
		m_undoStack.push(UndoActions(action, row, col, topString));
		return;
	}

	// push actions done
	m_undoStack.push(UndoActions(action, row, col, s));

}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
	if (m_undoStack.empty())
		return Action::ERROR;

	Action topAction = m_undoStack.top().m_actions;
	row = m_undoStack.top().m_row;
	col = m_undoStack.top().m_col;

	if (topAction == Action::INSERT) {
		count = m_undoStack.top().m_str.length();
	}
	else {
		count = 1;
	}

	if (topAction == Action::DELETE)
		text = m_undoStack.top().m_str;
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
	case Action::ERROR:
		return Action::ERROR;
	}
	return Action::ERROR;
}

void StudentUndo::clear() {
	// O(N)
	while (!m_undoStack.empty())
		m_undoStack.pop();
}
