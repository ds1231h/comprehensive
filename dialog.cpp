#include "struct.h"

BOOL CALLBACK TextInputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			AddTextBuffer();
			GetDlgItemText(hDlg, IDC_EDIT1, (LPWSTR)pgPaints.gTexts.pBuffer, 128);
			EndDialog(hDlg, TRUE);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}
