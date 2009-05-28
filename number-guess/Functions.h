//NumberGuess.Functions - Ko Soo Youl - 09.05.26

//수치 출력
void DrawInt(int x, int y, int value){
	string str;
	IntToAscii(str, value);
	DrawStr(x, y, str);
}

//n의 exp제곱값을 반환
int Power(int n, int exp){
	int i;
	int result = n;
	for(i = 1; i < exp; i++){
		result *= n;
	}
	return result;
}

//날짜를 정수로 변환
int DateToInt(int *sourceDate){
	int result = 0;

	result += *(sourceDate) * 12 * 31;
	result += *(sourceDate + 1) * 31;
	result += *(sourceDate + 2);

	return result;
}

//정수를 날짜로변환
void IntToDate(int *result, int sourceDate){
	*(result)		= sourceDate / 31 / 12;
	*(result + 1)	= sourceDate / 31 % 12;
	*(result + 2)	= sourceDate % 31;
}

//현재 날짜를 정수로 반환
int GetDateToInt(){
	int tempDate[3];

	GetDate(tempDate);

	return DateToInt(tempDate);
}

