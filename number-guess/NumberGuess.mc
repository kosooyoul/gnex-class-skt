//NumberGuess.Main - Ko Soo Youl - 09.05.26

///////////////////////////////////////////////////////////////////////////
// NumberGuess.mc - Auto Created by GNEX IDE
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
	#DEFINE SCRIPTNAME	"NumberGuess GVM2X App"
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
	#DEFINE APPNAME		"NumberGuess GNEX App"
	#DEFINE COMPTYPE	0
	#DEFINE AGENTTYPE	0
	#DEFINE VALIDCOUNT	255
	#DEFINE VALIDTERM	255
	#DEFINE DIRECTRUN	0
	#DEFINE APPVER		1
%}
#endif

#include <SScript.h>
#include "Defines.h"
#include "Functions.h"
#include "Design.h"
#include "States.h"
#include "ModeManager.h"

#include "ControlPlay.h"
#include "DrawPlay.h"
#include "ControlNumberGuess.h"
#include "DrawNumberGuess.h"

string testString;

void TEST(){
	SetFontAlign(S_ALIGN_LEFT);
	DrawStr(14, 250, "QUEST_");
	DrawInt(50, 250, questNumber);
	DrawStr(14, 270, "TIMER_");
	DrawInt(50, 270, timeValue);
}

void EVENT_START(){
	LoadROM();		//세이브 데이터 읽음
	SetTimer(50,1);	//타이머 시작
}

void EVENT_TIMEOUT(){
	switch(swData){
		case TIMER_PLAY:
			timeValue += 1;
		case TIMER_DRAW:
			Clear(S_WHITE);
			DrawGame();
			Flush();
	}	
}

void EVENT_KEYPRESS(){
	
	Clear(S_WHITE);
	DrawGame();
	Flush();

	switch(currentMode){
		case GAME_INDEX:
			ControlIndex(swData);
			break;
		case GAME_MAIN:
			ControlMain(swData);
			break;
		case GAME_PLAY:
			ControlPlay(swData);
			break;
		case GAME_RANK:
			ControlRank(swData);
			break;
		case GAME_OPTION:
			ControlOption(swData);
	}
}

void EVENT_RESULT(){
	switch(currentMode){
		//게임 플레이 모드
		case GAME_PLAY:
			switch(currentPlayMode){
				//숫자 입력 모드
				case PLAY_INPUT:
					switch(swData){
						//입력을 마친 이벤트
						case S_RST_TEDIT_DONE:
							//입력 받은 값 검사
							if(!StrCmp(inputedString, "0")){
								answeredNumber = 0;
							}else{	
								answeredNumber = AsciiToInt(inputedString);
								if(answeredNumber == 0){
									error(ERROR_NUMBER_FORMAT);	//숫자가 아님
								}else if(answeredNumber >= Power(10, numberSize)){
									error(ERROR_OUT_OF_RANGE);	//원하는 범위에 없음(2자릿수 인경우, 0~99사이만 허용)
								}else{
									error(ERROR_NO);			//제대로 입력했음
								}
							}
					}//end switch(EVENT_RESULT:swData)
			}//end switch(currentPlayMode)
	}//end switch(currentMode)

}