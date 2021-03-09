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
		UndoActions(const Action action, int row, int col, std::string str) : m_actions(action), m_row(row), m_col(col), m_str(str) {}
		UndoActions(const Action action, int row, int col) : m_actions(action), m_row(row), m_col(col) {}
		const Action m_actions;
		int m_row;
		int m_col;
		std::string m_str;
	};
	std::stack<UndoActions> m_undoStack;
};

#endif // STUDENTUNDO_H_
