#pragma once
#include "gdiplusbrush.h"
#include "gdiplusgraphics.h"
#include "gdiplusgpstubs.h"
#include "gdipluspen.h"
#include "./ImTexture.h"

extern int ind;

#define PAWN			0	// пешка
#define KNIGHT			1   // конь
#define BISHOP			2	// слон
#define ROOK			3	// ладья  
#define QUEEN			4	// КОРОЛЕВА
#define KING			5	// КОРОЛЬ
#define EMPTY			6

extern ImgTexture SlonBl_txr;
extern ImgTexture SlonWt_txr;
extern ImgTexture TuraBl_txr;
extern ImgTexture TuraWt_txr;
extern ImgTexture KonjBl_txr;
extern ImgTexture KonjWt_txr;
extern ImgTexture KingBl_txr;
extern ImgTexture QueenBl_txr; // ферзь
extern ImgTexture QueenWt_txr; // ферзь
extern ImgTexture PawnBl_txr;
extern ImgTexture PawnWt_txr;
extern ImgTexture KingWt_txr;

struct FMove{ // координаты фигуры, также ход для известной фигуры
	int x, y;
	void Set(int ix, int iy) { x = ix; y = iy; }
};


// !!! условность: если координата x больше 32, то фигуры нет (она за доской)
struct Position5{
	int x[32]; // координаты для жесткого массива фигур,
	int y[32]; // определенного в Fig[]
	bool IsHere(int ix, int iy); // есть ли здесь с (то есть пересечение с фигурами на доске)
	int WhoIs (int ix, int iy); // кто здесь, какая фигура  если >5 то нет ничего
	// под ударом или под контролем других фигур противника
	bool OnOtherField(int ix, int iy, int no); 
	bool IsEqual(Position5* ps);
	Position5(){
		for(int i=0;i<32;i++){x[i]=100; y[i]=i;}
	}
};

class TFigure
{
public:
	int x, y; // координаты 0-7
	int Type; // // 5 - king, 3-tura, 2-slon, 1-kon
	int color=0; // 0 -white, 1-black
	int Enbl=1; // есть фигура или ее нет
	ImgTexture* Img; // картинка данной фигуры
	int num; // номер фигуры в условленом массиве фигур условленного порядка
	FMove RP[30]; // возможные координаты (ходы)
	int Rcnt; // их количество
	FMove CF[30]; // control field - поля контроля (нужно для короля, у нас только для белого)
	int Ccnt; // их количество, они будут высчитываться в CalcRP

	void Draw(float sz, float x0, float y0 ) { Img->Print(x*sz+sz/2, y*sz+sz/2); }
	void Draw(float ix, float iy) { Img->Print(ix, iy); }
	void Draw1(float ix, float iy) { Img->PrintE(ix, iy); }
	void DrawRP();
	void DrawCF();
	bool On_RP_CF(int xx, int yy); 
	bool On_RP(int xx, int yy); 
	void KingCorrect(Position5* p);
	virtual void CalcRP(const Position5* p){} // дает реально возможные ходы из данной позиции
	void SetPos(float xf, float yf) { x = xf, y = yf; }
	TFigure(){num = ind++;};
	TFigure(ImgTexture* it) { Img = it; x = y = 0; num = ind++; };
	TFigure(ImgTexture* it, int col) { Img = it; x = y = 0; color = col; num = ind++;};
	~TFigure(){};

private:

};


class TKing : public TFigure
{
public:
	void CalcRP(const Position5* p); // дает реально возможные ходы из данной позиции (ok-onother)
	TKing() :TFigure(&KingWt_txr) { Type = KING; }
	TKing(ImgTexture* it, int cl):TFigure(it,cl){Type = KING;}
	~TKing(){}

private:

};

class TSlon : public TFigure
{
public:
	void CalcRP(const Position5* p); // дает реально возможные ходы из данной позиции (ok)
	TSlon() :TFigure(&SlonBl_txr) { color = 1; Type=BISHOP; }
	TSlon(ImgTexture* it, int cl):TFigure(it,cl){Type = BISHOP;}
	~TSlon(){Type=BISHOP;}

private:

};

class TTura : public TFigure
{
public:
	void CalcRP(const Position5* p); // дает реально возможные ходы из данной позиции (ok)
	TTura() :TFigure(&TuraBl_txr) { color = 1; Type = ROOK; }
	TTura(ImgTexture* it, int cl):TFigure(it,cl){Type = ROOK;}
	~TTura(){Type = ROOK;}

private:

};

class TKonj : public TFigure
{
public:
	void CalcRP(const Position5* p); // дает реально возможные ходы из данной позиции (ok)
	TKonj() :TFigure(&KonjBl_txr) { color = 1; Type = KNIGHT; }
	TKonj(ImgTexture* it, int cl):TFigure(it,cl){Type = KNIGHT;}
	~TKonj(){Type = KNIGHT;}

private:

};

class TQueen : public TFigure
{
public:
	void CalcRP(const Position5* p); // дает реально возможные ходы из данной позиции (ok)
	TQueen() :TFigure(&QueenBl_txr) { color = 1; Type = QUEEN; }
	TQueen(ImgTexture* it, int cl):TFigure(it,cl){Type = QUEEN;}
	~TQueen(){Type = QUEEN;}

private:

};

class TPawn : public TFigure
{
public:
	void CalcRP(const Position5* p); // дает реально возможные ходы из данной позиции
	TPawn() :TFigure(&PawnBl_txr) { color = 1; Type = PAWN; }
	TPawn(ImgTexture* it, int cl):TFigure(it,cl){Type = PAWN;}
	~TPawn(){Type = PAWN;}

private:

};

struct TBoard
{
	Color color_white=SwKorr;
	Color color_black=Korr;
	float x0, y0; // координаты лев верх края доски
	float Size; // размер клетки
	TFigure* Fig[32];
	void GetPosition(Position5& p);
	void SetPosition(Position5* p);
	int Count; // колич фигур на доске
	void setPos(float x, float y) { x0 = x; y0 = y; }
	bool InBoardRect(int mx, int my); // мыша на доске
	void SetFigCoord(int mx, int my, int i);
	void GoFigToCoord(int mx, int my, int i);
	void GoFigToCoord0(int mx, int my, int i);
	int FindBoardFig(int mx, int my);
	int WhoIs (int ix, int iy); // кто здесь, какая фигура  если >31 то нет ничего
	void InitColor(){color_white=SwKorr; color_black=Korr;}
	void DrawBoard();
	void Square(int sx, int sy);
	void Square1(int sx, int sy);
	void DrawFigures(float dx, float dy);

	TBoard() { x0 = y0 = 10; Size = 90; }
	TBoard(TFigure* fg[], int cnt) { Count = cnt; for (int i = 0; i < Count; i++)Fig[i] = fg[i]; }
	TBoard(TFigure* fg[], int cnt, float sz, float x, float y){
		Count = cnt;
		for (int i = 0; i < Count; i++)
			Fig[i]=fg[i];
		Size = sz;
		x0 = x; y0 = y;
		color_white=SwKorr;
		color_black=Korr;

	}

};

extern TBoard Board;

extern int H; // чей текущий ход (-1)-белых, +1-черных
void SavePos();
extern int Pmcnt,Rmemcnt;
void BackMove();
void NextMove();
void FirstMove();
void BlackWhite();
void PrintHelpInWindow(int x, int y);
