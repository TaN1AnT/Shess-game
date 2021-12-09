для N строк

// ===============================================================
// это вкинуть напр в ImTexture.h
//
//  ! здесь защиты нет, строки не дольше 100 с посл. нулем !!!!!
//
// печатать можно сколько хочешь, в памяти и для отображения 
// будет 100 последних строк, думаю для норм. партии достаточно

extern HFONT font; // это тот фонт, что у меня

struct TMemo10 {
    int x, y, w, h; // лев, верх, ширина, высота
    int dy=20;
    int ind=0; // хвост
    int tp=0; // top string
    int offset = 0; // смещение по клавишах
    int N; // количество отображаемых строк
    char string[100][100]; // 100 строк по 100 символов
    //Color Fon; // пока все это с MyText(...
    //Color Ton;
    //HFONT fnt;
    TMemo10(int ix, int iy, int iw, int ih) {
        x = ix, y = iy, w = iw, h = ih; 
	N = 4; // количество строк по умолчанию
        //Fon = WinFon; // по умолчанию
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



// это добавить в обработчик клвиш ----------------------------------------


        case 38: memo.offset++; memo.Draw(); break; // вверх
        case 40: memo.offset--; memo.Draw();break; // вниз

//-------------------------------------------------------------------------










//==========================================
//
// это вкинуть например в файл Graf.cpp


TMemo10 memo(780,530, 470,148); // x,y,ширина, высота, подобрать числа для себя

void TMemo10::ClearBar()
{
    Bar(x, y, x + w, y + h, Green); // этот цвет заменить на фон WinFon

// или любой другой цвет, можно при желании добавить рамку RectAng(x, y, x + w, y + h, цвет);
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
// цифры 4 - это смещение текста относительно лев, верх прямоугольника фона.
// если нужно, изменить на свои

}

// это можно выкинуть, этопросто для проверки
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



далее все, что будет напечатано типа


memo.print("adfgf= %d %d %f",a,b,c);

(точно как в printf) будет печататься в мемо и подниматься вверх.
потом его можно клавишами вверх-вниз прокрутить в пределах 100 строк

Но переводы строк не применять, они здесь не работают. все по одной строчке!

* пока цвет фона оставил зеленым, далее заменить на нужный.


