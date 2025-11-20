#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<fstream>
using namespace std;

const int WIDTH = 35;  //х
const int HEIGHT = 18; //y
const int GALL_X = 6;
const int GALL_Y = 12;



vector<string> gameField = {
	"==================================\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|________________________________|\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"==================================\n"
};
vector<string> gameFieldReset = {
	"==================================\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|________________________________|\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"|                                |\n",
	"==================================\n"
};
vector<string> gameFieldStart = {
	"==================================\n",
	"|                                |\n",
	"|                                |\n",
	"|    _________________           |\n",
	"|     |              |           |\n",
	"|     |            ('-')         |\n",
	"|     |             /|\\          |\n",
	"|     |             / \\          |\n",
	"|     |                          |\n",
	"|____/|\\_________________________|\n",
	"|         CONSOLE GAME!          |\n",
	"|            GALLOWS!            |\n",
	"|                                |\n",
	"|            Play: 1             |\n",
	"|            Quit: 0             |\n",
	"|                                |\n",
	"|                                |\n",
	"==================================\n"
};
vector<string> gameFieldWin = {
	"==================================\n",
	"|                                |\n",
	"|                                |\n",
	"|    _________________           |\n",
	"|     |              |           |\n",
	"|     |            ('-')         |\n",
	"|     |             /|\\          |\n",
	"|     |             / \\          |\n",
	"|     |                          |\n",
	"|____/|\\_________________________|\n",
	"|         CONSOLE GAME!          |\n",
	"|            GALLOWS!            |\n",
	"|                                |\n",
	"|             WIN!               |\n",
	"|          Next LVL: 1           |\n",
	"|            Quit:  0            |\n",
	"|                                |\n",
	"==================================\n"
};
vector<string> gameFieldLos = {
	"==================================\n",
	"|                                |\n",
	"|                                |\n",
	"|    _________________           |\n",
	"|     |              |           |\n",
	"|     |            ('-')         |\n",
	"|     |             /|\\          |\n",
	"|     |             / \\          |\n",
	"|     |                          |\n",
	"|____/|\\_________________________|\n",
	"|         CONSOLE GAME!          |\n",
	"|            GALLOWS!            |\n",
	"|                                |\n",
	"|          GAME OVER!            |\n",
	"|            Reset: 1            |\n",
	"|            Quit:  0            |\n",
	"|                                |\n",
	"==================================\n"
};

//Функции игры
void drawGameField(vector<string> &gameField);
void drawGall(int &countMistake, vector<string>& gameField);
char getLitter();
void printCorrectLitter(char& ch, string word, vector<string>& gameField);
void printMistakeLitter(char& ch, int& countMisLit, vector<string>& gameField, bool& gameOver);
bool isCorrectLitter(char ch, string word);
bool isGameOver(vector<string>& gameField);
bool isGameWin(vector<string>& gameField, string word);
void printExpLvl(int& exp,int &lvl);

int GAME_GALLOWS(vector<string>& gameField, vector<string>& words);

int main() {
	vector<string> words;
	string line;
	ifstream outFile("Word.txt");
	if (!outFile.is_open()) { // Проверяем, открылся ли файл  
		std::cerr << "Ошибка открытия файла!" << std::endl;
		return 1;
	}
	while (getline(outFile, line)) {
		words.push_back(line);
	}
	outFile.close();
	setlocale(0, "ru");
	SetConsoleCP(1251);
	srand(static_cast<unsigned int>(time(0)));
	GAME_GALLOWS(gameField, words);
	

	return 0;
}

void drawGameField(vector<string> &gameField) {
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			cout << gameField[y][x];
}

void drawGall(int &countMistake, vector<string>&gameField){
	if (countMistake == 0) {
		gameField[9][5] = '/';
		gameField[9][6] = '|';
		gameField[9][7] = '\\';
	}
	if (countMistake == 1) {
		gameField[8][6] = '|';
		gameField[7][6] = '|';
		gameField[6][6] = '|';
	}
	if (countMistake == 2) {
		gameField[5][6] = '|';
		gameField[5][7] = '/';
		gameField[4][6] = '|';
		gameField[4][7] = ' ';
		gameField[4][8] = '/';
	}
	if (countMistake == 3) {
		for (int x = 5; x < 18; x++)
			gameField[3][x] = '_';
	}
	if (countMistake == 4) {
		gameField[4][17] = '|';
	}
	if (countMistake == 5) {
		gameField[5][15] = '(';
		gameField[5][16] = '\'';
		gameField[5][17] = '-';
		gameField[5][18] = '\'';
		gameField[5][19] = ')';
	}
	if (countMistake == 6) {
		gameField[6][16] = '/';
		gameField[6][17] = '|';
		gameField[6][18] = '\\';
	}
	if (countMistake == 7) {
		gameField[7][16] = '/';
		gameField[7][17] = ' ';
		gameField[7][18] = '\\';	
	}
}

char getLitter()
{
	char ch;
	cout << "\nВведите букву: ";
	ch = _getch();
	cout << ch;
	cout << '\n';
	return ch;
}

void printCorrectLitter(char &ch, string word, vector<string>& gameField){
	int lit_x = GALL_X;
	int lit_y = GALL_Y;
	for (int i = 0; i < size(word); i++) 
		if (word[i] == ch && gameField[lit_y][lit_x + i * 3] != ch)
			gameField[lit_y][lit_x + i * 3] = ch;
}

bool isGameWin(vector<string>& gameField, string word) {
	int lenWord = static_cast<int> (size(word));
	int cut = 0;
	for (int i = 0; i < lenWord; i++) {
		if (gameField[GALL_Y][GALL_X + i * 3] != ' ') cut += 1;
	}
	if (cut == lenWord) return true;
	else return false;
}

void printExpLvl(int& exp, int &lvl){
	printf(" lvl: %d\n exp: %d", lvl, exp);
}

void printMistakeLitter(char& ch, int& countMistake, vector<string>& gameField, bool & gameOver) {
	int lit_y = GALL_Y + 2;
	int mist = countMistake;
	int lit_x = GALL_X + mist * 2;
	gameField[lit_y][lit_x] = ch;
	if (countMistake > 8) {
		gameOver = true;
	}
	else gameOver = false;
}

bool isCorrectLitter(char ch, string word){return word.find(ch) != string::npos;}

bool isGameOver(vector<string>&gameField) {
	if (gameField[7][16] == '/') return true;
	else return false;
}


int GAME_GALLOWS(vector<string>& gameField, vector<string>& words) {
	srand(static_cast<unsigned int>(time(0)));
	string word;
	char ch;
	int countMistake=0;
	int exp = 0;
	int lvl_a = 0;
	int lvl = 0;
	bool gameOver = false;
	drawGameField(gameFieldStart);
	ch = getLitter();
	if (ch == '0') return 0;
	if (ch == '1') {
		system("cls");
	}
	while (1) {
		lvl_a = 0 + rand() % size(words);
		word = words[lvl_a];
		while (!isGameWin(gameField, word)) {
			drawGameField(gameField);
			printExpLvl(exp, lvl);
			ch = getLitter();
			if (isCorrectLitter(ch, word)) {
				for (int i = 0; i < size(word); i++)
					if (word[i] == ch && gameField[GALL_Y][GALL_X + i * 3] != ch)
						 exp += 10;
				printCorrectLitter(ch, word, gameField);
				printExpLvl(exp, lvl);
			}
			if (!isCorrectLitter(ch, word)) {
				printMistakeLitter(ch, countMistake, gameField, gameOver);
				drawGall(countMistake, gameField);
				countMistake += 1;
				printExpLvl(exp, lvl);
				system("cls");
				if (countMistake == 8) {
					drawGameField(gameFieldLos);
					gameField = gameFieldReset;
					exp -= 50;
					printExpLvl(exp, lvl);
					ch = getLitter();
					if (ch == '0') break;
					if (ch == '1') {
						countMistake = 0;
						drawGameField(gameField);
						printExpLvl(exp, lvl);
						system("cls");
					}
				}
			}
			system("cls");
		}
		if (isGameWin(gameField, word)){ 
			drawGameField(gameFieldWin);
			printExpLvl(exp, lvl);
			gameField = gameFieldReset;
			lvl = lvl + 1;
			countMistake = 0;
			ch = getLitter();
			if (ch == '0') break;
			if (ch == '1') {
				drawGameField(gameField);
				printExpLvl(exp, lvl);
				system("cls");
			}
		}
	}
	return 0;
}
