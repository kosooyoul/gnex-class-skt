//NumberGuess.Defines - Ko Soo Youl - 09.05.26

//게임 제목 = Number Guess
const string LABEL_TITLE = "찍기능력시험";

//게임 메뉴
const string LABEL_MENU[] = {
	"게임시작",
	"기록보기",
	"게임설정"
};

//게임모드
#define	GAME_INDEX	1
#define	GAME_MAIN	2
#define	GAME_PLAY	30
#define	GAME_RANK	31
#define	GAME_OPTION	32
//타이머
#define TIMER_DRAW	0
#define TIMER_PLAY	1

//선택한 메뉴
#define MENU_PLAY	0
#define MENU_RANK	1
#define MENU_OPTION	2

//플레이모드내 모드
#define PLAY_READY		0
#define PLAY_INPUT		1
#define PLAY_COMPARED	2
#define PLAY_OVER		3
#define PLAY_RECORD		4
#define PLAY_GIVEUP		5
#define PLAY_NEXTQUEST	6

#define PLAY_INPUT_INPUT	0
#define PLAY_INPUT_SUBMIT	1

#define PLAY_QUEST_YES		0
#define PLAY_QUEST_NO		1

#define LAST_MENU	MENU_OPTION		//마지막 메뉴

//게임 플레이 관련
#define MIN_NUMBER_SIZE		1		//최소 정답의 자릿수
#define MAX_NUMBER_SIZE		4		//최대 정답의 자릿수
#define MAX_COUNT_HISTORY	5		//최대 숫자기억수

//랭크관련
#define MAX_COUNT_RANK		5		//최대 랭크 갯수

#define START_CHANCE		10		//게임시작시 기본 기회

//색상
#define S_RED		109		//빨간색
#define S_MARGENTA	112		//보라색
#define S_ROSE		114		//장미색
#define S_ORANGE	117		//주황색
#define S_PINK		119		//분혼색
#define S_APRICOT	122		//살구색
#define S_YELLOW	129		//노란색
#define S_GREEN		44		//초록색
#define S_CYAN		73		//하늘색
#define S_BLUE		20		//파란색
#define S_GRAY		1		//연회색
#define S_REDBLACK	140		//빨강-검정 교차