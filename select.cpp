#include <stdio.h>
#include "struct.h"

void selectObj(MYOCOUNT myCount, LONG sx, LONG sy, LOGPEN gPenInfo, LOGBRUSH gBrushInfo, LOGFONT gFontInfo)
{
	for (int i = 0; i < myCount.rectangle; i++)
	{
		if (sx >= pgPaints.pgRectangle[i].rect.left && sx <= pgPaints.pgRectangle[i].rect.right)
		{
			if (sy >= pgPaints.pgRectangle[i].rect.top && sy <= pgPaints.pgRectangle[i].rect.bottom) // �Ҽ�����������һ������
			{
				// �ı���ѡ�о��ε���ɫ������
				pgPaints.pgRectangle[i].brInfo = gBrushInfo;
				pgPaints.pgRectangle[i].penInfo = gPenInfo;
				AddOneRectInfo(pgPaints.pgRectangle[i]);
				
			}
		} 
	}
}