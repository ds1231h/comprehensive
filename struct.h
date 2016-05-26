#pragma once

#ifndef _STRUCT_H_
#define _STRUCT_H_
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

// ��
#define DRAW_LINE	1
#define DRAW_RECT	2
#define DRAW_ELIP	3
#define MYMESSAGE	4

#define DEF_BUFFER_SIZE			3
#define DEF_BUFFER_INC_SIZE		1

// �ṹ��
typedef struct Myline
{
	POINT		ptS;		// ��ʼ����
	POINT		ptE;		// ��ֹ����
	LOGPEN		penInfo;
}MYLINE, *PMYLINE;

typedef struct MyEllipse
{
	RECT		rect;		// ��Ӿ���
	LOGPEN		penInfo;
	LOGBRUSH	brInfo;
}MYELLIPSE, *PELLIPSE;

typedef struct MyRectangle
{
	RECT		rect;		// ��Ӿ���
	LOGPEN		penInfo;
	LOGBRUSH	brInfo;
}MYRECTANGLE, *PRECTANGLE;

// ��Ҫ�����������롢�ͷţ����Ҵ洢���ļ�ʱ��Ҫ�ֱ���ṹ�еĸ���������
// �������ַ�ʽ������Ӧ������ı��������
typedef struct MyText
{
	POINT		ptS;
	LOGFONT		fontInfo;
	char*		pBuffer;	// ָ�뷽ʽ�ı������������������ı����������ڴ�
	DWORD		rgbCurrent;
}MYTEXT, *PMYTEXT;

typedef struct goCount
{
	int line;
	int ellipse;
	int rectangle;
	int message;
	int textBuffer;
}MYOCOUNT, *PMYOCOUNT;

typedef struct pgpaints
{
	PMYLINE pgLines;
	PELLIPSE pgEllipse;
	PRECTANGLE pgRectangle;
	PMYTEXT pgTexts;
	MYLINE gLines;
	MYELLIPSE gEllipse;
	MYRECTANGLE gRectangle;
	MYTEXT gTexts;
}PGPAINTS;
// ��������
extern MYOCOUNT myCount;
extern MYTEXT gTexts;
extern PGPAINTS pgPaints;
extern MYOCOUNT myCountSize;

// ��������
BOOL MySaveData(void);
BOOL MyLoadData(void);
BOOL GetMyColor(HWND hWnd, COLORREF *pColor);
BOOL GetMyFont(HWND hWnd, LOGFONT *lf, DWORD *rgbCurrent);
BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DrawMyline(HDC hdc, PMYLINE pLine);
void DrawMyEllipse(HDC hdc, PELLIPSE pEllipse);
void DrawMyRectangle(HDC hdc, PRECTANGLE pRectangle);
void DrawMytext(HDC hdc, PMYTEXT pText);
VOID FreeBuffer(void);
VOID AddOneRectInfo(MYRECTANGLE);
VOID AddOneEllipseInfo(MYELLIPSE);
VOID AddOneLineInfo(PMYLINE);
VOID AddOneTextInfo(MYTEXT);
BOOL CALLBACK TextInputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void AddTextBuffer();
void selectObj(MYOCOUNT myCount, LONG sx, LONG sy, LOGPEN gPenInfo, LOGBRUSH gBrushInfo, LOGFONT gFontInfo);

#endif
