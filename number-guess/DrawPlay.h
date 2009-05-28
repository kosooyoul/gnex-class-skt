//NumberGuess.Draw.DrawPlay - Ko Soo Youl - 09.05.26

void DrawPlayBase(){
	string tempString;
	int rowIndex = 0;
	int i;

	//배경 및 상자들
	DrawBack3();
	DrawBlueBox(30, 60, 120, 90);
	DrawBlueBox(130, 60, 210, 90);
	DrawPinkBox(30, 100, 130, 135);
	DrawPinkBox(30, 130, 130, 160);
	DrawBlueBox(30, 170, 130, 200);
	DrawBlueBox(10, 210, 230, 240);
	DrawBlueBox(140, 100, 210, 200);

	//입력 / 확정 선택표시
	SetColor(S_YELLOW);
	if(selectedValue == PLAY_QUEST_YES){
		FillRect(35, 135, 80, 155);
	}else{
		FillRect(80, 135, 125, 155);
	}

	//좌측정렬 출력 모음
	SetFontAlign(S_ALIGN_LEFT);
	DrawStr(40, 70, "점수");
	DrawStr(140, 70, "기회");
	MakeStr1(tempString, "범위 0~%d", Power(10, numberSize) - 1);
	DrawStr(40, 180, tempString);
	
	//대답 기록 출력
	for(i = lastHistoryIndex; i > -1; i--){
		if(historyNumber[i] < 0) continue;
		DrawHistory(rowIndex, historyNumber[i]);
		rowIndex += 1;
	}for(i = MAX_COUNT_HISTORY - 1; i > lastHistoryIndex; i--){
		if(historyNumber[i] < 0) continue;
		DrawHistory(rowIndex, historyNumber[i]);
		rowIndex += 1;
	}

	//우측정렬 출력 모음
	SetFontAlign(S_ALIGN_RIGHT);
	DrawInt(110, 70, gamePoint);
	DrawInt(200, 70, chance);

	//중앙정렬 출력 모음
	SetFontAlign(S_ALIGN_CENTER);
	DrawInt(80, 110 + Rand(0,2), answeredNumber);
	DrawStr(60, 140, "입력");
	DrawStr(105, 140, "확정");
	switch(errorType){
		case ERROR_NO:
			DrawStr(120, 220, "수치를 입력하세요");break;
		case ERROR_NUMBER_FORMAT:
			DrawStr(120, 220, "자연수로 다시 입력하세요");break;
		case ERROR_OUT_OF_RANGE:
			DrawStr(120, 220, "범위 내의 수로 입력하세요");
	}
}

void DrawPlayReady(){
	string tempString;

	DrawPlayBase();
	DrawNoticeBox();

	SetFontAlign(S_ALIGN_CENTER);
	MakeStr1(tempString, "%d번째 문제입니다", playCount + 1);
	DrawStr(120, 135, "준비하세요");
	DrawStr(120, 155, tempString);	
	
}

void DrawPlayInput(){
	DrawPlayBase();
}

void DrawPlayCompared(){
	DrawPlayBase();
	DrawNoticeBox();

	SetFontAlign(S_ALIGN_CENTER);
	//입력값이 작은 경우
	if(answeredNumber < questNumber){
		DrawStr(120, 145, "그 수보다 큽니다.");
	//입력값이 큰경우
	}else if(answeredNumber > questNumber){
		DrawStr(120, 145, "그 수보다 작습니다.");
	//정답을 입력한 경우
	}else{
		DrawStr(120, 145, "맞았습니다!!");
	}
}

void DrawPlayOver(){
	DrawBack2();	
	SetFontAlign(S_ALIGN_CENTER);
	DrawStr(120, 135, "게임이 끝났습니다");
}

void DrawPlayRecord(){
	DrawRank();
	DrawBlueBox(10, 210, 230, 240);
	
	SetFontAlign(S_ALIGN_CENTER);
	if(gameRank < MAX_COUNT_RANK){
		SetColor(S_REDBLACK);
		DrawRect(20, 95 + gameRank * 20, 220, 115 + gameRank * 20);
		DrawStr(120, 220, "축하합니다. 순위에 올랐습니다.");
	}else{
		DrawStr(120, 220, "안타깝습니다. 순위권 밖입니다.");
	}

}

void DrawPlayGiveup(){
	DrawPlayBase();
	DrawQuestion();
}

void DrawPlayNextquest(){
	DrawPlayBase();
	DrawQuestion();
}