#include <stdio.h>
#include "struct.h"
int goCountSizerectangle;
int goCountSizeellipse;
int goCountSizeline;
int goCountSizemessage;
int goCountrectangle;
int goCountellipse;
int goCountline;
int goCountmessage;
PMYLINE pgLines = NULL;
PELLIPSE pgEllipse = NULL;
PRECTANGLE pgRectangle = NULL;
PMYTEXT pgTexts = NULL;

VOID AddOneRectInfo(MYRECTANGLE myrc)
{
	if (pgRectangle == NULL)
	{
		pgRectangle = new MYRECTANGLE[DEF_BUFFER_SIZE];
		if (pgRectangle == NULL)
		{return;}		// 申请缓冲区不成功，直接返回
		goCountSizerectangle = DEF_BUFFER_SIZE;
	}
	if (goCountrectangle >= goCountSizerectangle)
	{
		// 扩大缓冲区
		PRECTANGLE pNew = new MYRECTANGLE[goCountrectangle+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNew, pgRectangle, goCountrectangle*sizeof(MYRECTANGLE));
		delete pgRectangle;					// 释放之前的缓冲区
		pgRectangle = pNew;
		goCountSizerectangle += DEF_BUFFER_INC_SIZE;
	}
	pgRectangle[goCountrectangle++] = myrc;		// 保存图形数据
}

VOID AddOneEllipseInfo(MYELLIPSE myrc)
{
	if (pgEllipse == NULL)
	{
		pgEllipse = new MYELLIPSE[DEF_BUFFER_SIZE];
		if (pgEllipse == NULL)	return;		// 申请缓冲区不成功，直接返回
		goCountSizeellipse = DEF_BUFFER_SIZE;
	}
	if (goCountellipse >= goCountSizeellipse)
	{
		// 扩大缓冲区
		PELLIPSE pNew = new MYELLIPSE[goCountellipse+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNew, pgEllipse, goCountellipse*sizeof(MYELLIPSE));
		delete pgEllipse;					// 释放之前的缓冲区
		pgEllipse = pNew;
		goCountSizeellipse += DEF_BUFFER_INC_SIZE;
	}
	pgEllipse[goCountellipse++] = myrc;		// 保存图形数据
}

VOID AddOneLineInfo(MYLINE myrc)
{
	if (pgLines == NULL)
	{
		pgLines = new MYLINE[DEF_BUFFER_SIZE];
		if (pgLines == NULL)	return;		// 申请缓冲区不成功，直接返回
		goCountSizeline = DEF_BUFFER_SIZE;
	}
	if (goCountline >= goCountSizeline)
	{
		// 扩大缓冲区
		PMYLINE pNew = new MYLINE[goCountline+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNew, pgLines, goCountline*sizeof(MYLINE));
		delete pgLines;					// 释放之前的缓冲区
		pgLines = pNew;
		goCountSizeline += DEF_BUFFER_INC_SIZE;
	}
	pgLines[goCountline++] = myrc;		// 保存图形数据
}

VOID AddOneTextInfo(MYTEXT mytt)
{
	if (pgTexts == NULL)
	{
		pgTexts = new MYTEXT[DEF_BUFFER_SIZE];
		if (pgTexts == NULL)	return;		// 申请缓冲区不成功，直接返回
		goCountSizemessage = DEF_BUFFER_SIZE;
	}
	if (goCountmessage >= goCountSizemessage)
	{
		// 扩大缓冲区
		MYTEXT* pNewTexts = new MYTEXT[goCountmessage + DEF_BUFFER_INC_SIZE];
		if (pNewTexts == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNewTexts, pgTexts, goCountmessage*sizeof(MYTEXT));
		delete pgTexts;					// 释放之前的缓冲区
		pgTexts = pNewTexts;
		goCountSizemessage += DEF_BUFFER_INC_SIZE;
	}
	pgTexts[goCountmessage++] = mytt;		// 保存图形数据
}

BOOL MySaveData(void)
{
	FILE* fp = fopen("E:\\VSworksapce\\comprehensive1_2\\comprehensive1_2\\a.bin", "ab");

	if (fp != NULL)
	{
		fwrite(&goCountline, sizeof(int), 1, fp);
		fwrite(&pgLines, sizeof(MYLINE), goCountline, fp);

		fwrite(&goCountrectangle, sizeof(int), 1, fp);
		fwrite(&pgRectangle, sizeof(MYRECTANGLE), goCountrectangle, fp);

		fwrite(&goCountellipse, sizeof(int), 1, fp);
		fwrite(&pgEllipse, sizeof(MYELLIPSE), goCountellipse, fp);

		fwrite(&goCountmessage, sizeof(int), 1, fp);
		fwrite(&pgTexts, sizeof(MYTEXT), goCountmessage, fp);

		fclose(fp);
		return TRUE;
	}

	return FALSE;
}

BOOL MyLoadData(void)
{
	FreeBuffer();
	FILE* fp = fopen("E:\\VSworksapce\\comprehensive 1\\comprehensive\\a.bin", "rb");

	if (fp != NULL)
	{
		int iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		
		for (int i = 0;i < iCount; i++)
		{
			MYLINE r;
			fread(&r, sizeof(MYLINE), 1, fp);
			AddOneLineInfo(r);
		}
		fseek(fp, iCount, SEEK_CUR);

		iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		for (int i = 0;i < iCount; i++)
		{
			MYLINE r;
			fread(&r, sizeof(MYLINE), 1, fp);
			AddOneLineInfo(r);
		}
		fseek(fp, iCount, SEEK_CUR);

		iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		for (int i = 0;i < iCount; i++)
		{
			MYLINE r;
			fread(&r, sizeof(MYLINE), 1, fp);
			AddOneLineInfo(r);
		}
		fseek(fp, iCount, SEEK_CUR);

		iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		for (int i = 0;i < iCount; i++)
		{
			MYLINE r;
			fread(&r, sizeof(MYLINE), 1, fp);
			AddOneLineInfo(r);
		}
		fseek(fp, iCount, SEEK_CUR);

		fclose(fp);
		return TRUE;
	}

	return FALSE;
} 

VOID FreeBuffer()
{
	if (pgLines != NULL)		// 如果原来有数据，删掉
	{
		delete pgLines;
		goCountSizeline = 0;
		goCountline = 0;
	}
	if (pgRectangle != NULL)		// 如果原来有数据，删掉
	{
		delete pgRectangle;
		goCountSizerectangle = 0;
		goCountrectangle = 0;
	}
	if (pgEllipse != NULL)		// 如果原来有数据，删掉
	{
		delete pgEllipse;
		goCountSizeellipse = 0;
		goCountellipse = 0;
	}
	if (pgTexts != NULL)		// 如果原来有数据，删掉
	{
		delete pgTexts;
		goCountSizemessage = 0;
		goCountmessage = 0;
	}
}
