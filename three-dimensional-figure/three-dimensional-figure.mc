///////////////////////////////////////////////////////////////////////////
// Ahyane3DTest.mc - Auto Created by GNEX IDE
///////////////////////////////////////////////////////////////////////////

#ifdef _GVM
%{
        #DEFINE SCRIPTVER        2
        #DEFINE LCDCLASS        255
        #DEFINE IMAGETYPE        255
        #DEFINE AUDIOTYPE        255
        #DEFINE SCRIPTTYPE        1
        #DEFINE SCRIPTCPID        60000
        #DEFINE SCRIPTID        1
        #DEFINE SCRIPTNAME        "Ahyane3DTest"
        #DEFINE VALIDCOUNT        255
        #DEFINE VALIDTERM        255
%}
#else
%{
        #DEFINE PLAYERVER        4
        #DEFINE LCDCLASS        255
        #DEFINE IMAGETYPE        255
        #DEFINE AUDIOTYPE        255
        #DEFINE APPTYPE                1
        #DEFINE APPCPID                60000
        #DEFINE APPID                1
        #DEFINE APPNAME                "Ahyane3DTest"
        #DEFINE COMPTYPE        0
        #DEFINE AGENTTYPE        0
        #DEFINE VALIDCOUNT        255
        #DEFINE VALIDTERM        255
        #DEFINE DIRECTRUN        0
        #DEFINE APPVER                1
%}
#endif

#include <SScript.h>
#define S_RED                109                //빨간색
#define S_MARGENTA        112                //보라색
#define S_ROSE                114                //장미색
#define S_ORANGE        117                //주황색
#define S_PINK                119                //분혼색
#define S_APRICOT        122                //살구색
#define S_YELLOW        129                //노란색

int CounterR = 0;
int CounterX = 0;
int CounterY = 0;
int X[3] = {10, 30, 35};
int Y[3] = {10, 15, 30};
int Edge = 3;
int DirectionX = 1;
int DirectionY = 1;
int Mode = 0;

void FrameCounting(int How){
        string temp;
        MakeStr3(temp, "X = %3d′, Y = %3d′, Z = %3d′", CounterX, CounterY, CounterR);
        SetFontType(S_FONT_LARGE, S_BLACK, S_BLACK, S_ALIGN_LEFT);
        DrawStr(20,20,temp);

        switch(How){
                case 0:
                        if(CounterX < 360) CounterX += 10;
                        else CounterX = 0;
                        break;

                case 1:
                        if(CounterY < 360) CounterY += 10;
                        else CounterY = 0;
                        break;

                case 2:
                        if(CounterR < 360) CounterR += 10;
                        else CounterR = 0;
                        break;
        }
}

void DrawPolygon(){
        int TX[3], TY[3];
        int i;
        string temp;

        for(i = 0; i < Edge; i++){
                TX[i] = X[i] * Sin100(CounterY)/100 + 120;
                TY[i] = Y[i] * Sin100(CounterX)/100 + 150;
        }

        FillPoly(TX, TY, Edge);
        
        MakeStr2(temp, "%d, %d", TX[0], TY[0]);
        DrawStr(20,50,temp);
}

void DrawCoax(){
        DrawHLine(0, 240, 150);
        DrawVLine(120, 0, 300);
}

void RotatePolygon(int *VX, int *VY, int VEdge, int AngleX, int AngleY, int AngleZ, int DgreeX, int DgreeY){
        int TX[5], TY[5];        //메모리 낭비. 해결방법 찾아야함(포인터나 동적배열로)
        int UX, UY;
        int DX, DY;
        int i;
        
        for(i = 0; i < VEdge; i++){
                UX = *(VX+i) + DgreeX;
                UY = *(VY+i) + DgreeY;
                DX = (UX * Sin100(AngleZ)/100 + UY * Cos100(AngleZ)/100);
                DY = (UX * Cos100(AngleZ)/100 - UY * Sin100(AngleZ)/100);
                UX = (DX * Sin100(AngleY)/100 + DY * Cos100(AngleY)/100);
                UY = (DX * Cos100(AngleX)/100 - DY * Sin100(AngleX)/100);
                TX[i] = UX + 120;
                TY[i] = UY + 150;
        }
        
        FillPoly(TX, TY, VEdge);
}

void main(){
        SetTimer(20,1);

}

void EVENT_TIMEOUT(){
        int i;
        ClearWhite();

        FrameCounting(Mode);

        SetColor(S_ROSE);
        DrawPolygon();
        DrawCoax();

        SetColor(S_APRICOT);
        FillEllipse(120,150,8,8);

        SetColor(S_ORANGE);
        for(i = 0; i < 6; i++){
                RotatePolygon(X, Y, Edge, CounterX, CounterY, CounterR - i * 60, i, 0);
        }

        Flush();
}

void EVENT_KEYPRESS(){
        if(swData == SWAP_KEY_OK){
                Mode = (Mode + 1) % 3;
        }
}

void EVENT_END(){

}
