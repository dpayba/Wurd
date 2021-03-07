#include "StudentUndo.h"

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
	m_undoStack.push(UndoActions(action, row, col, ch));
	
	// TODO
}

StudentUndo::Action StudentUndo::get(int &row, int &col, int& count, std::string& text) {
	UndoActions topStack = m_undoStack.top();
	row = topStack.getRow();
	col = topStack.getCol();
    return topStack.getActions();  // TODO
}

void StudentUndo::clear() {
	while (m_undoStack.empty())
		m_undoStack.pop();
}
