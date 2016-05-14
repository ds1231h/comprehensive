#pragma once

#ifndef _STRUCT_H_
#define _STRUCT_H_
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

// 宏
#define DRAW_LINE	1
#define DRAW_RECT	2
#define DRAW_ELIP	3
#define MYMESSAGE	4

#define DEF_BUFFER_SIZE			3
#define DEF_BUFFER_INC_SIZE		2

// 结构体
typedef struct Myline
{
	POINT		ptS;		// 起始坐标
	POINT		ptE;		// 终止坐标
	LOGPEN		penInfo;
}MYLINE, *PMYLINE;

typedef struct MyEllipse
{
	RECT		rect;		// 外接矩形
	LOGPEN		penInfo;
	LOGBRUSH	brInfo;
}MYELLIPSE, *PELLIPSE;

typedef struct MyRectangle
{
	RECT		rect;		// 外接矩形
	LOGPEN		penInfo;
	LOGBRUSH	brInfo;
}MYRECTANGLE, *PRECTANGLE;

// 需要处理缓冲区申请、释放，并且存储到文件时需要分别处理结构中的各个变量，
// 但是这种方式可以适应任意的文本输入情况
typedef struct MyText
{
	POINT		ptS;
	LOGFONT		fontInfo;
	char*		pBuffer;	// 指针方式文本缓冲区，根据输入文本长度申请内存
	CHAR szText[128];
}MYTEXT, *PMYTEXT;

// 声明变量
extern int goCountSizerectangle;
extern int goCountSizeellipse;
extern int goCountSizeline;
extern int goCountSizemessage;
extern int goCountrectangle;
extern int goCountellipse;
extern int goCountline;
extern int goCountmessage;
extern BOOL gLoad;
extern PMYLINE pgLines;
extern PELLIPSE pgEllipse;
extern PRECTANGLE pgRectangle;
extern PMYTEXT pgTexts;
extern MYTEXT gTexts;
extern MYLINE gLines;
extern MYELLIPSE gEllipse;
extern MYRECTANGLE gRectangle;


// 函数声明
BOOL MySaveData(void);
BOOL MyLoadData(void);
BOOL GetMyColor(HWND hWnd, COLORREF *pColor);
BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DrawMyline(HDC hdc, PMYLINE pLine);
void DrawMyLines(HDC hdc, PMYLINE pLines, int iCount);
void DrawMyEllipse(HDC hdc, PELLIPSE pEllipse);
void DrawMyRectangle(HDC hdc, PRECTANGLE pRectangle);
VOID FreeBuffer();
VOID AddOneRectInfo(MYRECTANGLE myrc);
VOID AddOneEllipseInfo(MYELLIPSE myrc);
VOID AddOneLineInfo(MYLINE myrc);
VOID AddOneTextInfo(MYTEXT mytt);
BOOL CALLBACK TextInputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif
