#include "stdafx.h"
#include "ProcessMain.h"

// Process message from message loop
LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message) {
	case WM_PAINT: {
		// draw the window
		hdc = BeginPaint(hWnd, &ps);

		OnPaint(hdc);

		EndPaint(hWnd, &ps);

		return 0;
	}
				 // keyboard input
	case WM_KEYDOWN: {
		switch (wParam) {
			// press esc to exit
		case VK_ESCAPE: {
			// message box to exit
			// yes no options
			int value = MessageBox(hWnd, L"Are you sure?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
			if (value == IDYES) {		// click yes
				PostQuitMessage(0);
				return 0;
			}
			// click no or X
			break;
		}
					  // press space to reset objects
		case VK_SPACE:
			SVGReader::getInstance().x = SVGReader::getInstance().y = 0;
			SVGReader::getInstance().scale = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

			// press arrow keys to move around
		case VK_LEFT:
			SVGReader::getInstance().x -= 20;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_UP:
			SVGReader::getInstance().y -= 20;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_RIGHT:
			SVGReader::getInstance().x += 20;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case VK_DOWN:
			SVGReader::getInstance().y += 20;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

			// zoom in and out
		case 'I': // in
			SVGReader::getInstance().setScale(0.05);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 'O':
			SVGReader::getInstance().setScale(-0.05);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		break;
	}
				   // menu bar
	case WM_COMMAND: {
		switch (wParam) {
		case IDM_ABOUT: // about in view
			DialogBoxW(SVGReader::getInstance().hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, DlgProc);
			break;

			// open file in file menu bar
		case ID_FILE_OPEN:
			SVGReader::getInstance().openFile();

			SVGReader::getInstance().processXML();

			InvalidateRect(hWnd, NULL, TRUE);

			break;
		case IDM_EXIT: { // exit in file
			// message box to exit
			// yes no options
			int value = MessageBox(hWnd, L"Are you sure?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
			if (value == IDYES) {		// click yes
				PostQuitMessage(0);
				return 0;
			}
			// click no or X
			break;
		}

					 // zoom in and out, reset zoom in menu view
		case ID_VIEW_ZOOMIN:
			SVGReader::getInstance().setScale(0.05);
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_VIEW_ZOOMOUT:
			SVGReader::getInstance().setScale(-0.05);
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_VIEW_RESETZOOM:
			SVGReader::getInstance().scale = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		break;
	}
	// press X
	//case WM_CLOSE: { 
	//	// message box to exit
	//		// yes no options
	//	int value = MessageBox(hWnd, L"Are you sure?", L"Exit", MB_YESNO | MB_ICONEXCLAMATION);
	//	if (value == IDYES) {		// click yes
	//		PostQuitMessage(0);
	//		return 0;
	//	}
	//	// click no or X
	//	break;
	//}
	case WM_DESTROY: // click X
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc


// Process message from dialog box (about in menu bar)
LRESULT CALLBACK DlgProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam) {
		case IDOK: case WM_DESTROY: // close or X
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}


// draw shapes in WndProc
VOID OnPaint(HDC hdc) {
	Graphics graphics(hdc);

	SVGReader::getInstance().render(graphics);

	//processXML(graphics, SVGReader::getInstance().curFileName);

} // OnPaint

