/*
��������ѧ ��Ȩ���� 2014
*/

#ifndef GUI_H
#define GUI_h

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int play_gui(void); /*����ͼ���û����洰��*/
void quit_gui(void); /*����ͼ���û����洰��*/

/*
	������ɫ��˵����
	������Ҫ�õ���ɫ�ĵط�����ͨ��RGB(x, y, z)����ʽ��������ɫ��
	x��y��z��ȡֵ��Χ��0��255���ֱ��ʾ���������������ı������磺
	RGB(255, 0, 0)��ʾ��ɫ��RGB(0, 255, 0)��ʾ��ɫ��RGB(0, 0, 255)��ʾ��ɫ��
*/


/*���Ƹ��ּ���ͼ��*/
void draw_line(int x1, int y1, int x2, int y2); /*��ֱ�ߣ�x1, y1Ϊ��㣬x1, y1Ϊ�յ�*/
void draw_rectangle(int x1, int y1, int x2, int y2); /*�����Σ�x1, y1Ϊ���Ͻ����꣬x1, y1Ϊ���½�����*/
void draw_circle(int x, int y, int r); /*��Բ�Σ�x, yΪԲ�����꣬rΪ�뾶*/
void draw_pie(int x, int y, int from, int to, int r); /*�����Σ�x,yΪԲ�ģ�rΪ�뾶���뾶�ӽǶ�from��ʼ����ʱ��ɨ���Ƕ�to*/
void set_pen_color(COLORREF color); /*���û�����ɫ��RGB(255, 0, 0)��ʾ��ɫ��RGB(0, 255, 0)��ʾ��ɫ��RGB(0, 0, 255)��ʾ��ɫ*/
void set_pen_width(int width); /*���û��ʴ�ϸ��ȡֵ1��2��3������*/
void turn_on_fill(void); /*����ͼ����䣺����ͼ�����󣬻�һ��Բ��Բ���ڲ��ͻᱻͼ����ɫ������ν����䡱*/
void turn_off_fill(void); /*�ر�ͼ�����*/
void set_fill_color(COLORREF color); /*�������ɫ*/


/*�������*/
void draw_text(int x, int y, const char * s); /*��ָ��λ�ô�����ַ���*/
void gui_printf(int x, int y, const char *fmt, ...); /*��ָ��λ�������ʽ���ַ���*/
void set_gui_font_name(const char * name); /*�����������ƣ����塢����*/
void set_gui_font_height(int height); /*�������ָ߶�*/
void set_gui_font_color(COLORREF color); /*����������ɫ*/
void turn_on_gui_font_bk_color(void); /*�������ֱ���ɫ*/
void turn_off_gui_font_bk_color(void); /*�ر����ֱ���ɫ*/
void set_gui_font_bk_color(COLORREF color); /*�������ֱ���ɫ*/


/*��ʾͼƬ*/
void draw_bmp(int x, int y, const char *name); /*��ָ��λ�ô���ʾ��չ��Ϊ.bmp��ͼƬ*/


/*
	ָ��������ʽ��һ��������������������û�����������ʱ������
	void on_left_button(int x, int y)
	{
	}
	x��yΪ��ʱ����λ������
*/
void please_call_this_function_when_left_button_pressed(void (*f)(int x, int y));


/*
	ָ��������ʽ��һ��������������������û���������Ҽ�ʱ������
	void on_right_button(int x, int y)
	{
	}
	x��yΪ��ʱ����λ������
*/
void please_call_this_function_when_right_button_pressed(void (*f)(int x, int y));


/*
	ָ��������ʽ��һ������������������ڴ���ˢ��ʱ������
	void on_refresh(void)
	{
	}
	x��yΪ��ʱ����λ������
*/
void please_call_this_function_when_refresh(void (*f)(void));


/*
	ָ��������ʽ��һ��������������������û�ͨ�����������ַ�ʱ������
	void on_input(const char *s)
	{
	}
	sΪ�û�������ַ�����һ��Ϊ�����ַ��򵥸�����
*/
void please_call_this_function_when_keyboard_input(void (*f)(const char *));

enum ArrowDirection {
	AD_UP, /*��*/
	AD_DOWN, /*��*/
	AD_LEFT, /*��*/
	AD_RIGHT /*��*/
};
/*
	ָ��������ʽ��һ��������������������û����¼����ϵķ����ʱ������
	void on_arrow(enum ArrowDirection d)
	{
	}
	dΪAD_UP��ʾ�û��������ϼ�
	dΪAD_DOWN��ʾ�û��������¼�
	dΪAD_LEFT��ʾ�û����������
	dΪAD_RIGHT��ʾ�û��������Ҽ�
*/
void please_call_this_function_when_arrow_key_pressed(void (*f)(enum ArrowDirection));

/*
	ָ��������ʽ��һ��������������������û����¼����ϵĹ��ܼ���F1-F12��ʱ������
	void on_fn(int n)
	{
	}
	nΪ1��ʾ�û�����F1���Դ����ơ�
*/
void please_call_this_function_when_fn_key_pressed(void (*f)(int n));


/*
	ָ��������ʽ��һ��������������������û����¼����ϵ�Esc��ʱ������
	void on_esc(void)
	{
	}
*/
void please_call_this_function_when_esc_key_pressed(void (*f)(void));


/*
	ָ��������ʽ��һ��������һ��ʱ������λ��΢�룩��ϵͳÿ��ָ����ʱ���ͻ�����������
	void on_time_pass(void)
	{
	}
	�ر�ע�⣺����㲻����һ��gui���ڣ��㼴��ָ����һ��������Ҳ���ᱻ���á�
*/
void please_call_this_function_every_N_milliseconds(void (*f)(void), int seconds);

#ifdef __cplusplus
}
#endif

#endif
