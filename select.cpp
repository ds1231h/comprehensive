#include <stdio.h>
#include "struct.h"

void selectObj(MYOCOUNT myCount, LONG sx, LONG sy, LOGPEN gPenInfo, LOGBRUSH gBrushInfo, LOGFONT gFontInfo)
{
	for (int i = 0; i < myCount.rectangle; i++)
	{
		if (sx >= pgPaints.pgRectangle[i].rect.left && sx <= pgPaints.pgRectangle[i].rect.right)
		{
			if (sy >= pgPaints.pgRectangle[i].rect.top && sy <= pgPaints.pgRectangle[i].rect.bottom) // 右键所在区域是一个矩形
			{
				// 改变所选中矩形的颜色、线型
				pgPaints.pgRectangle[i].brInfo = gBrushInfo;
				pgPaints.pgRectangle[i].penInfo = gPenInfo;
				AddOneRectInfo(pgPaints.pgRectangle[i]);
				
			}
		} 
	}
}