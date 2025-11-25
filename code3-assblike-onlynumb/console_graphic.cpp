#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

#include "console_graphic.hpp"

using namespace std;
//╚ ╔ ╩ ╦ ╠ ═ ╬ ╣ ║ ╗ ╝

/// ///////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                    ///
/// ///////////////////////////////////////////////////////                                         ///
///         ╔═╗ ╗ ╗ ╔═╗ ═╦═ ╔═╗ ╔╗╔╗ ╔═╗
/// ------* ╚═╗ ╚╦╝ ╚═╗  ║  ╠═  ║╚╝║ ╠═  *------
///         ╚═╝  ╚  ╚═╝  ╚  ╚═╝ ╚  ╚ ╚═╝
///  * SYSTEM FUNCTIONS, PROCEDURES AND VARIABLES

int WINDOW_WIDTH = 96;
int WINDOW_HEIGHT = 24;

int WINDOW_HALF_WIDTH = 48;
int WINDOW_HALF_HEIGHT = 12;

bool RUN_WINDOW = false;

//to use to start main loop (optional, you can create your own start/end variables)
void startWindow(int width, int height){
    setWindowSize(width, height);
    RUN_WINDOW = true;
}
bool windowRunning(){
    return RUN_WINDOW;
}
//set cursor at the bottom for the "return 0" of the main to be at the correct place, and set color to default
bool endWindow(){
    writeGoto(0, WINDOW_HEIGHT);
    setColorPrecise(/*default*/);
    RUN_WINDOW = false;
    return RUN_WINDOW;
}

//define the size of the window
void setWindowSize(int width, int height){
    WINDOW_WIDTH = width;
    WINDOW_HEIGHT = height;

    WINDOW_HALF_WIDTH = WINDOW_WIDTH >> 1;
    WINDOW_HALF_HEIGHT = WINDOW_HEIGHT >> 1;
}                                                                                                                ///
                                                                                                                 ///
                                                                                                                 ///
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////











/// ///////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                    ///
/// ///////////////////////////////////////////////////////                                         ///
///         ╔═╗ ╔╦╗ ╗ ╔ ╔═╗ ╔   ╔═╗                     ///                                         ///
/// ------* ╠═╝  ║   ╬  ╠═  ║   ╚═╗ *------             ///
///         ╚   ╚╩╝ ╝ ╚ ╚═╝ ╚═╝ ╚═╝                     ///
///  * PIXELWISE FUNCTIONS, PROCEDURES AND VARIABLES    ///

              //*      text back */
#define RED 31  //red     31   41
#define YELLOW 33  //yellow  33   43
#define GREEN 32   //green   32   42
#define CYAN 36  //cyan    36   46
#define BLUE 34  //blue    34   44
#define MAGENTA 35  //magenta 35   45
#define WHITE 37  //white   37   47
#define BLACK 30  //black   30   40
#define DARK 30

//set cursor position
void writeGoto(int x,int y){
    COORD coord={(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//write a "pixel"
void putPixel(int x, int y, char letter){
    if ( (0 <= x) and (x < WINDOW_WIDTH) and (0 <= y) and (y < WINDOW_HEIGHT) ){
        writeGoto(x, y);
        cout<<letter;
    }
}

//set color with for forground (text) and background colors
void setText(textStatus hexmode, int color){
    if (color==-1)
        cout<<"\033["<<hexmode<<'m';
    else
        cout<<"\033["<<hexmode<<';'<<color<<'m';
}
void setColorPrecise(int forground /*= 37 white forground*/, int background /*= 40 black background*/){
    cout << "\033[" << forground << ";" << background << "m";
}
//set color with the #define of the lib
void setColor(int forground /*WHITE*/, int background /*BLACK*/){
    setColorPrecise(forground, background + 10);
    //cout << "\033[" << forground << ";" << background + 10<< "m";
}

//put "pixel" with specific color
void putPixelColor(int x, int y, char letter, int forgroundColor, int backgroundColor){
    setColor(forgroundColor, backgroundColor);
    putPixel(x, y, letter);
}                                                                                                                ///

char fromUseLetterColorToActualDefinedColorValue(char letter){
    switch (letter){
        case 'r' : return RED;
        case 'y' : return YELLOW;
        case 'g' : return GREEN;
        case 'c' : return CYAN;
        case 'b' : return BLUE;
        case 'm' : return MAGENTA;
        case 'w' : return WHITE;
        case 'd' : return BLACK; //d for dark to differ from B of Blue
        default: return RED;
    }
}

//transform "ryg" into {RED,YELLOW,GREEN} for exemple
string textToCol(string colorText){
    int len = colorText.length();
    for (int i=0 ; i<len ; i++){
        colorText[i] = fromUseLetterColorToActualDefinedColorValue(colorText[i]);
    }
    return colorText;
}                                                                                                                 ///
                                                                                                                 ///
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////







/// ///////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                    ///
/// //////////////////////////////////////////////////////////                                      ///
///         ╔ ╔ ╔╦╗ ╔═╗ ╔ ╔   ╔   ╔═╗ ╔ ╔ ╔═╗ ╔            ///                                      ///
/// ------* ╠═╣  ║  ║╔╗ ╠═╣   ║   ╠═  ║ ║ ╠═  ║  *------   ///                                      ///
///         ╚ ╚ ╚╩╝ ╚═╝ ╚ ╚   ╚═╝ ╚═╝  V  ╚═╝ ╚═╝          ///
///  * HIGH LEVEL DRAW PROCEDURES

//draw the whole window with a character
void drawBlankWindowInit(char blankChar /*=' '*/){
    for (int y=0; y<WINDOW_HEIGHT; y++) for (int x=0; x<WINDOW_WIDTH; x++) putPixel(x,y,blankChar);
}

//draw the whole window with a character
void drawBlankWindowInitColors(char blankChar /*=' '*/,int forgroundColor, int backgroundColor){
    setColor(forgroundColor, backgroundColor);
    for (int y=0; y<WINDOW_HEIGHT; y++) for (int x=0; x<WINDOW_WIDTH; x++) putPixel(x,y,blankChar);
}

//draw a simple Column from a string texture
void drawColumn(string texture, int drawPosX, int drawPosYTop){

    int ySize = texture.length();//get column Size from the texture size

    for (int index=0 ; index<ySize ; index++){
        putPixel(drawPosX, drawPosYTop + index, texture[index]);
    }
}

//draw a simple Line from a string texture
void drawLine(string texture, int drawPosXStart, int drawPosY){

    int xSize = texture.length();//get column Size from the texture size
    //not just cout to not go out of frame
    for (int index=0 ; index<xSize ; index++){
        putPixel(drawPosXStart+index, drawPosY, texture[index]);
    }
}


//draw a variable height Column from a string texture
void drawColumnExt(string texture, int drawPosX, int drawPosYTop, int drawPosYBottom){

    if (drawPosYBottom < drawPosYTop){
        throw("drawColumnExt : got drawPosYTop bigger than drawPosYBottom (the system draw from top to bottom)");
    }

    float step = texture.length() / float(drawPosYBottom - drawPosYTop);
    float stringPixel = 0;

    for (int drawPosY=drawPosYTop ; drawPosY<drawPosYBottom ; drawPosY++){

        putPixel(drawPosX, drawPosY,  texture[int(stringPixel)] );
        //increment for next pixel
        stringPixel += step;
    }
}
//draw a variable height Line from a string texture
void drawLineExt(string texture, int drawPosXStart, int drawPosXEnd,int drawPosY){

    float step = texture.length() / float(drawPosXEnd - drawPosXStart);
    float stringPixel = 0;

    for (int drawPosX=drawPosXStart ; drawPosX<drawPosXEnd ; drawPosX++){
        putPixel(drawPosX, drawPosY,  texture[int(stringPixel)] );
        //increment for next pixel
        stringPixel += step;
    }
}



//draw a simple Column from a string texture
void drawColumnColor(string texture,string forgroundColor,string backgroundColor, int drawPosX, int drawPosYTop){

    int ySize = texture.length();//get column Size from the texture size

    for (int index=0 ; index<ySize ; index++){
        putPixelColor(drawPosX, drawPosYTop + index, texture[index],forgroundColor[index], backgroundColor[index]);
    }
}

//draw a simple Line from a string texture
void drawLineColor(string texture,string forgroundColor,string backgroundColor, int drawPosXStart, int drawPosY){

    int xSize = texture.length();//get column Size from the texture size
    //not just cout to not go out of frame
    for (int index=0 ; index<xSize ; index++){
        putPixelColor(drawPosXStart+index, drawPosY, texture[index], forgroundColor[index], backgroundColor[index]);
    }
}


//draw a variable height Column from a string texture
void drawColumnExtColor(string texture,string forgroundColor, string backgroundColor, int drawPosX, int drawPosYTop, int drawPosYBottom){

    const float step = texture.length() / float(drawPosYBottom - drawPosYTop);
    float index = 0;

    for (int drawPosY=drawPosYTop ; drawPosY<drawPosYBottom ; drawPosY++){
        putPixelColor(drawPosX, drawPosY,  texture[index], forgroundColor[index], backgroundColor[index] );
        //increment for next pixel
        index += step;
    }
}
//draw a variable height Line from a string texture
void drawLineExtColor(string texture,string forgroundColor, string backgroundColor, int drawPosXStart, int drawPosXEnd,int drawPosY){

    const float step = texture.length() / float(drawPosXEnd - drawPosXStart);
    float index = 0;

    for (int drawPosX=drawPosXStart ; drawPosX<drawPosXEnd ; drawPosX++){
        putPixelColor(drawPosX, drawPosY,  texture[index], forgroundColor[index], backgroundColor[index] );
        //increment for next pixel
        index += step;
    }
}




//draw a column of variable height from the center, for DDA raycasting
void drawColumnDDA(string texture, int drawPosX, float columnHeight){

    float columnHalfHeight = columnHeight/2 ;
    int y0 = WINDOW_HALF_HEIGHT - columnHalfHeight;
    int y1 = WINDOW_HALF_HEIGHT + columnHalfHeight;

    const float step = texture.length() / columnHeight;
    float stringPixel = 0;

    for (int drawPosY=y0 ; drawPosY<y1 ; drawPosY++){
        //get pixel to draw
        char letter = texture[int(stringPixel)];
        putPixel(drawPosX, drawPosY, letter);
        //increment for next pixel
        stringPixel += step;
    }
}





                                                                                                                 ///
                                                                                                                 ///
                                                                                                                 ///
/// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
