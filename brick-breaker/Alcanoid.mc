/*
	알카노이드 벽돌 깨기

만든이 : 고수열

ㅜ_ㅜ

완성도가 높아 보이도록 각 모드 구성을 완성하려고 했지만 시간이 부족했습니다. 시간이 더 있었으면 완성했는데 ㄲㄲㄲ
우선 기본 모드는 플레이모드.
블럭깨면 점수도 올라갑니다. ㅇㅂㅇ;;

*/

#ifdef _GVM
%{
	#DEFINE SCRIPTVER	2
	#DEFINE LCDCLASS	255
	#DEFINE IMAGETYPE	255
	#DEFINE AUDIOTYPE	255
	#DEFINE SCRIPTTYPE	1
	#DEFINE SCRIPTCPID	60000
	#DEFINE SCRIPTID	1
	#DEFINE SCRIPTNAME	"Alcanoid GVM2X App"
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
	#DEFINE APPNAME		"Alcanoid GNEX App"
	#DEFINE COMPTYPE	0
	#DEFINE AGENTTYPE	0
	#DEFINE VALIDCOUNT	255
	#DEFINE VALIDTERM	255
	#DEFINE DIRECTRUN	0
	#DEFINE APPVER		1
%}
#endif

#include <SScript.h>
#include "images.sbm"
#include "DefineAlcanoid.h"
#include "GameStatus.h"

#include "InitAlcanoid.h"
#include "DrawAlcanoid.h"
#include "ControlAlcanoid.h"
#include "ActAlcanoid.h"

void EVENT_START(){
	InitAlcanoid();
	SetTimer(20, 1);
}

void EVENT_TIMEOUT(){
	DrawAlcanoid();
}

void EVENT_KEYPRESS(){
	ControlAlcanoid(swData);
}