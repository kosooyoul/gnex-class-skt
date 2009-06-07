/* Ahyane.net KoSooYoul ^^* 2009.06.07 */

#define WALL_MAX_COUNT	10

#define WALL_SIZE		5

//고정
#define DIRECTION_IN	0
#define DIRECTION_OUT	1

//벽
struct Wall{
	int x1, x2;
	int y1, y2;
	int direction;				//벽 방향(내부에서 접촉, 외부에서 접촉)

	int enabled;				//벽 활성화 여부
}PublicWall[WALL_MAX_COUNT];

//벽 초기화
void InitWall(int index, int x1, int x2, int y1, int y2, int direction){
	PublicWall[index].x1 = x1;
	PublicWall[index].x2 = x2;
	PublicWall[index].y1 = y1;
	PublicWall[index].y2 = y2;
	PublicWall[index].direction = direction;
}

//벽 활성화 하는지
void SetWallEnabled(int index, int enabled){
	PublicWall[index].enabled = enabled;
}

int GetWallEnabled(int index){
	return PublicWall[index].enabled;
}

//벽 모두 그리기
void DrawAllWall(){
	int i;
	for(i = 0; i < WALL_MAX_COUNT; i++){
		/*if(GetWallEnabled(i) == TRUE)*/ DrawWall(i);
	}
}

//벽 그리기
void DrawWall(int index){
	DrawRect(PublicWall[index].x1, PublicWall[index].y1, PublicWall[index].x2, PublicWall[index].y2);
}