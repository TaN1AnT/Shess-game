#include "workGL.h"
#include <stdio.h>

#include "gdiplusbrush.h"
#include "gdiplusgraphics.h"
#include "gdiplusgpstubs.h"
#include "gdipluspen.h"
#include "gdipluscolor.h"

#include <stdlib.h>

#include "Shess.h"
#include "./ImTexture.h"


Color Blue(0,0,255);
Color Green(0,255,0);
Color White(255,255,255);
Color Black(0,0,0);
Color SwKorr(240,227,176);
Color Korr(153,102,0);
Color GrBlu(191,191,255);
Color WinFon(200,200,200);

int ImgTexture::LoadFromFile(const wchar_t* fname)
{
    if(Loaded)delete bmp;
    bmp=new Bitmap(fname);
    Width=bmp->GetWidth();
    Height=bmp->GetHeight();
    Loaded=1;
    return 0;
}

// !!!!! застосовувати обережно, буде їсти память, потрібен зовнішній fdc і його звільнення!!!!!
void ImgTexture::DrawImage(int x, int y)
{
    Graphics graphics(fdc);
    graphics.DrawImage(bmp, x, y, Width, Height);

}//ImgTexture::DrawImage------------------------

 // не звільняє память hdc !!!! це не самостійна, а внутрішня функція
void ImgTexture::DrawImageE(int x, int y)
{
    HDC hdc = GetDC(hwnd);
    Graphics graphics(hdc);
    graphics.DrawImage(bmp, x, y, Width, Height);
    //ReleaseDC(hwnd, fdc); // Освобождаем контекст устройства

}//ImgTexture::DrawImage------------------------


void ImgTexture::Print(float x, float y)
{
    DrawImage(x-Width/2, y-Height/2);
}

void ImgTexture::PrintE(float x, float y)
{
    DrawImageE(x-Width/2, y-Height/2);
}


void Bar(float SX,float SY,float EX,float EY, Color clr)
{
    RectF rct(SX, SY, EX-SX, EY-SY);
    Graphics g(fdc);
    SolidBrush  Brsh(clr);
    g.FillRectangle(&Brsh, rct);
}

// прямо на екран виводить, не у фреймбуфер
void BarE(float SX,float SY,float EX,float EY, Color clr)
{
    RectF rct(SX, SY, EX-SX, EY-SY);
    HDC hdc = GetDC(hwnd);
    Graphics g(hdc);
    SolidBrush  Brsh(clr);
    g.FillRectangle(&Brsh, rct);
    ReleaseDC(hwnd, hdc); // Освобождаем контекст устройства
}

void RectAng(float SX, float SY, float EX, float EY, Color clr)
{
    HDC hdc = GetDC(hwnd);
    Graphics g(hdc);
    Pen      pen(clr,1);
    g.DrawRectangle(&pen, SX, SY, EX-SX, EY-SY);
    ReleaseDC(hwnd, hdc); // Освобождаем контекст устройства
}

