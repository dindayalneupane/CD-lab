#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULES 20
#define MAX_PROD 10
#define MAX_SYMBOLS 20

// Structure for Grammar Rule
typedef struct
{
    char head;
    char body[MAX_PROD][MAX_SYMBOLS];
    int prodCount;
} GrammarRule;

GrammarRule grammar[MAX_RULES];
int ruleCount = 0;

// FIRST and FOLLOW sets
char firstSets[26][MAX_SYMBOLS];
char followSets[26][MAX_SYMBOLS];

// Check whether symbol is Non-terminal
bool isNonTerminal(char ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

// Add symbol to set
bool addToSet(char set[], char ch)
{
    for (int i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == ch)
            return false;
    }

    int len = strlen(set);
    set[len] = ch;
    set[len + 1] = '\0';
    return true;
}

// Merge two sets
bool mergeSets(char dest[], char src[], bool ignoreEpsilon)
{
    bool changed = false;

    for (int i = 0; src[i] != '\0'; i++)
    {
        if (ignoreEpsilon && src[i] == 'e')
            continue;

        if (addToSet(dest, src[i]))
            changed = true;
    }

    return changed;
}

// Check epsilon
bool hasEpsilon(char set[])
{
    for (int i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == 'e')
            return true;
    }

    return false;
}

// ---------------- FIRST ----------------

void computeFirst()
{
    bool changed = true;

    while (changed)
    {
        changed = false;

        for (int i = 0; i < ruleCount; i++)
        {
            int headIndex = grammar[i].head - 'A';

            for (int j = 0; j < grammar[i].prodCount; j++)
            {
                char *prod = grammar[i].body[j];

                if (prod[0] == 'e')
                {
                    if (addToSet(firstSets[headIndex], 'e'))
                        changed = true;
                    continue;
                }

                bool allNullable = true;

                for (int k = 0; prod[k] != '\0'; k++)
                {
                    char symbol = prod[k];

                    if (!isNonTerminal(symbol))
                    {
                        if (addToSet(firstSets[headIndex], symbol))
                            changed = true;

                        allNullable = false;
                        break;
                    }
                    else
                    {
                        int idx = symbol - 'A';

                        if (mergeSets(firstSets[headIndex], firstSets[idx], true))
                            changed = true;

                        if (!hasEpsilon(firstSets[idx]))
                        {
                            allNullable = false;
                            break;
                        }
                    }
                }

                if (allNullable)
                {
                    if (addToSet(firstSets[headIndex], 'e'))
                        changed = true;
                }
            }
        }
    }
}

// ---------------- FOLLOW ----------------

void computeFollow(char startSymbol)
{
    addToSet(followSets[startSymbol - 'A'], '$');

    bool changed = true;

    while (changed)
    {
        changed = false;

        for (int i = 0; i < ruleCount; i++)
        {
            int headIndex = grammar[i].head - 'A';

            for (int j = 0; j < grammar[i].prodCount; j++)
            {
                char *prod = grammar[i].body[j];

                for (int k = 0; prod[k] != '\0'; k++)
                {
                    char current = prod[k];

                    if (!isNonTerminal(current))
                        continue;

                    int curIndex = current - 'A';

                    bool nullable = true;

                    for (int n = k + 1; prod[n] != '\0'; n++)
                    {
                        char next = prod[n];

                        if (!isNonTerminal(next))
                        {
                            if (addToSet(followSets[curIndex], next))
                                changed = true;

                            nullable = false;
                            break;
                        }
                        else
                        {
                            int nextIndex = next - 'A';

                            if (mergeSets(followSets[curIndex],
                                          firstSets[nextIndex], true))
                                changed = true;

                            if (!hasEpsilon(firstSets[nextIndex]))
                            {
                                nullable = false;
                                break;
                            }
                        }
                    }

                    if (nullable)
                    {
                        if (mergeSets(followSets[curIndex],
                                      followSets[headIndex], false))
                            changed = true;
                    }
                }
            }
        }
    }
}

// ---------------- MAIN ----------------

int main()
{
    // Initialize
    for (int i = 0; i < 26; i++)
    {
        firstSets[i][0] = '\0';
        followSets[i][0] = '\0';
    }

    // Grammar
    // E -> TA
    grammar[ruleCount].head = 'E';
    strcpy(grammar[ruleCount].body[0], "TA");
    grammar[ruleCount].prodCount = 1;
    ruleCount++;


    // A -> +TA | e
    grammar[ruleCount].head = 'A';
    strcpy(grammar[ruleCount].body[0], "+TA");
    strcpy(grammar[ruleCount].body[1], "e");
    grammar[ruleCount].prodCount = 2;
    ruleCount++;


    // T -> FB
    grammar[ruleCount].head = 'T';
    strcpy(grammar[ruleCount].body[0], "FB");
    grammar[ruleCount].prodCount = 1;
    ruleCount++;


    // B -> *FB | e
    grammar[ruleCount].head = 'B';
    strcpy(grammar[ruleCount].body[0], "*FB");
    strcpy(grammar[ruleCount].body[1], "e");
    grammar[ruleCount].prodCount = 2;
    ruleCount++;


    // F -> (E) | i
    grammar[ruleCount].head = 'F';
    strcpy(grammar[ruleCount].body[0], "(E)");
    strcpy(grammar[ruleCount].body[1], "i");
    grammar[ruleCount].prodCount = 2;
    ruleCount++;

    computeFirst();
    computeFollow('E');

    printf("========== FIRST SETS ==========\n\n");

    for (int i = 0; i < ruleCount; i++)
    {
        char head = grammar[i].head;

        printf("FIRST(%c) = { ", head);

        char *set = firstSets[head - 'A'];

        for (int j = 0; set[j] != '\0'; j++)
        {
            printf("%c", set[j]);

            if (set[j + 1] != '\0')
                printf(", ");
        }

        printf(" }\n");
    }

    printf("\n========== FOLLOW SETS ==========\n\n");

    for (int i = 0; i < ruleCount; i++)
    {
        char head = grammar[i].head;

        printf("FOLLOW(%c) = { ", head);

        char *set = followSets[head - 'A'];

        for (int j = 0; set[j] != '\0'; j++)
        {
            printf("%c", set[j]);

            if (set[j + 1] != '\0')
                printf(", ");
        }

        printf(" }\n");
    }

    return 0;
}