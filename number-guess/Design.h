//NumberGuess.Defines - Ko Soo Youl - 09.05.26

void DrawBlueBox(int x1, int y1, int x2, int y2){
	SetColor(S_BLUE);
	FillRect(x1, y1, x2, y2);
	SetColor(S_WHITE);
	FillRect(x1+5, y1+5, x2-5, y2-5);
}

void DrawPinkBox(int x1, int y1, int x2, int y2){
	SetColor(S_PINK);
	FillRect(x1, y1, x2, y2);
	SetColor(S_WHITE);
	FillRect(x1+5, y1+5, x2-5, y2-5);
}

void DrawNoticeBox(){
	SetColor(S_ORANGE);
	FillRect(10, 120, 230, 180);
	SetColor(S_WHITE);
	FillRect(15, 125, 225, 175);
}

void DrawBack1(){
	SetColor(S_BLUE);
	FillRect(0, 0, 240, 120);
	FillRect(0, 160, 240, 320);
	SetColor(S_WHITE);
	DrawHLine(0, 240, 117);
	DrawHLine(0, 240, 163);
}

void DrawBack2(){
	SetColor(S_BLUE);
	FillRect(0, 0, 240, 120);
	FillRect(0, 160, 240, 320);
}

void DrawBack3(){
	SetColor(S_BLUE);
	FillRect(0, 0, 240, 50);
	FillRect(0, 250, 240, 320);
}

void DrawQuestion(){
	DrawNoticeBox();
	SetFontAlign(S_ALIGN_CENTER);
	DrawStr(120, 135, "게임 포기 안하실거죠?");
	DrawStr(100, 155, "네");
	DrawStr(160, 155, "아니오");

	if(selectedValue == PLAY_QUEST_YES){
		DrawStr(100, 157, "__");	
	}else{
		DrawStr(160, 157, "______");
	}
}

void DrawHistory(int rowIndex, int historyNum){
	DrawInt(165, 115 + 15 * rowIndex, historyNum);
	if(historyNum > questNumber){
		DrawStr(155, 115 + 15 * rowIndex, "<");
	}else{
		DrawStr(155, 115 + 15 * rowIndex, ">");
	}
}