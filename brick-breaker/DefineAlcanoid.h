#define START_BAR_X		120
#define BAR_Y			280
#define START_BALL_X	120
#define START_BALL_Y	200

#define WALL_MIN_X		0
#define WALL_MAX_X		240
#define WALL_MIN_Y		0

#define BAR_WIDTH_HALF	13
#define BAR_HEIGHT_HALF 2
#define BALL_WIDTH_HALF	2

#define BLOCKMAP_SIZE_X	10
#define BLOCKMAP_SIZE_Y	10
#define BLOCKMAP_POS_X	20
#define BLOCKMAP_POS_Y	30
#define BLOCK_HEIGHT	10
#define BLOCK_WIDTH		20
#define BLOCK_HEIGHT_HALF	5
#define BLOCK_WIDTH_HALF	10
#define BLOCK_TYPE_CNT	2

struct Ball{
	int x, y;
	int moveX;
	int moveY;
}unitBall;

struct Bar{
	int x;
	int move;
}unitBar;

int blockMap[BLOCKMAP_SIZE_Y][BLOCKMAP_SIZE_X];