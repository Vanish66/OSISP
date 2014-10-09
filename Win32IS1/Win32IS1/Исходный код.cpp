#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
// ����������� �������:
int WINAPI WinMain(HINSTANCE hInst, // ���������� ���������� ����������
                   HINSTANCE hPrevInst, // �� ����������
                   LPSTR lpCmdLine, // �� ����������
                   int nCmdShow) // ����� ����������� ������
{
    TCHAR szClassName[] = L"�����"; // ������ � ������ ������
    HWND hMainWnd; // ������ ���������� �������� ������
    MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������
    WNDCLASSEX wc; // ������ ���������, ��� ��������� � ������ ������ WNDCLASSEX
    wc.cbSize        = sizeof(wc); // ������ ��������� (� ������)
    wc.style         = CS_HREDRAW | CS_VREDRAW; // ����� ������ ������
    wc.lpfnWndProc   = WndProc; // ��������� �� ���������������� �������
    wc.lpszMenuName  = NULL; // ��������� �� ��� ���� (� ��� ��� ���)
    wc.lpszClassName = szClassName; // ��������� �� ��� ������
    wc.cbWndExtra    = NULL; // ����� ������������� ������ � ����� ���������
    wc.cbClsExtra    = NULL; // ����� ������������� ������ ��� �������� ���������� ����������
    wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO); // ��������� �����������
    wc.hIconSm       = LoadIcon(NULL, IDI_WINLOGO); // ���������� ��������� ����������� (� ����)
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // ���������� �������
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ���������� ����� ��� �������� ���� ����
    wc.hInstance     = hInst; // ��������� �� ������, ���������� ��� ����, ������������ ��� ������


    if(!RegisterClassEx(&wc)){
        // � ������ ���������� ����������� ������:
        MessageBox(NULL, L"�� ���������� ���������������� �����!", L"������", MB_OK);
        return NULL; // ����������, ������� �� WinMain
    }
    // �������, ��������� ����
    hMainWnd = CreateWindow(
        szClassName, // ��� ������
        L"�������", // ��� ������ (�� ��� ������)
        WS_OVERLAPPEDWINDOW | WS_VSCROLL, // ������ ����������� ������
        CW_USEDEFAULT, // ������� ������ �� ��� �
        NULL, // ������� ������ �� ��� � (��� ������ � �, �� ������ �� �����)
        CW_USEDEFAULT, // ������ ������
        NULL, // ������ ������ (��� ������ � ������, �� ������ �� �����)
        (HWND)NULL, // ���������� ������������� ����
        NULL, // ���������� ����
        HINSTANCE(hInst), // ���������� ���������� ����������
        NULL); // ������ �� ������� �� WndProc
    if(!hMainWnd){
        // � ������ ������������� �������� ������ (�������� ��������� � ��):
        MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
        return NULL;
    }
    ShowWindow(hMainWnd, nCmdShow); // ���������� ������
    UpdateWindow(hMainWnd); // ��������� ������

	//HWND hStatusWindow = CreateStatusWindow (WS_CHILD | WS_VISIBLE, L"", hMainWnd, 5000); 
 
    HMENU hmenu1;
	HMENU hmenu2;
    hmenu1 = CreateMenu();// ������� ����
    hmenu2 = CreatePopupMenu();// ������� ������ ����
    AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hmenu2, L"&File"); // bool = AppendMeny - ������� ��� ���������� ��������
	{
		AppendMenu(hmenu2, MF_STRING, 1000, L"Open");
		AppendMenu(hmenu2, MF_SEPARATOR, 1000, L"");

		AppendMenu(hmenu2, MF_STRING, 1000, L"Save");
        AppendMenu(hmenu2, MF_STRING, 1000, L"Save as...");// ����������� ���� ��� file
		AppendMenu(hmenu2, MF_SEPARATOR, 1000, L"");

        AppendMenu(hmenu2, MF_STRING, 1000, L"Print");
		AppendMenu(hmenu2, MF_SEPARATOR, 1000, L"");

        AppendMenu(hmenu2, MF_STRING, 1000, L"Exit");
	}
    AppendMenu(hmenu1, MF_STRING | MF_POPUP, 0, L"&Edit"); 
    AppendMenu(hmenu1, MF_STRING | MF_POPUP, 0, L"&Help"); 
 
    SetMenu(hMainWnd, hmenu1);    //  ��������� ��������� ����� � ���� ����   
	//SetMenu(hMainWnd, hmenu2);

    while(GetMessage(&msg, NULL, NULL, NULL)){ // ��������� ��������� �� �������, ���������� ��-�����, ��
        TranslateMessage(&msg); // �������������� ���������
        DispatchMessage(&msg); // ������� ��������� ������� ��
    }
    return msg.wParam; // ���������� ��� ������ �� ����������
}
 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    HDC hDC; // ������ ���������� ���������� ������ �� ������
    PAINTSTRUCT ps; // ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
    RECT rect; // ���-��, ������������ ������ ���������� �������
    COLORREF colorText = RGB(255, 0, 0); // ����� ���� ������
	int x, y, a, b;
    switch(uMsg){
     
    case WM_LBUTTONDOWN

    case WM_DESTROY: // ���� ������ ���������, ��:
        PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���� ������� ������
    }
    return NULL; // ���������� ��������
}