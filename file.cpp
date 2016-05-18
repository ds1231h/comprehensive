#include <stdio.h>
#include "struct.h"

// ȫ�ֱ�����¼ͼԪ��Ŀ
MYOCOUNT myCount;
MYOCOUNT myCountSize;

//ȫ�ֱ������ͼԪ��Ϣ
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
		{return;}		// ���뻺�������ɹ���ֱ�ӷ���
		myCountSize.rectangle = DEF_BUFFER_SIZE;
	}
	if (myCount.rectangle >= myCountSize.rectangle)
	{
		// ���󻺳���
		PRECTANGLE pNew = new MYRECTANGLE[myCount.rectangle+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNew, pgPaints.pgRectangle, myCount.rectangle*sizeof(MYRECTANGLE));
		if (myCount.message != 0)
		{
			delete pgPaints.pgRectangle;					// �ͷ�֮ǰ�Ļ�����
		}
		pgPaints.pgRectangle = pNew;
		myCountSize.rectangle += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgRectangle[myCount.rectangle++] = myrc;		// ����ͼ������
}

VOID AddOneEllipseInfo(MYELLIPSE myep)
{
	if (pgPaints.pgEllipse == NULL)
	{
		pgPaints.pgEllipse = new MYELLIPSE[DEF_BUFFER_SIZE];
		if (pgPaints.pgEllipse == NULL)	return;		// ���뻺�������ɹ���ֱ�ӷ���
		myCountSize.ellipse = DEF_BUFFER_SIZE;
	}
	if (myCount.ellipse >= myCountSize.ellipse)
	{
		// ���󻺳���
		PELLIPSE pNew = new MYELLIPSE[myCount.ellipse+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNew, pgPaints.pgEllipse, myCount.ellipse*sizeof(MYELLIPSE));
		if (myCount.message != 0)
		{
			delete pgPaints.pgEllipse;					// �ͷ�֮ǰ�Ļ�����
		}
		pgPaints.pgEllipse = pNew;
		myCountSize.ellipse += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgEllipse[myCount.ellipse++] = myep;		// ����ͼ������
}

VOID AddOneLineInfo(PMYLINE myl)
{
	if (pgPaints.pgLines == NULL)
	{
		pgPaints.pgLines = new MYLINE[DEF_BUFFER_SIZE];
		if (pgPaints.pgLines == NULL)	return;		// ���뻺�������ɹ���ֱ�ӷ���
		myCountSize.line = DEF_BUFFER_SIZE;
	}
	if (myCount.line >= myCountSize.line)
	{
		// ���󻺳���
		PMYLINE pNew = new MYLINE[myCount.line+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNew, pgPaints.pgLines, myCount.line*sizeof(MYLINE));
		if (myCount.message != 0)
		{
			delete pgPaints.pgLines;					// �ͷ�֮ǰ�Ļ�����
		}
		pgPaints.pgLines = pNew;
		myCountSize.line += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgLines[myCount.line++] = *myl;		// ����ͼ������
}

VOID AddOneTextInfo(MYTEXT mytt)
{
	if (pgPaints.pgTexts == NULL)
	{
		pgPaints.pgTexts = new MYTEXT[DEF_BUFFER_SIZE];
		if (pgPaints.pgTexts == NULL)	return;		// ���뻺�������ɹ���ֱ�ӷ���
		myCountSize.message = DEF_BUFFER_SIZE;
	}
	if (myCount.message >= myCountSize.message)// �����ǰ�ı������ڻ�������
	{
		// ���󻺳���
		PMYTEXT pNewTexts = new MYTEXT[myCount.message + DEF_BUFFER_INC_SIZE];
		if (pNewTexts == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNewTexts, pgPaints.pgTexts, myCount.message*sizeof(MYTEXT));
		if (myCount.message != 0)			// �ڶ�ȡ������freebuffer�����Ѿ���ԭ��������գ���ʱ���������һ��
		{
			delete pgPaints.pgTexts;					// �ͷ�֮ǰ�Ļ�����
		}
		pgPaints.pgTexts = pNewTexts;			// ���¸�ԭ��������ֵ
		myCountSize.message += DEF_BUFFER_INC_SIZE;
	}
	pgPaints.pgTexts[myCount.message++] = mytt;		// ����ͼ������
}

void AddTextBuffer()
{
	pgPaints.gTexts.pBuffer = new char[DEF_BUFFER_SIZE];
	if (pgPaints.gTexts.pBuffer == NULL)
	{return;}		// ���뻺�������ɹ���ֱ�ӷ���
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
	if (pgPaints.pgLines != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgPaints.pgLines;
		myCountSize.line = 0;
		myCount.line = 0;
	}
	if (pgPaints.pgRectangle != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgPaints.pgRectangle;
		myCountSize.rectangle = 0;
		myCount.rectangle = 0;
	}
	if (pgPaints.pgEllipse != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgPaints.pgEllipse;
		myCountSize.ellipse = 0;
		myCount.ellipse = 0;
	}
	if (pgPaints.pgTexts != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgPaints.pgTexts;
		myCountSize.message = 0;
		myCount.message = 0;
	}
}
