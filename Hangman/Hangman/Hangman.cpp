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
};

int main() {

    srand(time(NULL));

    printf("%s\n", "H a n g m a n");
    printf("%s\n", "숨겨진 단어를 추측하여 알파벳을 선택하면서 최종 단어를 완성한다.");
    printf("%s\n", "숨겨진 단어를 추측하여 알파벳을 선택하면서 최종 단어를 완성한다.");

    int random_variable = rand() % 100;

    char setword[MAX_LENGTH] = "";



    printf("%s\n", words[random_variable]);

    for (int i = 0; i < MAX_LENGTH; ++i) {
        setword[i] = words[random_variable][i];
    }

    printf("%s\n", setword);

    // 배열에 채워진 단어들 출력 (확인용)
    /*printf("채워진 단어들:\n");
    for (int i = 0; i < MAX_WORDS; ++i) {
        printf("%s\n", words[i]);
    }*/

    int gameState = 1;
    int viewWordSize = strlen(setword);
    char viewword[MAX_LENGTH]="";
    char selectedChar[28] = {};
    int count = 0;
    int wrongCount = 0;

    for (int i = 0; i < viewWordSize; ++i) {
        viewword[i] = '_';
    }
    while (gameState) {
        //printf("%d\n", strlen(setword));
        system("cls");
        bool isSelected = false;
        char selectChar[2];
        for (int i = 0; i < viewWordSize; ++i) {
            printf("%c", viewword[i]);
        }
        printf("\t");
        printf("%s%d\n", "wrongCount", wrongCount);
        printf("\t");
        printf("%s%d\n", "count", count);
        printf("\t");
        printf("%s%s\n", "입력했던 문자", selectedChar);

        printf("\n");
        scanf_s("%s", &selectChar , 2);
        printf("%s\n", selectChar);



        for(int i = 0; i < count; ++i) {
            if (selectedChar[i] == selectChar[0]) {
                isSelected = true;
            }
        }


        if(!isSelected){
            selectedChar[count] = selectChar[0];
            count++;

            int charCount = 0;
            for (int i = 0; i < viewWordSize; ++i) {
                if (setword[i] == selectChar[0]) {
                    viewword[i] = setword[i];
                }
                else {
                    charCount++;
                }
            }
            if (viewWordSize == charCount) {
                wrongCount++;
            }
            int unresolvedCount = viewWordSize;
            for (int i = 0; i < viewWordSize; ++i) {
                if (viewword[i] != '_') {
                    unresolvedCount--;
                }
            }

            if (unresolvedCount == 0)
            {
                system("cls");
                printf("%s\n", "Congratulations");
                printf("%s%s\n", "answer : ", setword);
                break;
            }

            if (wrongCount == 5)
            {
                system("cls");
                printf("%s\n", "GameOver");
                printf("%s%s\n", "answer : ", setword);
                break;
            }

        }
        else {
            continue;

        }
    }

    return 0;
}