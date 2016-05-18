#include "struct.h"

int WINAPI WinMain(HINSTANCE hInstance,         //当前实例句柄
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	MSG msg;

	if (!InitWindow(hInstance, iCmdShow))
		return FALSE;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

BOOL InitWindow(HINSTANCE hInstance, int iCmdShow)
{
	TCHAR szAppName[] = TEXT("EasyWin");
	HWND hwnd;
	WNDCLASS wcMainWnd;
	ATOM a;

	wcMainWnd.style = CS_VREDRAW | CS_HREDRAW;
	wcMainWnd.lpfnWndProc = WinProc;
	wcMainWnd.cbClsExtra = 0;
	wcMainWnd.cbWndExtra = 0;
	wcMainWnd.hInstance = hInstance;
	wcMainWnd.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcMainWnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcMainWnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcMainWnd.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wcMainWnd.lpszClassName = szAppName;

	a = RegisterClass(&wcMainWnd);

	if (!a)
	{
		MessageBox(NULL, TEXT("注册窗口类失败！"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("简易绘图——作者：穆沛"),
		WS_OVERLAPPEDWINDOW | WS_EX_LEFT,
		100,
		100,
		400,
		300,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd) return FALSE;

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return TRUE;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	HMENU hMenu;
	static int gDrawMode = DRAW_LINE;// 绘画模式
	// 逻辑笔、刷、字体
	static LOGPEN gPenInfo = {PS_SOLID, 1, RGB(0, 0, 0)};
	static LOGBRUSH gBrInfo = { BS_SOLID, RGB(255, 255, 255), NULL};
	static LOGFONT gFontInfo;

	switch (message)
	{
	case WM_INITMENUPOPUP:
		// 下拉菜单自左边起从0开始
		// 对指定绘图模式打钩
		CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
		CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
		CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
		CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
		if (lParam == 1)
		{
			if (gDrawMode == DRAW_LINE)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_CHECKED);
			}
			else if (gDrawMode == DRAW_RECT)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_CHECKED);
			}
			else if (gDrawMode == DRAW_ELIP)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_CHECKED);
			}
			else if (gDrawMode == MYMESSAGE)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_CHECKED);
			}
		}
		return 0;

	case WM_COMMAND:
		hMenu = GetMenu(hWnd);

		if (lParam == 0)
		{
			switch(LOWORD(wParam))
			{
			case ID_FILE_mySAVE:
				if (!MySaveData())
				{
					// 保存失败
					MessageBox(hWnd, TEXT("save data error!"), TEXT("error"), TRUE);
				}
				return 0;

			case ID_FILE_myLOAD:
				if (!MyLoadData())
				{
					// 读取失败
					MessageBox(hWnd, TEXT("load data error!"), TEXT("error"), TRUE);
				}
				else
				{
					// 读取成功，刷新屏幕
					InvalidateRect(hWnd, NULL, TRUE);
				}
				return 0;

				// 判断绘图模式
			case ID_DRAW_DRAWMYLINE:
				gDrawMode = DRAW_LINE;
				return 0;

			case ID_DRAW_DRAWMYELLIPSE:
				gDrawMode = DRAW_ELIP;
				return 0;

			case ID_DRAW_DRAWMYRECTANGLE:
				gDrawMode = DRAW_RECT;
				return 0;

			case ID_DRAW_MESSAGE:
				gDrawMode = MYMESSAGE;
				return 0;

			case ID_SETTING_PEN:
				GetMyColor(hWnd, &gPenInfo.lopnColor);
				return 0;

			case ID_SETTING_BRUSH:
				GetMyColor(hWnd, &gBrInfo.lbColor);
				break;
			}
		}

		// 取得开始位置与终止位置坐标
	case WM_LBUTTONDOWN:
		if(gDrawMode == DRAW_LINE)
		{
			pgPaints.gLines.ptS.x = GET_X_LPARAM(lParam);
			pgPaints.gLines.ptS.y = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == DRAW_RECT)
		{
			pgPaints.gRectangle.rect.left = GET_X_LPARAM(lParam);
			pgPaints.gRectangle.rect.top = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == DRAW_ELIP)
		{
			pgPaints.gEllipse.rect.left = GET_X_LPARAM(lParam);
			pgPaints.gEllipse.rect.top = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == MYMESSAGE)
		{
			
			pgPaints.gTexts.ptS.x = GET_X_LPARAM(lParam);
			pgPaints.gTexts.ptS.y = GET_Y_LPARAM(lParam);
			// 弹出对话框输入文本内容
			if (DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				MAKEINTRESOURCE(IDD_DIALOG1),
				hWnd, TextInputDlgProc) == IDOK)
			{
				//pgPaints.gTexts.pBuffer[myCount.textBuffer++] = *pgPaints.gTexts.pBuffer;
				// 内存管理
				AddOneTextInfo(pgPaints.gTexts);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		return 0;

	case WM_LBUTTONUP:
		if(gDrawMode == DRAW_LINE)
		{
			pgPaints.gLines.ptE.x = GET_X_LPARAM(lParam);
			pgPaints.gLines.ptE.y = GET_Y_LPARAM(lParam);
			pgPaints.gLines.penInfo = gPenInfo;
			AddOneLineInfo(&pgPaints.gLines);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (gDrawMode == DRAW_RECT)
		{
			pgPaints.gRectangle.rect.right = GET_X_LPARAM(lParam);
			pgPaints.gRectangle.rect.bottom = GET_Y_LPARAM(lParam);
			pgPaints.gRectangle.brInfo = gBrInfo;
			pgPaints.gRectangle.penInfo = gPenInfo;
			AddOneRectInfo(pgPaints.gRectangle);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (gDrawMode == DRAW_ELIP)
		{
			pgPaints.gEllipse.rect.right = GET_X_LPARAM(lParam);
			pgPaints.gEllipse.rect.bottom = GET_Y_LPARAM(lParam);
			pgPaints.gEllipse.brInfo = gBrInfo;
			pgPaints.gEllipse.penInfo = gPenInfo;
			AddOneEllipseInfo(pgPaints.gEllipse);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:
		hdc=BeginPaint (hWnd, &ps);
		GetClientRect (hWnd, &rect);
		DrawMyline(hdc, pgPaints.pgLines);
		DrawMyEllipse(hdc, pgPaints.pgEllipse);
		DrawMyRectangle(hdc, pgPaints.pgRectangle);
		for (int i=0; i <myCount.message; i++)
		{
			TextOut(hdc, pgPaints.pgTexts[i].ptS.x, pgPaints.pgTexts[i].ptS.y, 
				(LPCWSTR)pgPaints.pgTexts[i].pBuffer, lstrlen((LPCWSTR)pgPaints.pgTexts[i].pBuffer));// 一直显示最后一次pBuffer的值
		}
		EndPaint(hWnd, &ps ); 
		return 0;

	case WM_DESTROY:
		FreeBuffer();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

}

