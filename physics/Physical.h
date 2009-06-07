#define TRUE	1
#define FALSE	0

#define MATERIAL_MAX_COUNT	6
//#define GRAVITY				3
int		GRAVITY				= 10;
#define MOVECOUNT_PER_TIME	10

#define WALL_MAX_COUNT	10
#define DIRECTION_IN	0
#define DIRECTION_OUT	1

#define DIRECTION_NORTH	0
#define DIRECTION_WEST	1
#define DIRECTION_EAST	2
#define DIRECTION_SOUTH	3
#define WALL_SIZE		5

#define STRIKE_NONE			0
#define STRIKE_HORIZONTAL	1
#define STRIKE_VERTICAL		2

//이동 물체
struct Material{
	int x, y;			//화면상의 좌표
	int powerX;			//수평 힘(-인 경우 좌, +인 경우 우)
	int powerY;			//수직 힘(-인 경우 하, +인 경우 상)

	int weight;			//물체 무게(적용X)
	int elastic;		//탄성력
	int friction;		//마찰력
	
	int type;			//물체 모양(현재 색상으로 대체)

	int enabled;		//표시여부
}PublicMaterial[MATERIAL_MAX_COUNT];

//물체 초기화
void initMaterial(int index, int x, int y, int powerX, int powerY, int weight, int elastic, int friction, int type){
	PublicMaterial[index].x = x;
	PublicMaterial[index].y = y;
	PublicMaterial[index].powerX = powerX;
	PublicMaterial[index].powerY = powerY;
	PublicMaterial[index].weight = weight;
	PublicMaterial[index].elastic = elastic;
	PublicMaterial[index].friction = friction;
	PublicMaterial[index].type = type;
}

//물체 활성화
void setEnabledMaterial(int index, int Enabled){
	PublicMaterial[index].enabled = Enabled;
}

//벽
struct Wall{
	int x1, x2;
	int y1, y2;
	int direction;	//벽 방향(내부에서 접촉, 외부에서 접촉)
}PublicWall[WALL_MAX_COUNT];

//벽 초기화
void initWall(int index, int x1, int x2, int y1, int y2, int direction){
	PublicWall[index].x1 = x1;
	PublicWall[index].x2 = x2;
	PublicWall[index].y1 = y1;
	PublicWall[index].y2 = y2;
	PublicWall[index].direction = direction;
}



void moveMaterial(int index){
	int tempX = PublicMaterial[index].x;
	int tempY = PublicMaterial[index].y;	
	
	//충돌 체크
	int strikeResult = strikeWall(index);
	
	if(strikeResult != STRIKE_HORIZONTAL){
		PublicMaterial[index].x += PublicMaterial[index].powerX / MOVECOUNT_PER_TIME;
	}
	if(strikeResult != STRIKE_VERTICAL){
		PublicMaterial[index].y -= PublicMaterial[index].powerY / MOVECOUNT_PER_TIME;
	}
	

	//선긋기
	if(PublicMaterial[index].enabled == TRUE){
		SetColor(PublicMaterial[index].type);
		DrawLine(tempX, tempY, PublicMaterial[index].x, PublicMaterial[index].y);
	}

	//가중력 적용
	PublicMaterial[index].powerY -= GRAVITY;
	
}

int strikeWall(int index){
	int i;
	int resultStrike = STRIKE_NONE;
	for(i = 0; i < WALL_MAX_COUNT; i++){
		if(PublicWall[i].direction == DIRECTION_IN){
			if(strikeWallHorizontalIn(index, i) == TRUE) resultStrike = STRIKE_HORIZONTAL;
			if(strikeWallVerticalIn(index, i) == TRUE) resultStrike = STRIKE_VERTICAL;
		}else{
			if(strikeWallHorizontalOut(index, i) == TRUE) resultStrike = STRIKE_HORIZONTAL;
			if(strikeWallVerticalOut(index, i) == TRUE) resultStrike = STRIKE_VERTICAL;
		}
	}
	return resultStrike;
}

void applyElasticX(int index){
	PublicMaterial[index].powerX *= -1;
	
	if(PublicMaterial[index].powerX > 0)PublicMaterial[index].powerX+=2;
	else if(PublicMaterial[index].powerX < 0)PublicMaterial[index].powerX-=2;
	//PublicMaterial[index].powerX *= PublicMaterial[index].elastic;
	//PublicMaterial[index].powerX /= 100;
}

void applyElasticY(int index, int gravityDirection){
	PublicMaterial[index].powerY *= -1;

	if(gravityDirection == TRUE){
		PublicMaterial[index].powerY *= PublicMaterial[index].elastic;
		PublicMaterial[index].powerY /= 100;	
		if(PublicMaterial[index].powerX > 0)PublicMaterial[index].powerX -= PublicMaterial[index].friction / 10;
		else if(PublicMaterial[index].powerX < 0)PublicMaterial[index].powerX += PublicMaterial[index].friction / 10;
	}
}

int strikeWallHorizontalOut(int index, int i){
	//DIRECT-WEST
	if(PublicMaterial[index].y >= PublicWall[i].y1 && PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x <= PublicWall[i].x2 - PublicMaterial[index].powerX / 10 && PublicMaterial[index].x > PublicWall[i].x2 - WALL_SIZE){

			PublicMaterial[index].x = PublicWall[i].x2;
			applyElasticX(index);
			return TRUE;
		}		
	}
	//DIRECT-EAST
	if(PublicMaterial[index].y >= PublicWall[i].y1 && PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x >= PublicWall[i].x1 - PublicMaterial[index].powerX / 10 && PublicMaterial[index].x < PublicWall[i].x1 + WALL_SIZE){

			PublicMaterial[index].x = PublicWall[i].x1;
			applyElasticX(index);
			return TRUE;
		}
	}
	return FALSE;
}	

int strikeWallVerticalOut(int index, int i){
	//DIRECT-NORTH
	if(PublicMaterial[index].x >= PublicWall[i].x1 && PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y <= PublicWall[i].y2 + PublicMaterial[index].powerY / 10 && PublicMaterial[index].y > PublicWall[i].y2 - WALL_SIZE){
			
			PublicMaterial[index].y = PublicWall[i].y2;
			applyElasticY(index, FALSE);
			return TRUE;
		}		
	}
	//DIRECT-SOUTH
	if(PublicMaterial[index].x >= PublicWall[i].x1 && PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y >= PublicWall[i].y1 + PublicMaterial[index].powerY / 10 && PublicMaterial[index].y < PublicWall[i].y1 + WALL_SIZE){
			
			PublicMaterial[index].y = PublicWall[i].y1;
			applyElasticY(index, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

int strikeWallHorizontalIn(int index, int i){
	//DIRECT-WEST
	if(PublicMaterial[index].y >= PublicWall[i].y1 && PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x <= PublicWall[i].x1 - PublicMaterial[index].powerX / 10 && PublicMaterial[index].x > PublicWall[i].x1 - WALL_SIZE){

			PublicMaterial[index].x = PublicWall[i].x1;
			applyElasticX(index);
			return TRUE;
		}		
	}
	//DIRECT-EAST
	if(PublicMaterial[index].y >= PublicWall[i].y1 && PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x >= PublicWall[i].x2 - PublicMaterial[index].powerX / 10 && PublicMaterial[index].x < PublicWall[i].x2 + WALL_SIZE){

			PublicMaterial[index].x = PublicWall[i].x2;
			applyElasticX(index);
			return TRUE;
		}
	}
	return FALSE;
}	

int strikeWallVerticalIn(int index, int i){
	//DIRECT-NORTH
	if(PublicMaterial[index].x >= PublicWall[i].x1 && PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y <= PublicWall[i].y1 + PublicMaterial[index].powerY / 10 && PublicMaterial[index].y > PublicWall[i].y1 - WALL_SIZE){
			
			PublicMaterial[index].y = PublicWall[i].y1;
			applyElasticY(index, FALSE);
			return TRUE;
		}		
	}
	//DIRECT-SOUTH
	if(PublicMaterial[index].x >= PublicWall[i].x1 && PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y >= PublicWall[i].y2 + PublicMaterial[index].powerY / 10 && PublicMaterial[index].y < PublicWall[i].y2 + WALL_SIZE){
			
			PublicMaterial[index].y = PublicWall[i].y2;
			applyElasticY(index, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}



void drawAllWall(){
	int i;
	for(i = 0; i < WALL_MAX_COUNT; i++){
		drawWall(i);
	}
}

void drawWall(int index){
	SetColor(S_BLACK);
	DrawRect(PublicWall[index].x1, PublicWall[index].y1, PublicWall[index].x2, PublicWall[index].y2);
}

void drawMaterial(int index){
	if(PublicMaterial[index].enabled == FALSE) return;
	SetColor(PublicMaterial[index].type);
	FillEllipse(PublicMaterial[index].x, PublicMaterial[index].y, 2, 2);
	//DrawRect(PublicMaterial[index].x - 2, PublicMaterial[index].y - 2, PublicMaterial[index].x, PublicMaterial[index].y);
}