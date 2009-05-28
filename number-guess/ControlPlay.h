//NumberGuess.Control - Ko Soo Youl - 09.05.26

void ChangePlayMode(int mode){
	prevPlayMode = currentPlayMode;
	currentPlayMode = mode;

	switch(prevPlayMode){
		case PLAY_READY:
			//문제 만들기
			questNumber = Rand(0, Power(10, numberSize));
			break;
		case PLAY_INPUT:
			break;
		case PLAY_COMPARED:
			break;
		case PLAY_OVER:
			gameRank = AddRank(gamePoint);
			break;
		case PLAY_RECORD:
			break;
		case PLAY_GIVEUP:
			break;
		case PLAY_NEXTQUEST:
			playCount += 1;					//맟춘 문제 갯수 증가
			PointUp();						//점수 증가
			chance += GetAidChance() + 7;	//기회 증가
			answeredNumber = 0;
			break;
	}
	InitPlayMode();

}

void InitPlayMode(){

	switch(currentPlayMode){
		case PLAY_READY:
			InitHistory();
			InitTimer();
			break;
		case PLAY_INPUT:
			//기본선택값:입력
			selectedValue = PLAY_INPUT_INPUT;
			PlayTimer();
			break;
		case PLAY_COMPARED:
			PauseTimer();
			//기회감소
			chance -= 1;
			//대답 횟수 증가
			gameTurn += 1;			
			break;
		case PLAY_OVER:
			break;
		case PLAY_RECORD:
			break;
		case PLAY_GIVEUP:
			//기본선택값:네
			selectedValue = PLAY_QUEST_YES;
			PauseTimer();
			break;
		case PLAY_NEXTQUEST:
			selectedValue = PLAY_QUEST_YES;	//기본선택값:네
			break;
	}

}

void ControlPlayReady(int key){
	switch(key){
		case SWAP_KEY_OK:
		case SWAP_KEY_CLR:
			//답 입력하러
			ChangePlayMode(PLAY_INPUT);
	}
}

void ControlPlayInput(int key){

	switch(key){
		//선택 변경
		case SWAP_KEY_LEFT:
		case SWAP_KEY_UP:
		case SWAP_KEY_RIGHT:
		case SWAP_KEY_DOWN:
			if(selectedValue == PLAY_INPUT_INPUT){
				selectedValue = PLAY_INPUT_SUBMIT;
			}else{
				selectedValue = PLAY_INPUT_INPUT;
			}
			break;
		case SWAP_KEY_OK:
			switch(selectedValue){
				//수 입력
				case PLAY_INPUT_INPUT:
					StrInput("수를 입력하세요", inputedString);
					break;
				//입력 완료
				case PLAY_INPUT_SUBMIT:
					if(errorType == ERROR_NO){
						//답인지 확인하러
						ChangePlayMode(PLAY_COMPARED);
					}else{
						StrInput("수를 다시 입력하세요", inputedString);
					}
			}
			break;
		case SWAP_KEY_CLR:
			ChangePlayMode(PLAY_GIVEUP);
	}
}

void ControlPlayCompared(int key){
	switch(key){
		case SWAP_KEY_OK:
			if(answeredNumber == questNumber){
				//맟췄으니 다음 문제로, 계속하는지 질문
				ChangePlayMode(PLAY_NEXTQUEST);
			}else{
				//기회가 있으면
				if(chance > 0){
					//입력받은 답을 기록하고 다시 수를 입력 하러
					AddHistory(answeredNumber);
					ChangePlayMode(PLAY_INPUT);
				}else{
					//게임오버
					ChangePlayMode(PLAY_OVER);
				}
			}
	}
}

void ControlPlayOver(int key){
	switch(key){
		case SWAP_KEY_OK:
			ChangePlayMode(PLAY_RECORD);
	}
}

void ControlPlayRecord(int key){
	switch(key){
		case SWAP_KEY_OK:
			ChangeMode(GAME_MAIN);
	}
}

void ControlPlayGiveup(int key){
	switch(key){
		//선택 변경
		case SWAP_KEY_LEFT:
		case SWAP_KEY_UP:
		case SWAP_KEY_RIGHT:
		case SWAP_KEY_DOWN:
			if(selectedValue == PLAY_QUEST_YES){
				selectedValue = PLAY_QUEST_NO;
			}else{
				selectedValue = PLAY_QUEST_YES;
			}
			break;
		case SWAP_KEY_OK:
			switch(selectedValue){
				//포기 안함
				case PLAY_QUEST_YES:
					ChangePlayMode(PLAY_INPUT);
					break;
				//포기함
				case PLAY_QUEST_NO:
					ChangePlayMode(PLAY_OVER);
			}
	}
}

void ControlPlayNextquest(int key){
	switch(key){
		//선택 변경
		case SWAP_KEY_LEFT:
		case SWAP_KEY_UP:
		case SWAP_KEY_RIGHT:
		case SWAP_KEY_DOWN:
			if(selectedValue == PLAY_QUEST_YES){
				selectedValue = PLAY_QUEST_NO;
			}else{
				selectedValue = PLAY_QUEST_YES;
			}
			break;
		case SWAP_KEY_OK:
			switch(selectedValue){
				//그만 안둠
				case PLAY_QUEST_YES:
					ChangePlayMode(PLAY_READY);
					break;
				//그만둠
				case PLAY_QUEST_NO:
					ChangePlayMode(PLAY_OVER);
			}
	}
}
