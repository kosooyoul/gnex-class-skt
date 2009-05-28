//NumberGuess.ModeManager - Ko Soo Youl - 09.05.26

void ChangeMode(int mode){
	int prevMode = currentMode;
	currentMode = mode;

	//데이터 정리
	switch(prevMode){
		case GAME_INDEX:
			break;
		case GAME_MAIN:
			break;
		case GAME_PLAY:
			break;
		case GAME_RANK:
			break;
		case GAME_OPTION:
			swRsRcvBuf[1] = numberSize;
			NVROM[1] = numberSize;
			break;	
	}
	InitMode();
}

void InitMode(){
	//데이터 초기화
	switch(currentMode){
		case GAME_INDEX:
			break;
		case GAME_MAIN:
			break;
		case GAME_PLAY:
			currentPlayMode = PLAY_READY;			//답 기록 초기화	
			InitTimer();							//타이머 초기화
			InitHistory();							//답 목록 초기화
			gamePoint = 0;							//점수 초기화
			gameTurn = 0;							//대답횟수 초기화
			answeredNumber = 0;						//입력한 값 초기화
			playCount = 0;							//해결한 문제 갯수 초기화
			chance = START_CHANCE + GetAidChance();	//기회 초기화
			break;
		case GAME_RANK:
			break;
		case GAME_OPTION:
			selectedValue = numberSize;
	}	
}
