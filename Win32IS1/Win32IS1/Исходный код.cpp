#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
 
// Управляющая функция:
int WINAPI WinMain(HINSTANCE hInst, // дескриптор экземпляра приложения
                   HINSTANCE hPrevInst, // не используем
                   LPSTR lpCmdLine, // не используем
                   int nCmdShow) // режим отображения окошка
{
    TCHAR szClassName[] = L"класс"; // строка с именем класса
    HWND hMainWnd; // создаём дескриптор будущего окошка
    MSG msg; // создём экземпляр структуры MSG для обработки сообщений
    WNDCLASSEX wc; // создаём экземпляр, для обращения к членам класса WNDCLASSEX
    wc.cbSize        = sizeof(wc); // размер структуры (в байтах)
    wc.style         = CS_HREDRAW | CS_VREDRAW; // стиль класса окошка
    wc.lpfnWndProc   = WndProc; // указатель на пользовательскую функцию
    wc.lpszMenuName  = NULL; // указатель на имя меню (у нас его нет)
    wc.lpszClassName = szClassName; // указатель на имя класса
    wc.cbWndExtra    = NULL; // число освобождаемых байтов в конце структуры
    wc.cbClsExtra    = NULL; // число освобождаемых байтов при создании экземпляра приложения
    wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO); // декриптор пиктограммы
    wc.hIconSm       = LoadIcon(NULL, IDI_WINLOGO); // дескриптор маленькой пиктограммы (в трэе)
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // дескриптор кисти для закраски фона окна
    wc.hInstance     = hInst; // указатель на строку, содержащую имя меню, применяемого для класса


    if(!RegisterClassEx(&wc)){
        // в случае отсутствия регистрации класса:
        MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
        return NULL; // возвращаем, выходим из WinMain
    }
    // Функция, создающая окно
    hMainWnd = CreateWindow(
        szClassName, // имя класса
        L"Пробнул", // имя окошка (то что сверху)
        WS_OVERLAPPEDWINDOW | WS_VSCROLL, // режимы отображения окошка
        CW_USEDEFAULT, // позиция окошка по оси х
        NULL, // позиция окошка по оси у (раз дефолт в х, то писать не нужно)
        CW_USEDEFAULT, // ширина окошка
        NULL, // высота окошка (раз дефолт в ширине, то писать не нужно)
        (HWND)NULL, // дескриптор родительского окна
        NULL, // дескриптор меню
        HINSTANCE(hInst), // дескриптор экземпляра приложения
        NULL); // ничего не передаём из WndProc
    if(!hMainWnd){
        // в случае некорректного создания окошка (неверные параметры и тп):
        MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
        return NULL;
    }
    ShowWindow(hMainWnd, nCmdShow); // отображаем окошко
    UpdateWindow(hMainWnd); // обновляем окошко

	//HWND hStatusWindow = CreateStatusWindow (WS_CHILD | WS_VISIBLE, L"", hMainWnd, 5000); 
 
    HMENU hmenu1;
	HMENU hmenu2;
    hmenu1 = CreateMenu();// создать меню
    hmenu2 = CreatePopupMenu();// создать второе меню
    AppendMenu(hmenu1, MF_STRING | MF_POPUP, (UINT)hmenu2, L"&File"); // bool = AppendMeny - функция для добавления элемента
	{
		AppendMenu(hmenu2, MF_STRING, 1000, L"Open");
		AppendMenu(hmenu2, MF_SEPARATOR, 1000, L"");

		AppendMenu(hmenu2, MF_STRING, 1000, L"Save");
        AppendMenu(hmenu2, MF_STRING, 1000, L"Save as...");// всплывающее меню для file
		AppendMenu(hmenu2, MF_SEPARATOR, 1000, L"");

        AppendMenu(hmenu2, MF_STRING, 1000, L"Print");
		AppendMenu(hmenu2, MF_SEPARATOR, 1000, L"");

        AppendMenu(hmenu2, MF_STRING, 1000, L"Exit");
	}
    AppendMenu(hmenu1, MF_STRING | MF_POPUP, 0, L"&Edit"); 
    AppendMenu(hmenu1, MF_STRING | MF_POPUP, 0, L"&Help"); 
 
    SetMenu(hMainWnd, hmenu1);    //  привязать созданный пункт к окну меню   
	//SetMenu(hMainWnd, hmenu2);

    while(GetMessage(&msg, NULL, NULL, NULL)){ // извлекаем сообщения из очереди, посылаемые фу-циями, ОС
        TranslateMessage(&msg); // интерпретируем сообщения
        DispatchMessage(&msg); // передаём сообщения обратно ОС
    }
    return msg.wParam; // возвращаем код выхода из приложения
}
 
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    HDC hDC; // создаём дескриптор ориентации текста на экране
    PAINTSTRUCT ps; // структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
    RECT rect; // стр-ра, определяющая размер клиентской области
    COLORREF colorText = RGB(255, 0, 0); // задаём цвет текста
	int x, y, a, b;
    switch(uMsg){
     
    case WM_LBUTTONDOWN

    case WM_DESTROY: // если окошко закрылось, то:
        PostQuitMessage(NULL); // отправляем WinMain() сообщение WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
    }
    return NULL; // возвращаем значение
}