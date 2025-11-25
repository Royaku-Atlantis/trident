#ifndef CONSOLE_GRAPHIC_HPP
#define CONSOLE_GRAPHIC_HPP
#include <string>
using namespace std;

/// SYSTEM FUNCTIONS, PROCEDURES AND VARIABLES

extern int WINDOW_HEIGHT;
extern int WINDOW_WIDTH;

extern int WINDOW_HALF_WIDTH;
extern int WINDOW_HALF_HEIGHT;

extern bool RUN_WINDOW;

//to use to start main loop (optional, you can create your own start/end variables)
void startWindow(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT);
//get if the window is running or not
bool windowRunning();
//set cursor at the bottom for the "return 0" of the main to be at the correct place, and set color to default
bool endWindow();

//define the size of the window
void setWindowSize(int width, int height);



///  * PIXELWISE FUNCTIONS, PROCEDURES AND VARIABLES
              //*      text back */
#define RED 31     //red     31   41
#define YELLOW 33  //yellow  33   43
#define GREEN 32   //green   32   42
#define CYAN 36    //cyan    36   46
#define BLUE 34    //blue    34   44
#define MAGENTA 35 //magenta 35   45
#define WHITE 37   //white   37   47
#define BLACK 30   //black   30   40
#define DARK 30
//setColorPrecise() RED YELLOW GREEN CYAN BLUE MAGENTA WHITE BLACK/DARK

void writeGoto(int x, int y);
void putPixel(int x, int y, char letter);

enum textStatus {TXT_DEFAULT, TXT_BOLD, TXT_DARKER, TXT_idk1, TXT_UNDERLINED, TXT_idk5, TXT_idk6, TXT_SETBACKGROUND, TXT_idk8, TXT_STRIKETHROUGH};
void setText(textStatus hexmode, int color=-1);

//set color with for forground (text) and background colors
void setColorPrecise(int forground = 37 /*white forground*/, int background = 40 /*black background*/);
//set color with the #define of the lib
void setColor(int forground /*WHITE*/, int background /*BLACK*/);

//put "pixel" with specific color
void putPixelColor(int x, int y, char letter, int forgroundColor, int backgroundColor);

//transform "ryg" into {RED,YELLOW,GREEN} for exemple
string textToCol(string colorText);



///  * HIGH LEVEL DRAW PROCEDURES

//draw the whole window with a character
void drawBlankWindowInit(char blankChar = ' ');
//draw the whole window with a character
void drawBlankWindowInitColors(char blankChar /*  =' '  */,int forgroundColor, int backgroundColor);



//draw a simple Column from a string texture
void drawColumn(string texture, int drawPosX, int drawPosYTop);
//draw a simple Line from a string texture
void drawLine(string texture, int drawPosXStart, int drawPosY);

//draw a variable height Column from a string texture
void drawColumnExt(string texture, int drawPosX, int drawPosYTop, int drawPosYBottom);
//draw a variable height Line from a string texture
void drawLineExt(string texture, int drawPosXStart, int drawPosXEnd,int drawPosY);


//draw a simple Column from a string texture
void drawColumnColor(string texture,string forgroundColor,string backgroundColor, int drawPosX, int drawPosYTop);
//draw a simple Line from a string texture
void drawLineColor(string texture,string forgroundColor,string backgroundColor, int drawPosXStart, int drawPosY);

//draw a variable height Column from a string texture
void drawColumnExtColor(string texture,string forgroundColor,string backgroundColor, int drawPosX, int drawPosYTop, int drawPosYBottom);
//draw a variable height Line from a string texture
void drawLineExtColor(string texture,string forgroundColor,string backgroundColor, int drawPosXStart, int drawPosXEnd,int drawPosY);

//draw a column of variable height from the center, for DDA raycasting
void drawColumnDDA(string texture, int drawPosX, float columnHeight);








#endif





