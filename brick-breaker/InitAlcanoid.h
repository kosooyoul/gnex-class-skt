
void InitAlcanoid(){
	InitBall();
	InitBar();
	InitBlockMap();
}

void InitBall(){
	unitBall.x = START_BALL_X;
	unitBall.y = START_BALL_Y;
	unitBall.moveX = 3;
	unitBall.moveY = -3;
}

void InitBar(){
	unitBar.x = START_BAR_X;
	unitBar.move = 5;
}

void InitBlockMap(){
	int i, j;
	
	for(i = 0; i < BLOCKMAP_SIZE_X; i++){
		for(j = 0; j < BLOCKMAP_SIZE_Y; j++){
			blockMap[i][j] = Rand(-1, 2);
		}
	}
	
}