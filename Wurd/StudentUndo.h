#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <stack>

class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
	struct UndoActions {
		UndoActions(Action action, int row, int col, char ch) : m_actions(action), m_row(row), m_col(col), m_ch(ch) {}
		Action getActions() const { return m_actions; }
		int getRow() const { return m_row;  }
		int getCol() const { return m_col; }
		char getChar() const { return m_ch;  }
	private:
		Action m_actions;
		int m_row;
		int m_col;
		char m_ch;
	};
	std::stack<UndoActions> m_undoStack;
};

#endif // STUDENTUNDO_H_
