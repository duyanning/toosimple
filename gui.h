/*
西安理工大学 版权所有 2014
*/

#ifndef GUI_H
#define GUI_h

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int play_gui(void); /*开启图形用户界面窗口*/
void quit_gui(void); /*结束图形用户界面窗口*/

/*
	关于颜色的说明：
	凡是需要用到颜色的地方，就通过RGB(x, y, z)的形式来构造颜色。
	x、y、z的取值范围是0到255，分别表示红绿蓝三个分量的比例：如：
	RGB(255, 0, 0)表示红色，RGB(0, 255, 0)表示绿色，RGB(0, 0, 255)表示蓝色。
*/


/*绘制各种几何图形*/
void draw_line(int x1, int y1, int x2, int y2); /*画直线：x1, y1为起点，x1, y1为终点*/
void draw_rectangle(int x1, int y1, int x2, int y2); /*画矩形：x1, y1为左上角坐标，x1, y1为右下角坐标*/
void draw_circle(int x, int y, int r); /*画圆形：x, y为圆心坐标，r为半径*/
void draw_pie(int x, int y, int from, int to, int r); /*画扇形：x,y为圆心，r为半径，半径从角度from开始，逆时针扫到角度to*/
void set_pen_color(COLORREF color); /*设置画笔颜色：RGB(255, 0, 0)表示红色，RGB(0, 255, 0)表示绿色，RGB(0, 0, 255)表示蓝色*/
void set_pen_width(int width); /*设置画笔粗细：取值1、2、3、……*/
void turn_on_fill(void); /*开启图形填充：开启图形填充后，画一个圆，圆的内部就会被图上颜色，即所谓“填充”*/
void turn_off_fill(void); /*关闭图形填充*/
void set_fill_color(COLORREF color); /*设置填充色*/


/*输出文字*/
void draw_text(int x, int y, const char * s); /*在指定位置处输出字符串*/
void gui_printf(int x, int y, const char *fmt, ...); /*在指定位置输出格式化字符串*/
void set_gui_font_name(const char * name); /*设置字体名称：宋体、隶书*/
void set_gui_font_height(int height); /*设置文字高度*/
void set_gui_font_color(COLORREF color); /*设置文字颜色*/
void turn_on_gui_font_bk_color(void); /*开启文字背景色*/
void turn_off_gui_font_bk_color(void); /*关闭文字背景色*/
void set_gui_font_bk_color(COLORREF color); /*设置文字背景色*/


/*显示图片*/
void draw_bmp(int x, int y, const char *name); /*在指定位置处显示扩展名为.bmp的图片*/


/*
	指定如下形式的一个函数，这个函数会在用户按下鼠标左键时被调用
	void on_left_button(int x, int y)
	{
	}
	x和y为当时鼠标的位置坐标
*/
void please_call_this_function_when_left_button_pressed(void (*f)(int x, int y));


/*
	指定如下形式的一个函数，这个函数会在用户按下鼠标右键时被调用
	void on_right_button(int x, int y)
	{
	}
	x和y为当时鼠标的位置坐标
*/
void please_call_this_function_when_right_button_pressed(void (*f)(int x, int y));


/*
	指定如下形式的一个函数，这个函数会在窗口刷新时被调用
	void on_refresh(void)
	{
	}
	x和y为当时鼠标的位置坐标
*/
void please_call_this_function_when_refresh(void (*f)(void));


/*
	指定如下形式的一个函数，这个函数会在用户通过键盘输入字符时被调用
	void on_input(const char *s)
	{
	}
	s为用户输入的字符串，一般为单个字符或单个汉字
*/
void please_call_this_function_when_keyboard_input(void (*f)(const char *));

enum ArrowDirection {
	AD_UP, /*上*/
	AD_DOWN, /*下*/
	AD_LEFT, /*左*/
	AD_RIGHT /*右*/
};
/*
	指定如下形式的一个函数，这个函数会在用户按下键盘上的方向键时被调用
	void on_arrow(enum ArrowDirection d)
	{
	}
	d为AD_UP表示用户按了向上键
	d为AD_DOWN表示用户按了向下键
	d为AD_LEFT表示用户按了向左键
	d为AD_RIGHT表示用户按了向右键
*/
void please_call_this_function_when_arrow_key_pressed(void (*f)(enum ArrowDirection));

/*
	指定如下形式的一个函数，这个函数会在用户按下键盘上的功能键（F1-F12）时被调用
	void on_fn(int n)
	{
	}
	n为1表示用户按了F1，以此类推。
*/
void please_call_this_function_when_fn_key_pressed(void (*f)(int n));


/*
	指定如下形式的一个函数，这个函数会在用户按下键盘上的Esc键时被调用
	void on_esc(void)
	{
	}
*/
void please_call_this_function_when_esc_key_pressed(void (*f)(void));


/*
	指定如下形式的一个函数和一个时长（单位：微秒），系统每隔指定的时长就会调用这个函数
	void on_time_pass(void)
	{
	}
	特别注意：如果你不创建一个gui窗口，你即便指定了一个函数，也不会被调用。
*/
void please_call_this_function_every_N_milliseconds(void (*f)(void), int seconds);

#ifdef __cplusplus
}
#endif

#endif
