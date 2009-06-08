
void DrawAlcanoid(){
	ClearWhite();

	switch(gameMode){
		case GAME_INDEX:
			DrawIndex();
			break;
		case GAME_MENU:
			DrawMenu();
			break;
		case GAME_PLAY:
			ActAlcanoid();		//볼은 행동함
			DrawPoint();		//점수
			DrawBlockMap();		//맵 그림
			DrawBall();			//공 그림
			DrawBar();			//막대기 그림
			break;
		case GAME_RECORD:
			DrawRecord();
			break;
		case GAME_OPTION:
			DrawOption();
			break;
	}
	
	Flush();
}

void DrawPoint(){
	string strPoint;
	MakeStr1(strPoint, "POINT = %d", playPoint);
	DrawStr(10, 10, strPoint);
}

void DrawBlockMap(){
	int i, j;

	for(i = 0; i < BLOCKMAP_SIZE_X; i++){
		for(j = 0; j < BLOCKMAP_SIZE_Y; j++){
			if(blockMap[i][j] > -1){
				CopyImage(BLOCKMAP_POS_X + BLOCK_WIDTH * i, BLOCKMAP_POS_Y + BLOCK_HEIGHT * j, imgBlock[blockMap[i][j]]);
				//CopyImage(BLOCKMAP_POS_X + BLOCK_WIDTH * i, BLOCKMAP_POS_Y + BLOCK_HEIGHT * j, imgBlock[1]);
			}
		}
	}

}

void DrawBall(){
	CopyImage(unitBall.x, unitBall.y, imgBall);
}

void DrawBar(){
	CopyImage(unitBar.x , BAR_Y, imgBar);
}

void DrawIndex(){
	DrawStr(10, 10, "벽돌깨기 - 고수열");
	DrawStr(10, 50, "ahyane@ahyane.net");
	DrawStr(10, 80, "010-2839-4096");
}

void DrawMenu(){
	DrawStr(10, 150, "시작 하기");
	DrawStr(10, 170, "성적 보기");
	DrawStr(10, 190, "환경 설정");

	//선택 메뉴
	DrawRect(5, 145 + selectedMenu * 20, 50, 160 + selectedMenu * 20);
}

void DrawRecord(){
	DrawStr(10, 10, "게임 오버 -> 성적보여주기 코드 삽입");
}

void DrawOption(){
	DrawStr(10, 10, "옵션");
}
