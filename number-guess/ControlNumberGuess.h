//NumberGuess.Control - Ko Soo Youl - 09.05.26

void ControlIndex(int key){
	switch(key){
		case SWAP_KEY_OK:
			ChangeMode(GAME_MAIN);
	}
}

void ControlMain(int key){
	switch(key){
		//메뉴 위로 이동
		case SWAP_KEY_LEFT:
		case SWAP_KEY_UP:
			if(currentMenu > 0){
				currentMenu -= 1;
			}else{
				currentMenu = LAST_MENU;
			}
			break;
		//메뉴 아래로 이동
		case SWAP_KEY_RIGHT:
		case SWAP_KEY_DOWN:
			if(currentMenu < LAST_MENU){
				currentMenu += 1;
			}else{
				currentMenu = 0;
			}
			break;
		//메뉴 선택
		case SWAP_KEY_OK:
			switch(currentMenu){
				case MENU_PLAY:
					ChangeMode(GAME_PLAY);
					break;
				case MENU_RANK:
					ChangeMode(GAME_RANK);
					break;
				case MENU_OPTION:
					ChangeMode(GAME_OPTION);
			}
	}
}

void ControlPlay(int key){
	switch(currentPlayMode){
		case PLAY_READY:
			ControlPlayReady(key);
			break;
		case PLAY_INPUT:
			ControlPlayInput(key);
			break;
		case PLAY_COMPARED:
			ControlPlayCompared(key);
			break;
		case PLAY_OVER:
			ControlPlayOver(key);
			break;
		case PLAY_RECORD:
			ControlPlayRecord(key);
			break;
		case PLAY_GIVEUP:
			ControlPlayGiveup(key);
			break;
		case PLAY_NEXTQUEST:
			ControlPlayNextquest(key);
	}
}

void ControlRank(int key){
	switch(key){
		//메뉴로 돌아가기
		case SWAP_KEY_OK:
		case SWAP_KEY_CLR:
			ChangeMode(GAME_MAIN);
	}
}

void ControlOption(int key){
	//selectedValue는 numberSize의 임시

	switch(key){
		//자릿수 감소 선택
		case SWAP_KEY_LEFT:
		case SWAP_KEY_UP:
			if(selectedValue > MIN_NUMBER_SIZE){
				selectedValue -= 1;
			}else{
				selectedValue = MAX_NUMBER_SIZE;
			}
			//선택표시(화살표)
			delayTime = 3;
			delayKey = SWAP_KEY_LEFT;

			break;
		//자릿수 증가 선택
		case SWAP_KEY_RIGHT:
		case SWAP_KEY_DOWN:
			if(selectedValue < MAX_NUMBER_SIZE){
				selectedValue += 1;
			}else{
				selectedValue = MIN_NUMBER_SIZE;
			}
			//선택표시(화살표)
			delayTime = 3;
			delayKey = SWAP_KEY_RIGHT;

			break;
		//값 적용
		case SWAP_KEY_OK:
			numberSize = selectedValue;
			//옵션 저장
			SaveOption();
		//옵션 적용 취소
		case SWAP_KEY_CLR:
			ChangeMode(GAME_MAIN);
	}
}