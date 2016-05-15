#include "struct.h"

int WINAPI WinMain(HINSTANCE hInstance,         //��ǰʵ�����
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
		MessageBox(NULL, TEXT("ע�ᴰ����ʧ�ܣ�"), szAppName,
			MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("���׻�ͼ�������ߣ�����"),
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
	static int gDrawMode = DRAW_LINE;// �滭ģʽ
	// �ṹ����ͼԪ��Ϣ
	static MYLINE gLines;
	static MYELLIPSE gEllipse;
	static MYRECTANGLE gRectangle;
	// �߼��ʡ�ˢ������
	static LOGPEN gPenInfo = {PS_SOLID, 1, RGB(255,255,255)};
	static LOGBRUSH gBrInfo = { BS_SOLID, RGB(0,0,0), NULL};
	static LOGFONT gFontInfo;

	switch (message)
	{
	case WM_INITMENUPOPUP:
		// �����˵���������0��ʼ
		// ��ָ����ͼģʽ��
		if (lParam == 1)
		{
			if (gDrawMode == DRAW_LINE)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_CHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
			}
			else if (gDrawMode == DRAW_RECT)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_CHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
			}
			else if (gDrawMode == DRAW_ELIP)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_CHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_MESSAGE, MF_UNCHECKED);
			}
			else if (gDrawMode == MYMESSAGE)
			{
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYLINE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYRECTANGLE, MF_UNCHECKED);
				CheckMenuItem((HMENU)wParam, ID_DRAW_DRAWMYELLIPSE, MF_UNCHECKED);
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
					// ����ʧ��
					MessageBox(hWnd, TEXT("save data error!"), TEXT("error"), TRUE);
				}
				return 0;

			case ID_FILE_myLOAD:
				if (!MyLoadData())
				{
					// ��ȡʧ��
					MessageBox(hWnd, TEXT("load data error!"), TEXT("error"), TRUE);
				}
				else
				{
					// ��ȡ�ɹ���ˢ����Ļ
					InvalidateRect(hWnd, NULL, TRUE);
				}
				return 0;

				// �жϻ�ͼģʽ
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

		// ȡ�ÿ�ʼλ������ֹλ������
	case WM_LBUTTONDOWN:
		if(gDrawMode == DRAW_LINE)
		{
			gLines.ptS.x = GET_X_LPARAM(lParam);
			gLines.ptS.y = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == DRAW_RECT)
		{
			gRectangle.rect.left = GET_X_LPARAM(lParam);
			gRectangle.rect.top = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == DRAW_ELIP)
		{
			gEllipse.rect.left = GET_X_LPARAM(lParam);
			gEllipse.rect.top = GET_Y_LPARAM(lParam);
		}
		else if (gDrawMode == MYMESSAGE)
		{
			gTexts.ptS.x = GET_X_LPARAM(lParam);
			gTexts.ptS.y = GET_Y_LPARAM(lParam);
			// �����Ի��������ı�����
			if (DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
				MAKEINTRESOURCE(IDD_DIALOG1),
				hWnd, TextInputDlgProc) == IDOK)
			{
				// �ڴ����
				AddOneTextInfo(gTexts);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		return 0;

	case WM_LBUTTONUP:
		if(gDrawMode == DRAW_LINE)
		{
			gLines.ptE.x = GET_X_LPARAM(lParam);
			gLines.ptE.y = GET_Y_LPARAM(lParam);
			gLines.penInfo = gPenInfo;
			AddOneLineInfo(gLines);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (gDrawMode == DRAW_RECT)
		{
			gRectangle.rect.right = GET_X_LPARAM(lParam);
			gRectangle.rect.bottom = GET_Y_LPARAM(lParam);
			gRectangle.brInfo = gBrInfo;
			gRectangle.penInfo = gPenInfo;
			AddOneRectInfo(gRectangle);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (gDrawMode == DRAW_ELIP)
		{
			gEllipse.rect.right = GET_X_LPARAM(lParam);
			gEllipse.rect.bottom = GET_Y_LPARAM(lParam);
			gEllipse.brInfo = gBrInfo;
			gEllipse.penInfo = gPenInfo;
			AddOneEllipseInfo(gEllipse);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

	case WM_PAINT:
		hdc=BeginPaint (hWnd, &ps);
		GetClientRect (hWnd, &rect);
		DrawMyline(hdc, pgLines);
		DrawMyEllipse(hdc, pgEllipse);
		DrawMyRectangle(hdc, pgRectangle);
		for (int i=0; i <goCountmessage; i++)
		{
			TextOut(hdc, pgTexts[i].ptS.x, pgTexts[i].ptS.y, 
				(LPCWSTR)pgTexts[i].szText, lstrlen((LPCWSTR)pgTexts[i].szText));
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

