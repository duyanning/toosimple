#include <stdio.h>
#include "../../gui.h" // using ../../gui.c

// extra-compile-flags: -DWIN32
// extra-link-flags: -mwindows -lole32 -luuid -lcomctl32

void on_left_button(int x, int y)
{
	set_pen_width(6);
	set_pen_color(RGB(255, 0, 0));
	set_fill_color(RGB(255, 0, 0));
	turn_off_fill();
	draw_circle(x, y, 40);
}

void on_right_button(int x, int y)
{
	set_pen_width(3);
	set_pen_color(RGB(255, 255, 0));
	set_fill_color(RGB(0, 0, 255));
	turn_on_fill();
	//draw_circle(x, y, 20);
	//draw_rectangle(x, y, x+10, y+10);
	set_gui_font_name("隶书");
	set_gui_font_height(60);
	set_gui_font_color(RGB(255, 255, 0));
	turn_on_gui_font_bk_color();
	set_gui_font_bk_color(RGB(0, 0, 255));
	draw_text(x, y, "西安理工大学");
}

void on_refresh(void)
{
	//draw_circle(100, 100, 80);
	//draw_line(10, 10, 100, 100);
	draw_bmp(300, 10, "黑猩猩.bmp");
}

void on_input(const char *s)
{
	draw_text(3, 3, s);
}

int sun_x = 100;
int sun_y = 300;
void on_arrow(enum ArrowDirection d)
{

	set_pen_color(RGB(255, 255, 255));
	turn_on_fill();
	set_fill_color(RGB(255, 255, 255));
	draw_circle(sun_x, sun_y, 30);

	switch (d) {
	case AD_UP:
		sun_y -= 10;
		break;
	case AD_DOWN:
		sun_y += 10;
		break;
	case AD_LEFT:
		sun_x -= 10;
		break;
	case AD_RIGHT:
		sun_x += 10;
		break;
	}

	set_pen_color(RGB(255, 255, 0));
	set_fill_color(RGB(255, 255, 0));
	draw_circle(sun_x, sun_y, 30);
}

void timer(void)
{
	on_arrow(AD_RIGHT);
}

int main(void)
{

	please_call_this_function_when_left_button_pressed(on_left_button);
	please_call_this_function_when_right_button_pressed(on_right_button);
	please_call_this_function_when_refresh(on_refresh);
	please_call_this_function_when_keyboard_input(on_input);
	please_call_this_function_when_arrow_key_pressed(on_arrow);
	please_call_this_function_every_N_milliseconds(timer, 50);

	play_gui();

	puts("bye");
	

	return 0;
}
