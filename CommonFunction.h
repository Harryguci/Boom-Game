#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <time.h>
#include <vector>
#undef main

// SCREEN

const int g_SCREEN_WIDTH = 500;
const int g_SCREEN_HEIGHT = 600;
const int BPP = 32;
const int g_ground = 500;

//static SDL_Surface* g_background = NULL;
static SDL_Surface* g_background = NULL;
static SDL_Surface* g_screen = NULL;
static SDL_Event g_event;

// AUDIO

static Mix_Music* g_bk_audio = NULL;

namespace CommonFunction
{
	// LoadImage From a File to a Element in the Game program
	SDL_Surface* LoadImage(std::string file_name);

	// Display a Image element on Screen
	void ApplySurface(SDL_Surface* image, SDL_Surface* screen, int x, int y);

	// Cleaning System before Quitting game.
	void FreeSurface();
}

#endif // !COMMOM_FUNCTION_H_
