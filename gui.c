/*
西安理工大学 版权所有 2014
*/

#include "gui.h"
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159

HINSTANCE hInst;
HWND hWnd;
char szWindowClass[] = "tooSimpleMainWindow";

/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_left_button_pressed)(int x, int y) = 0;

void please_call_this_function_when_left_button_pressed(void (*f)(int x, int y))
{
	function_to_call_when_left_button_pressed = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_right_button_pressed)(int x, int y) = 0;

void please_call_this_function_when_right_button_pressed(void (*f)(int x, int y))
{
	function_to_call_when_right_button_pressed = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_refresh)(void) = 0;

void please_call_this_function_when_refresh(void (*f)(void))
{
	function_to_call_when_refresh = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_keyboard_input)(const char *) = 0;

void please_call_this_function_when_keyboard_input(void (*f)(const char *))
{
	function_to_call_when_keyboard_input = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_arrow_key_pressed)(enum ArrowDirection d) = 0;

void please_call_this_function_when_arrow_key_pressed(void (*f)(enum ArrowDirection))
{
	function_to_call_when_arrow_key_pressed = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_fn_key_pressed)(int n) = 0;

void please_call_this_function_when_fn_key_pressed(void (*f)(int n))
{
	function_to_call_when_fn_key_pressed = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_esc_key_pressed)(void) = 0;

void please_call_this_function_when_esc_key_pressed(void (*f)(void))
{
	function_to_call_when_esc_key_pressed = f;
}
/*--------------------------------------------------------------------------------*/
void (*function_to_call_when_time_pass)(void) = 0;

void CALLBACK timer_proc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	function_to_call_when_time_pass();
}

UINT_PTR timer_id = 0;

void please_call_this_function_every_N_milliseconds(void (*f)(void), int seconds)
{
	if (timer_id != 0) {
		KillTimer(NULL, timer_id);
	}

	function_to_call_when_time_pass = f;
	timer_id = SetTimer(NULL, 0, seconds, timer_proc);
}
/*--------------------------------------------------------------------------------*/


int pen_width;
COLORREF pen_color;
COLORREF fill_color;
HPEN hPen = NULL;
HBRUSH hBrush = NULL;
int fill_state = 0; // 默认状态下不填充颜色


void set_pen_color(COLORREF color)
{
	pen_color = color;

	if (hPen) {
		DeleteObject(hPen);
	}

	hPen = CreatePen (PS_SOLID, pen_width, pen_color);

}

void set_pen_width(int width)
{
	pen_width = width;

	if (hPen) {
		DeleteObject(hPen);
	}

	hPen = CreatePen (PS_SOLID, pen_width, pen_color);
}

void set_fill_color(COLORREF color)
{
	fill_color = color;

	if (hBrush) {
		DeleteObject(hBrush);
	}

	hBrush = CreateSolidBrush(fill_color);
}

void turn_on_fill(void)
{
	fill_state = 1;

	if (hBrush) {
		DeleteObject(hBrush);
	}

	hBrush = CreateSolidBrush(fill_color);
}

void turn_off_fill(void)
{
	fill_state = 0;

	if (hBrush) {
		DeleteObject(hBrush);
	}

	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
}

/*--------------------------------------------------------------------------------*/
void draw_line(int x1, int y1, int x2, int y2)
{
	HDC hdc;
	hdc = GetDC (hWnd);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, x1, y1, NULL) ;
	LineTo(hdc, x2, y2);
	ReleaseDC(hWnd, hdc);
}
/*--------------------------------------------------------------------------------*/
void draw_circle(int x, int y, int r)
{
	HDC hdc;
	hdc = GetDC (hWnd);
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	Ellipse(hdc, x-r, y-r, x+r+1, y+r+1);
	ReleaseDC(hWnd, hdc);
}
/*--------------------------------------------------------------------------------*/
void draw_pie(int x, int y, int from, int to, int r)
{
	HDC hdc;
	int d;
	int x_delta_from, y_delta_from;
	int x_delta_to, y_delta_to;

	hdc = GetDC (hWnd);
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);

	d = (r >= 2) ? r / 2 : 1;

	x_delta_from = (int)(d*cos(from*PI/180));
	y_delta_from = (int)(d*sin(from*PI/180));
	x_delta_to = (int)(d*cos(to*PI/180));
	y_delta_to = (int)(d*sin(to*PI/180));

	// 弦从起始角度逆时针扫到终止角度
	//Pie(hdc, x-r, y-r, x+r+1, y+r+1, (int)(x+d*cos(from*PI/180)), (int)(y-d*sin(from*PI/180)), x+d*cos(end*PI/180), y-d*sin(end*PI/180));
	Pie(hdc, x-r, y-r, x+r+1, y+r+1, x+x_delta_from, y-y_delta_from, x+x_delta_to, y-y_delta_to);


	ReleaseDC(hWnd, hdc);
}
/*--------------------------------------------------------------------------------*/
void draw_rectangle(int x1, int y1, int x2, int y2)
{
	HDC hdc;
	hdc = GetDC (hWnd);
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, x1, y1, x2, y2);
	ReleaseDC(hWnd, hdc);
}
/*--------------------------------------------------------------------------------*/
HFONT hFont = NULL;
COLORREF gui_font_color;
COLORREF gui_font_bk_color = RGB(0, 0, 196);
int gui_use_font_bk_color = 0; // 默认状态下字体背景透明
char gui_font_name[100];
int gui_font_height;

void set_gui_font_name(const char * name)
{
	LOGFONT lf;

	strcpy(gui_font_name, name);


	lf.lfHeight         = gui_font_height;
	lf.lfWidth          = 0 ;
	lf.lfEscapement     = 0 ;
	lf.lfOrientation    = 0 ;
	lf.lfWeight         = 0;
	lf.lfItalic         = 0;
	lf.lfUnderline      = 0;
	lf.lfStrikeOut      = 0;
	lf.lfCharSet        = DEFAULT_CHARSET ;
	lf.lfOutPrecision   = 0 ;
	lf.lfClipPrecision  = 0 ;
	lf.lfQuality        = 0 ;
	lf.lfPitchAndFamily = 0 ;
	strcpy(lf.lfFaceName, gui_font_name);

	if (hFont) {
		DeleteObject(hFont);
	}

	hFont = CreateFontIndirect(&lf) ;
}

void set_gui_font_height(int height)
{
	LOGFONT lf;


	gui_font_height = height;

	lf.lfHeight         = gui_font_height;
	lf.lfWidth          = 0 ;
	lf.lfEscapement     = 0 ;
	lf.lfOrientation    = 0 ;
	lf.lfWeight         = 0;
	lf.lfItalic         = 0;
	lf.lfUnderline      = 0;
	lf.lfStrikeOut      = 0;
	lf.lfCharSet        = DEFAULT_CHARSET ;
	lf.lfOutPrecision   = 0 ;
	lf.lfClipPrecision  = 0 ;
	lf.lfQuality        = 0 ;
	lf.lfPitchAndFamily = 0 ;
	strcpy(lf.lfFaceName, gui_font_name);

	if (hFont) {
		DeleteObject(hFont);
	}

	hFont = CreateFontIndirect(&lf) ;
}

void set_gui_font_color(COLORREF color)
{
	gui_font_color = color;
}

void set_gui_font_bk_color(COLORREF color)
{
	gui_font_bk_color = color;
}

void turn_on_gui_font_bk_color(void)
{
	gui_use_font_bk_color = 1;
}

void turn_off_gui_font_bk_color(void)
{
	gui_use_font_bk_color = 0;
}
/*--------------------------------------------------------------------------------*/
void draw_text(int x, int y, const char * s)
{
	HDC hdc;

	hdc = GetDC (hWnd);

	SetTextColor(hdc, gui_font_color);
	SetBkColor(hdc, gui_font_bk_color);
	SetBkMode(hdc, (gui_use_font_bk_color ? OPAQUE : TRANSPARENT));

	SelectObject (hdc, hFont);

	TextOut(hdc, x, y, s, strlen(s));

	ReleaseDC(hWnd, hdc);
}
/*--------------------------------------------------------------------------------*/
void gui_printf(int x, int y, const char *fmt, ...)
{
	int len;
	char s[1000] ;
	va_list args;
	
	va_start(args, fmt);

	len = vsprintf(s, fmt, args) ;
	
	draw_text(x, y, s);

	va_end(args);
}
/*--------------------------------------------------------------------------------*/
void draw_bmp(int x, int y, const char *name)
{
	HBITMAP hBitmap;
	BITMAP bitmap;
	int cxSource, cySource;
	HDC hdc;
	HDC hdcMem;

	hBitmap = (HBITMAP) LoadImage(NULL, name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBitmap, sizeof (BITMAP), &bitmap);
	cxSource = bitmap.bmWidth;
    cySource = bitmap.bmHeight ;

	hdc = GetDC(hWnd);
	hdcMem = CreateCompatibleDC(hdc);

	SelectObject(hdcMem, hBitmap);
	BitBlt(hdc, x, y, cxSource, cySource, hdcMem, 0, 0, SRCCOPY) ;

	DeleteDC(hdcMem);
	ReleaseDC(hWnd, hdc);

	DeleteObject (hBitmap) ;

}
/*--------------------------------------------------------------------------------*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		int wmId, wmEvent;
	
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId) {
			//case IDM_ABOUT:
			   //DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			  // break;
			//case IDM_EXIT:
			  // DestroyWindow(hWnd);
			   //ybreak;
			default:
			   return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc;
		RECT rt;

		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rt);
		
		
		if (function_to_call_when_refresh) {
			function_to_call_when_refresh();
		}

		EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN: {
		if (function_to_call_when_left_button_pressed) {
			int x;
			int y;

			x = LOWORD (lParam);
			y = HIWORD(lParam);

			function_to_call_when_left_button_pressed(x, y);
			
		}
		break;
	}
	case WM_RBUTTONDOWN: {
		if (function_to_call_when_right_button_pressed) {
			int x;
			int y;

			x = LOWORD (lParam);
			y = HIWORD(lParam);

			function_to_call_when_right_button_pressed(x, y);
			
		}
		break;
	}
	case WM_CHAR: {
		char c = wParam;
		char buf[2];
		buf[0] = c;
		buf[1] = 0;

		//draw_text(3, 3, buf);
		if (function_to_call_when_keyboard_input) {
			function_to_call_when_keyboard_input(buf);
		}
		break;
	}
	case WM_IME_CHAR: {
		char c0 = (BYTE)(wParam >> 8);
		char c1 = wParam;
		char buf[3];

		buf[0] = c0;
		buf[1] = c1;
		buf[2] = 0;

		//draw_text(3, 3, buf);
		if (function_to_call_when_keyboard_input) {
			function_to_call_when_keyboard_input(buf);
		}
		break;
	}
	case WM_KEYDOWN: {
		switch (wParam) {
		
		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12: {
			if (function_to_call_when_fn_key_pressed) {
				function_to_call_when_fn_key_pressed(wParam-0x6F);
			}
			break;
		}

		case VK_LEFT: {
			if (function_to_call_when_arrow_key_pressed) {
				function_to_call_when_arrow_key_pressed(AD_LEFT);
			}
			break;
		}
		case VK_RIGHT: {
			if (function_to_call_when_arrow_key_pressed) {
				function_to_call_when_arrow_key_pressed(AD_RIGHT);
			}
			break;
		}
		case VK_UP: {
			if (function_to_call_when_arrow_key_pressed) {
				function_to_call_when_arrow_key_pressed(AD_UP);
			}
			break;
		}
		case VK_DOWN: {
			if (function_to_call_when_arrow_key_pressed) {
				function_to_call_when_arrow_key_pressed(AD_DOWN);
			}
			break;
		}
		case VK_ESCAPE: {
			if (function_to_call_when_esc_key_pressed) {
				function_to_call_when_esc_key_pressed();
			}
			break;
		}
		
		}
		break;
	}
	/*
	case WM_TIMER: {
		int i = wParam - 1;

		void (*f)(void);
		f = timer_map.data[i].f;
		f();
 
		break;
	}
	*/
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
   }


	return 0;

}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd) {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int play_gui(void)
{
	MSG msg;

	set_pen_color(RGB(255, 0, 0));
	set_gui_font_name("Courier New");
	set_gui_font_height(40);
	
	MyRegisterClass(0);

	if (!InitInstance(GetModuleHandle(NULL), SW_SHOWNORMAL)) {
		return 0;
	}

	SetForegroundWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	hWnd = NULL;
	return 1;
}

void quit_gui(void)
{
	//PostQuitMessage(0);
	DestroyWindow(hWnd);
}
