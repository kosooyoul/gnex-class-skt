//AlcanoidControl.h에 의존

void ActAlcanoid(){
	MoveBar();
	MoveBall();
}

//막대기 이동
void MoveBar(){
	switch(nextKey){
		case SWAP_KEY_LEFT:
			if(unitBar.x > WALL_MIN_X + BAR_WIDTH_HALF + unitBar.move){
				unitBar.x -= unitBar.move;
			}
			break;
		case SWAP_KEY_RIGHT:
			if(unitBar.x < WALL_MAX_X - BAR_WIDTH_HALF - unitBar.move){
				unitBar.x += unitBar.move;
			}
			break;
	}
}

//공 이동
void MoveBall(){
	StrikeWall();
	StrikeBlockMap();

	//이동
	unitBall.x += unitBall.moveX;
	unitBall.y += unitBall.moveY;
}

//블럭과의 충돌
void StrikeBlockMap(){
	int i, j;
	
	for(i = 0; i < BLOCKMAP_SIZE_X; i++){
		for(j = 0; j < BLOCKMAP_SIZE_Y; j++){
			if(blockMap[i][j] > -1){

				//블럭의 좌우경계 내부인지 검사(Y축으로 충돌)
				if(/*PosX*/(BLOCKMAP_POS_X + BLOCK_WIDTH * i) + BLOCK_WIDTH_HALF > unitBall.x){
					if(/*PosX*/(BLOCKMAP_POS_X + BLOCK_WIDTH * i) - BLOCK_WIDTH_HALF < unitBall.x){
						if(HitCheck(BLOCKMAP_POS_Y + BLOCK_HEIGHT * j, unitBall.y, BALL_WIDTH_HALF + BLOCK_HEIGHT_HALF + Abs(unitBall.moveY))){
							unitBall.moveY *= -1;
							DestroyBlock(i, j);		//블럭 삭제
						}
					}
				}
				
				//블럭의 상하경계 내부인지 검사(X축으로 충돌)
				if(/*PosY*/(BLOCKMAP_POS_Y + BLOCK_HEIGHT * j) + BLOCK_HEIGHT_HALF > unitBall.y){
					if(/*PosY*/(BLOCKMAP_POS_Y + BLOCK_HEIGHT * j) - BLOCK_HEIGHT_HALF < unitBall.y){
						if(HitCheck(BLOCKMAP_POS_X + BLOCK_WIDTH * i, unitBall.x, BALL_WIDTH_HALF + BLOCK_WIDTH_HALF + Abs(unitBall.moveX))){
							unitBall.moveX *= -1;
							DestroyBlock(i, j);		//블럭 삭제
						}
					}
				}


			}
		}
	}

}

//블럭을 깸
void DestroyBlock(int x, int y){
	blockMap[x][y] = -1;	//블럭 삭제
	playPoint += DEFAULT_POINT;
}

void StrikeWall(){
	//위쪽 벽 충돌?
	if(unitBall.y < WALL_MIN_Y + BALL_WIDTH_HALF + Abs(unitBall.moveY)){
		unitBall.moveY *= -1;
	//아래쪽 발판 충돌?
	}else if(unitBall.y > BAR_Y - BAR_HEIGHT_HALF - Abs(unitBall.moveY)){
		if(unitBall.y < BAR_Y){
			//발판 안에 있는가?
			if(Abs(unitBar.x - unitBall.x) < BAR_WIDTH_HALF){
				unitBall.moveY *= -1;
				//ChangeDirection(unitBar.x - unitBall.x);	//각도 변경
			}
		}else{
			ChangeMode(GAME_RECORD);
		}
	}
	//좌측 벽 충돌?
	if(unitBall.x < WALL_MIN_X + BALL_WIDTH_HALF + Abs(unitBall.moveX)){
		unitBall.moveX *= -1;
	//우측 벽 충돌?
	}else if(unitBall.x > WALL_MAX_X - BALL_WIDTH_HALF  - Abs(unitBall.moveX)){
		unitBall.moveX *= -1;
	}
}

//각도 변형 :: 미구현
void ChangeDirection(int position){
	int xPerY = unitBall.moveX * unitBall.moveY;
	int xPerYFromPosition = Abs(position) * 2 / BAR_WIDTH_HALF + 1;
	
	if(position < 0) xPerYFromPosition *= -1;
	
	xPerY *= xPerYFromPosition;

	unitBall.moveX *= xPerY;
	unitBall.moveY *= xPerY;

	//unitBall.moveX = BAR_WIDTH_HALF / position;
	//unitBall.moveY = 
}