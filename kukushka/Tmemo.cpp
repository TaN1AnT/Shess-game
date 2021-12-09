��� N �����

// ===============================================================
// ��� ������� ���� � ImTexture.h
//
//  ! ����� ������ ���, ������ �� ������ 100 � ����. ����� !!!!!
//
// �������� ����� ������� ������, � ������ � ��� ����������� 
// ����� 100 ��������� �����, ����� ��� ����. ������ ����������

extern HFONT font; // ��� ��� ����, ��� � ����

struct TMemo10 {
    int x, y, w, h; // ���, ����, ������, ������
    int dy=20;
    int ind=0; // �����
    int tp=0; // top string
    int offset = 0; // �������� �� ��������
    int N; // ���������� ������������ �����
    char string[100][100]; // 100 ����� �� 100 ��������
    //Color Fon; // ���� ��� ��� � MyText(...
    //Color Ton;
    //HFONT fnt;
    TMemo10(int ix, int iy, int iw, int ih) {
        x = ix, y = iy, w = iw, h = ih; 
	N = 4; // ���������� ����� �� ���������
        //Fon = WinFon; // �� ���������
        //Ton = Black;
        //fnt = font;
    }
    void Clear();
    void ClearBar();
    void print(const char* Format, ...);
    void Draw();

};

extern TMemo10 memo; 


//==============================================================================



// ��� �������� � ���������� ����� ----------------------------------------


        case 38: memo.offset++; memo.Draw(); break; // �����
        case 40: memo.offset--; memo.Draw();break; // ����

//-------------------------------------------------------------------------










//==========================================
//
// ��� ������� �������� � ���� Graf.cpp


TMemo10 memo(780,530, 470,148); // x,y,������, ������, ��������� ����� ��� ����

void TMemo10::ClearBar()
{
    Bar(x, y, x + w, y + h, Green); // ���� ���� �������� �� ��� WinFon

// ��� ����� ������ ����, ����� ��� ������� �������� ����� RectAng(x, y, x + w, y + h, ����);
}

void TMemo10::Clear()
{
    ind = 0; tp = 0;
    ClearBar();
}



void TMemo10:: print( const char * Format,...)
{
    //----printfs-----------------------
    va_list ArgList;
    __crt_va_start(ArgList, Format);
    char str[300];
    vsprintf_s(str, 300, Format, ArgList);
    __crt_va_end(ArgList);
    //----------------------------------
    ClearBar();

    if (ind < 100)strcpy(&string[ind++][0], str);
    else{ 
        memcpy(&string[0][0], &string[1][0], 99 * sizeof(string[0]));
        strcpy(&string[99][0], str);
        ind = 100;
    }

    if (ind > N) { tp = ind - N; }
    else { if (ind == 100)tp = 99-N; }

    for(int i=0;i<N;i++){
        MyText(x+4, y+i*dy+4, string[tp+i]);
    }
    offset = 0;
}

void TMemo10::Draw()
{
    if (offset < 0)offset = 0;
	if (offset > (100-N))offset = 100-N;
    if((tp-offset)<0)offset=tp; // fixxx!
    ClearBar();
    for(int i=0;i<N;i++){
        MyText(x+4, y+i*dy+4, string[tp+i-offset]);
    }
// ����� 4 - ��� �������� ������ ������������ ���, ���� �������������� ����.
// ���� �����, �������� �� ����

}

// ��� ����� ��������, ��������� ��� ��������
void test()
{
    static int a = 0; 
    static int raz = 1;
    if(raz){
        for(int i=0;i<97;i++)
        {
            memo.print("adfgf= %d", a); a++;
        }
        raz = 0;
    }
    a++;
    memo.print("adfgf= %d",a);
}

//======================================================================



����� ���, ��� ����� ���������� ����


memo.print("adfgf= %d %d %f",a,b,c);

(����� ��� � printf) ����� ���������� � ���� � ����������� �����.
����� ��� ����� ��������� �����-���� ���������� � �������� 100 �����

�� �������� ����� �� ���������, ��� ����� �� ��������. ��� �� ����� �������!

* ���� ���� ���� ������� �������, ����� �������� �� ������.


