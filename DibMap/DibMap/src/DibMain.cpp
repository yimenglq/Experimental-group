#include<windows.h>
#include"../head/WndProc.h"




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	WNDCLASS wndclass;

	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = wndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground =(HBRUSH) COLOR_WINDOW;
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Ê§°Ü"), szAppName, MB_OK | MB_ICONERROR);
		return -1;
	}

	wndclass.lpfnWndProc = wndProcPOUP;
	wndclass.lpszClassName = szAPPpoupName;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);

	
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Ê§°Ü"), szAPPpoupName, MB_OK | MB_ICONERROR);
		return -1;
	}

	HWND hwnd_1 = CreateWindow(szAppName, szAppName,
		WS_OVERLAPPEDWINDOW,
		0, 0,
		100, 100,
		NULL, NULL, hInstance, NULL
	);

	//HWND hwnd_1 =CreateWindow(
	//	szAppName, NULL,
	//	WS_POPUP | WS_SIZEBOX | WS_CAPTION | WS_BORDER,
	//	100, 10, 100, 300, NULL, NULL, hInstance,//(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE),
	//	NULL
	//);


	ShowWindow(hwnd_1, nCmdShow);
	UpdateWindow(hwnd_1);

	MSG msg = {0};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
		return msg.wParam;


	
}




