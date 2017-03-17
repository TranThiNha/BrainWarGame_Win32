// 1412363_DE01.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1412363_DE01.h"
#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>
#include <cstdlib>
#include <ctime>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

#define MAX_LOADSTRING 100

void CALLBACK f_out(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
void CALLBACK f_run(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
static bool bStillBusy = false;

int a, b, result;
int location;             //positon of right result 
static int answer[4];     //array of 4 answer
int temp_answer;          //wrong answers 
int CountRightAnswer = 0;
int CountSum = 0;
int second;
int remain_Time = 30;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	//InitCommonControls();


	MSG msg;
	HACCEL hAccelTable;
		// Initialize global strings
		LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadString(hInstance, IDC_MY1412363_DE01, szWindowClass, MAX_LOADSTRING);
		MyRegisterClass(hInstance);

		// Perform application initialization:
		if (!InitInstance(hInstance, nCmdShow))
		{
			return FALSE;
		}

		hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1412363_DE01));

		// Main message loop:
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}


	return (int)msg.wParam;

}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_1412363_DE01));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY1412363_DE01);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindowEx(0, szWindowClass, L"Brain War_MATH GAME",
		WS_OVERLAPPEDWINDOW,
		200, 0, 400, 500 , NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		 
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}


}

HWND txtDe, txtkq, hwndA, hwndB, hwndC, hwndD, txtInfo, hwndStart, hwnd, StaticTime;


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hb;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}

#define CreateTextBox(text, left, top, width, height, ID) 

//HWND txtDe, txtkq, hwndA, hwndB, hwndC, hwndD, txtInfo, hwndStart, hwnd;

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	StaticTime = CreateWindowEx(0, L"STATIC", L"00:00", WS_CHILD | WS_VISIBLE, 100, 50, 200, 50, hWnd, NULL, NULL, NULL);
	HFONT hfontTime = CreateFont(40, 30, 10, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Fixedsys");
	SendMessage(StaticTime, WM_SETFONT, WPARAM(hfontTime), TRUE);
	
	hwndStart = CreateWindowEx(0, L"BUTTON", L"START", WS_CHILD | WS_VISIBLE | ACS_CENTER | BS_PUSHBUTTON, 100, 150, 200, 50, hWnd, (HMENU)IDC_BUTTONSTART, hInst, NULL);
	SendMessage(hwndStart, 100, WPARAM(hFont), TRUE);
	txtDe = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_CENTER | WS_DISABLED, 100, 200, 200, 50, hWnd, NULL, hInst, NULL);
	SendMessage(txtDe, 100, WPARAM(hFont), TRUE);
	txtInfo = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_CENTER | WS_DISABLED, 150, 100, 150, 50, hWnd, NULL, hInst, NULL);
	SendMessage(txtInfo, 200, WPARAM(hFont), TRUE);
	hwnd = CreateWindowEx(0, L"STATIC", L"Score:", WS_CHILD | WS_VISIBLE | SS_CENTER, 100, 100, 50, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, 0, WPARAM(hFont), TRUE);
	txtkq = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ACS_CENTER | WS_DISABLED, 150, 260, 95, 50, hWnd, NULL, hInst, NULL);
	SendMessage(txtkq, 100, WPARAM(hFont), TRUE);
	hwndA = CreateWindowEx(0, L"BUTTON", L"NULL", WS_CHILD | WS_VISIBLE | ACS_CENTER | BS_PUSHBUTTON, 100, 320, 85, 45, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
	SendMessage(hwndA, WM_SETFONT, WPARAM(hFont), TRUE);
	hwndB = CreateWindowEx(0, L"BUTTON", L"NULL", WS_CHILD | WS_VISIBLE | ACS_CENTER | BS_PUSHBUTTON, 195, 320, 85, 45, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
	SendMessage(hwndB, WM_SETFONT, WPARAM(hFont), TRUE);
	hwndC = CreateWindowEx(0, L"BUTTON", L"NULL", WS_CHILD | WS_VISIBLE | ACS_CENTER | BS_PUSHBUTTON, 100, 370, 85, 45, hWnd, (HMENU)IDC_BUTTON3, hInst, NULL);
	SendMessage(hwndC, WM_SETFONT, WPARAM(hFont), TRUE);
	hwndD = CreateWindowEx(0, L"BUTTON", L"NULL", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | ACS_CENTER, 195, 370, 85, 45, hWnd, (HMENU)IDC_BUTTON4, hInst, NULL);
	SendMessage(hwndD, WM_SETFONT, WPARAM(hFont), TRUE);

	return true;
}

void CALLBACK f_run(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	remain_Time--;
	if (remain_Time == -1)
	{
		MessageBox(hwnd, L"Time is over! :(((", L"Look! :o", MB_ICONSTOP | MB_OK);
		KillTimer(hwnd, IDT_TIME_RUN);
		EnableWindow(hwndA, false);
		EnableWindow(hwndB, false);
		EnableWindow(hwndC, false);
		EnableWindow(hwndD, false);
		EnableWindow(hwndStart, false);
	}

	return;
}

void CALLBACK f_out(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	WCHAR * buffer = new WCHAR[255];

	if (remain_Time  >=10)
	{
		swprintf(buffer,100, L"00:%d", remain_Time);
	}
	else if (remain_Time == 0)
	{
		swprintf(buffer, 100, L"00:0%d", remain_Time);
		KillTimer(hwnd, IDT_TIME_OUT);
	}
	else
	{
		swprintf(buffer,100, L"00:0%d", remain_Time);
	}
	SetWindowText(StaticTime, buffer);
	return;
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	WCHAR* bufferDe = NULL;
	WCHAR* buffer1 = NULL;

	int size1;
	int size2;
	int compare;

	//random for location of right answer
	srand(time(NULL));
	location = rand() % 4;

	bufferDe = new WCHAR[255];

	switch (id)
	{



	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;

	case IDC_BUTTONSTART:
		//create expression 

		SetTimer(hWnd, IDT_TIME_RUN, 1000, (TIMERPROC)f_run);
		SetTimer(hWnd, IDT_TIME_OUT, 1000, (TIMERPROC)f_out);
		srand(time(NULL));
		a = rand() % 50;
		b = rand() % 50;
		result = a + b;

		//set value for elements of answer Array
		for (int i = 0; i < 4; i++)
		{
			if (i == location)
			{
				answer[i] = result;
			}
			else
			{
				temp_answer = rand() % 50;
				while (temp_answer == result){

					temp_answer = rand() % 50;
				}
				answer[i] = temp_answer;
			}
		}

		//set value for button
		swprintf(bufferDe, 10000, L"%d", answer[0]);
		SetWindowText(hwndA, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[1]);
		SetWindowText(hwndB, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[2]);
		SetWindowText(hwndC, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[3]);
		SetWindowText(hwndD, bufferDe);

		//print expression 
		swprintf(bufferDe, 10000, L"%d + %d =?", a, b);
		SetWindowText(txtDe, bufferDe);

		break;


	case IDC_BUTTON1:

		CountSum++;

		//get Value of Button
		size1 = GetWindowTextLength(hwndA);
		buffer1 = new WCHAR[size1 + 1];
		GetWindowText(hwndA, buffer1, size1 + 1);
		compare = _wtoi(buffer1);

		//compare the value with the result 
		if (compare == result)
		{
			CountRightAnswer++;
			swprintf(bufferDe, 10000, L"true");
			SetWindowText(txtkq, bufferDe);
		}
		else
		{
			swprintf(bufferDe, 10000, L"false");
			SetWindowText(txtkq, bufferDe);
		}


		//create expression 
		srand(time(NULL));

		a = rand() % 50;
		b = rand() % 50;
		result = a + b;

		//print expression 
		swprintf(bufferDe, 10000, L"%d + %d =?", a, b);
		SetWindowText(txtDe, bufferDe);

		//set value for elements of answer Array
		for (int i = 0; i < 4; i++)
		{
			if (i == location)
			{
				answer[i] = result;
			}
			else
			{
				temp_answer = rand() % 50;
				while (temp_answer == result){

					temp_answer = rand() % 50;
				}
				answer[i] = temp_answer;
			}
		}

		//set value for button
		swprintf(bufferDe, 10000, L"%d", answer[0]);
		SetWindowText(hwndA, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[1]);
		SetWindowText(hwndB, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[2]);
		SetWindowText(hwndC, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[3]);
		SetWindowText(hwndD, bufferDe);

		//print proportion 
		swprintf(bufferDe, 10000, L"%d / %d", CountRightAnswer, CountSum);
		SetWindowText(txtInfo, bufferDe);
		break;
	case IDC_BUTTON2:
		CountSum++;

		//get Value of Button
		size1 = GetWindowTextLength(hwndA);
		buffer1 = new WCHAR[size1 + 1];
		GetWindowText(hwndB, buffer1, size1 + 1);
		compare = _wtoi(buffer1);

		//compare the value with the result 
		if (compare == result)
		{
			CountRightAnswer++;
			swprintf(bufferDe, 10000, L"true");
			SetWindowText(txtkq, bufferDe);
		}
		else
		{
			swprintf(bufferDe, 10000, L"false");
			SetWindowText(txtkq, bufferDe);
		}


		//create expression 
		srand(time(NULL));
		a = rand() % 50;
		b = rand() % 50;
		result = a + b;

		//print expression 
		swprintf(bufferDe, 10000, L"%d + %d =?", a, b);
		SetWindowText(txtDe, bufferDe);

		//set value for elements of answer Array
		for (int i = 0; i < 4; i++)
		{
			if (i == location)
			{
				answer[i] = result;
			}
			else
			{
				temp_answer = rand() % 50;
				while (temp_answer == result){

					temp_answer = rand() % 50;
				}
				answer[i] = temp_answer;
			}
		}

		//set value for button
		swprintf(bufferDe, 10000, L"%d", answer[0]);
		SetWindowText(hwndA, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[1]);
		SetWindowText(hwndB, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[2]);
		SetWindowText(hwndC, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[3]);
		SetWindowText(hwndD, bufferDe);

		//print proportion 
		swprintf(bufferDe, 10000, L"%d / %d", CountRightAnswer, CountSum);
		SetWindowText(txtInfo, bufferDe);
		break;

	case IDC_BUTTON3:
		CountSum++;

		//get Value of Button
		size1 = GetWindowTextLength(hwndA);
		buffer1 = new WCHAR[size1 + 1];
		GetWindowText(hwndC, buffer1, size1 + 1);
		compare = _wtoi(buffer1);

		//compare the value with the result 
		if (compare == result)
		{
			CountRightAnswer++;
			swprintf(bufferDe, 10000, L"true");
			SetWindowText(txtkq, bufferDe);
		}
		else
		{
			swprintf(bufferDe, 10000, L"false");
			SetWindowText(txtkq, bufferDe);
		}


		//create expression 
		srand(time(NULL));
		a = rand() % 50;
		b = rand() % 50;
		result = a + b;

		//print expression 
		swprintf(bufferDe, 10000, L"%d + %d =?", a, b);
		SetWindowText(txtDe, bufferDe);

		//set value for elements of answer Array
		for (int i = 0; i < 4; i++)
		{
			if (i == location)
			{
				answer[i] = result;
			}
			else
			{
				temp_answer = rand() % 50;
				while (temp_answer == result){

					temp_answer = rand() % 50;
				}
				answer[i] = temp_answer;
			}
		}

		//set value for button
		swprintf(bufferDe, 10000, L"%d", answer[0]);
		SetWindowText(hwndA, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[1]);
		SetWindowText(hwndB, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[2]);
		SetWindowText(hwndC, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[3]);
		SetWindowText(hwndD, bufferDe);

		//print proportion 
		swprintf(bufferDe, 10000, L"%d / %d", CountRightAnswer, CountSum);
		SetWindowText(txtInfo, bufferDe);
		break;
	case IDC_BUTTON4:
		CountSum++;

		//get Value of Button
		size1 = GetWindowTextLength(hwndA);
		buffer1 = new WCHAR[size1 + 1];
		GetWindowText(hwndD, buffer1, size1 + 1);
		compare = _wtoi(buffer1);

		//compare the value with the result 
		if (compare == result)
		{
			CountRightAnswer++;
			swprintf(bufferDe, 10000, L"true");
			SetWindowText(txtkq, bufferDe);
		}
		else
		{
			swprintf(bufferDe, 10000, L"false");
			SetWindowText(txtkq, bufferDe);
		}


		//create expression 
		srand(time(NULL));
		a = rand() % 50;
		b = rand() % 50;
		result = a + b;

		//print expression 
		swprintf(bufferDe, 10000, L"%d + %d =?", a, b);
		SetWindowText(txtDe, bufferDe);

		//set value for elements of answer Array
		for (int i = 0; i < 4; i++)
		{
			if (i == location)
			{
				answer[i] = result;
			}
			else
			{
				temp_answer = rand() % 50;
				while (temp_answer == result){

					temp_answer = rand() % 50;
				}
				answer[i] = temp_answer;
			}
		}

		//set value for button
		swprintf(bufferDe, 10000, L"%d", answer[0]);
		SetWindowText(hwndA, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[1]);
		SetWindowText(hwndB, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[2]);
		SetWindowText(hwndC, bufferDe);
		swprintf(bufferDe, 10000, L"%d", answer[3]);
		SetWindowText(hwndD, bufferDe);

		//print proportion 
		swprintf(bufferDe, 10000, L"%d / %d", CountRightAnswer, CountSum);
		SetWindowText(txtInfo, bufferDe);
		break;
	}



	if (!bufferDe)
		delete[] bufferDe;


}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	SetDCPenColor(hdc, RGB(0, 0, 255));

	//    Drawing a rectangle with the current Device Context    


}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}