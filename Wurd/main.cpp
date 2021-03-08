#include "EditorGui.h"
#include "TextIO.h"
#include <iostream>
#include <string>

// Do not change anything in this file other than these initializer values
<<<<<<< HEAD
const char* DICTIONARYPATH = "dictionary.txt";
=======
static const std::string DICTIONARYPATH = "dictionary.txt";
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
const int FOREGROUND_COLOR = COLOR_WHITE;
const int BACKGROUND_COLOR = COLOR_BLACK;
const int HIGHLIGHT_COLOR  = COLOR_RED;
// Choices are COLOR_x, where x is WHITE, BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN

int main(int argc, char* argv[]) {
	TextIO ti(FOREGROUND_COLOR, BACKGROUND_COLOR, HIGHLIGHT_COLOR);

	EditorGui editor(LINES, COLS);

	if (!editor.loadDictionary(DICTIONARYPATH)) {
<<<<<<< HEAD
		editor.writeStatus(std::string("Error: Can not load dictionary ") + DICTIONARYPATH);
=======
		editor.writeStatus("Error: Can not load dictionary " + DICTIONARYPATH);
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
	}
	if (argc == 2) {
		editor.loadFileToEdit(argv[1]);
	}
	editor.run();
<<<<<<< HEAD
}
=======
}       
>>>>>>> 0dfdde5f78b0d8b17c2d9fe99e4083b1627ed55c
