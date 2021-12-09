#pragma once
#include <windows.h>
#pragma comment(lib,"Gdi32.lib")

// Файлы заголовков C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <gdiplus.h>

extern HWND hwnd;

using namespace Gdiplus;

extern Color Blue;
extern Color White;
extern Color Black;
extern Color Green;
extern Color Red;
extern Color Korr;
extern Color SwKorr;
extern Color GrBlu;
extern Color WinFon;

extern int Stop;

void Bar(float SX, float SY, float EX, float EY, Color clr);
void BarE(float SX, float SY, float EX, float EY, Color clr);
void RectAng(float SX, float SY, float EX, float EY, Color clr);

void Shess_init();
void init_img();
void Shess_Draw();
void MyText(int x, int y, const char* txt);




