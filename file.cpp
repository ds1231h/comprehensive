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
		{return;}		// ���뻺�������ɹ���ֱ�ӷ���
		goCountSizerectangle = DEF_BUFFER_SIZE;
	}
	if (goCountrectangle >= goCountSizerectangle)
	{
		// ���󻺳���
		PRECTANGLE pNew = new MYRECTANGLE[goCountrectangle+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNew, pgRectangle, goCountrectangle*sizeof(MYRECTANGLE));
		delete pgRectangle;					// �ͷ�֮ǰ�Ļ�����
		pgRectangle = pNew;
		goCountSizerectangle += DEF_BUFFER_INC_SIZE;
	}
	pgRectangle[goCountrectangle++] = myrc;		// ����ͼ������
}

VOID AddOneEllipseInfo(MYELLIPSE myrc)
{
	if (pgEllipse == NULL)
	{
		pgEllipse = new MYELLIPSE[DEF_BUFFER_SIZE];
		if (pgEllipse == NULL)	return;		// ���뻺�������ɹ���ֱ�ӷ���
		goCountSizeellipse = DEF_BUFFER_SIZE;
	}
	if (goCountellipse >= goCountSizeellipse)
	{
		// ���󻺳���
		PELLIPSE pNew = new MYELLIPSE[goCountellipse+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNew, pgEllipse, goCountellipse*sizeof(MYELLIPSE));
		delete pgEllipse;					// �ͷ�֮ǰ�Ļ�����
		pgEllipse = pNew;
		goCountSizeellipse += DEF_BUFFER_INC_SIZE;
	}
	pgEllipse[goCountellipse++] = myrc;		// ����ͼ������
}

VOID AddOneLineInfo(MYLINE myrc)
{
	if (pgLines == NULL)
	{
		pgLines = new MYLINE[DEF_BUFFER_SIZE];
		if (pgLines == NULL)	return;		// ���뻺�������ɹ���ֱ�ӷ���
		goCountSizeline = DEF_BUFFER_SIZE;
	}
	if (goCountline >= goCountSizeline)
	{
		// ���󻺳���
		PMYLINE pNew = new MYLINE[goCountline+DEF_BUFFER_INC_SIZE];
		if (pNew == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNew, pgLines, goCountline*sizeof(MYLINE));
		delete pgLines;					// �ͷ�֮ǰ�Ļ�����
		pgLines = pNew;
		goCountSizeline += DEF_BUFFER_INC_SIZE;
	}
	pgLines[goCountline++] = myrc;		// ����ͼ������
}

VOID AddOneTextInfo(MYTEXT mytt)
{
	if (pgTexts == NULL)
	{
		pgTexts = new MYTEXT[DEF_BUFFER_SIZE];
		if (pgTexts == NULL)	return;		// ���뻺�������ɹ���ֱ�ӷ���
		goCountSizemessage = DEF_BUFFER_SIZE;
	}
	if (goCountmessage >= goCountSizemessage)
	{
		// ���󻺳���
		MYTEXT* pNewTexts = new MYTEXT[goCountmessage + DEF_BUFFER_INC_SIZE];
		if (pNewTexts == NULL) return;	// ����Ӵ�Ļ��������ɹ���ֱ�ӷ���

		memcpy(pNewTexts, pgTexts, goCountmessage*sizeof(MYTEXT));
		delete pgTexts;					// �ͷ�֮ǰ�Ļ�����
		pgTexts = pNewTexts;
		goCountSizemessage += DEF_BUFFER_INC_SIZE;
	}
	pgTexts[goCountmessage++] = mytt;		// ����ͼ������
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
	if (pgLines != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgLines;
		goCountSizeline = 0;
		goCountline = 0;
	}
	if (pgRectangle != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgRectangle;
		goCountSizerectangle = 0;
		goCountrectangle = 0;
	}
	if (pgEllipse != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgEllipse;
		goCountSizeellipse = 0;
		goCountellipse = 0;
	}
	if (pgTexts != NULL)		// ���ԭ�������ݣ�ɾ��
	{
		delete pgTexts;
		goCountSizemessage = 0;
		goCountmessage = 0;
	}
}
