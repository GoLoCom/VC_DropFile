#include <Windows.h>
HWND Hwnd_WinClass;
HWND Hwnd_ListBox;
LRESULT CALLBACK WinProc(HWND,UINT,WPARAM,LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG Msg;
	WNDCLASS WndClass;
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WinProc;
	WndClass.lpszClassName=L"YWinClass";
	WndClass.lpszMenuName=NULL;
	WndClass.style=0;
	RegisterClass(&WndClass);
	Hwnd_WinClass=CreateWindow(L"YWinClass",L"文件拖拽",WS_BORDER|WS_SYSMENU,CW_USEDEFAULT,CW_USEDEFAULT,306,226,NULL,NULL,hInstance,0);
	ShowWindow(Hwnd_WinClass,SW_SHOWNORMAL);
	Hwnd_ListBox=CreateWindow(L"listbox",L"",WS_CHILD|WS_VISIBLE|WS_VSCROLL,0,0,300,200,Hwnd_WinClass,NULL,hInstance,0);
	UpdateWindow(Hwnd_WinClass);
	while(GetMessage(&Msg,NULL,0,0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
LRESULT CALLBACK WinProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case WM_DROPFILES:
		{
			HDROP hDrop=(HDROP)wParam;
			wchar_t FilePath[MAX_PATH];
			unsigned int nFiles;
			unsigned int Temp;
			nFiles=DragQueryFile(hDrop,0xFFFFFFFF,NULL,0);
			//获得拖拽的文件数量
			SendMessage(Hwnd_ListBox,LB_RESETCONTENT,0,0);
			for(Temp=0;Temp<nFiles;Temp++)
			{
				DragQueryFile(hDrop,Temp,FilePath,MAX_PATH);
				SendMessage(Hwnd_ListBox,LB_ADDSTRING,0,(LPARAM)FilePath);
			}
			DragFinish(hDrop);
			break;
		}
	case WM_CREATE:
		{
			//CREATESTRUCT *CreateInfo=(CREATESTRUCT*)lParam;
			DragAcceptFiles(hWnd,true);
			//标示窗口是否接受从shell拖放过来的文件
			break;
		}
	case WM_CLOSE:
		exit(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd,Msg,wParam,lParam);
}