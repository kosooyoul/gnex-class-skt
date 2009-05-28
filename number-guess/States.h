//NumberGuess.States - Ko Soo Youl - 09.05.26

//메인
int currentMode = 0;
int currentMenu = 0;

//게임
int chance;								//기회
int gamePoint;							//점수
int questNumber;						//정답
int answeredNumber;						//입력한 답
int historyNumber[MAX_COUNT_HISTORY];	//지난 답 목록
int lastHistoryIndex = 0;				//목록의 마지막 답
int gameRank;							//현재 게임의 순위
int gameTurn;							//몇번째 대답하는건지

int playCount;							//플레이한 문제 갯수
int currentPlayMode;					//게임 플레이중 모드
int prevPlayMode;						//게임 플레이중 이전 모드
string inputedString;					//입력받은 문자열

//게임 타이머 관련 (1번 타이머 사용)
int timeValue = 0;
void InitTimer(){
	ResetTimer1();
	timeValue = 0;
}

void PauseTimer(){
	ResetTimer1();
}

void PlayTimer(){
	SetTimer1(50,1);
}

//옵션
int numberSize = 2;				//정답의 범위; Rand(0, 10 ^ 2)

//임시 선택값
int selectedValue;

//지난 답 목록 추가
void AddHistory(int value){
	//입력한 답을 추가할 위치 설정
	if(lastHistoryIndex < MAX_COUNT_HISTORY - 1){
		lastHistoryIndex += 1;
	}else{
		lastHistoryIndex = 0;
	}

	//입력한 답 추가
	historyNumber[lastHistoryIndex] = value;
}

void InitHistory(){
	ArrayToVar(historyNumber, -1, MAX_COUNT_HISTORY, S_OP_SET);
}

//오류 처리
/*
	errorType : ERROR_NO, ERROR_NUMBER_FORMAT, ERROR_OUT_OF_RANGE

*/
int errorType = 0;				//발생한 오류 종류(0이면 없음)

//에러 종류
#define ERROR_NO			0	//에러없음
#define ERROR_NUMBER_FORMAT	1	//입력에러 숫자로 이루어진 문자열이 아님
#define ERROR_OUT_OF_RANGE	2	//요구 입력 범위 초과

void error(int error){
	errorType = error;
}

//점수 계산, 증가
void PointUp(){
	//기본 점수 증가
	gamePoint += numberSize + 8;
	//시간 점수 증가
	gamePoint += GetBonusPoint();
}

//시간, 대답 횟수에 따른 점수
int GetBonusPoint(){
	int bonus;
	bonus = (numberSize - 2) * 3 - gameTurn;
	if(bonus < 0) bonus = 0;
	bonus += (100 + numberSize * 5) / (timeValue / numberSize);
	return bonus;
}

//게임레벨에 따른 추가 기회
int GetAidChance(){
	return (numberSize - 2) * 3;
}

//랭크
/*
	점수 : 0 이상
	날짜 : 년 x 24 x 31 + 월 x 31 + 일
*/
struct Rank{
	int point;
	int date;
}rank[MAX_COUNT_RANK];

//랭크 추가 및 저장, 등수 반환
int AddRank(int point){
	int rankNumber = MAX_COUNT_RANK;	//초기값 = 순위권밖
	int i;
	
	//순위 조사
	for(i = 0; i < MAX_COUNT_RANK; i++){	
		if(rank[i].point < point){
			rankNumber = i;
			break;
		}
	}

	//순위권 내인 경우
	if(rankNumber < MAX_COUNT_RANK){
		//하위 순위권 순위 밀려남
		for(i = MAX_COUNT_RANK - 1; i > rankNumber; i--){
			rank[i].point	= rank[i - 1].point;	
			rank[i].date	= rank[i - 1].date;
		}
	
		//현재 랭크정보를 현재 순위에 저장
		rank[rankNumber].point	= point;
		rank[rankNumber].date	= GetDateToInt();

		//랭크 저장
		SaveRank();
	}

	return rankNumber;
}

//세이브 데이터 관련
/*
	[         0 ] 최초 실행 여부 (최초 = 0, else;4096)
	[         1 ] 문제 자릿수 옵션 (2 ~ 5)
	[ 2 + 2 x n ] 랭크.점수 : 0 이상
	[ 3 + 2 x n ] 랭크.날짜 : 년 x 24 x 31 + 월 x 31 + 일

	초기 로드 : LoadRom()
	랭크 저장 : SaveRank()
	옵션 저장 : SaveOption()
*/
#define	NV_SIZE	12
int NVROM[NV_SIZE];
string gOutStr;

//세이브 데이터 로드
void LoadROM(){
	int i, j = 0;

	GetBytes(swRsRcvBuf, 0, gOutStr, NV_SIZE);
	GetUserNV(NVROM, NV_SIZE);
	
	//처음 시작인지
	if(NVROM[0] != 4096){
		NVROM[0] = 4096;
		NVROM[1] = 2;
		PutUserNV(NVROM, NV_SIZE);
	}

	for(i = 0; i < MAX_COUNT_RANK; i++){
		j += 2;
		rank[i].point	= NVROM[j];
		rank[i].date	= NVROM[j+1];
	}

	//문제의 수치 범위
	numberSize = NVROM[1];

}

//랭크 저장
void SaveRank(){
	int i, j = 0;

	for(i = 0; i < MAX_COUNT_RANK; i++){
		j += 2;
		NVROM[j]	= rank[i].point;
		NVROM[j+1]	= rank[i].date;
	}
	PutUserNV(NVROM, NV_SIZE);

}

//옵션 저장
void SaveOption(){
	NVROM[1] = numberSize;
	PutUserNV(NVROM, NV_SIZE);
}

/*
	옵션에서 선택표시
*/
int delayTime;
int delayKey;
