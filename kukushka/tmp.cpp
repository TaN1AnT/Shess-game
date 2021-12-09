// из позиции, на доске
// три уровня глубины (около 10000 позиций) полный перебор
TMove BestMove3()
{
	static int cnt=0;
	int MATT = 0;

	int H0 = H; // H (цвет хода )
	CalcMoves();
	Position5 p5; // запоминаем исходную позицию
	Board.SetPosition(&p5); // берем з доски

	H = H0;
	//int MaxMax_Score = MIN_SCOR;
	int MaxMinMax3 = MIN_SCOR;
	TMove MaxMinMax3_Mv; MaxMinMax3_Mv.x = 9; // макс из максимумов груп (детей) 3 уровня
	int f1=0, i1=0; if(H==1)f1=1;
	Position5 P_x; // tmp
				   //int MaxScore3 = MIN_SCOR;

	while(1)
	{
		//int MinMax2 = MAX_SCOR;
		TMove m2;
		int MinMax3 = MAX_SCOR;
		TMove MinMax3_Mv;  MinMax3_Mv.x = 9;
		// первый уровень
		H = H0;
		TMove m1 = NextMove(f1,i1);  // посунули фигуру (ход певвого уровня)
		if (m1.x > 7){break;} // конец перебора всех ходов
		Move(&m1); // пересунули

				   // не повторяется ли позиция
		Position5 px; // запоминаем исходную позицию
		Board.SetPosition(&px); // берем з доски
		if (FindPos(&px)) // если повтор, то на следующую позицию 1 уровня
		{
			Board.GetPosition(p5); CalcMoves(); // восстанавливаем исходную позицию
			continue;
		}

		H = -H0; // меняем цвет 
		CalcMoves(); // просчет ходов
		int f2=0, i2=0; if(H==1)f2=1; // выставление индексов перебора на начало
		while(1)
		{

			//  2 уровень -----
			Position5 p5_1; // очередная подпозиция после хода первого уровня
			Board.SetPosition(&p5_1); // берем з доски
			m2 = NextMove(f2,i2);  // очередной ход второго уровня
			Move(&m2); // пересунули

			if (m2.x > 7)// конец перебора всех ходов
			{
				if (m2.x == 200){
					Move(&m2); CalcMoves(); Board.SetPosition(&P_x); // берем з доски
					if (P_x.OnOtherField(Board.Fig[0]->x, Board.Fig[0]->y, 0)){MATT = 1;}
					else { MinMax3 = MIN_SCOR; MinMax3_Mv = m1;} // ceitnot
				}
				break;
			}

			//-------------------------------------------------------------------------------------------
			//  третий уровень -----
			Position5 p5_2; // очередная подпозиция после хода первого уровня
			Board.SetPosition(&p5_2); // берем з доски
									  ///Board2.DrawPos(&p5_2);
			H = H0; // меняем цвет 
			CalcMoves(); // просчет ходов
			int f3=0, i3=0; if(H==1)f3=1; // выставление индексов перебора на начало
			int Max3 = MIN_SCOR;
			TMove Max3_Mv;  Max3_Mv.x = 9;
			while(1)
			{cnt++;
			TMove m3 = NextMove(f3,i3);  // очередной ход второго уровня
			if (m3.x > 7){ // конец перебора всех ходов
				if (m3.x == 200) { Max3 = MAX_SCOR; Max3_Mv = m1;} // ceitnot !!!!
				break;
			}
			Move(&m3); CalcMoves();

			int Score = Evaluate(&Board)*H; // оценка хода 3 уровня
			if (Score > Max3){Max3 = Score; Max3_Mv = m1; }
			Board.GetPosition(p5_2); CalcMoves(); // восстанавливаем подпозицию (потомка) первого уровня
			}
			//---------------------------------------------------------------------------------------

			H = -H0; // меняем цвет 
			if (Max3 < MinMax3){MinMax3 = Max3; MinMax3_Mv = Max3_Mv; 
			}

			Board.GetPosition(p5_1); CalcMoves(); // восстанавливаем подпозицию (потомка) первого уровня
		}//while2


		if (MATT) { 
			printf("\n= MATT = !!!!!"); 
			MaxMinMax3_Mv = m1; 
			H = H0;
			Board.GetPosition(p5); CalcMoves(); // восстанавливаем
			break; 
		}

		if (MinMax3 > MaxMinMax3){MaxMinMax3 = MinMax3; MaxMinMax3_Mv = MinMax3_Mv; 
		}
		H = H0;
		Board.GetPosition(p5); CalcMoves(); // восстанавливаем исходную позицию

	}
	return MaxMinMax3_Mv;
}
