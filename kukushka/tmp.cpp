// �� �������, �� �����
// ��� ������ ������� (����� 10000 �������) ������ �������
TMove BestMove3()
{
	static int cnt=0;
	int MATT = 0;

	int H0 = H; // H (���� ���� )
	CalcMoves();
	Position5 p5; // ���������� �������� �������
	Board.SetPosition(&p5); // ����� � �����

	H = H0;
	//int MaxMax_Score = MIN_SCOR;
	int MaxMinMax3 = MIN_SCOR;
	TMove MaxMinMax3_Mv; MaxMinMax3_Mv.x = 9; // ���� �� ���������� ���� (�����) 3 ������
	int f1=0, i1=0; if(H==1)f1=1;
	Position5 P_x; // tmp
				   //int MaxScore3 = MIN_SCOR;

	while(1)
	{
		//int MinMax2 = MAX_SCOR;
		TMove m2;
		int MinMax3 = MAX_SCOR;
		TMove MinMax3_Mv;  MinMax3_Mv.x = 9;
		// ������ �������
		H = H0;
		TMove m1 = NextMove(f1,i1);  // �������� ������ (��� ������� ������)
		if (m1.x > 7){break;} // ����� �������� ���� �����
		Move(&m1); // ����������

				   // �� ����������� �� �������
		Position5 px; // ���������� �������� �������
		Board.SetPosition(&px); // ����� � �����
		if (FindPos(&px)) // ���� ������, �� �� ��������� ������� 1 ������
		{
			Board.GetPosition(p5); CalcMoves(); // ��������������� �������� �������
			continue;
		}

		H = -H0; // ������ ���� 
		CalcMoves(); // ������� �����
		int f2=0, i2=0; if(H==1)f2=1; // ����������� �������� �������� �� ������
		while(1)
		{

			//  2 ������� -----
			Position5 p5_1; // ��������� ���������� ����� ���� ������� ������
			Board.SetPosition(&p5_1); // ����� � �����
			m2 = NextMove(f2,i2);  // ��������� ��� ������� ������
			Move(&m2); // ����������

			if (m2.x > 7)// ����� �������� ���� �����
			{
				if (m2.x == 200){
					Move(&m2); CalcMoves(); Board.SetPosition(&P_x); // ����� � �����
					if (P_x.OnOtherField(Board.Fig[0]->x, Board.Fig[0]->y, 0)){MATT = 1;}
					else { MinMax3 = MIN_SCOR; MinMax3_Mv = m1;} // ceitnot
				}
				break;
			}

			//-------------------------------------------------------------------------------------------
			//  ������ ������� -----
			Position5 p5_2; // ��������� ���������� ����� ���� ������� ������
			Board.SetPosition(&p5_2); // ����� � �����
									  ///Board2.DrawPos(&p5_2);
			H = H0; // ������ ���� 
			CalcMoves(); // ������� �����
			int f3=0, i3=0; if(H==1)f3=1; // ����������� �������� �������� �� ������
			int Max3 = MIN_SCOR;
			TMove Max3_Mv;  Max3_Mv.x = 9;
			while(1)
			{cnt++;
			TMove m3 = NextMove(f3,i3);  // ��������� ��� ������� ������
			if (m3.x > 7){ // ����� �������� ���� �����
				if (m3.x == 200) { Max3 = MAX_SCOR; Max3_Mv = m1;} // ceitnot !!!!
				break;
			}
			Move(&m3); CalcMoves();

			int Score = Evaluate(&Board)*H; // ������ ���� 3 ������
			if (Score > Max3){Max3 = Score; Max3_Mv = m1; }
			Board.GetPosition(p5_2); CalcMoves(); // ��������������� ���������� (�������) ������� ������
			}
			//---------------------------------------------------------------------------------------

			H = -H0; // ������ ���� 
			if (Max3 < MinMax3){MinMax3 = Max3; MinMax3_Mv = Max3_Mv; 
			}

			Board.GetPosition(p5_1); CalcMoves(); // ��������������� ���������� (�������) ������� ������
		}//while2


		if (MATT) { 
			printf("\n= MATT = !!!!!"); 
			MaxMinMax3_Mv = m1; 
			H = H0;
			Board.GetPosition(p5); CalcMoves(); // ���������������
			break; 
		}

		if (MinMax3 > MaxMinMax3){MaxMinMax3 = MinMax3; MaxMinMax3_Mv = MinMax3_Mv; 
		}
		H = H0;
		Board.GetPosition(p5); CalcMoves(); // ��������������� �������� �������

	}
	return MaxMinMax3_Mv;
}
