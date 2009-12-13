#define TRUE				1
#define FALSE				0
#define NULL				-1

//option
#define DEFAULT_GAMER		6
#define ENABLE_JUMP			FALSE

#define LADDER_STYLE_RECT	0
#define LADDER_STYLE_CROSS	1
#define LADDER_STYLE_JUMP	2
#define DEFAULT_MARGIN_TOP			10
#define DEFAULT_MARGIN_BOTTOM		10

//only one
struct Ladder{
	int gamer;
	int nodeCount;
	int defaultNodeCount;
	//int jumpable;
}ladder;

//only one
struct LadderLayout{
	int gap;
	int top;
	int bottom;
	int left;
	int right;
	int onScrollX;
}ladderLayout;

//Support Bit Operation
#define L_MASK_1B			0XF
#define L_MASK_2B			0XFF
#define L_MASK_3B			0XFFF
#define L_MASK_4B			0XFFFF
#define L_CLEAR_2B			0X00
#define L_CLEAR_3B			0X000
#define L_CLEAR_4B			0X0000
#define L_CLEAR_6B			0X000000
#define SHIFT_2B			8
#define SHIFT_3B			12
#define SHIFT_4B			16
#define SHIFT_6B			24

//Ladder Node
int loaded_LadderNode = FALSE;
int *ladderNode_LineNumber;
int *ladderNode_Top;
int *ladderNode_Option;
#define setNodeLineNumber(index, ln1, ln2)		*(ladderNode_LineNumber+index) = (ln2 & L_MASK_2B) << SHIFT_2B | (ln1 & L_MASK_2B)
	#define getNodeLineNumber1(index)			(*(ladderNode_LineNumber+index) & L_MASK_2B)
	#define getNodeLineNumber2(index)			((*(ladderNode_LineNumber+index) >> SHIFT_2B) & L_MASK_2B)
#define setNodeTop(index, t1, t2)				*(ladderNode_Top+index) = (t2 & L_MASK_4B) << SHIFT_4B | (t1 & L_MASK_4B)
	#define getNodeTop1(index)					(*(ladderNode_Top+index) & L_MASK_4B)
	#define getNodeTop2(index)					((*(ladderNode_Top+index) >> SHIFT_4B) & L_MASK_4B)
#define setNodeOption(index, id1, id2, opt)		*(ladderNode_Option+index) = ((opt & L_MASK_1B) << SHIFT_3B | (id2 & L_MASK_3B)) << SHIFT_3B | (id1 & L_MASK_3B);
#define setNodeIndex(index, id1, id2)			*(ladderNode_Option+index) = ((*(ladderNode_Option+index) & L_CLEAR_6B) | (id2 & L_MASK_3B)) << SHIFT_3B | (id1 & L_MASK_3B);
	#define getNodeIndex1(index)				(*(ladderNode_Option+index) & L_MASK_3B)
	#define getNodeIndex2(index)				((*(ladderNode_Option+index) >> SHIFT_3B) & L_MASK_3B)
	#define getNodeOption(index)				((*(ladderNode_Option+index) >> SHIFT_6B) & L_MASK_1B)
#define setladderNodeLineNumber(index, value)	*(ladderNode_LineNumber+index) = value
#define setladderNodeTop(index, value)			*(ladderNode_Top+index) = value
#define setladderNodeOption(index, value)		*(ladderNode_Option+index) = value
	#define getladderNodeLineNumber(index)		*(ladderNode_LineNumber+index)
	#define getladderNodeTop(index)				*(ladderNode_Top+index)
	#define getladderNodeOption(index)			*(ladderNode_Option+index)
void initLadderNode_P(int index, int lineNumber1, int lineNumber2, int top1, int top2, int enabled){
	setNodeLineNumber(index, lineNumber1, lineNumber2);
	setNodeTop(index, top1, top2);
	setNodeOption(index, 0, 0, TRUE);
}

//Vertical Ladder
int loaded_LadderVertical = FALSE;
int *ladderVertical_Value;
int *ladderVertical_FirstNodeIndex;
#define setVerticalValue(index, head, foot, result)	*(ladderVertical_Value+index) = ((result & L_MASK_2B) << SHIFT_2B | (foot & L_MASK_2B)) << SHIFT_2B | (head & L_MASK_2B)
	#define getVerticalHeadValue(index)				(*(ladderVertical_Value+index) & L_MASK_2B)
	#define getVerticalFootValue(index)				((*(ladderVertical_Value+index) >> SHIFT_2B) & L_MASK_2B)
	#define getVerticalResult(index)				((*(ladderVertical_Value+index) >> SHIFT_4B) & L_MASK_2B)
#define setVerticalFirstNodeIndexCounting(index)	(*(ladderVertical_FirstNodeIndex+index) += 1)
#define setVerticalFirstNodeIndex(index, value)		(*(ladderVertical_FirstNodeIndex+index) = value)
	#define getVerticalFirstNodeIndex(index)		(*(ladderVertical_FirstNodeIndex+index))
void initLadderVertical_P(int index, int headValue, int footValue){
	setVerticalValue(index, headValue, footValue, NULL);
	setVerticalFirstNodeIndex(index, 0);
}

//Node Index Array(nodeCount * 2 + gamer)
int loaded_LadderNodeIndexArray = FALSE;
int *ladderNodeIndex;
#define setIndexArray(index, value)				*(ladderNodeIndex+index) = value
	#define getIndexArray(index)				(*(ladderNodeIndex+index))

//Option
int isLoadding;

void ladder_layout(int left, int top, int bottom, int gap){
	ladderLayout.left = left;
	ladderLayout.right = (ladder.gamer - 1) * gap + left;
	ladderLayout.top = top;
	ladderLayout.bottom = bottom;
	ladderLayout.gap = gap;
	
	if(ladderLayout.right > swWidth){
		ladderLayout.onScrollX = TRUE;
	}else{
		ladderLayout.onScrollX = FALSE;
		ladderLayout.left = (swWidth - (ladderLayout.right - ladderLayout.left)) / 2;
		ladderLayout.right = (ladder.gamer - 1) * gap + left;
	}

}

int ladder_create(int gamer, int nodeCount){
	int result;

	ladder.gamer = gamer;
	if(nodeCount > 0){
		ladder.nodeCount = nodeCount;
	}else{
		ladder.nodeCount = (ladder.gamer - 1) * (2 + (ladder.gamer - 1) / 2);
		ladder.defaultNodeCount = 2 + (ladder.gamer - 1) / 2;
	}

	//ladder.jumpable = jumpable;

	ladder_destroy();

	if(loaded_LadderNode == FALSE){
		ladderNode_LineNumber = MallocInt(ladder.nodeCount);
		if(ladderNode_LineNumber == 0){
			return FALSE;
		}else{
			ladderNode_Top = MallocInt(ladder.nodeCount);
			if(ladderNode_Top == 0){
				result = FreeInt(ladderNode_LineNumber);
			}else{
				ladderNode_Option = MallocInt(ladder.nodeCount);
				if(ladderNode_Option == 0){
					result = FreeInt(ladderNode_LineNumber);
					result = FreeInt(ladderNode_Top);
				}else{
					loaded_LadderNode = TRUE;
				}
			}
		}
	}if(loaded_LadderNode == FALSE) return FALSE;
	
	if(loaded_LadderVertical == FALSE){
		ladderVertical_Value = MallocInt(ladder.gamer);
		if(ladderVertical_Value == 0){
			ladder_destroy();
		}else{
			ladderVertical_FirstNodeIndex = MallocInt(ladder.gamer);
			if(ladderVertical_FirstNodeIndex == 0){
				result = FreeInt(ladderVertical_Value);
				ladder_destroy();
			}else{
				loaded_LadderVertical = TRUE;
			}
		}
	}if(loaded_LadderVertical == FALSE) return FALSE;

	if(loaded_LadderNodeIndexArray == FALSE){
		ladderNodeIndex = MallocInt(ladder.nodeCount * 2 + ladder.gamer);
		if(ladderNodeIndex == 0){
			ladder_destroy();
		}else{
			loaded_LadderNodeIndexArray = TRUE;
		}
	}if(loaded_LadderNodeIndexArray == FALSE) return FALSE;


	return TRUE;
}

void ladder_destroy(){
	int result;

	if(loaded_LadderNode == TRUE){
		result = FreeInt(ladderNode_LineNumber);
		result = FreeInt(ladderNode_Top);
		result = FreeInt(ladderNode_Option);
		loaded_LadderNode = FALSE;
	}
	if(loaded_LadderVertical == TRUE){
		result = FreeInt(ladderVertical_Value);
		result = FreeInt(ladderVertical_FirstNodeIndex);
		loaded_LadderVertical = FALSE;
	}
	if(loaded_LadderNodeIndexArray == TRUE){
		result = FreeInt(ladderNodeIndex);
		loaded_LadderNodeIndexArray = FALSE;
	}
}


void ladder_set(){
	int i, j;
	int needSwap;
	int sum, temp;
	int result;

	isLoadding = TRUE;

	//사람수 입력 받고서 생성한 세로줄
	for(i = 0; i < ladder.gamer; i++){
		initLadderVertical_P(i,  0,  0);
	}

	//입력받은 노드를 왼쪽 라인번호 순, 왼쪽 라인의 높이 순으로 오름차순 정렬
	for(i = 0; i < ladder.nodeCount; i++){
		for(j = i; j < ladder.nodeCount; j++){
			if(getNodeLineNumber1(i) > getNodeLineNumber1(j)){
				needSwap = TRUE;	
			}else if(getNodeLineNumber1(i) == getNodeLineNumber1(j)){
				if(getNodeTop1(i) > getNodeTop1(j)){
					needSwap = TRUE;
				}else{
					needSwap = FALSE;
				}
			}else{
				needSwap = FALSE;
			}

			if(needSwap == TRUE){
				temp = getladderNodeLineNumber(i);
				setladderNodeLineNumber(i, getladderNodeLineNumber(j));
				setladderNodeLineNumber(j, temp);

				temp = getladderNodeTop(i);
				setladderNodeTop(i, getladderNodeTop(j));
				setladderNodeTop(j, temp);
				
				temp = getladderNodeOption(i);
				setladderNodeOption(i, getladderNodeOption(j));
				setladderNodeOption(j, temp);
			}
		}
	}

	//각 라인의 시작 노드 인덱스를 저장
	for(i = 0; i < ladder.nodeCount; i++){
		if( getNodeLineNumber1(i) < ladder.gamer)
			setVerticalFirstNodeIndexCounting(getNodeLineNumber1(i));
		if( getNodeLineNumber2(i) < ladder.gamer)
			setVerticalFirstNodeIndexCounting(getNodeLineNumber2(i));
	}

	sum = 0;
	for(i = 0; i < ladder.gamer; i++){
		temp = getVerticalFirstNodeIndex(i);
		setVerticalFirstNodeIndex(i, sum);
		sum = sum + temp;
		setIndexArray(sum, NULL);		//노드 인덱스 배열의 끝 식별하기 위함
		sum++;							//1더함은 라인의 끝 식별자까지 포함
	}

	//각 라인에 대해 노드들의 순번
	for(i = 0; i < ladder.nodeCount; i++){
		sum = 0;
		temp = 0;
		//같은 라인을 찾고 자신의 순번을 계산
		for(j = 0; j < ladder.nodeCount; j++){
			if(getNodeLineNumber1(i) == getNodeLineNumber1(j)){
				if(getNodeTop1(i) > getNodeTop1(j)) sum++;
			}else if(getNodeLineNumber1(i) == getNodeLineNumber2(j)){
				if(getNodeTop1(i) > getNodeTop2(j)) sum++;
			}

			if(getNodeLineNumber2(i) == getNodeLineNumber1(j)){
				if(getNodeTop2(i) > getNodeTop1(j)) temp++;
			}else if(getNodeLineNumber2(i) == getNodeLineNumber2(j)){
				if(getNodeTop2(i) > getNodeTop2(j)) temp++;
			}
		}
		setNodeIndex(i, sum, temp);
	}

	//각 라인에 대응된 노드들의 인덱스 배열
	for(i = 0; i < ladder.nodeCount; i++){
		setIndexArray(getVerticalFirstNodeIndex(getNodeLineNumber1(i)) + getNodeIndex1(i), i);
		setIndexArray(getVerticalFirstNodeIndex(getNodeLineNumber2(i)) + getNodeIndex2(i), i);
	}
	isLoadding = FALSE;
}

void ladder_render(int x, int y){
	int i;

	//draw vertical line
	for(i = 0; i < ladder.gamer; i++){
		DrawLine(ladderLayout.gap * i + ladderLayout.left + x, ladderLayout.top + y,
				 ladderLayout.gap * i + ladderLayout.left + x, ladderLayout.bottom + y);
	}

	//draw nodes
	for(i = 0; i < ladder.nodeCount; i++){
		if(getladderNodeOption(i) == FALSE) continue;
		DrawLine(ladderLayout.gap * getNodeLineNumber1(i) + ladderLayout.left + x, getNodeTop1(i) + ladderLayout.top + y,
				 ladderLayout.gap * getNodeLineNumber2(i) + ladderLayout.left + x, getNodeTop2(i) + ladderLayout.top + y);
	}

}

int ladder_search(int startLineNumber, int x, int y){
	int currentLineNumber = startLineNumber;
	int currentNodeIndexIndex = getVerticalFirstNodeIndex(currentLineNumber);
	int count = 0;	

	int traceTop = 0;		//_T
	int traceBottom = 0;	//_T
	string temp;
	do{
		//end or null
		if(getIndexArray(currentNodeIndexIndex) == NULL){
			break;
		//node is disabled
		}else if(getladderNodeOption(getIndexArray(currentNodeIndexIndex)) == FALSE){
			//move next node
			currentNodeIndexIndex++;
				//무한 루프 방지(일반 사다리에서는 ladder.nodeCount가 최대)
				if(count > ladder.nodeCount) break;
				else count++;
			//조건 재시작을 위한 이동
			continue;
		//current is node1
		}else if(getNodeLineNumber1(getIndexArray(currentNodeIndexIndex)) == currentLineNumber){
			//TRACE::draw trace1-1
			traceBottom = getNodeTop1(getIndexArray(currentNodeIndexIndex));
			DrawLine(ladderLayout.gap * currentLineNumber + ladderLayout.left + x, ladderLayout.top + traceTop + y,
					 ladderLayout.gap * currentLineNumber + ladderLayout.left + x, ladderLayout.top + traceBottom + y);
			traceTop = getNodeTop2(getIndexArray(currentNodeIndexIndex));

			currentLineNumber = getNodeLineNumber2(getIndexArray(currentNodeIndexIndex));
			currentNodeIndexIndex = getNodeIndex2(getIndexArray(currentNodeIndexIndex));
			currentNodeIndexIndex += getVerticalFirstNodeIndex(currentLineNumber);

		//current is node2
		}else if(getNodeLineNumber2(getIndexArray(currentNodeIndexIndex)) == currentLineNumber){
			//TRACE::draw trace1-2
			traceBottom = getNodeTop2(getIndexArray(currentNodeIndexIndex));
			DrawLine(ladderLayout.gap * currentLineNumber + ladderLayout.left + x, ladderLayout.top + traceTop + y,
					 ladderLayout.gap * currentLineNumber + ladderLayout.left + x, ladderLayout.top + traceBottom + y);
			traceTop = getNodeTop1(getIndexArray(currentNodeIndexIndex));

			currentLineNumber = getNodeLineNumber1(getIndexArray(currentNodeIndexIndex));
			currentNodeIndexIndex = getNodeIndex1(getIndexArray(currentNodeIndexIndex));
			currentNodeIndexIndex += getVerticalFirstNodeIndex(currentLineNumber);
	
		//current is not node, or error
		}else{
			break;
		}

		//TRACE::draw trace2
		DrawLine(ladderLayout.gap * getNodeLineNumber1(getIndexArray(currentNodeIndexIndex)) + ladderLayout.left + x,
				 getNodeTop1(getIndexArray(currentNodeIndexIndex)) + ladderLayout.top + y,
				 ladderLayout.gap * getNodeLineNumber2(getIndexArray(currentNodeIndexIndex)) + ladderLayout.left + x,
				 getNodeTop2(getIndexArray(currentNodeIndexIndex)) + ladderLayout.top + y);

		//move next node
		currentNodeIndexIndex++;

		//무한 루프 방지(일반 사다리에서는 ladder.nodeCount가 최대)
		if(count > ladder.nodeCount) break;
		else count++;

	}while(TRUE);

	//TRACE::draw trace3

	//AHYANE::TRACE PHONE ERROR_1
	//traceBottom = getNodeTop2(getIndexArray(currentNodeIndexIndex));	<< 불필요 한데다가 -1번째 값을 참조하고 있어 오류를 일으킴

	DrawLine(ladderLayout.gap * currentLineNumber + ladderLayout.left + x, ladderLayout.top + traceTop + y,
			 ladderLayout.gap * currentLineNumber + ladderLayout.left + x, ladderLayout.bottom + y);

	//finish is current line
	return currentLineNumber;
}

void ladder_error(int errorId){
	SetFontAlign(S_ALIGN_CENTER);
	FillRectEx(0, (swHeight - GetFontHeight()) / 2, swWidth, (swHeight + GetFontHeight()) / 2, 3);
	DrawStr(swWidth / 2, (swHeight - GetFontHeight()) / 2, "메모리가 부족합니다");
	FlushPartial(0, (swHeight - GetFontHeight()) / 2, swWidth, (swHeight + GetFontHeight()) / 2);
}