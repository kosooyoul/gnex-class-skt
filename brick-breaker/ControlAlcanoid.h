
int nextKey = SWAP_KEY_RELEASE;

void ControlAlcanoid(int swData){
	switch(gameMode){
		case GAME_INDEX:
			switch(swData){
				case SWAP_KEY_OK:
					ChangeMode(GAME_MENU);
			}
			break;
		case GAME_MENU:
			switch(swData){
				case SWAP_KEY_UP:
				case SWAP_KEY_LEFT:
					if(selectedMenu > 0)selectedMenu--;
					else selectedMenu = MENU_COUNT;
					break;
				case SWAP_KEY_DOWN:
				case SWAP_KEY_RIGHT:
					if(selectedMenu < MENU_COUNT)selectedMenu++;
					else selectedMenu = 0;
					break;
				case SWAP_KEY_OK:
					switch(selectedMenu){
						case MENU_PLAY:
							ChangeMode(GAME_PLAY);
							break;
						case MENU_RECORD:
							ChangeMode(GAME_RECORD);
							break;
						case MENU_OPTION:
							ChangeMode(GAME_OPTION);
					}
			}
			break;
		case GAME_PLAY:
			switch(swData){
				case SWAP_KEY_LEFT:
				case SWAP_KEY_RIGHT:
				case SWAP_KEY_RELEASE:
					nextKey = swData;
					break;
				case SWAP_KEY_CLR:
					ChangeMode(GAME_MENU);
			}
			break;
		case GAME_RECORD:
			switch(swData){
				case SWAP_KEY_OK:
				case SWAP_KEY_CLR:
					ChangeMode(GAME_MENU);
			}
			break;
		case GAME_OPTION:
			switch(swData){
				case SWAP_KEY_OK:
					//옵션 저장 코드 삽입
				case SWAP_KEY_CLR:
					ChangeMode(GAME_MENU);
			}
	}
}