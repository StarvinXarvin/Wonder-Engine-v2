#pragma once
#define NOMINMAX
#include <windows.h>
#include <stdio.h>

//#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
//
//void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI 3.141592654
#define HAVE_M_PI

typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define WINDOW_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "A Wonderful Game Engine"