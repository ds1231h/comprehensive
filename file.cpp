#include <stdio.h>
#include "struct.h"

// 全局变量记录图元数目
MYOCOUNT myCount;
MYOCOUNT myCountSize;

//全局变量存放图元信息
PGPAINTS pgPaints;

VOID AddOneRectInfo(MYRECTANGLE myrc)
{
// 	if (pgPaints==NULL)
// 	{
// 	}
	if (pgPaints.pgRectangle == NULL)
	{
		pgPaints.pgRectangle = new MYRECTANGLE[DEF_BUFFER_SIZE];
		if (pgPaints.pgRectangle == NULL)
		{return;}		// 申请缓冲区不成功，直接返回
		myCountSize.rectangle = DEF_BUFFER_SIZE;
	}
	if (myCount.rectangle >= myCountSize.rectangle)
	{
		// 扩大缓冲区
		PRECTANGLE pNew = new MYRECTANGLE[myCount.rectangle+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNew, pgPaints.pgRectangle, myCount.rectangle*sizeof(MYRECTANGLE));
		if (myCount.message != 0)
		{
			delete pgPaints.pgRectangle;					// 释放之前的缓冲区
		}
		pgPaints.pgRectangle = pNew;
		myCountSize.rectangle += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgRectangle[myCount.rectangle++] = myrc;		// 保存图形数据
}

VOID AddOneEllipseInfo(MYELLIPSE myep)
{
	if (pgPaints.pgEllipse == NULL)
	{
		pgPaints.pgEllipse = new MYELLIPSE[DEF_BUFFER_SIZE];
		if (pgPaints.pgEllipse == NULL)	return;		// 申请缓冲区不成功，直接返回
		myCountSize.ellipse = DEF_BUFFER_SIZE;
	}
	if (myCount.ellipse >= myCountSize.ellipse)
	{
		// 扩大缓冲区
		PELLIPSE pNew = new MYELLIPSE[myCount.ellipse+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNew, pgPaints.pgEllipse, myCount.ellipse*sizeof(MYELLIPSE));
		if (myCount.message != 0)
		{
			delete pgPaints.pgEllipse;					// 释放之前的缓冲区
		}
		pgPaints.pgEllipse = pNew;
		myCountSize.ellipse += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgEllipse[myCount.ellipse++] = myep;		// 保存图形数据
}

VOID AddOneLineInfo(PMYLINE myl)
{
	if (pgPaints.pgLines == NULL)
	{
		pgPaints.pgLines = new MYLINE[DEF_BUFFER_SIZE];
		if (pgPaints.pgLines == NULL)	return;		// 申请缓冲区不成功，直接返回
		myCountSize.line = DEF_BUFFER_SIZE;
	}
	if (myCount.line >= myCountSize.line)
	{
		// 扩大缓冲区
		PMYLINE pNew = new MYLINE[myCount.line+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNew, pgPaints.pgLines, myCount.line*sizeof(MYLINE));
		if (myCount.message != 0)
		{
			delete pgPaints.pgLines;					// 释放之前的缓冲区
		}
		pgPaints.pgLines = pNew;
		myCountSize.line += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgLines[myCount.line++] = *myl;		// 保存图形数据
}

VOID AddOneTextInfo(MYTEXT mytt)
{
	if (pgPaints.pgTexts == NULL)
	{
		pgPaints.pgTexts = new MYTEXT[DEF_BUFFER_SIZE];
		if (pgPaints.pgTexts == NULL)	return;		// 申请缓冲区不成功，直接返回
		myCountSize.message = DEF_BUFFER_SIZE;
	}
	if (myCount.message >= myCountSize.message)// 如果当前文本数大于缓冲区数
	{
		// 扩大缓冲区
		PMYTEXT pNewTexts = new MYTEXT[myCount.message + DEF_BUFFER_INC_SIZE];
		if (pNewTexts == NULL) return;	// 申请加大的缓冲区不成功，直接返回

		memcpy(pNewTexts, pgPaints.pgTexts, myCount.message*sizeof(MYTEXT));
		if (myCount.message != 0)			// 在读取操作中freebuffer函数已经将原缓冲区清空，此时不能再清空一次
		{
			delete pgPaints.pgTexts;					// 释放之前的缓冲区
		}
		pgPaints.pgTexts = pNewTexts;			// 重新给原缓冲区赋值
		myCountSize.message += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgTexts[myCount.message++] = mytt;		// 保存图形数据
}

void AddTextBuffer()
{
	pgPaints.gTexts.pBuffer = new char[DEF_BUFFER_SIZE];
	if (pgPaints.gTexts.pBuffer == NULL)
	{return;}		// 申请缓冲区不成功，直接返回
	myCountSize.textBuffer = DEF_BUFFER_SIZE;
}

BOOL MySaveData(void)
{
	FILE* fp = fopen("a.bin", "wb");

	if (fp != NULL)
	{
		fwrite(&myCount.line, sizeof(int), 1, fp);
		fwrite(pgPaints.pgLines, sizeof(MYLINE), myCount.line, fp);

		fwrite(&myCount.rectangle, sizeof(int), 1, fp);
		fwrite(pgPaints.pgRectangle, sizeof(MYRECTANGLE), myCount.rectangle, fp);

		fwrite(&myCount.ellipse, sizeof(int), 1, fp);
		fwrite(pgPaints.pgEllipse, sizeof(MYELLIPSE), myCount.ellipse, fp);

		fwrite(&myCount.message, sizeof(int), 1, fp);
		fwrite(pgPaints.pgTexts, sizeof(MYTEXT), myCount.message, fp);

		fclose(fp);
		return TRUE;
	}

	return FALSE;
}

BOOL MyLoadData(void)
{
	FreeBuffer();
	FILE* fp = fopen("a.bin", "rb");

	if (fp != NULL)
	{
		int iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		
		for (int i = 0;i < iCount; i++)
		{
			MYLINE r;
			fread(&r, sizeof(MYLINE), 1, fp);
			AddOneLineInfo(&r);
		}

		iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		for (int i = 0;i < iCount; i++)
		{
			MYRECTANGLE r;
			fread(&r, sizeof(MYRECTANGLE), 1, fp);
			AddOneRectInfo(r);
		}

		iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		for (int i = 0;i < iCount; i++)
		{
			MYELLIPSE r;
			fread(&r, sizeof(MYELLIPSE), 1, fp);
			AddOneEllipseInfo(r);
		}

		iCount = 0;
		fread(&iCount, sizeof(int), 1, fp);
		for (int i = 0;i < iCount; i++)
		{
			MYTEXT r;
			fread(&r, sizeof(MYTEXT), 1, fp);
			AddOneTextInfo(r);
		}

		fclose(fp);
		return TRUE;
	}

	return FALSE;
} 

VOID FreeBuffer()
{
	if (pgPaints.pgLines != NULL)		// 如果原来有数据，删掉
	{
		delete pgPaints.pgLines;
		myCountSize.line = 0;
		myCount.line = 0;
	}
	if (pgPaints.pgRectangle != NULL)		// 如果原来有数据，删掉
	{
		delete pgPaints.pgRectangle;
		myCountSize.rectangle = 0;
		myCount.rectangle = 0;
	}
	if (pgPaints.pgEllipse != NULL)		// 如果原来有数据，删掉
	{
		delete pgPaints.pgEllipse;
		myCountSize.ellipse = 0;
		myCount.ellipse = 0;
	}
	if (pgPaints.pgTexts != NULL)		// 如果原来有数据，删掉
	{
		delete pgPaints.pgTexts;
		myCountSize.message = 0;
		myCount.message = 0;
	}
}
