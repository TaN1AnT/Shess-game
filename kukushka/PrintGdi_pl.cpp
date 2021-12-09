// ��� ������� �������� ����� �� �������������� rect , ������������ �� � ���� �����
void prtH(int x, int y,Color clr, int FntSize,RectF  rect, const char* str)
{
    //----------------------------------
    HDC hdc = GetDC(hwnd);
    Graphics g(hdc);
    FontFamily  fontFamily(L"Arial");
    Font        font(&fontFamily, FntSize, FontStyleRegular, UnitPixel);
    SolidBrush  solidBrush(clr);

    wchar_t wcstr[300];
    size_t r, sw, cc;
    r = strlen(str);
    mbstowcs_s(&r, wcstr, 300, str, 300);
    SolidBrush  wb(Color(255,200,255,200));// ���� ����
    g.FillRectangle(&wb, rect);
    g.DrawString(wcstr, -1, &font, rect, NULL, &solidBrush);
    ReleaseDC(hwnd, hdc); // ����������� �������� ����������
}
