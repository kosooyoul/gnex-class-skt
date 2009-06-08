#define GAME_INDEX	0
#define GAME_MENU	1
#define GAME_PLAY	2
#define GAME_RECORD	3
#define GAME_OPTION	4

#define MENU_COUNT	2	//TOTAL - 1

#define MENU_PLAY	0
#define MENU_RECORD	1
#define MENU_OPTION	2

#define DEFAULT_POINT	5;

int gameMode = GAME_PLAY;
int playStage = 0;
int playPoint = 0;

int selectedMenu = 0;

void ChangeMode(int mode){
	gameMode = mode;
}
