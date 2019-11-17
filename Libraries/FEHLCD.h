#ifndef FEHLCD_H
#define FEHLCD_H

#include "spi.h"
#include "derivative.h"
#include <LCDColors.h>
//#include <string>

//using namespace std;

class FEHLCD
{
public:

    typedef enum
    {
        Black = 0,
        White,
        Red,
        Green,
        Blue,
		Scarlet,
		Gray
    } FEHLCDColor;

    typedef enum
    {
        North = 0,
        South,
        East,
        West
    } FEHLCDOrientation;

    FEHLCD();
	
	bool Touch(float *x_pos,float *y_pos);

    void PrintImage(int x, int y);
    void PrintLogo(int x, int y);
    void Initialize();
    void SetOrientation(FEHLCDOrientation orientation);

    void Clear( FEHLCDColor color );
    void Clear(unsigned int color);
    void Clear();

    void SetFontColor( FEHLCDColor color );
    void SetFontColor( unsigned int color);
    void SetBackgroundColor( FEHLCDColor color );
    void SetBackgroundColor(unsigned int color);

    // Drawing Functions
    void DrawPixel(int x, int y);
    void DrawHorizontalLine(int y,int x1, int x2);
    void DrawVerticalLine(int x, int y1, int y2);
    void DrawLine(int x1, int y1, int x2, int y2);
    void DrawRectangle(int x, int y, int width, int height);
    void FillRectangle(int x, int y, int width, int height);
    void DrawCircle(int x0, int y0, int r);
    void FillCircle(int x0, int y0, int r);

    // Write information at a specific Pixel on the screen
	void WriteAt( const char * str, int x, int y );
	void WriteAt( int i, int x, int y );
	void WriteAt( float f, int x, int y );
	void WriteAt( double d, int x, int y );
	void WriteAt( bool b, int x, int y );
	void WriteAt( char c, int x, int y );

	// Write to Row, Column

	void WriteRC( const char * str, int row, int col );
	void WriteRC( int i, int row, int col );
	void WriteRC( float f, int row, int col );
	void WriteRC( double d, int row, int col );
	void WriteRC( bool b, int row, int col );
	void WriteRC( char c, int row, int col );

    // Write to the screen
    void Write( const char* str );
    void Write( int i );
    void Write( float f );
    void Write( double d );
    void Write( bool b );
	void Write( char c );

    // Write to the screeen and advance to next line
    void WriteLine( const char* str );
    void WriteLine( int i );
    void WriteLine( float f );
    void WriteLine( double d );
    void WriteLine( bool b );
	void WriteLine( char c );

private:
    typedef struct regColVal {
        uint32_t BVal;
        uint32_t CVal;
        uint32_t DVal;
    } RegisterColorValues;
	
	

	void TS_SPI_Init();

	int abs(int);
	
    void _Initialize();
    void _Clear();
    void _RepeatColor();
    void _BackPixel();
    void _ForePixel();
    void SetRegisterColorValues();

    void WriteChar(int row, int col, char c);
    void WriteCharAt(int x, int y, char c);

    void WriteIndex( unsigned char index );
    void WriteParameter( unsigned char param );
    void RepeatColor();

    unsigned int ConvertFEHColorTo24Bit(FEHLCDColor color);
    unsigned int Convert24BitColorTo16Bit(unsigned int color);
    unsigned int ConvertRGBColorTo16Bit(unsigned char r,unsigned char g,unsigned char b);

    void NextLine();
    void CheckLine();
    void NextChar();
    void SetDrawRegion(int x, int y, int width, int height);

    FEHLCDOrientation _orientation;

    int _maxlines;
    int _maxcols;
    int _width;
    int _height;
    int _currentline;
    int _currentchar;
    unsigned int _forecolor;
    unsigned int _backcolor;
    RegisterColorValues foreRegisterValues, backRegisterValues;
	
    int lastx;
    int lasty;

    static unsigned char fontData[];
};

namespace FEHMenu
{
    /* Class definition for software buttons */
    class Button
    {
        private:
            int x_start, y_start;
            int width, height;
            int line_color;
            int txt_color;
            char label[200];
            int selected;
        public:
            Button();
            FEHMenu::Button& SetName(char name[20]);
            FEHMenu::Button& SetName(int name);
            FEHMenu::Button& SetName(float name);
            FEHMenu::Button& SetName(double name);
            FEHMenu::Button& SetStart(int start_x, int start_y);
            FEHMenu::Button& SetDimensions(int w, int h);
            FEHMenu::Button& SetColors(int border_color, int text_color);
            void Draw();
            void Select();
            void Deselect();
            int IsSelected();
            int Contains(float x, float y);
            int IsPressed();
            void AwaitTouchUp(int alternate = 0);
    };

    /* Class definition that stores menu information */
    class Menu
    {
        int rows, cols;
        FEHMenu::Button * buttons;

        public:
            /* Class must be initialized with:
             * - Array of buttons (row*col in length)
             * - # rows, # cols
             * - Button labels, from top left across each row to the bottom right
             * - (Optional) Top, bottom, left, and right margins from edges of screen,
             * - (Optional) Color for the rectangle and the text color */
            Menu(Button * button, int row_length, int col_length, char labels[][20], int top = 0, int bottom = 0, int left = 0, int right = 0, int border_color = 0xFFFFFF, int text_color = 0xFFFFFF);
            int AwaitPress(int alternate = 0);
            void Draw();
            int Contains(float xc, float yc);
            int IsPressed();
    };

    void CheckMenus(Menu * menus, int menu_count, int * menu_index, int * btn_index);
}

extern FEHLCD LCD;

#endif // FEHLCD_H
