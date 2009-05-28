//NumberGuess.Draw - Ko Soo Youl - 09.05.26

void DrawGame(){
	switch(currentMode){
		case GAME_INDEX:
			DrawIndex();
			break;
		case GAME_MAIN:
			DrawMain();
			break;
		case GAME_PLAY:
			DrawPlay();
			break;
		case GAME_RANK:
			DrawRank();
			break;
		case GAME_OPTION:
			DrawOption();
			break;
		default:
			ChangeMode(GAME_INDEX);
	}
}

void DrawIndex(){
	DrawBack1();
	SetFontAlign(S_ALIGN_CENTER);
	DrawStr(120, 135, LABEL_TITLE);
}

void DrawMain(){
	DrawBack3();
	SetFontAlign(S_ALIGN_CENTER);
	DrawStr(120, 100, LABEL_TITLE);
	DrawStr(120, 150, LABEL_MENU[0]);
	DrawStr(120, 170, LABEL_MENU[1]);
	DrawStr(120, 190, LABEL_MENU[2]);
	//선택한 메뉴에 표시
	DrawRect(40, 145 + currentMenu * 20, 200, 165 + currentMenu * 20);
}

void DrawPlay(){
	switch(currentPlayMode){
		case PLAY_READY:
			DrawPlayReady();
			break;
		case PLAY_INPUT:
			DrawPlayInput();
			break;
		case PLAY_COMPARED:
			DrawPlayCompared();
			break;
		case PLAY_OVER:
			DrawPlayOver();
			break;
		case PLAY_RECORD:
			DrawPlayRecord();
			break;
		case PLAY_GIVEUP:
			DrawPlayGiveup();
		case PLAY_NEXTQUEST:
			DrawPlayNextquest();
	}
}

void DrawRank(){
	int i;
	int rankTime[3];
	string printFormat;

	DrawBack3();

	//순위 기록 출력
	SetFontAlign(S_ALIGN_LEFT);
	for(i = 0; i < MAX_COUNT_RANK; i++){	
		MakeStr1(printFormat, "%2d등", i + 1);
		DrawStr(40, 100 + 20 * i, printFormat);

		if(rank[i].point > 0){
			IntToDate(rankTime, rank[i].date);
			MakeStr4(printFormat, "%4d점   %4d.%2d.%2d", rank[i].point, rankTime[0], rankTime[1], rankTime[2]);
			DrawStr(80, 100 + 20 * i, printFormat);
		}else{
			DrawStr(100, 100 + 20 * i, "기록이 없습니다");
		}
	}
}

void DrawOption(){
	//selectedValue는 numberSize의 임시

	DrawBack3();

	SetFontAlign(S_ALIGN_CENTER);
	DrawStr(120, 120, "옵션");
	DrawStr(80, 150, "문제 자릿수");
	DrawInt(170, 150, selectedValue);
	DrawStr(150, 150, "◁");
	DrawStr(190, 150, "▷");

	if(delayTime > 0){
		switch(delayKey){
			case SWAP_KEY_LEFT:	DrawStr(150, 150, "◀");break;
			case SWAP_KEY_RIGHT:DrawStr(190, 150, "▶");
		}delayTime--;
	}
}