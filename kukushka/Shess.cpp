#include "workGL.h"
#include <stdio.h>
#include <math.h>

#include "./ImTexture.h"
#include "Shess.h"

int ind;

int H; // чей текущий ход (0)-белых, 1-черных

// king all positions
FMove KP[] = {{-1,0}, {-1,-1}, {0,-1}, {1,-1},  {1,0}, {1,1}, {0,1}, {-1,1}};

// дает реально возможные ходы из данной позиции
void TKing::CalcRP(const Position5* p)
{
	Rcnt = 0;
	Ccnt = 0;
	if (Enbl == 0)return;
	Position5 p5 = *p;

	for(int i=0;i<8;i++){
		int px = x + KP[i].x; int py = y + KP[i].y;
		if( px >=0 && px<8 && py>=0 && py<8) // только на доске
		{
			int f = p5.WhoIs(px, py);
			if( f<32){ // здесь стоит фигура
				if(color==Board.Fig[f]->color){CF[Ccnt].x=px; CF[Ccnt].y=py; Ccnt++;continue;} // своя
				else {RP[Rcnt].x=px; RP[Rcnt].y=py; Rcnt++;}

			}
			RP[Rcnt].x=px; RP[Rcnt].y=py; Rcnt++;
		}
	}

}

// для короля
// выкидание полей, контролируемых вражескими фигурами (RP+CF) 
void TFigure::KingCorrect(Position5* p)
{
	if (Type != KING)return;// тільки для короля
	if (Enbl == 0)return;
	int c = 0;
	for(int i=0;i<Rcnt;i++){
		if (p->OnOtherField(RP[i].x, RP[i].y, num))
			RP[i].x = 8;// маркер, что выкинуть
	}
	FMove RP_t[30]; for(int i=0;i<Rcnt;i++)RP_t[i]=RP[i];
	for(int i=0;i<Rcnt;i++)
		if(RP_t[i].x!=8)
		{RP[c].Set(RP_t[i].x, RP_t[i].y); c++;} 
	Rcnt=c;
}

// для короля
bool Position5::OnOtherField(int ix, int iy, int no)
{
	Position5 pos; Board.SetPosition(&pos); // mem
	Board.GetPosition(this[0]);

	for(int i=0;i<32;i++){
		if (Board.Fig[no]->Enbl == 0)continue;
		if (Board.Fig[i]->Enbl == 0)continue;
		if (Board.Fig[i]->color == Board.Fig[no]->color)continue; // свои не считать
		if (i == no)continue;
		if(Board.Fig[i]->Type==KNIGHT || Board.Fig[i]->Type==KING || Board.Fig[i]->Type==PAWN)Board.Fig[i]->CalcRP(this);
		if(Board.Fig[i]->Type==BISHOP || Board.Fig[i]->Type==ROOK || Board.Fig[i]->Type==QUEEN){
			int mem = this->x[no];
			this->x[no] >7; // отключаем себя (короля), так как оно пробивает и за ними
			Board.Fig[i]->CalcRP(this); // считаем поля сонтроля без себя
			this->x[no] = mem; // восстановление
		}
		int on = Board.Fig[i]->On_RP_CF(ix, iy);
		Board.GetPosition(pos); // назад
		if (on){return true;}
	}
	return false;

}


bool TFigure::On_RP_CF(int xx, int yy)
{
	if(Type!=PAWN)
	{
		for(int i=0;i<Rcnt;i++){
			if(xx==RP[i].x && yy==RP[i].y)return true;
		}
	}
	for(int i=0;i<Ccnt;i++){
		if(xx==CF[i].x && yy==CF[i].y)return true;
	}
	return false;
}

bool TFigure::On_RP(int xx, int yy)
{
	for(int i=0;i<Rcnt;i++){
		if(xx==RP[i].x && yy==RP[i].y)return true;
	}
	return false;
}

FMove LP[] = {{-2,-1}, {-1,-2}, {1,-2},  {2,-1},  {2,1}, {1,2}, {-1,2}, {-2,1}};
void TKonj::CalcRP(const Position5* p) // дает реально возможные ходы из данной позиции
{
	Rcnt = 0;
	Ccnt = 0;
	if (Enbl == 0)return;
	Position5 p5 = *p;
	for(int i=0;i<8;i++){
		int px = x + LP[i].x; int py = y + LP[i].y;
		if( px >=0 && px<8 && py>=0 && py<8) // только на доске
		{
			int f = p5.WhoIs(px, py);
			if( f<32){ // здесь стоит фигура
				if(color==Board.Fig[f]->color)
				{CF[Ccnt].x=px; CF[Ccnt].y=py; Ccnt++;continue;}
				
			}
			RP[Rcnt].x=px; RP[Rcnt].y=py; Rcnt++;
		}
	}

}

void TTura::CalcRP(const Position5* p) // дает реально возможные ходы из данной позиции
{
	
	Rcnt = 0;
	Ccnt = 0;
	if (Enbl == 0)return;
	Position5 p5 = *p;

	for(int i=y-1;i>=0;i--){ // движение вверх
		int f = p5.WhoIs(x, i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x; CF[Ccnt].y=i; Ccnt++;}
			else {RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;
	}

	for(int i=y+1;i<8;i++){ // движение вниз
		int f = p5.WhoIs(x, i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x; CF[Ccnt].y=i; Ccnt++;}
			else {RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;
	}

	for(int i=x+1;i<8;i++){ // движение вправо
		int f = p5.WhoIs(i, y);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=i; CF[Ccnt].y=y; Ccnt++;}
			else {RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;}
			break;
		}
		RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;
	}

	for(int i=x-1;i>=0;i--){ // движение влкво
		int f = p5.WhoIs(i, y);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=i; CF[Ccnt].y=y; Ccnt++;}
			else {RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;}
			break;
		}
		RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;
	}

}


// дает реально возможные ходы из данной позиции
void TSlon::CalcRP(const Position5* p)
{
	Rcnt = 0;
	Ccnt = 0;
	Position5 p5 = *p;
	if (Enbl == 0)return;
	for(int i=1;i<8;i++){ // движение to left top
		if((x-i)<0 || (y-i)<0)break;
		int f = p5.WhoIs(x-i, y-i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x-i; CF[Ccnt].y=y-i; Ccnt++;}
			else {RP[Rcnt].x=x-i; RP[Rcnt].y=y-i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x-i; RP[Rcnt].y=y-i; Rcnt++;
	}

	for(int i=1;i<8;i++){ // движение to right top
		if((x+i)>7 || (y-i)<0)break;
		int f = p5.WhoIs(x+i, y-i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x+i; CF[Ccnt].y=y-i; Ccnt++;}
			else {RP[Rcnt].x=x+i; RP[Rcnt].y=y-i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x+i; RP[Rcnt].y=y-i; Rcnt++;
	}

	for(int i=1;i<8;i++){ // движение to right down
		if((x+i)>7 || (y+i)>7)break;
		int f = p5.WhoIs(x+i, y+i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x+i; CF[Ccnt].y=y+i; Ccnt++;}
			else {RP[Rcnt].x=x+i; RP[Rcnt].y=y+i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x+i; RP[Rcnt].y=y+i; Rcnt++;
	}

	for(int i=1;i<8;i++){ // движение to left down
		if((x-i)<0 || (y+i)>7)break;
		int f = p5.WhoIs(x-i, y+i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x-i; CF[Ccnt].y=y+i; Ccnt++;}
			else {RP[Rcnt].x=x-i; RP[Rcnt].y=y+i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x-i; RP[Rcnt].y=y+i; Rcnt++;
	}

}

void TQueen::CalcRP(const Position5* p)
{
	// слон і тура разом = королева
	Rcnt = 0;
	Ccnt = 0;
	Position5 p5 = *p;
	if (Enbl == 0)return;
	for(int i=1;i<8;i++){ // движение to left top
		if((x-i)<0 || (y-i)<0)break;
		int f = p5.WhoIs(x-i, y-i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x-i; CF[Ccnt].y=y-i; Ccnt++;}
			else {RP[Rcnt].x=x-i; RP[Rcnt].y=y-i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x-i; RP[Rcnt].y=y-i; Rcnt++;
	}

	for(int i=1;i<8;i++){ // движение to right top
		if((x+i)>7 || (y-i)<0)break;
		int f = p5.WhoIs(x+i, y-i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x+i; CF[Ccnt].y=y-i; Ccnt++;}
			else {RP[Rcnt].x=x+i; RP[Rcnt].y=y-i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x+i; RP[Rcnt].y=y-i; Rcnt++;
	}

	for(int i=1;i<8;i++){ // движение to right down
		if((x+i)>7 || (y+i)>7)break;
		int f = p5.WhoIs(x+i, y+i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x+i; CF[Ccnt].y=y+i; Ccnt++;}
			else {RP[Rcnt].x=x+i; RP[Rcnt].y=y+i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x+i; RP[Rcnt].y=y+i; Rcnt++;
	}

	for(int i=1;i<8;i++){ // движение to left down
		if((x-i)<0 || (y+i)>7)break;
		int f = p5.WhoIs(x-i, y+i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x-i; CF[Ccnt].y=y+i; Ccnt++;}
			else {RP[Rcnt].x=x-i; RP[Rcnt].y=y+i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x-i; RP[Rcnt].y=y+i; Rcnt++;
	}
 //------------------------------
	
	for(int i=y-1;i>=0;i--){ // движение вверх
		int f = p5.WhoIs(x, i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x; CF[Ccnt].y=i; Ccnt++;}
			else {RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;
	}
	
	for(int i=y+1;i<8;i++){ // движение вниз
		int f = p5.WhoIs(x, i);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=x; CF[Ccnt].y=i; Ccnt++;}
			else {RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;}
			break;
		}
		RP[Rcnt].x=x; RP[Rcnt].y=i; Rcnt++;
	}
	
	for(int i=x+1;i<8;i++){ // движение вправо
		int f = p5.WhoIs(i, y);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=i; CF[Ccnt].y=y; Ccnt++;}
			else {RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;}
			break;
		}
		RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;
	}
	
	for(int i=x-1;i>=0;i--){ // движение влкво
		int f = p5.WhoIs(i, y);
		if( f<32){ // здесь стоит фигура
			if(color==Board.Fig[f]->color){CF[Ccnt].x=i; CF[Ccnt].y=y; Ccnt++;}
			else {RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;}
			break;
		}
		RP[Rcnt].x=i; RP[Rcnt].y=y; Rcnt++;
	}
	
}

void TPawn::CalcRP(const Position5* p)
{
	Rcnt = 0;
	Ccnt = 0;
	Position5 p5 = *p;
	if (Enbl == 0)return;
	if(color){// чорний пішак
			  // поля продвижения
			int f = p5.WhoIs(x, y+1);
			if( f>31){ // здесь не стоит фигура
				RP[Rcnt].x=x; RP[Rcnt].y=y+1; Rcnt++;
				if(y==1){// тільки один раз на 2 клітинки ходити
					f = p5.WhoIs(x, y+2);
					if( f>31){ // здесь не стоит фигура
						RP[Rcnt].x=x; RP[Rcnt].y=y+2; Rcnt++;
					}
				}
			}

			// поля боя
			f = p5.WhoIs(x-1, y+1);
			if( f<32 && color!=Board.Fig[f]->color){RP[Rcnt].x=x-1; RP[Rcnt].y=y+1; Rcnt++;}
			if( f<32 && color==Board.Fig[f]->color){CF[Ccnt].x=x-1; CF[Ccnt].y=y+1; Ccnt++;}
			if( f>31){CF[Ccnt].x=x-1; CF[Ccnt].y=y+1; Ccnt++;}// нет фигури
			
			f = p5.WhoIs(x+1, y+1);
			if( f<32 && color!=Board.Fig[f]->color){RP[Rcnt].x=x+1; RP[Rcnt].y=y+1; Rcnt++;}
			if( f<32 && color==Board.Fig[f]->color){CF[Ccnt].x=x+1; CF[Ccnt].y=y+1; Ccnt++;}
			if( f>31){CF[Ccnt].x=x+1; CF[Ccnt].y=y+1; Ccnt++;}
			
	}else{// білий пішак
		  // поля продвижения
		int f = p5.WhoIs(x, y-1);
		if( f>31){ // здесь не стоит фигура
			RP[Rcnt].x=x; RP[Rcnt].y=y-1; Rcnt++;
			if(y==6){// тільки один раз на 2 клітинки ходити
				f = p5.WhoIs(x, y-2);
				if( f>31){ // здесь не стоит фигура
					RP[Rcnt].x=x; RP[Rcnt].y=y-2; Rcnt++;
				}
			}
		}
		// поля бо
		f = p5.WhoIs(x-1, y-1);
		if( f<32 && color!=Board.Fig[f]->color){RP[Rcnt].x=x-1; RP[Rcnt].y=y-1; Rcnt++;}
		if( f<32 && color==Board.Fig[f]->color){CF[Ccnt].x=x-1; CF[Ccnt].y=y-1; Ccnt++;}
		if( f>31 ){CF[Ccnt].x=x-1; CF[Ccnt].y=y-1; Ccnt++;}
		f = p5.WhoIs(x+1, y-1);
		if( f<32 && color!=Board.Fig[f]->color){RP[Rcnt].x=x+1; RP[Rcnt].y=y-1; Rcnt++;}
		if( f<32 && color==Board.Fig[f]->color){CF[Ccnt].x=x+1; CF[Ccnt].y=y-1; Ccnt++;}
		if( f>31 ){CF[Ccnt].x=x+1; CF[Ccnt].y=y-1; Ccnt++;}

	}

}

// есть ли здесь с (то есть пересечение с фигурами на доске)
bool Position5::IsHere(int ix, int iy)
{
	for(int i=0;i<32;i++){
		if (x[i] > 32)continue;
		if (x[i] == ix && y[i] == iy) return true;
	}
	return false;
}

int Position5::WhoIs (int ix, int iy) // кто здесь, какая фигура
{
	for(int i=0;i<32;i++){
		if (x[i] > 32)continue;
		if (x[i] == ix && y[i] == iy) return i; // ее номер
	}
	return 100; // нет фигур
}

int TBoard::WhoIs (int ix, int iy) // кто здесь, какая фигура  если >31 то нет ничего
{
	for(int i=0;i<32;i++){
		if (Fig[i]->Enbl==0)continue;
		if (Fig[i]->x == ix && Fig[i]->y == iy) return i; // ее номер
	}
	return 100; // нет фигур

}
