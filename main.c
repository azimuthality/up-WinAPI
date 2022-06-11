#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0A00
#include <windows.h>
#define masSize 10
#include <time.h>
#include <math.h>

RECT mas;
RECT rct;
double a = 0;

void FillMas()
{
    mas.left=rand() % 1;
    mas.top=rand() % 1;
    mas.right=mas.left + 100; //mas.left+100;
    mas.bottom=mas.top;
}

void WinMove()
{
    mas.left += 3;
    mas.right += 3;
    mas.top= 300-(int)(150*sin(a)); //rand() % 720;
    mas.bottom=mas.top+100;
    a+=0.35;
}

void WinShow(HDC dc)
{
    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(0,0,0));
    Rectangle(dc,0,0,1200,600);

    SelectObject(dc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(dc, RGB(255,255,255));
    SelectObject(dc, GetStockObject(DC_PEN));
    SetDCPenColor(dc, RGB(0,0,0));
    Ellipse(dc,mas.left, mas.top, mas.right,mas.bottom);
}
LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == WM_DESTROY)
    PostQuitMessage(0);

    else return DefWindowProcA(hwnd, message, wparam, lparam);
}

int main()
{
    WNDCLASSA wcl;
    memset(&wcl, 0, sizeof(WNDCLASSA));
    wcl.lpszClassName = "myWindows";
    wcl.lpfnWndProc = WndProc;
    RegisterClassA(&wcl);

    HWND hwnd;
    hwnd = CreateWindow("myWindows", "MyWindow", WS_OVERLAPPEDWINDOW, 0, 0, 1200, 600, NULL, NULL, NULL, NULL);

    HDC dc = GetDC(hwnd);

    ShowWindow(hwnd, SW_NORMAL);
    FillMas();

    MSG msg;

    while(1)
    {
    if (PeekMessageA(&msg,NULL,0,0,PM_REMOVE))
    {
    if (msg.message == WM_QUIT)break;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }

    WinMove();
    WinShow(dc);
    Sleep(5);
    }
    return 0;
}
