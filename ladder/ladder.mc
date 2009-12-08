///////////////////////////////////////////////////////////////////////////
// jumpLadder.mc - Auto Created by GNEX IDE
///////////////////////////////////////////////////////////////////////////

#ifdef _GVM
%{
	#DEFINE SCRIPTVER	2
	#DEFINE LCDCLASS	255
	#DEFINE IMAGETYPE	255
	#DEFINE AUDIOTYPE	255
	#DEFINE SCRIPTTYPE	1
	#DEFINE SCRIPTCPID	60000
	#DEFINE SCRIPTID	1
	#DEFINE SCRIPTNAME	"Jump Ladder"
	#DEFINE VALIDCOUNT	255
	#DEFINE VALIDTERM	255
%}
#else
%{
	#DEFINE PLAYERVER	4
	#DEFINE LCDCLASS	255
	#DEFINE IMAGETYPE	255
	#DEFINE AUDIOTYPE	255
	#DEFINE APPTYPE		1
	#DEFINE APPCPID		19732
	#DEFINE APPID		12012
	#DEFINE APPNAME		"Jump Ladder"
	#DEFINE COMPTYPE	0
	#DEFINE AGENTTYPE	0
	#DEFINE VALIDCOUNT	255
	#DEFINE VALIDTERM	255
	#DEFINE DIRECTRUN	0
	#DEFINE APPVER		1
%}
#endif

#include <SScript.h>
#define TRUE				1
#define FALSE				0
#define NULL				-1

//option
#define DEFAULT_GAMER		7
#define ENABLE_JUMP			TRUE

struct Ladder{
	int gamer;
	int jumpable;
	int nodeCount;
}ladder;

struct LadderLayout{
	int gap;
	int top;
	int bottom;
	int left;
}ladderLayout;

struct LadderNode{
	int lineNumber1;
	int lineNumber2;
	int top1;
	int top2;
	int index1;
	int index2;
	int enabled;
}ladderNode[10];

	void initLadderNode(int index, int lineNumber1, int lineNumber2, int top1, int top2, int enabled){
		ladderNode[index].lineNumber1 = lineNumber1;
		ladderNode[index].lineNumber2 = lineNumber2;
		ladderNode[index].top1 = top1;
		ladderNode[index].top2 = top2;
		ladderNode[index].enabled = enabled;
	}

	void setLadderNodeIndex(int index, int index1, int index2){
		ladderNode[index].index1 = index1;
		ladderNode[index].index2 = index2;
	}

struct LadderVertical{
	int headValue;
	int footValue;
	int firstNodeIndex;
	int finishVertical;
}ladderVertical[DEFAULT_GAMER];

	void initLadderVertical(int index, int headValue, int footValue, int firstNodeIndex){
		ladderVertical[index].headValue = headValue;
		ladderVertical[index].footValue = footValue;
		ladderVertical[index].firstNodeIndex = firstNodeIndex;
		ladderVertical[index].finishVertical = NULL;
	}

int ladderNodeIndex[27];	//ladder.nodeCount * 2 + ladder.gamer
int isloadding;
int testStartNode;
//int *p;

void main(){

	//p = MallocInt(10);
	//*(p+0) = 1;
	//*(p+5) = 2;
	//*(p+9) = 3;
	testStartNode = 0;

	init(DEFAULT_GAMER, ENABLE_JUMP);
	setDatas();

	SetTimer(50, 1);
}

void setDatas(){
	int i, j;
	int needSwap, temp;
	int sum;

	isloadding = TRUE;

	//제공된 데이터 : 라인1, 라인2, 세로좌표1, 세로좌표2 (라인1이 라인2보다 반드시 작아야 함, 별도로 정렬이 필요함)
	initLadderNode( 0,  0,  1, Rand(10,30), Rand(40,50),  TRUE);
	initLadderNode( 1,  0,  1, Rand(80,90), Rand(80,175),  TRUE);
	initLadderNode( 2,  1,  2,  30,  30,  TRUE);
	initLadderNode( 3,  1,  2, 140,  90,  TRUE);
	initLadderNode( 4,  2,  3,  40,  50,  TRUE);
	initLadderNode( 5,  2,  3,  80, 160,  TRUE);
	initLadderNode( 6,  3,  4,  90, 120,  TRUE);
	initLadderNode( 7,  3,  4, 140, 150,  TRUE);
	initLadderNode( 8,  4,  5, 100,  60,  TRUE);
	initLadderNode( 9,  5,  6, Rand(10,150), Rand(10,150),  TRUE);

	//입력받은 노드를 왼쪽 라인번호 순, 왼쪽 라인의 높이 순으로 오름차순 정렬
	for(i = 0; i < 10; i++){
		for(j = i; j < 10; j++){
			if(ladderNode[i].lineNumber1 > ladderNode[j].lineNumber1){
				needSwap = TRUE;	
			}else if(ladderNode[i].lineNumber1 == ladderNode[j].lineNumber1){
				if(ladderNode[i].top1 > ladderNode[j].top1){
					needSwap = TRUE;
				}else{
					needSwap = FALSE;
				}
			}else{
				needSwap = FALSE;
			}

			if(needSwap == TRUE){
				temp = ladderNode[i].lineNumber1;
				ladderNode[i].lineNumber1 = ladderNode[j].lineNumber1;
				ladderNode[j].lineNumber1 = temp;

				temp = ladderNode[i].lineNumber2;
				ladderNode[i].lineNumber2 = ladderNode[j].lineNumber2;
				ladderNode[j].lineNumber2 = temp;

				temp = ladderNode[i].top1;
				ladderNode[i].top1 = ladderNode[j].top1;
				ladderNode[j].top1 = temp;

				temp = ladderNode[i].top2;
				ladderNode[i].top2 = ladderNode[j].top2;
				ladderNode[j].top2 = temp;
			}
		}
	}

	//각 라인의 시작 노드 인덱스를 저장
	initLadderVertical( 0,  0,  0,  0);
	initLadderVertical( 1,  0,  0,  0);
	initLadderVertical( 2,  0,  0,  0);
	initLadderVertical( 3,  0,  0,  0);
	initLadderVertical( 4,  0,  0,  0);
	initLadderVertical( 5,  0,  0,  0);
	initLadderVertical( 6,  0,  0,  0);
	for(i = 0; i < 10; i++){
		if(ladderNode[i].lineNumber1 < ladder.gamer)
			ladderVertical[ladderNode[i].lineNumber1].firstNodeIndex++;
		if(ladderNode[i].lineNumber2 < ladder.gamer)
			ladderVertical[ladderNode[i].lineNumber2].firstNodeIndex++;
	}

	sum = 0;
	for(i = 0; i < ladder.gamer; i++){
		temp = ladderVertical[i].firstNodeIndex;
		ladderVertical[i].firstNodeIndex = sum;
		sum = sum + temp;
		ladderNodeIndex[sum] = NULL;	//노드 인덱스 배열의 끝 식별하기 위함
		sum++;							//1더함은 라인의 끝 식별자까지 포함
	}

	//각 라인에 대해 노드들의 순번
	for(i = 0; i < 10; i++){
		sum = 0;
		temp = 0;
		//같은 라인을 찾고 자신의 순번을 계산
		for(j = 0; j < 10; j++){
			if(ladderNode[i].lineNumber1 == ladderNode[j].lineNumber1){
				if(ladderNode[i].top1 > ladderNode[j].top1) sum++;
			}else if(ladderNode[i].lineNumber1 == ladderNode[j].lineNumber2){
				if(ladderNode[i].top1 > ladderNode[j].top2) sum++;
			}

			if(ladderNode[i].lineNumber2 == ladderNode[j].lineNumber1){
				if(ladderNode[i].top2 > ladderNode[j].top1) temp++;
			}else if(ladderNode[i].lineNumber2 == ladderNode[j].lineNumber2){
				if(ladderNode[i].top2 > ladderNode[j].top2) temp++;
			}
		}
		setLadderNodeIndex(i, sum, temp);
	}

	//각 라인에 대응된 노드들의 인덱스 배열
	for(i = 0; i < 10; i++){
		ladderNodeIndex[ladderVertical[ladderNode[i].lineNumber1].firstNodeIndex + ladderNode[i].index1] = i;
		ladderNodeIndex[ladderVertical[ladderNode[i].lineNumber2].firstNodeIndex + ladderNode[i].index2] = i;
	}

	isloadding = FALSE;

}

void init(int gamer, int jumpable){
	ladder.gamer = gamer;
	ladder.jumpable = jumpable;
	ladder.nodeCount = 10;
	
	ladderLayout.gap = 32;
	ladderLayout.top = 40;
	ladderLayout.bottom = 240;
	ladderLayout.left = 20;
}

void EVENT_TIMEOUT(){
	int i;
	int tempString;

	ClearWhite();	
	
	//for(i = 0; i < 10; i++){
	//	DrawLine(0, 10*i + 10, *(p+i) * 10 +10, 10*i + 10);
	//}

	SetColor(S_LGRAY);
	if(isloadding == FALSE)render();

	SetFont(S_FONT_LARGE);
	SetFontColor(S_BLACK, S_BLACK);
	SetColorRGB(255, 0, 0);
	//for(i = 0; i < 6; i++){
		tempString = "";
		MakeStr2(tempString, "S%d=E%d", testStartNode, search(testStartNode));
		DrawStr(5 + ladderLayout.gap * testStartNode, swHeight - 45, tempString);
	//}

	SetFont(S_FONT_MEDIUM);
	DrawStr(10, 15, "Ahyane Jump Ladder v0.2");
	DrawStr(10, swHeight - 20, "Copyrightⓒ2010. Ahyane.");
	//DrawStr(40, swHeight - 30, "Copyrightⓒ2010. Ahyane.");
	//DrawStr(80, swHeight - 20, "All rights reserved.");

	Flush();
}

void EVENT_KEYPRESS(){
	switch(swData){
		case SWAP_KEY_LEFT:
			testStartNode = (testStartNode + DEFAULT_GAMER - 1) % DEFAULT_GAMER;
			break;
		case SWAP_KEY_RIGHT:
			testStartNode = (testStartNode + 1) % DEFAULT_GAMER;
			break;
		case SWAP_KEY_OK:
			if(isloadding == FALSE)setDatas();
			break;
	}

}

void render(){
	int i;

	//draw vertical line
	for(i = 0; i < ladder.gamer; i++){
		DrawLine(ladderLayout.gap * i + ladderLayout.left, ladderLayout.top,
				 ladderLayout.gap * i + ladderLayout.left, ladderLayout.bottom);
	}

	//draw nodes
	for(i = 0; i < ladder.nodeCount; i++){
		DrawLine(ladderLayout.gap * ladderNode[i].lineNumber1 + ladderLayout.left, ladderNode[i].top1 + ladderLayout.top,
				 ladderLayout.gap * ladderNode[i].lineNumber2 + ladderLayout.left, ladderNode[i].top2 + ladderLayout.top);
	}

}

int search(int startLineNumber){
	int currentLineNumber = startLineNumber;
	int currentNodeIndexIndex = ladderVertical[currentLineNumber].firstNodeIndex;
	
	int traceTop = 0;
	int traceBottom = 0;
	
	
	do{
		//end or null
		if(ladderNodeIndex[currentNodeIndexIndex] == NULL){
			break;
		//current is node1
		}else if(ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1 == currentLineNumber){
			//TRACE::draw trace1-1
			traceBottom = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top1;
			DrawLine(ladderLayout.gap * currentLineNumber + ladderLayout.left, ladderLayout.top + traceTop,
					 ladderLayout.gap * currentLineNumber + ladderLayout.left, ladderLayout.top + traceBottom);		
			traceTop = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top2;

			currentLineNumber = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2;
			currentNodeIndexIndex = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].index2;
			currentNodeIndexIndex += ladderVertical[currentLineNumber].firstNodeIndex;

		//current is node2
		}else if(ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2 == currentLineNumber){
			//TRACE::draw trace1-2
			traceBottom = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top2;
			DrawLine(ladderLayout.gap * currentLineNumber + ladderLayout.left, ladderLayout.top + traceTop,
					 ladderLayout.gap * currentLineNumber + ladderLayout.left, ladderLayout.top + traceBottom);
			traceTop = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top1;

			currentLineNumber = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1;
			currentNodeIndexIndex = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].index1;
			currentNodeIndexIndex += ladderVertical[currentLineNumber].firstNodeIndex;
	
		//current is not node, or error
		}else{
			break;
		}

		//TRACE::draw trace2
		DrawLine(ladderLayout.gap * ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1 + ladderLayout.left, ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top1 + ladderLayout.top,
				 ladderLayout.gap * ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2 + ladderLayout.left, ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top2 + ladderLayout.top);

		//move next node
		currentNodeIndexIndex++;
	}while(TRUE);

	//TRACE::draw trace3
	traceBottom = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top2;
	DrawLine(ladderLayout.gap * currentLineNumber + ladderLayout.left, ladderLayout.top + traceTop,
			 ladderLayout.gap * currentLineNumber + ladderLayout.left, ladderLayout.bottom);

	//finish is current line
	return currentLineNumber;
}

int trace(int startLineNumber){
	//ArrayList<Position> -> struct LabberTrace{int x, y;}labberTrace[];
	//return ArrayList<Position> -> return currentLineNumber;
	return NULL;
}