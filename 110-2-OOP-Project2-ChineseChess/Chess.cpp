#include "Chess.h"

// every chesses' move

bool King::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	// �M���(rkX, rkY)��N(bkX, bkY)
	int rkX, rkY, bkX, bkY;
	for (int b = 0, r = 7; b <= 2; b++, r++) {
		for (int j = 3; j <= 5; j++) {
			if (chessBoard[b][j]->getName() == "king") {
				bkX = b;
				bkY = j;
			}
			if (chessBoard[r][j]->getName() == "king") {
				rkX = r;
				rkY = j;
			}
		}
	}
	int countChess = 0;
	if (rkY == bkY) { // �p�G����b�P�@�����u�W
		for (int i = bkX + 1; i < rkX; i++) {
			if (chessBoard[i][rkY]->getName() != "empty") countChess++;
		}
		if (countChess == 0) { // ����������
			if (color == "red" && (x2 == bkX && y2 == bkY)) {
				 return true;
			}
			if (color == "black" && (x2 == rkX && y2 == rkY)) {
				return true;
			}
		}
	}


	if (y2 >= 3 && y2 <= 5) {
		if (color == "red") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 7 && x2 <= 9) {
					if (abs(x1 - x2) + abs(y1 - y2) == 1) {
						return true;
					}
				}
			}
		}
		if (color == "black") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 0 && x2 <= 2) {
					if (abs(x1 - x2) + abs(y1 - y2) == 1) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Advisor::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	if (y2 >= 3 && y2 <= 5) {
		if (color == "red") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 7 && x2 <= 9) {
					if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1) {
						return true;
					}
				}
			}
		}
		if (color == "black") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 0 && x2 <= 2) {
					if (abs(x1 - x2) == 1 && abs(y1 - y2) == 1) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Elephant::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	if (y2 >= 0 && y2 <= 8) {
		if (color == "red") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 5 && x2 <= 9) {
					if (abs(x1 - x2) == 2 && abs(y1 - y2) == 2) {
						// �p�G�Цr�������Ѥl�N���ਫ
						if (x1 > x2 && y1 < y2) { // ���k�W��
							if (chessBoard[x1 - 1][y1 + 1]->getName() == "empty") {
								return true;
							}
						}
						if (x1 > x2 && y1 > y2) { // �����W��
							if (chessBoard[x1 - 1][y1 - 1]->getName() == "empty") {
								return true;
							}
						}
						if (x1 < x2 && y1 < y2) { // ���k�U��
							if (chessBoard[x1 + 1][y1 + 1]->getName() == "empty") {
								return true;
							}
						}
						if (x1 < x2 && y1 > y2) { // �����U��
							if (chessBoard[x1 + 1][y1 - 1]->getName() == "empty") {
								return true;
							}
						}
					}
				}
			}
		}
		if (color == "black") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 0 && x2 <= 4) {
					if (abs(x1 - x2) == 2 && abs(y1 - y2) == 2) {
						// �p�G�Цr�������Ѥl�N���ਫ
						if (x1 > x2 && y1 < y2) { // ���k�W��
							if (chessBoard[x1 - 1][y1 + 1]->getName() == "empty") {
								return true;
							}
						}
						if (x1 > x2 && y1 > y2) { // �����W��
							if (chessBoard[x1 - 1][y1 - 1]->getName() == "empty") {
								return true;
							}
						}
						if (x1 < x2 && y1 < y2) { // ���k�U��
							if (chessBoard[x1 + 1][y1 + 1]->getName() == "empty") {
								return true;
							}
						}
						if (x1 < x2 && y1 > y2) { // �����U��
							if (chessBoard[x1 + 1][y1 - 1]->getName() == "empty") {
								return true;
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool Horse::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	if (y2 >= 0 && y2 <= 8) {
		if (color == "red") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 0 && x2 <= 9) {
					if (abs(x1 - x2) + abs(y1 - y2) == 3) {
						// ����Q�d�차�}
						if (abs(x1 - x2) == 1) { // ����k
							if (y1 < y2) { // ���k
								if (chessBoard[x1][y1 + 1]->getName() == "empty") {
									return true;
								}
							}
							if (y1 > y2) { // ����
								if (chessBoard[x1][y1 - 1]->getName() == "empty") {
									return true;
								}
							}
						}
						if (abs(y1 - y2) == 1) { // �W��U
							if (x1 > x2) { // ���W
								if (chessBoard[x1 - 1][y1]->getName() == "empty") {
									return true;
								}
							}
							if (x1 < x2) { // ���U
								if (chessBoard[x1 + 1][y1]->getName() == "empty") {
									return true;
								}
							}
						}
					}
				}
			}
		}
		if (color == "black") {
			if (chessBoard[x2][y2]->getColor() != color) {
				if (x2 >= 0 && x2 <= 9) {
					if (abs(x1 - x2) + abs(y1 - y2) == 3) {
						// ����Q�d�차�}
						if (abs(x1 - x2) == 1) { // ����k
							if (y1 < y2) { // ���k
								if (chessBoard[x1][y1 + 1]->getName() == "empty") {
									return true;
								}
							}
							if (y1 > y2) { // ����
								if (chessBoard[x1][y1 - 1]->getName() == "empty") {
									return true;
								}
							}
						}
						if (abs(y1 - y2) == 1) { // �W��U
							if (x1 > x2) { // ���W
								if (chessBoard[x1 - 1][y1]->getName() == "empty") {
									return true;
								}
							}
							if (x1 < x2) { // ���U
								if (chessBoard[x1 + 1][y1]->getName() == "empty") {
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

bool Chariot::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	// �P�_�n�h���I�A�u��Oempty�άO���P���C��
	if (chessBoard[x2][y2]->getColor() != color) {
		// �P�_���I�����O�_���u
		if ((x1 == x2 && y1 != y2) || (x1 != x2 && y1 == y2)) {
			// �A�P�_�����O�_���Ѥl
			if (x1 == x2) { // �
				if (y1 < y2) { // ���k
					for (int i = y1 + 1; i < y2; i++) {
						if (chessBoard[x1][i]->getName() != "empty") return false;
					}
				}
				if (y1 > y2) { // ����
					for (int i = y1 - 1; i > y2; i--) {
						if (chessBoard[x1][i]->getName() != "empty") return false;
					}
				}

			}
			if (y1 == y2) { // �
				if (x1 < x2) { // ���U
					for (int i = x1 + 1; i < x2; i++) {
						if (chessBoard[i][y1]->getName() != "empty") return false;
					}
				}
				if (x1 > x2) { // ����
					for (int i = x1 - 1; i > x2; i--) {
						if (chessBoard[i][y1]->getName() != "empty") return false;
					}
				}
			}
			return true;
		}
	}
	return false;

}

bool Cannon::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	// �P�_�n�h���I�A
	if (chessBoard[x2][y2]->getColor() != color) {
		// �P�_���I�����O�_���u
		if ((x1 == x2 && y1 != y2) || (x1 != x2 && y1 == y2)) {
			// �A�P�_�����O�_���Ѥl
			if (x1 == x2) { // �
				if (y1 < y2) { // ���k
					if (chessBoard[x2][y2]->getName() == "empty") { // �n�h���I�Oempty
						for (int i = y1 + 1; i < y2; i++) {
							if (chessBoard[x1][i]->getName() != "empty") return false;
						}
					}
					else { // �n�h���I�O���P�C�⪺�Ѥl
						int countChess = 0;
						for (int i = y1 + 1; i < y2; i++) {
							if (chessBoard[x1][i]->getName() != "empty") countChess++;
						}
						if (countChess != 1) return false;
					}

				}
				if (y1 > y2) { // ����
					if (chessBoard[x2][y2]->getName() == "empty") { // �n�h���I�Oempty
						for (int i = y1 - 1; i > y2; i--) {
							if (chessBoard[x1][i]->getName() != "empty") return false;
						}
					}
					else { // �n�h���I�O���P�C�⪺�Ѥl
						int countChess = 0;
						for (int i = y1 - 1; i > y2; i--) {
							if (chessBoard[x1][i]->getName() != "empty") countChess++;
						}
						if (countChess != 1) return false;
					}
				}

			}
			if (y1 == y2) { // �
				if (x1 < x2) { // ���U
					if (chessBoard[x2][y2]->getName() == "empty") { // �n�h���I�Oempty
						for (int i = x1 + 1; i < x2; i++) {
							if (chessBoard[i][y1]->getName() != "empty") return false;
						}
					}
					else { // �n�h���I�O���P�C�⪺�Ѥl
						int countChess = 0;
						for (int i = x1 + 1; i < x2; i++) {
							if (chessBoard[i][y1]->getName() != "empty") countChess++;
						}
						if (countChess != 1) return false;
					}

				}
				if (x1 > x2) { // ����
					if (chessBoard[x2][y2]->getName() == "empty") { // �n�h���I�Oempty
						for (int i = x1 - 1; i > x2; i--) {
							if (chessBoard[i][y1]->getName() != "empty") return false;
						}
					}
					else { // �n�h���I�O���P�C�⪺�Ѥl
						int countChess = 0;
						for (int i = x1 - 1; i > x2; i--) {
							if (chessBoard[i][y1]->getName() != "empty") countChess++;
						}
						if (countChess != 1) return false;
					}
				}
			}
			return true;
		}
	}

	// �P�_�n�h���I�A�O���P���C��
	if (chessBoard[x2][y2]->getColor() != color) {
		// �P�_���I�����O�_���u
		if ((x1 == x2 && y1 != y2) || (x1 != x2 && y1 == y2)) {
			// �A�P�_�����O�_���Ѥl
			if (x1 == x2) { // �
				if (y1 < y2) { // ���k
					for (int i = y1 + 1; i < y2; i++) {
						if (chessBoard[x1][i]->getName() != "empty") return false;
					}
				}
				if (y1 > y2) { // ����
					for (int i = y1 - 1; i > y2; i--) {
						if (chessBoard[x1][i]->getName() != "empty") return false;
					}
				}

			}
			if (y1 == y2) { // �
				if (x1 < x2) { // ���U
					for (int i = x1 + 1; i < x2; i++) {
						if (chessBoard[i][y1]->getName() != "empty") return false;
					}
				}
				if (x1 > x2) { // ����
					for (int i = x1 - 1; i > x2; i--) {
						if (chessBoard[i][y1]->getName() != "empty") return false;
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool Soldier::canMove(int x1, int y1, int x2, int y2, std::vector<std::vector<Chess*>> chessBoard)
{
	if (color == "red") {
		if (chessBoard[x2][y2]->getColor() != color) {
			// �u�ઽ�� ���W
			if (y1 == y2 && x2 - x1 == -1) return true;
			// ���L�e => �i�H����k
			if (x1 <= 4) { // �L�e
				if (x1 == x2 && abs(y1 - y2) == 1) {
					return true;
				}
			}
		}
	}
	if (color == "black") {
		if (chessBoard[x2][y2]->getColor() != color) {
			// �u�ઽ�� ���U
			if (y1 == y2 && x2 - x1 == 1) return true;
			// ���L�e => �i�H����k
			if (x1 >= 5) { // �L�e
				if (x1 == x2 && abs(y1 - y2) == 1) {
					return true;
				}
			}
		}
	}
	return false;
}