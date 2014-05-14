#include <iostream>
#include <string>
using namespace std;
void main()
{
	string strArray[5]; // 문자열 변수 선언.
	int count = 0; 	// 최대 5개의 단어를 입력받는다.  end가 나오면 종료한다.
	while (count < 5)
	{
		string str; // 입력을 받을 변수를 선언한다.
		cin >> str; // 단어 입력
		if (str == "end") // end 를 입력하면 루프를 종료한다.
			break;
		strArray[ count] = str; // 단어 저장.
		++count;
	}
	if (count <= 0) // 입력된 단어가 없다면 종료한다.
		return;
	const string table[ 10] = { "grape", "apple", "banana", // 과일 이름 테이블
		"watermelon", "orange", "kiwi", "melon", 
		"cherry", "pear", "tomato" };
	// 입력한 문장이 모두 테이블에 포함되었다면 메세지를 출력한다.
	for (int i=0; i < count; ++i)
	{
		bool isFind = false;
		for (int k=0; k < 10; ++k)
		{
			if (table[ k] == strArray[ i]) // 단어가 일치했다면 다음 단어로 넘어간다.
			{
				isFind = true;
				break;
			}
		}
		if (!isFind)
		{
			cout << "일치하지 않은 단어가 있습니다. " << strArray[ i] 
			<< endl;
			return;
		}
	}
	cout << "모든 단어가 일치하였습니다. " << endl;
}
