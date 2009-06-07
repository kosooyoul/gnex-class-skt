///////////////////////////////////////////////////////////////////////////
// Physical.mc - Auto Created by GNEX IDE
///////////////////////////////////////////////////////////////////////////

#ifdef _GVM
%{
	#DEFINE SCRIPTVER	2
	#DEFINE LCDCLASS	255
	#DEFINE IMAGETYPE	255
	#DEFINE AUDIOTYPE	255
	#DEFINE SCRIPTTYPE	1
	#DEFINE SCRIPTCPID	60000
	#DEFINE SCRIPTID	1
	#DEFINE SCRIPTNAME	"Physical GVM2X App"
	#DEFINE VALIDCOUNT	255
	#DEFINE VALIDTERM	255
%}
#else
%{
	#DEFINE PLAYERVER	4
	#DEFINE LCDCLASS	255
	#DEFINE IMAGETYPE	255
	#DEFINE AUDIOTYPE	255
	#DEFINE APPTYPE		1
	#DEFINE APPCPID		60000
	#DEFINE APPID		1
	#DEFINE APPNAME		"Physical GNEX App"
	#DEFINE COMPTYPE	0
	#DEFINE AGENTTYPE	0
	#DEFINE VALIDCOUNT	255
	#DEFINE VALIDTERM	255
	#DEFINE DIRECTRUN	0
	#DEFINE APPVER		1
%}
#endif

#include <SScript.h>
#include "Palette.h"
#include "Physical.h"

int option = TRUE;

void main(){
	initW();
	initS();
	setEnabledMaterial(0, TRUE);
	setEnabledMaterial(1, FALSE);
	setEnabledMaterial(2, FALSE);
	setEnabledMaterial(3, FALSE);
	setEnabledMaterial(4, TRUE);
	setEnabledMaterial(5, TRUE);
	SetTimer(20, 1);
	ClearWhite();
}

void EVENT_TIMEOUT(){
	int i;
	string temp;

	if(option == TRUE){
		ClearWhite();
		DrawStr(10, 160, "잔상남음으로 : 별 키");
	}else{
		DrawStr(10, 160, "잔상없음으로 : 별 키");
	}

	DrawStr(10, 10, "화면을 지우려면 OK키를 누르세요.");
	DrawStr(10, 30, "재시작은 CLR키를 누르세요.");

	DrawStr(10, 305, "by kosooyoul");

	for(i = 0; i < MATERIAL_MAX_COUNT; i++){
		//MakeStr2(temp, "%d,%d", PublicMaterial[i].powerX,PublicMaterial[i].powerY);
		//DrawStr(10 + 50*i, 10, temp);
				SetColor(S_BLACK);
		FillRect(58, 53 + 15 * i, 65, 60 + 15 * i);
		if(PublicMaterial[i].enabled == TRUE){
			moveMaterial(i);
			drawMaterial(i);

			MakeStr1(temp, "%d키  on", i+1);
			SetColor(PublicMaterial[i].type);
		}else{
			MakeStr1(temp, "%d키 off", i+1);
			SetColor(S_WHITE);
		}
		DrawStr(10, 50 + 15 * i, temp);
		FillRect(60, 55 + 15 * i, 63, 58 + 15 * i);
	}


	MakeStr1(temp, "LEFT KEY < 중력 : %d > RIGHT KEY", GRAVITY);
	DrawStr(30, 280, temp);

	drawAllWall();

	Flush();
}

void initW(){
	initWall(0,  10, 230,  10, 300, DIRECTION_IN);
	initWall(1,  70, 170, 200, 250, DIRECTION_OUT);
	initWall(2,  30, 120, 120, 150, DIRECTION_OUT);
	initWall(3, 170, 200,  30, 100, DIRECTION_OUT);
}

void initS(){
	initMaterial(0, 200, 200, -50, 150,   0,  77,  10, S_RED);
	initMaterial(1,  50, 250,  50, 200,   0,  99,  20, S_CHOCO);
	initMaterial(2,  20, 100,-100,-200,   0,  80,  50, S_BLUE);
	initMaterial(3,  20, 100,  50, 100,   0,  57,  20, S_MARGENTA);
	initMaterial(4,  50,  50,  70,  70,   0,  30,  50, S_OLDLEAF);
	initMaterial(5,  50,  50,  50,  90,   0,  10,  10, S_SEA);
}

void EVENT_KEYPRESS(){
	switch(swData){
		case SWAP_KEY_OK:
			ClearWhite();
			break;
		case SWAP_KEY_CLR:
			ClearWhite();
			initS();
			break;
		case SWAP_KEY_1:
		case SWAP_KEY_2:
		case SWAP_KEY_3:
		case SWAP_KEY_4:
		case SWAP_KEY_5:
		case SWAP_KEY_6:
			if(PublicMaterial[swData-1].enabled == TRUE) PublicMaterial[swData-1].enabled = FALSE;
			else PublicMaterial[swData-1].enabled = TRUE;
			break;
		
		case SWAP_KEY_STAR:
			if(option == TRUE) option = FALSE;
			else option = TRUE;
			break;
		case SWAP_KEY_LEFT:
			if(GRAVITY > 0) GRAVITY--;
			break;
		case SWAP_KEY_RIGHT:
			if(GRAVITY < 20) GRAVITY++;
			break;

	}

}