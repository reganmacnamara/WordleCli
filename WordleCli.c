#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

// ANSI Colour Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

// only matters for windows
void enableWindowsVirtualTerminal()
{
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(hOut, &mode))
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
}

void getWordFromFile(char *wordBuffer)
{
    char buffer[256];
    int currentLine = 0;
    FILE *filePrt;
    int targetLine = rand() % 14855;

    filePrt = fopen("words.txt", "r"); // r for read only
    if (filePrt == NULL)
    {
        printf(RED "Error: could not open file.\n" RESET);
        return;
    }

    while (fgets(buffer, sizeof(buffer), filePrt) != NULL)
    {
        if (currentLine == targetLine)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            // printf(YELLOW "DEBUG: Line %d: %s" RESET "\n", targetLine, buffer);
            strcpy(wordBuffer, buffer);
            break;
        }
        currentLine++;
    }

    fclose(filePrt);
}

void handleGuess(char *guess, char *word)
{
    for (int i = 0; i < 5; i++)
    {
        char current = guess[i];
        if (word[i] == current)
        {
            printf(GREEN "%c" RESET, guess[i]);
            continue;
        }

        bool wordContainsLetter = false;
        for (int j = 0; j < 5; j++)
        {
            if (current == word[j])
            {
                wordContainsLetter = true;
                break;
            }
        }

        if (wordContainsLetter)
            printf(YELLOW "%c" RESET, guess[i]);
        else
            printf(RED "%c" RESET, guess[i]);
    }
    printf("\n");
}

int main()
{
    char input[6] = "";
    int guesses = 0;
    char word[6] = "";

    enableWindowsVirtualTerminal();
    srand(time(NULL));

    getWordFromFile(word);
    if (strlen(word) != 5)
    {
        printf(RED "Error: could not generate word.\n" RESET);
        return 1;
    }

    printf("Guess any 5 letter word to start. \n");

    while(true)
    {
        scanf("%5s", input);
        handleGuess(input, word);
        guesses++;
        if (strcmp(word, input) == 0)
        {
            printf(GREEN "You win in %d %s!\n" RESET, guesses, guesses == 1 ? "guess" : "guesses");
            break;
        }
    }

    system("pause"); // Press any key to exit prompt

    return 0;
}
