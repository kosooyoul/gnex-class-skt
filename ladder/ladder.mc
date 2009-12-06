//mobile-c
#define TRUE		1
#define FALSE		0

#define DEFAULT_GAMER	6
#define ENABLE_JUMP	true

struct Ladder{}ladder;
struct LadderNode{}ladderNode[];
struct LadderLayout{}ladderLayout;
int ladderNodeIndex[];

void main(void){

	init(DEFAULT_GAMER, ENABLE_JUMP);

	while(){
		render();
		control();
	}

}

void init(int gamer, int enableJump){
	ladder.gamer = gamer;
	ladder.enableJump = enableJump;
	//ladderNodes = new LadderNode[gamer];
}

void render(){
	int i;

	//draw default line
	for(i = 0; i < ladder.gamer; i++){
		DrawLine(ladderLayout.gap * i + ladderLayout.left, ladderLayout.top,
			 ladderLayout.gap * i + ladderLayout.left, ladderLayout.bottom);
	}

	//draw nodes
	for(i = 0; i < ladder.nodeCount; i++){
		DrawLine(ladderLayout.gap * ladderNode[i].lineNumber1 + ladderLayout.left, ladderLayout.top1,
			 ladderLayout.gap * ladderNode[i].lineNumber2 + ladderLayout.left, ladderLayout.top2);
	}

}

void control(){









}

int search(int startLineNumber){
	int currentLineNumber = startLineNumber;
	int currentNodeIndexIndex = getStartIndexFromLineNumber(currentLineNumber);

	do{

		if(ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1 == currentLineNumber){
			currentLineNumber = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2;
			currentNodeIndexIndex = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].index2;			
		}else if(ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2 == currentLineNumber){
			currentLineNumber = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1;
			currentNodeIndexIndex = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].index1;
		}else{
			break;
		}

	}while(1);

	return currentLineNumber;
}

int trace(int startLineNumber){
	//ArrayList<Position> -> struct LabberTrace{int x, y;}labberTrace[];
	//return ArrayList<Position> -> return currentLineNumber;
}

//JAVA
public ArrayList<Position> trace(int startLineNumber){
	ArrayList<Position> positionList = new ArrayList<Position>();
	int currentLineNumber = startLineNumber;
	int currentNodeIndexIndex = getStartIndexFromLineNumber(currentLineNumber);

	//start position
	positionList.add(new Position(ladderLayout.gap * currentLineNumber + ladderLayout.left,
				      ladderLayout.top1)
			);

	do{

		if(ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1 == currentLineNumber){
			positionList.add(new Position(ladderLayout.gap * currentLineNumber + ladderLayout.left,
						      ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top1)
					);

			currentLineNumber = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2;
			currentNodeIndexIndex = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].index2;

			positionList.add(new Position(ladderLayout.gap * currentLineNumber + ladderLayout.left,
						      ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top2)
					);
		}else if(ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber2 == currentLineNumber){
			positionList.add(new Position(ladderLayout.gap * currentLineNumber + ladderLayout.left,
						      ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top2)
					);

			currentLineNumber = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].lineNumber1;
			currentNodeIndexIndex = ladderNode[ladderNodeIndex[currentNodeIndexIndex]].index1;

			positionList.add(new Position(ladderLayout.gap * currentLineNumber + ladderLayout.left,
						      ladderNode[ladderNodeIndex[currentNodeIndexIndex]].top1)
					);
		}else{
			positionList.add(new Position(ladderLayout.gap * currentLineNumber + ladderLayout.left,
						      ladderLayout.bottom)
					);
			break;
		}

	}while(1);

	return currentLineNumber;
}