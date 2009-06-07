/* Ahyane.net KoSooYoul ^^* 2009.06.07 */

#define MATERIAL_MAX_COUNT	6

#define MOVECOUNT_PER_TIME	10
int GRAVITY = 10;	//#define GRAVITY 3

//고정
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
	int type;			//물체 형태(현재 색상으로 대체)

	int enabled;		//활성화 여부
}PublicMaterial[MATERIAL_MAX_COUNT];

//물체 초기화
void InitMaterial(int index, int x, int y, int powerX, int powerY, int weight, int elastic, int friction, int type){
	PublicMaterial[index].x = x;
	PublicMaterial[index].y = y;
	PublicMaterial[index].powerX = powerX;
	PublicMaterial[index].powerY = powerY;
	PublicMaterial[index].weight = weight;
	PublicMaterial[index].elastic = elastic;
	PublicMaterial[index].friction = friction;
	PublicMaterial[index].type = type;
}

//물체 활성화여부
void SetMaterialEnabled(int index, int Enabled){
	PublicMaterial[index].enabled = Enabled;
}

int GetMaterialEnabled(int index){
	return PublicMaterial[index].enabled;
}

//물체 모두 그리기
void DrawAllMaterial(){
	int i;
	for(i = 0; i < WALL_MAX_COUNT; i++){
		if(GetMaterialEnabled(i) == TRUE) DrawMaterial(i);
	}
}

//물체 그리기
void DrawMaterial(int index){
	SetColor(PublicMaterial[index].type);
	FillEllipse(PublicMaterial[index].x, PublicMaterial[index].y, 2, 2);
}

//물체 이동
void MoveMaterial(int index){
	//선긋기 위해 첫번째 위치 임시 저장
	//int tempX = PublicMaterial[index].x;
	//int tempY = PublicMaterial[index].y;
	
	//충돌 검사
	int strikeResult = StrikeWall(index);
	
	if(strikeResult != STRIKE_HORIZONTAL){
		PublicMaterial[index].x += PublicMaterial[index].powerX / MOVECOUNT_PER_TIME;
	}
	if(strikeResult != STRIKE_VERTICAL){
		PublicMaterial[index].y -= PublicMaterial[index].powerY / MOVECOUNT_PER_TIME;
	}
	//중력 적용
	PublicMaterial[index].powerY -= GRAVITY;

	//선긋기
	//if(PublicMaterial[index].enabled == TRUE){
	//	SetColor(PublicMaterial[index].type);
	//	DrawLine(tempX, tempY, PublicMaterial[index].x, PublicMaterial[index].y);
	//}	
}

//충돌 검사
int StrikeWall(int index){
	int i;
	int resultStrike = STRIKE_NONE;
	for(i = 0; i < WALL_MAX_COUNT; i++){
		if(PublicWall[i].direction == DIRECTION_IN){
			if(StrikeWallHorizontalIn(index, i) == TRUE) resultStrike = STRIKE_HORIZONTAL;
			if(StrikeWallVerticalIn(index, i) == TRUE) resultStrike = STRIKE_VERTICAL;
		}else{
			if(StrikeWallHorizontalOut(index, i) == TRUE) resultStrike = STRIKE_HORIZONTAL;
			if(StrikeWallVerticalOut(index, i) == TRUE) resultStrike = STRIKE_VERTICAL;
		}
	}
	return resultStrike;
}

//외부 충돌 수평
int StrikeWallHorizontalOut(int index, int i){
	//DIRECT-WEST
	if(PublicMaterial[index].y >= PublicWall[i].y1
	&& PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x < PublicWall[i].x2 - PublicMaterial[index].powerX / 10
		&& PublicMaterial[index].x > PublicWall[i].x2 - WALL_SIZE){
			PublicMaterial[index].x = PublicWall[i].x2;
			ApplyElasticX(index);
			return TRUE;
		}
	}
	//DIRECT-EAST
	if(PublicMaterial[index].y >= PublicWall[i].y1
	&& PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x > PublicWall[i].x1 - PublicMaterial[index].powerX / 10
		&& PublicMaterial[index].x < PublicWall[i].x1 + WALL_SIZE){
			PublicMaterial[index].x = PublicWall[i].x1;
			ApplyElasticX(index);
			return TRUE;
		}
	}
	return FALSE;
}	

//외부 충돌 수직
int StrikeWallVerticalOut(int index, int i){
	//DIRECT-NORTH
	if(PublicMaterial[index].x >= PublicWall[i].x1
	&& PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y < PublicWall[i].y2 + PublicMaterial[index].powerY / 10
		&& PublicMaterial[index].y > PublicWall[i].y2 - WALL_SIZE){
			PublicMaterial[index].y = PublicWall[i].y2;
			ApplyElasticY(index, FALSE);
			return TRUE;
		}		
	}
	//DIRECT-SOUTH
	if(PublicMaterial[index].x >= PublicWall[i].x1
	&& PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y > PublicWall[i].y1 + PublicMaterial[index].powerY / 10
		&& PublicMaterial[index].y < PublicWall[i].y1 + WALL_SIZE){
			PublicMaterial[index].y = PublicWall[i].y1;
			ApplyElasticY(index, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

//내부 충돌 수평
int StrikeWallHorizontalIn(int index, int i){
	//DIRECT-WEST
	if(PublicMaterial[index].y >= PublicWall[i].y1
	&& PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x <= PublicWall[i].x1 - PublicMaterial[index].powerX / 10
		&& PublicMaterial[index].x > PublicWall[i].x1 - WALL_SIZE){
			PublicMaterial[index].x = PublicWall[i].x1;
			ApplyElasticX(index);
			return TRUE;
		}		
	}
	//DIRECT-EAST
	if(PublicMaterial[index].y >= PublicWall[i].y1
	&& PublicMaterial[index].y <= PublicWall[i].y2){
		if(PublicMaterial[index].x > PublicWall[i].x2 - PublicMaterial[index].powerX / 10
		&& PublicMaterial[index].x < PublicWall[i].x2 + WALL_SIZE){
			PublicMaterial[index].x = PublicWall[i].x2;
			ApplyElasticX(index);
			return TRUE;
		}
	}
	return FALSE;
}

//내부 충돌 수직
int StrikeWallVerticalIn(int index, int i){
	//DIRECT-NORTH
	if(PublicMaterial[index].x >= PublicWall[i].x1
	&& PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y <= PublicWall[i].y1 + PublicMaterial[index].powerY / 10
		&& PublicMaterial[index].y > PublicWall[i].y1 - WALL_SIZE){
			PublicMaterial[index].y = PublicWall[i].y1;
			ApplyElasticY(index, FALSE);
			return TRUE;
		}		
	}
	//DIRECT-SOUTH
	if(PublicMaterial[index].x >= PublicWall[i].x1
	&& PublicMaterial[index].x <= PublicWall[i].x2){
		if(PublicMaterial[index].y >= PublicWall[i].y2 + PublicMaterial[index].powerY / 10
		&& PublicMaterial[index].y < PublicWall[i].y2 + WALL_SIZE){
			PublicMaterial[index].y = PublicWall[i].y2;
			ApplyElasticY(index, TRUE);
			return TRUE;
		}
	}
	return FALSE;
}

//좌우 벽 반사
void ApplyElasticX(int index){
	PublicMaterial[index].powerX *= -1;
	if(PublicMaterial[index].powerX > 0){
		PublicMaterial[index].powerX += 2;
	}else if(PublicMaterial[index].powerX < 0){
		PublicMaterial[index].powerX -= 2;
	}
	//
	//탄성력 적용
	//PublicMaterial[index].powerX *= PublicMaterial[index].elastic;
	//PublicMaterial[index].powerX /= 100;
}

//상하 벽 반사
void ApplyElasticY(int index, int gravityDirection){
	PublicMaterial[index].powerY *= -1;
	if(gravityDirection == TRUE){
		PublicMaterial[index].powerY *= PublicMaterial[index].elastic;
		PublicMaterial[index].powerY /= 100;	
		if(PublicMaterial[index].powerX > 0){
			PublicMaterial[index].powerX -= PublicMaterial[index].friction / 10;
		}else if(PublicMaterial[index].powerX < 0){
			PublicMaterial[index].powerX += PublicMaterial[index].friction / 10;
		}
	}
}