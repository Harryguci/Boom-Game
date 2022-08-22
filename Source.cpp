#include "CommonFunction.h"
using namespace std;

// Size of Button (standard)
const int g_B_WIDTH = 200;
const int g_B_HEIGHT = 200;

bool Init()
{
	// Check Init
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "ERROR of Everything\n";
		return 0;
	}
	// Music ON
	g_bk_audio = Mix_LoadMUS("MusicBK.mp3");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		std::cout << "ERROR of Audio\n";
		return 0;
	}
	
	// Create the window
	g_screen = SDL_SetVideoMode(g_SCREEN_WIDTH, g_SCREEN_HEIGHT, BPP, SDL_SWSURFACE);
	//g_bk_audio = Mix_LoadMUS("aesthetic-music-playlist.mp3");
	if (g_screen != NULL && g_bk_audio != NULL) return true;
	if (g_screen != NULL) return true;
	else return false;
}


// Game Screen Handle
void ReLoadBackground(SDL_Surface* Cell_Even, SDL_Surface* Cell_Odd, SDL_Surface* Cell_Active, const vector<vector<int>>& table) {
	const int size_of_matrix = 10;
	int x0 = 0;
	int y0 = 100;
	for (int i = 0; i < size_of_matrix; i++) {
		for (int j = 0; j < size_of_matrix; j++) {
			// Call ApplySurface() with x[i,j] , y[i,j] AND Check (Number or Bom) at here
			if (table[i][j] == 2) {
				CommonFunction::ApplySurface(Cell_Active, g_background, x0 + i * 50, y0 + j * 50);
				continue;
			}

			if (i % 2 == 0) {
				if (j % 2 == 0)
					CommonFunction::ApplySurface(Cell_Even, g_background, x0 + i * 50, y0 + j * 50);
				else
					CommonFunction::ApplySurface(Cell_Odd, g_background, x0 + i * 50, y0 + j * 50);
			}
			else
				if (j % 2 != 0)
					CommonFunction::ApplySurface(Cell_Even, g_background, x0 + i * 50, y0 + j * 50);
				else
					CommonFunction::ApplySurface(Cell_Odd, g_background, x0 + i * 50, y0 + j * 50);

		}
	}
}
void CreateNewGameMap(const int& size_of_matrix) {
	FILE* f = NULL;
	f = fopen("Game_map.txt", "w+");
	// The file is not found.
	if (f == NULL) {
		throw("ERROR map File");
		return;
	}
	srand(time(NULL));

	// The number of bom (The game at Starting).
	int Bom_Counter = 15;
	// 
	int** Matrix = new int* [size_of_matrix] {};
	for (int i = 0; i < size_of_matrix; i++)
		Matrix[i] = new int[size_of_matrix] {};
	for (int i = 0; i < 10; i++) {
		while (1) {
			int x, y;
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
			if (Matrix[x - 1][y - 1] != 1)
			{
				Matrix[x - 1][y - 1] = 1;
				break;
			}
		}
	}
	for (int i = 0; i < size_of_matrix; i++) {
		for (int j = 0; j < size_of_matrix; j++) {
			/* Get Random Numberand check if
			+ ODD : Set a number (1 or 2)
			+ Even : Set a bom. Then minus 1 remain number of Bom.
			*/
			fprintf(f, "%d", Matrix[i][j]);
		}
		fprintf(f, "\n");
	}
	delete[] Matrix;
	fclose(f);
}
void Display_BomMap(const int& size_of_matrix, SDL_Surface* Bom, vector<vector<int>> &Table) {
	int x0 = 5;
	int y0 = 105;
	for (int i = 0; i < size_of_matrix; i++) {
		for (int j = 0; j < size_of_matrix; j++) {
			if (Table[i][j] == 1) {
				CommonFunction::ApplySurface(Bom, g_background, x0 + i * 50, y0 + j * 50);
			}
		}
	}
}
void Demo(SDL_Surface* Boom) {
	CommonFunction::ApplySurface(Boom, g_background, 5, 105);
}
void Handle(const int& status) {
	/*
	Call :
		1. if (Status is Loading) then Create a new game map.
		2. Check Selection event
		3. Display it
		4. Return Source
	*/
}
// End of Game Screen Handle

// Behaviors of Game
bool CheckSelect(vector<vector<int>>& Table, int& current_score) {
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.
	buttons = SDL_GetMouseState(&x, &y);	// Get current location cursor.

	int x0 = 0;
	int y0 = 100;

	// Check the cell, That is pressed by the cursor.
	// is The Number or The Boom
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (x0 + i * 50 < x && x < x0 + (i + 1) * 50 && y0 + j * 50 < y && y < y0 + (j + 1) * 50) {
				if (Table[i][j] == 1) {
					return true;
				}
				else if (Table[i][j] == 2) return false;
				else {
					++current_score;

					Table[i][j] = 2;
					return false;
				}
			}
		}
	}

	return false;
}
void Set_BoomMap(vector<vector<int>>& Table, const int &size_of_matrix) {
	FILE* f = NULL;
	f = fopen("Game_map.txt", "r+");
	// If The file's not found, end function.
	if (f == NULL) {
		cout << "The file is not found";
		return;
	}

	for (int i = 0; i < size_of_matrix; i++) {
		for (int j = 0; j < size_of_matrix; j++) {
			char type_Cell;
			fscanf(f, "%c", &type_Cell);
			if (type_Cell == '1') {
				Table[i][j] = 1;
			}
		}
		fscanf(f, "\n");
	}

	// Close the map game file
	fclose(f);
}
void GetLocCursor() {
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);
	cout << "Mouse : " << x << ' ' << y << endl;
}
// Game's status.
enum status
{
	LOADING, PLAY, GAMEOVER, PAUSE, QUITGAME
};
// Display The score.
void DisplayScores(const int &current_score) {
	int x0 = 130, y0 = 20;
	string fileName;
	SDL_Surface* Digit_image = NULL;
	string text = to_string(current_score);
	for (int i = 0; i < text.length(); i++) {
		char digit = text.at(i);
		fileName = digit;
		fileName += ".png";
		Digit_image = CommonFunction::LoadImage(fileName);
		if (Digit_image != NULL) {
			CommonFunction::ApplySurface(Digit_image, g_background, x0 + i * 25, y0);
		}
	}
}
void DisplayScores(const int& current_score, const int& x0, const int& y0) {
	string fileName;
	SDL_Surface* Digit_image = NULL;
	string text = to_string(current_score);
	for (int i = 0; i < text.length(); i++) {
		char digit = text.at(i);
		fileName = digit;
		fileName += ".png";
		Digit_image = CommonFunction::LoadImage(fileName);
		if (Digit_image != NULL) {
			CommonFunction::ApplySurface(Digit_image, g_background, x0 + i * 25, y0);
		}
	}
}

bool CheckMouseLoc(const int& x0, const int& y0, const int dentaX, const int dentaY) {
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.
	buttons = SDL_GetMouseState(&x, &y);	// Get current location cursor.
	if (x0 < x && x < x0 + dentaX && y0 < y && y < y + dentaY) return true;
	else
		return false;
}
// Traveling Codes.
int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	status Status = PLAY;
	int current_score = 0;
	const int size_of_matrix = 10;
	if (Init() == false)
		return 0;
	bool is_quit = false;
	Mix_PlayMusic(g_bk_audio, -1);
	/*if (Mix_PlayMusic(g_bk_audio, -1) == -1)
	{
		std::cout << "Music not run\n";
		return 0;
	}*/
	SDL_Surface* Cell_Odd = NULL;
	SDL_Surface* Cell_Even = NULL;
	SDL_Surface* Cell_Active = NULL;
	SDL_Surface* MenuBar = NULL;
	SDL_Surface* Boom = NULL;
	SDL_Surface* Message = NULL;
	SDL_Surface* Button = NULL;

	Cell_Odd = CommonFunction::LoadImage("cell_odd.png");
	Cell_Even = CommonFunction::LoadImage("cell_even.png");
	Cell_Active = CommonFunction::LoadImage("cell_active.png");
	MenuBar = CommonFunction::LoadImage("MenuBar.png");
	Boom = CommonFunction::LoadImage("Bom.png");
	Message = CommonFunction::LoadImage("message_GameOver.png");
	Button = CommonFunction::LoadImage("button_restart.png");
	// The matrix which store locactions of bom
	vector<vector<int>> table(10, vector<int>(10));	
	// matrix have 10 columns, 10 rows (By default cell's value equal 0)

	CreateNewGameMap(10);	// Set Random Bom map (Start a new game).
	Set_BoomMap(table, 10);	// Assigning a bom map setup to Table(Matrix)

	// Loading Background (first time).
	g_background = CommonFunction::LoadImage("Back_white.png");
	while (!is_quit)
	{
		if (SDL_PollEvent(&g_event))
		{
			if (g_event.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
		}
		
		// Reload game screen
		CommonFunction::ApplySurface(g_background, g_screen, 0, 0);	// Loading White Background
		CommonFunction::ApplySurface(MenuBar, g_background, 0, 0);	// Loading Menu top bar
		ReLoadBackground(Cell_Even, Cell_Odd, Cell_Active, table);	// Loading all Cells in main screen
		DisplayScores(current_score);
		// Reload game screen

		if (Status == PLAY) {

			if (g_event.type == SDL_MOUSEBUTTONDOWN && CheckSelect(table, current_score))
			{
				Status = GAMEOVER;
				g_event.type = SDL_NOEVENT;
			}

			//GetLocCursor(); // Printing current Cursor location.
		}
		else if (Status == GAMEOVER) {
			Display_BomMap(10, Boom, table); // Display all Bom when Game Over.,
			// cout << "GAMEOVER !!\n";	// Print a message on terminal.
			if (Message != NULL) {
				CommonFunction::ApplySurface(Message, g_background, 150, 200);
				DisplayScores(current_score, 200, 320);
			}
			if (Button != NULL) {
				CommonFunction::ApplySurface(Button, g_background, 410, 30);
				if (g_event.type == SDL_MOUSEBUTTONDOWN && CheckMouseLoc(420, 30, 60, 40) == true)
					return main(argc, argv);
			}
		}

		if (SDL_Flip(g_screen) == -1)
			return 0;
	}
	// IF Terminal print "GOOD" : The program run well
	std::cout << "GOOD\n";

	// Close Music
	if (g_bk_audio != NULL)	// Only background music (Currently).
		Mix_CloseAudio();

	// Delete global variable
	CommonFunction::FreeSurface();

	//Sleep(5000);	// Delay 5s.

	// Quit
	SDL_Quit();

	return 1;
}