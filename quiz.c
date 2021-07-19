#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char lastquestion[1024];

bool same(char* x, char* y)
{
    if (strlen(x) != strlen(y))
        return false;
    for (int i = 0; i < strlen(x); i++)
        if (tolower(x[i]) != tolower(y[i]))
            return false;
    return true;
}

void ask(char* question, char* answer)
{
    printf("%s", question);
    char input[64];
    scanf("%s", input);
    if (same(input, answer)) {
        printf("Correct!\n");
    } else {
        printf("Wrong. The correct answer was: %s\n", answer);
    }
}

bool askNextQuestion(FILE* fp)
{
    char question[1024];
    fgets(question, sizeof(question), fp);
    if (same(question, lastquestion) || strlen(question) <= 1)
        return false;

    char answer[1024];
    fgets(answer, sizeof(answer), fp);
    answer[strlen(answer)-1] = '\0';

    ask(question, answer);

    strncpy(lastquestion, question, 1024);
    return true;
}

int main()
{
    FILE *fp;
    fp = fopen("test.txt", "r");
    while (askNextQuestion(fp)) { }
    fclose(fp);
    return 0;
}
