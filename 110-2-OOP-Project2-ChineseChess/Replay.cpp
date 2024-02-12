#include "Replay.h"

void Replay::selectFile()
{
	char filename[MAX_PATH] = { 0 };
	char currFile[MAX_PATH] = { 0 };

	OPENFILENAMEA ofn = { 0 };

	ZeroMemory(&filename, sizeof(filename));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files(*.txt)\0*.txt\0\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Select File";
	ofn.Flags = OFN_EXPLORER;
	ofn.lpstrCustomFilter = NULL;
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	GetCurrentDirectoryA(MAX_PATH, currFile);

	if (GetOpenFileNameA((LPOPENFILENAMEA)&ofn))
	{
		// std::cout << "You chose the file \"" << ofn.lpstrFile << "\"\n";
		for (int i = 0; i < strlen(filename); i++)
		{
			if (filename[i] == '\\')
				readPath += "\\\\";
			else
				readPath += filename[i];
		}
		// std::cout << readPath << "\n";
	}
	else
	{
		// All this stuff below is to tell you exactly how you messed up above.
		// Once you've got that fixed, you can often (not always!) reduce it to a 'user cancelled' assumption.
		switch (CommDlgExtendedError())
		{
		case CDERR_DIALOGFAILURE:
			std::cout << "CDERR_DIALOGFAILURE\n";
			break;
		case CDERR_FINDRESFAILURE:
			std::cout << "CDERR_FINDRESFAILURE\n";
			break;
		case CDERR_INITIALIZATION:
			std::cout << "CDERR_INITIALIZATION\n";
			break;
		case CDERR_LOADRESFAILURE:
			std::cout << "CDERR_LOADRESFAILURE\n";
			break;
		case CDERR_LOADSTRFAILURE:
			std::cout << "CDERR_LOADSTRFAILURE\n";
			break;
		case CDERR_LOCKRESFAILURE:
			std::cout << "CDERR_LOCKRESFAILURE\n";
			break;
		case CDERR_MEMALLOCFAILURE:
			std::cout << "CDERR_MEMALLOCFAILURE\n";
			break;
		case CDERR_MEMLOCKFAILURE:
			std::cout << "CDERR_MEMLOCKFAILURE\n";
			break;
		case CDERR_NOHINSTANCE:
			std::cout << "CDERR_NOHINSTANCE\n";
			break;
		case CDERR_NOHOOK:
			std::cout << "CDERR_NOHOOK\n";
			break;
		case CDERR_NOTEMPLATE:
			std::cout << "CDERR_NOTEMPLATE\n";
			break;
		case CDERR_STRUCTSIZE:
			std::cout << "CDERR_STRUCTSIZE\n";
			break;
		case FNERR_BUFFERTOOSMALL:
			std::cout << "FNERR_BUFFERTOOSMALL\n";
			break;
		case FNERR_INVALIDFILENAME:
			std::cout << "FNERR_INVALIDFILENAME\n";
			break;
		case FNERR_SUBCLASSFAILURE:
			std::cout << "FNERR_SUBCLASSFAILURE\n";
			break;
		default:
			std::cout << "You cancelled.\n";
		}
	}
	SetCurrentDirectoryA(currFile);
}

void Replay::readFile()
{
	std::ifstream fin(readPath);
	for (std::string input; getline(fin, input);)
	{
		std::stringstream ss(input);
		std::string temp, write = "";
		for (int i = 0; getline(ss, temp, ' '); i++)
		{
			if (temp.find("Red") != std::string::npos)
				gameStatus = 0;
			else if (temp.find("Black") != std::string::npos)
				gameStatus = 1;
			switch (i)
			{
			case 4:
			case 5:
			case 7:
			case 8:
				write += temp; break;
			}
		}
		if (gameStatus == -1)
			moveLog.push_back(write);
	}
	fin.close();
}

void Replay::reset()
{
	readPath = "";
	readMoveIndex = 0;
	gameStatus = -1;
	moveLog.clear();
}

std::string Replay::operator++(int)
{
	std::string temp = moveLog[readMoveIndex];
	if (readMoveIndex + 1 < moveLog.size())
		readMoveIndex++;
	return temp;
}
