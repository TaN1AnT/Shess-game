#include "workGL.h"
#include <stdio.h>
#include <math.h>

#include "./ImTexture.h"

#include "Shess.h"

int T_Frame = 5; // время между кадрами анимации, мс

ImgTexture SlonBl_txr;
ImgTexture SlonWt_txr;
ImgTexture TuraBl_txr;
ImgTexture TuraWt_txr;
ImgTexture KonjBl_txr;
ImgTexture KonjWt_txr;
ImgTexture KingBl_txr;
ImgTexture QueenBl_txr; // ферзь
ImgTexture QueenWt_txr; // ферзь
ImgTexture PawnBl_txr; // пешка
ImgTexture PawnWt_txr; // пешка
ImgTexture KingWt_txr;


int ind;


void init_img()
{
	PawnBl_txr.LoadFromFile(L"Pawn_bl.png");
	PawnWt_txr.LoadFromFile(L"Pawn_wt.png");
	KingBl_txr.LoadFromFile(L"King_bl.png");
	QueenBl_txr.LoadFromFile(L"ferz.png");
	QueenWt_txr.LoadFromFile(L"ferz_wt.png");
	SlonBl_txr.LoadFromFile(L"Slon_bl.png");
	SlonWt_txr.LoadFromFile(L"Slon_wt.png");
	TuraBl_txr.LoadFromFile(L"Tura_bl.png");
	TuraWt_txr.LoadFromFile(L"Tura_wt.png");
	KonjBl_txr.LoadFromFile(L"Konj_bl.png");
	KonjWt_txr.LoadFromFile(L"Konj_wt.png");
	KingWt_txr.LoadFromFile(L"King_wt.png");

}//---------

// рисує у фреймбуфер
void TBoard::DrawBoard()
{
	for(int i=0; i<8;i+=2){
		for(int h=0; h<8;h+=2){
			Bar(i * Size,  h * Size, (i + 1) * Size, (h + 1) * Size, color_white);
			Bar((i+1) * Size,  (h+1) * Size,  (i + 2) * Size,  (h + 2) * Size, color_white);
			Bar((i+1) * Size,  h * Size,  (i + 2) * Size,  (h + 1) * Size, color_black);
			Bar(i * Size,  (h+1) * Size,  (i + 1) * Size,  (h + 2) * Size, color_black);

		}
	}
	RectAng(x0-2, y0-2, x0+Size*8+2, y0+Size*8+2, Korr);
}


bool TBoard::InBoardRect(int mx, int my) // мыша на доске
{
	if (mx > x0&& mx < (x0 + 8 * Size))
		if (my > y0&& my < (y0 + 8 * Size))
			return true;
	return false;

}


void TBoard::SetFigCoord(int mx, int my, int i)
{
	Fig[i]->x = (mx-x0)/Size; Fig[i]->y = (my-y0)/Size; Fig[i]->Enbl = 1;
}

// вертає індекс фігури
int TBoard::FindBoardFig(int mx, int my)
{
	int fig_x=(mx-x0)/Size;
	int fig_y = (my-y0)/Size;
	for(int i=0;i<32;i++){
		if (Fig[i]->x == fig_x && Fig[i]->y == fig_y)return i;
	}
	return 100;
}

// берем координаты фигур из позиции p на доску (для отображения и управления) 
void TBoard::GetPosition(Position5& p)
{
	for (int i = 0; i < Count; i++) {
		if (p.x[i] > 7) { Fig[i]->Enbl = 0; continue; }
		Fig[i]->x = p.x[i];
		Fig[i]->y = p.y[i];
		Fig[i]->Enbl = 1;

	}
}

// берем позицию из доски в переменную p
void TBoard::SetPosition(Position5* p)
{
	for (int i = 0; i < Count; i++) {
		if(Fig[i]->Enbl==0){p->x[i]>7; continue;}
		p->x[i] = Fig[i]->x;
		p->y[i] = Fig[i]->y;
	}
}

Color GrBluBb(100,255,0,0);
Color GrGreen(100,0,255,0);
void TBoard::Square(int sx, int sy)
{
	BarE(x0+sx*Size, y0+sy*Size, x0+(sx+1)*Size, y0+(sy+1)*Size,GrBluBb);
}

void TBoard::Square1(int sx, int sy)
{
	BarE(x0+sx*Size, y0+sy*Size, x0+(sx+1)*Size, y0+(sy+1)*Size,GrGreen);
}


void TFigure::DrawRP() 
{
	if (Enbl == 0)return;
	for (int i = 0; i < Rcnt; i++)
		Board.Square(RP[i].x, RP[i].y);
}

void TFigure::DrawCF()
{
	if (Enbl == 0)return;
	for (int i = 0; i < Ccnt; i++)
		Board.Square1(CF[i].x, CF[i].y);

}


void test1()
{
	KingBl_txr.Print(100,100);
	SlonBl_txr.Print(100,200);
	TuraBl_txr.Print(100,300);
	KonjBl_txr.Print(100,400);
	KingWt_txr.Print(100,500);

	RectAng(30, 30, 100, 100, Blue);

}


TKing WKing; 
TKing BKing(&KingBl_txr,1);
TSlon BSlon1;
TSlon BSlon2;
TSlon WSlon1(&SlonWt_txr,0);
TSlon WSlon2(&SlonWt_txr,0);
TTura BTura1;
TTura BTura2;
TTura WTura1(&TuraWt_txr,0);
TTura WTura2(&TuraWt_txr,0);
TKonj BKonj1;
TKonj BKonj2;
TKonj WKonj1(&KonjWt_txr,0);
TKonj WKonj2(&KonjWt_txr,0);
TQueen BQueen;
TQueen WQueen(&QueenWt_txr,0);

TPawn BPawn[8];
TPawn WPawn[8];

TFigure* FG[] = {
	&WKing, &BKing, &WQueen, &BQueen, 
	&WTura1,&WTura2, &BTura1,&BTura2, 
	&WSlon1,&WSlon2, &BSlon1,&BSlon2,  
	&WKonj1,&WKonj2, &BKonj1,&BKonj2,
	&WPawn[0],&WPawn[1],&WPawn[2],&WPawn[3],&WPawn[4],&WPawn[5],&WPawn[6],&WPawn[7],
	&BPawn[0],&BPawn[1],&BPawn[2],&BPawn[3],&BPawn[4],&BPawn[5],&BPawn[6],&BPawn[7],
};

int StartPos[]{
	4,7, 4,0, 3,7, 3,0,
	0,7, 7,7, 0,0, 7,0,
	2,7, 5,7, 2,0, 5,0,
	1,7, 6,7, 1,0, 6,0,
	0,6, 1,6, 2,6, 3,6, 4,6, 5,6, 6,6, 7,6,
	0,1, 1,1, 2,1, 3,1, 4,1, 5,1, 6,1, 7,1
};

TBoard Board(FG, 32, 90, 10, 10);

void Shess_init()
{
	Board.InitColor();
	for(int i=0;i<8;i++){
		WPawn[i].color = 0;
		WPawn[i].Img = &PawnWt_txr;
	}
	for(int i=0;i<32;i++){
		FG[i]->SetPos(StartPos[2*i],StartPos[2*i+1]);
		FG[i]->Enbl = 1;
	}
}

void DrawFonRect()
{
	Bar(840, 590, 1290, 650, WinFon);
}

void TBoard::DrawFigures(float dx, float dy){
	for (int i = 0; i < Count; i++)
		if (Fig[i]->Enbl)Fig[i]->Draw(Size, x0, y0);
};

void TBoard::DrawSz(float dx, float dy){
	for (int i = 0; i < Count; i++)
		if (Fig[i]->Enbl)Fig[i]->DrawSz(Size, dx, dy);
};

void TBoard::DrawS(){
	for (int i = 0; i < Count; i++)
		if (Fig[i]->Enbl)Fig[i]->DrawSz(Size, x0, y0);
};


void BlackWhite()
{
	if(H==1){Bar(800,20,830,50,Black);}
	else {Bar(800,20,830,50,White); }
}


//
void Shess_Draw()
{
	HDC tdc;
	tdc = GetDC(hwnd);
	fdc = CreateCompatibleDC(tdc);
	RECT Rect; Rect.left = 0; Rect.top = 0; Rect.right = Rect.bottom = 0;
	GetClientRect(hwnd, &Rect);
	HBITMAP hBmp = CreateCompatibleBitmap(tdc, Board.Size*8,Board.Size*8);
	SelectObject(fdc, hBmp);

		Board.DrawBoard();
		Board.DrawFigures(0,70);
		BlackWhite();

	// Копируем изображение из теневого контекста на экран
	BitBlt(tdc, Board.x0, Board.y0, Board.Size*8, Board.Size*8,fdc, 0, 0, SRCCOPY);
			
	// Удаляем ненужные системные объекты
	ReleaseDC(hwnd, tdc); // Освобождаем контекст устройства
	DeleteDC(fdc);
	DeleteObject(hBmp);

}//Kuk_Task--------------


#define AN_N 40
// данная позиция записівается в отдельній буфер
// animation move from Fig[i]->x,Fig[i]->y   to kvadrat where mx,my
void TBoard::GoFigToCoord(int mx, int my, int fg)
{
	Position5 pos; Board.SetPosition(&pos); // mem
	Fig[fg]->CalcRP(&pos);
	int dx= (mx-x0)/Size; // destination point
	int dy= (my-y0)/Size;
	if (!Fig[fg]->On_RP(dx, dy))return;

	int N = AN_N; 

	float Xt[AN_N+1]; // path
	float Yt[AN_N+1];

	int figure_end = Board.WhoIs(dx, dy);
	if (figure_end < 32 && Fig[figure_end]->color == Fig[fg]->color) return; // тут вже є своя фігура !!!

	float x2 = dx * Size +Size / 2;
	float y2 = dy * Size +Size / 2;

	float x1 = Fig[fg]->x * Size + Size / 2;
	float y1 = Fig[fg]->y * Size + Size / 2;

	// розрахунок лінії шляху
	for(int i=0;i<=N;i++)
	{
		Xt[i] = x1 + (x2 - x1) * i / N;
		Yt[i] = y1 + (y2 - y1) * i / N;
	}
	HDC pdc; // кадр позиції без даннї фігури

	HDC tdc;
	tdc = GetDC(hwnd);
	fdc = CreateCompatibleDC(tdc);
	RECT Rect; Rect.left = 0; Rect.top = 0; Rect.right = Rect.bottom = 0;
	GetClientRect(hwnd, &Rect);
	HBITMAP hBmp = CreateCompatibleBitmap(tdc, Board.Size*8,Board.Size*8);
	SelectObject(fdc, hBmp);

	// рисуем позицію без фігури в fdc:
	Fig[fg]->Enbl = 0;
	Board.DrawBoard(); Board.DrawFigures(0,70);

	//----------------------------

	for(int i=0;i<N;i++) // до предпоследнего шага
	{
		BitBlt(tdc, Board.x0, Board.y0, Board.Size*8, Board.Size*8,fdc, 0, 0, SRCCOPY);
		Fig[fg]->Draw1(Xt[i]+Board.x0, Yt[i]+Board.y0);
		Sleep(T_Frame);
	}
	if(figure_end<32){ // тут чужа фігура
	
		Fig[figure_end]->Enbl = 0; // відключаємо її
		Fig[figure_end]->x = 8;
	}
	Fig[fg]->Enbl = 1;
	Fig[fg]->SetPos(dx,dy);

	// рисуємо кінцеве положення
	Board.DrawBoard(); Board.DrawFigures(0,70);
	Fig[fg]->Draw(Xt[N], Yt[N]);
	// Копируем изображение из теневого контекста на экран
	BitBlt(tdc, Board.x0, Board.y0, Board.Size*8, Board.Size*8,fdc, 0, 0, SRCCOPY);

	// Удаляем ненужные системные объекты
	ReleaseDC(hwnd, tdc); // Освобождаем контекст устройства
	DeleteDC(fdc);
	DeleteObject(hBmp);

}

// animation move from Fig[i]->x,Fig[i]->y   to kvadrat where mx,my
void TBoard::GoFigToCoord0(int mx, int my, int fg)
{
	Position5 pos; Board.SetPosition(&pos); // mem
	Fig[fg]->CalcRP(&pos);
	int dx= (mx-x0)/Size; // destination point
	int dy= (my-y0)/Size;
	if (!Fig[fg]->On_RP(dx, dy))return;


	int N = AN_N; 

	float Xt[AN_N+1]; // path
	float Yt[AN_N+1];

	int figure_end = Board.WhoIs(dx, dy);
	if (figure_end < 32 && Fig[figure_end]->color == Fig[fg]->color) return; // тут вже є своя фігура !!!

	float x2 = dx * Size +Size / 2;
	float y2 = dy * Size +Size / 2;

	float x1 = Fig[fg]->x * Size + Size / 2;
	float y1 = Fig[fg]->y * Size + Size / 2;

	// розрахунок лінії шляху
	for(int i=0;i<=N;i++)
	{
		Xt[i] = x1 + (x2 - x1) * i / N;
		Yt[i] = y1 + (y2 - y1) * i / N;
	}

	HDC tdc;
	tdc = GetDC(hwnd);
	fdc = CreateCompatibleDC(tdc);
	RECT Rect; Rect.left = 0; Rect.top = 0; Rect.right = Rect.bottom = 0;
	GetClientRect(hwnd, &Rect);
	HBITMAP hBmp = CreateCompatibleBitmap(tdc, Board.Size*8,Board.Size*8);
	SelectObject(fdc, hBmp);


	for(int i=0;i<N;i++) // до предпоследнего шага
	{
		Fig[fg]->Enbl = 0;
		Board.DrawBoard(); Board.DrawFigures(0,70);
		Fig[fg]->Draw(Xt[i], Yt[i]);
		//Sleep(5);
		// Копируем изображение из теневого контекста на экран
		BitBlt(tdc, Board.x0, Board.y0, Board.Size*8, Board.Size*8,fdc, 0, 0, SRCCOPY);
	}
	if(figure_end<32){ // тут чужа фігура

		Fig[figure_end]->Enbl = 0; // відключаємо її
		Fig[figure_end]->x = 8;
	}
	Fig[fg]->Enbl = 1;
	Fig[fg]->SetPos(dx,dy);

	// рисуємо кінцеве положення
	Board.DrawBoard(); Board.DrawFigures(0,70);
	Fig[fg]->Draw(Xt[N], Yt[N]);
	//Sleep(5);
	// Копируем изображение из теневого контекста на экран
	BitBlt(tdc, Board.x0, Board.y0, Board.Size*8, Board.Size*8,fdc, 0, 0, SRCCOPY);



	// Удаляем ненужные системные объекты
	ReleaseDC(hwnd, tdc); // Освобождаем контекст устройства
	DeleteDC(fdc);
	DeleteObject(hBmp);

}



int randInt(int min, int max)
{
	int r = rand() % (max - min + 1) + min;
	return r;
}

int TFigure::OverlapOther() // место фигуры совпадает с другой! (для рандомн тестирования)
{
	for(int i=0;i<5;i++){
		if (i == num)continue;
		if (x == Board.Fig[i]->x && y == Board.Fig[i]->y) return 1;
	}
	return 0;
}

int PositionBad()
{
	for(int i=0;i<5;i++){
		if (Board.Fig[i]->OverlapOther())return 1;
	}
	return 0;
}


bool Position5::IsEqual(Position5* ps)
{
	for (int i = 0; i < 5; i++){
		if (ps->x[i] > 7)continue;
		if (x[i] != ps->x[i])return false;
		if (y[i] != ps->y[i])return false;
	}
	return true;

}

Position5 Pmem[1000];
int Pmcnt;

void SavePos()
{
	Board.SetPosition(&Pmem[Pmcnt]);
	Pmcnt++;
}

bool FindPos(Position5* ps)
{
	for (int i = 0; i < Pmcnt; i++){
		//if (ps->x[i] > 7)continue;
		if (ps->IsEqual(&Pmem[i]))return true;
	}
	return false;
}

void BackMove()
{
	if (Pmcnt < 2)return;
	Pmcnt -= 2;
	Board.GetPosition(Pmem[Pmcnt++]);
}

void FirstMove()
{
	Board.GetPosition(Pmem[0]);
}


void TBoard::DrawPos(Position5* p)
{
	Position5 ps=*p;
	GetPosition(ps);
	DrawBoard();
	DrawS();
}

Position5 TestPos;
void SaveForTest()
{
	Board.SetPosition(&TestPos); 

}

void GetPosForTest()
{
	Board.GetPosition(TestPos); 
}