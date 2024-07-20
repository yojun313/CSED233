#include "open_hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int OpenHashFunction::openhashing(int key)
{
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int sum = 0;  // 키의 각 자리수의 합을 저장할 변수
    while (key > 0) {
        sum += key % 10;  // 마지막 자리수 더하기
        key /= 10;        // 키의 마지막 자리 제거
    }
    return sum % index_size;  // 합을 테이블 크기로 나눈 나머지 반환
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
