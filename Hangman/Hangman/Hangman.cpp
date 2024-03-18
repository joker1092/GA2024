#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#define MAX_WORDS 100
#define MAX_LENGTH 15   // 단어의 최대 알파벳 숫자는 14개, 끝은 ‘\0’

char words[MAX_WORDS][MAX_LENGTH] = {
    "elephant", "umbrella", "computer", "football", "calendar", "telephone", "sunshine", "telescope", "mountain", "hamburger",
    "umbrella", "pencil", "piano", "bicycle", "triangle", "elephant", "potato", "tomato", "octopus", "crocodile",
    "apartment", "magazine", "happiness", "beautiful", "firework", "volcano", "waterfall", "pineapple", "blueberry", "crocodile",
    "kangaroo", "elephant", "crocodile", "hamburger", "umbrella", "piano", "computer", "television", "elephant", "crocodile",
    "triangle", "telephone", "magazine", "calendar", "elephant", "umbrella", "hamburger", "computer", "telephone", "triangle",
    "watermelon", "telephone", "elephant", "octopus", "television", "happiness", "mountain", "volcano", "sunshine", "beautiful",
    "computer", "telephone", "hamburger", "elephant", "octopus", "sunshine", "telephone", "magazine", "apartment", "calendar",
    "volcano", "waterfall", "crocodile", "piano", "kangaroo", "elephant", "triangle", "computer", "telephone", "hamburger",
    "sunshine", "umbrella", "television", "calendar", "magazine", "octopus", "firework", "pineapple", "volcano", "watermelon",
    "elephant", "telephone", "computer", "umbrella", "beautiful", "hamburger", "octopus", "kangaroo", "triangle", "elephant"
};// 100개의 단어 목록



int main() {

    srand(time(NULL));
    // 랜덤 시드
    int isStart = 1;

    printf("%s\n", "H a n g m a n");
    printf("%s\n", "숨겨진 단어를 추측하여 알파벳을 선택하면서 최종 단어를 완성한다.");
    printf("%s\n", "단어에 없는 알파벳을 선택하면 Wrong Count가 늘어난다.");
    printf("%s\n", "단어에 있는 알파벳을 선택하면 해당 알파벳을 보여준다.");
    printf("%s\n", "기회는 5번 실패 시 게임오버");
    // 게임 설명
    while (isStart) {
        

        int random_variable = rand() % 100;

        char setword[MAX_LENGTH] = "";

        int viewWordSize = 0;

        // 단어를 맟추고 나온뒤 다시 시작시 난수와 단어와 단어 크기를 초기화


        // 배열에 채워진 단어들 출력 (확인용)
        /*printf("채워진 단어들:\n");
        for (int i = 0; i < MAX_WORDS; ++i) {
            printf("%s\n", words[i]);
        }*/
        //printf("%s\n", words[random_variable]);

        for (int i = 0; i < MAX_LENGTH; ++i) {
            setword[i] = words[random_variable][i];
            if (words[random_variable][i] == '\0') {
                viewWordSize = i;
                break;
            }
        }

        // 난수 단어를 받아와서 정답 단어 변수와 크기를 저장
        /*printf("%s%d\n", "length", viewWordSize);*/

        

        printf("%s\n", "1: 게임 시작, 0: 종료");
        scanf_s("%d", &isStart);

        int gameState = 0;
        gameState = isStart;
        char viewword[MAX_LENGTH] = "";
        char selectedChar[28] = {};
        int count = 0;
        int wrongCount = 0;

        for (int i = 0; i < viewWordSize; ++i) {
            viewword[i] = '_';
        }
        // 게임내 보여지는 단어 판과 카운트를 초기화

        while (gameState) {
            
            // 단어를 맟추거나 게임오버 될때까지 루프

            system("cls");
            
            bool isSelected = false;
            //이미 선택했던 문자인지 플래그

            char selectChar[2];

            for (int i = 0; i < viewWordSize; ++i) {
                printf("%c", viewword[i]);
            }
            //게임내에 보여지는 단어판
            printf("\t");
            printf("%s%d\n", "wrongCount", wrongCount);
            //틀린 횟수
            printf("\t");
            printf("%s%d\n", "count", count);
            //시도 횟수
            printf("\t");
            printf("%s%s\n", "입력했던 문자", selectedChar);
            //입력했던 문자

            printf("\n");
            scanf_s("%s", &selectChar, 2);
            printf("%s\n", selectChar);
            //문자입력


            for (int i = 0; i < count; ++i) {
                if (selectedChar[i] == selectChar[0]) {
                    isSelected = true;
                }
            }
            //입력했던 문자들의 배열과 비교하여 입력했던 문자인지 판별(옵션)

            if (!isSelected) {
                selectedChar[count] = selectChar[0];
                count++;
                //입력하지 않은 문자라면 입력한 문자 배열에 추가

                int charCount = 0;
                for (int i = 0; i < viewWordSize; ++i) {
                    if (setword[i] == selectChar[0]) {
                        viewword[i] = setword[i];
                        //문자열과 입려 문자 비교 하여 맞다면 정답지 공개
                    }
                    else {
                        charCount++;
                    }
                }
                if (viewWordSize == charCount) {
                    wrongCount++;
                }
                //문자열의 갯수와 입력한 문자를 맞는 갯수를 비교하여 wrongCount 판별
                int unresolvedCount = viewWordSize;
                for (int i = 0; i < viewWordSize; ++i) {
                    if (viewword[i] != '_') {
                        unresolvedCount--;
                    }
                }
                //정답판의 가려진 부분을 비교하여 정답 여부 확인
                if (unresolvedCount == 0)
                {
                    system("cls");
                    printf("%s\n", "Congratulations");
                    printf("%s%s\n", "answer : ", setword);
                    break;
                    //정답일 경우
                }

                if (wrongCount == 5)
                {
                    system("cls");
                    printf("%s\n", "GameOver");
                    printf("%s%s\n", "answer : ", setword);
                    break;
                    //오답이 5번인 경우
                }

            }
            else {
                continue;

            }
        }
    }
    

    return 0;
}