/* Lubna Haddad. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Size 12

struct Dictionary // Create AVL Tree
{
    char Word[30];
    char Meaning[80];
    char Synonym[30];
    char Antonym[30];
    int Height;
    struct Dictionary *Left;
    struct Dictionary *Right;
};
struct Hashing // Create Hash Table
{
    char word[30]; // Words are the keys
    char meaning[80];
    char synonym[30];
    char antonym[30];
    struct Hashing *next;
};

struct Hashing *hashTable[Size]; // Create array of linked list

int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
};

int Height(struct Dictionary *ptr)
{
    if(ptr == NULL)
        return -1;
    else
        return (ptr->Height);
};
int Balance(struct Dictionary *T) // Balance the tree after deleting
{
    if (T == NULL)
        return 0;
    return Height(T->Left) - Height(T->Right);
};
/* Rotations */
struct Dictionary *SingleRotateWithLeft(struct Dictionary *N2)
{
    struct Dictionary *N1;

    N1 = N2->Left;
    N2->Left = N1->Right;
    N1->Right = N2;

    N2->Height = Max(Height(N2->Left), Height(N2->Right)) + 1;
    N1->Height = Max(Height(N1->Left), N2->Height) + 1;

    return N1;  /* New root */
};
struct Dictionary *SingleRotateWithRight(struct Dictionary *N1)
{
    struct Dictionary *N2;

    N2 = N1->Right;
    N1->Right = N2->Left;
    N2->Left = N1;

    N1->Height = Max(Height(N1->Left), Height(N1->Right)) + 1;
    N2->Height = Max(Height(N2->Right), N1->Height) + 1;

    return N2;  /* New root */
};
struct Dictionary *DoubleRotateWithLeft(struct Dictionary *N3)
{
    /* Rotate between N1 and N2 */
    N3->Left = SingleRotateWithRight(N3->Left);

    /* Rotate between N3 and N2 */
    return SingleRotateWithLeft(N3);
};
struct Dictionary *DoubleRotateWithRight(struct Dictionary *N1)
{
    /* Rotate between K3 and K2 */
    N1->Right = SingleRotateWithLeft(N1->Right);

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight(N1);
};
struct Dictionary *findWord(char W[], struct Dictionary *T) // search for a word
{
    if(T == NULL)
        return NULL;
    if((strcmp(W, T->Word)) < 0)
        return findWord(W, T->Left);

    else if((strcmp(W, T->Word)) > 0)
        return findWord(W, T->Right);
    else
        return T;
};
void updateDic(struct Dictionary *T) // find a word in the tree and update its info
{
    char word[30];
    int choice;
    printf("Enter the word: ");
    scanf(" %s", word);
    T = findWord(word, T);
    if(T == NULL)
    {
        printf("The word is not found!\n");
        return;
    }
    else
    {
        printf("The word was found!\n");
        printf("\tWord: %s\n\tMeaning: %s\n\tSynonym: %s\n\tAntonym: %s\n", T->Word, T->Meaning, T->Synonym, T->Antonym);
    }
    while(1)
    {
        printf("Select the field to be updated: \n");
        printf("1- Meaning\n");
        printf("2- Synonym\n");
        printf("3- Antonym\n");
        printf("OR click '4' to back to main menu!\n");
        scanf(" %d", &choice);
        switch(choice)
        {
        case 1:
            printf("Enter the new meaning: ");
            scanf(" %80[^\n]", &T->Meaning);
            printf("DONE!\n");
            break;
        case 2:
            printf("Enter the new synonym: ");
            scanf(" %30[^\n]", &T->Synonym);
            printf("DONE!\n");
            break;
        case 3:
            printf("Enter the new antonym: ");
            scanf(" %30[^\n]", &T->Antonym);
            printf("DONE!\n");
            break;
        case 4:
            return;
        }
    }
};
struct Dictionary *findMin(struct Dictionary *T)
{
    if(T == NULL)
        return NULL;
    else if(T->Left == NULL)
        return T;
    else
        return (findMin(T->Left));
};
struct Dictionary *findMax(struct Dictionary *T)
{
    if(T != NULL)
        while(T->Right != NULL)
            T = T->Right;
    return T;
};
struct Dictionary *Insert(char word[], char meaning[], char synonym[], char antonym[],  struct Dictionary *T) // insert from tree
{
    if(T == NULL)
    {
        /* Create and return a one-node tree */
        T = malloc(sizeof(struct Dictionary));
        if(T == NULL)
            printf("System is out of memory!!!");
        else
        {
            strcpy(T->Word, word);
            strcpy(T->Meaning, meaning);
            strcpy(T->Synonym, synonym);
            strcpy(T->Antonym, antonym);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if((strcmp(word, T->Word)) < 0)
    {
        T->Left = Insert(word, meaning, synonym, antonym, T->Left);
        if(Height( T->Left ) - Height( T->Right ) == 2)
            if(strcmp(word, T->Left->Word) < 0 )
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
    }
    else if((strcmp(word, T->Word)) > 0)
    {
        T->Right = Insert(word, meaning, synonym, antonym, T->Right);
        if(Height(T->Right) - Height(T->Left) == 2)
            if(strcmp(word, T->Right->Word) > 0)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    /* Else data is in the tree already; we'll do nothing */
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
};
struct Dictionary *insertFromUser(struct Dictionary *T) // insert a word from user
{
    char word[30];
    if(T == NULL)
    {
        printf("Read the dictionary first!\n");
        return;
    }
    else
    {
        printf("Enter the new word: ");
        scanf(" %s", &word);
        T = malloc(sizeof(struct Dictionary));
        strcpy(T->Word, word);
        printf("Enter the meaning: ");
        scanf(" %80[^\n]", &T->Meaning);
        printf("Enter the synonym: ");
        scanf(" %30[^\n]", &T->Synonym);
        printf("Enter the antonym: ");
        scanf(" %30[^\n]", &T->Antonym);
        T->Height = 0;
        T->Left = T->Right = NULL;
    }
    if((strcmp(word, T->Word)) < 0)
    {
        T->Left = insertFromUser(T->Left);
        if(Height(T->Left) - Height(T->Right) == 2)
            if(strcmp(word, T->Left->Word) < 0 )
                T = SingleRotateWithLeft(T);
            else
                T = DoubleRotateWithLeft(T);
    }
    else if((strcmp(word, T->Word)) > 0)
    {
        T->Right = insertFromUser(T->Right);
        if(Height(T->Right) - Height(T->Left) == 2)
            if(strcmp(word, T->Right->Word) > 0)
                T = SingleRotateWithRight(T);
            else
                T = DoubleRotateWithRight(T);
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    return T;
};
void PrintInOrder(struct Dictionary *T) // print in lexicorder
{
    if(T != NULL)
    {
        PrintInOrder(T->Left);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("Word: %s, Meaning: %s, Synonym: %s, Antonym: %s\n", T->Word, T->Meaning, T->Synonym, T->Antonym);
        PrintInOrder(T->Right);
    }
};
struct Dictionary *ReadDic(struct Dictionary *dic) // Read from file and strtok
{
    char word[30];
    char meaning[80];
    char synonym[30], antonym[30];
    struct Dictionary *ptr = (struct Dictionary *)malloc(sizeof(struct Dictionary));
    ptr = dic;
    FILE *fptr;
    fptr = fopen("Words.txt", "r");
    if(fptr == NULL)
    {
        printf("The file is not found!\n");
    }
    else
    {
        char Line[200];
        while(!feof(fptr))
        {
            fgets(Line, 200, fptr);
            char *token = strtok(Line, ":");
            strcpy(word, token);
            token = strtok(NULL, "/");
            strcpy(meaning, token);
            token = strtok(NULL, "*");
            strcpy(synonym, token);
            token = strtok(NULL, " ");
            strcpy(antonym, token);
            ptr = Insert(word, meaning, synonym, antonym, ptr);
        }
        PrintInOrder(ptr);
    }
    fclose(fptr);
    return ptr;
};
struct Dictionary *MakeEmpty(struct Dictionary *T) // make the tree null
{
    if(T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
};
void ListWord(struct Dictionary *T) // list by giving word from user
{
    char word[30];
    printf("Enter the word: ");
    scanf(" %s", &word);
    T = findWord(word, T);
    if(T == NULL)
    {
        printf("The word is not found!\n");
    }
    else
    {
        printf("\n\tWord: %s, Synonym: %s, Antonym: %s\n", T->Word, T->Synonym, T->Antonym);
    }
};
void  ListByLetter(struct Dictionary *T, char L) // List by entering specific letter
{
    if(T != NULL)
    {
        ListByLetter(T->Left, L);
        if(L == T->Word[0])
        {
            printf("\n\tWord: %s, Meaning: %s, Synonym: %s, Antonym: %s\n", T->Word, T->Meaning, T->Synonym, T->Antonym);
        }
        ListByLetter(T->Right, L);
    }
};
void ListMenu(struct Dictionary *T) // List options
{
    int choice;
    char letter;
    printf("Choose an option: \n");
    printf("1- List words in lexicographic order with their associated data\n");
    printf("2- List the synonym and antonym of a word\n");
    printf("3- List all words that starts with the same letter\n");
    scanf(" %d", &choice);
    if(choice == 1)
        PrintInOrder(T);
    else if(choice == 2)
        ListWord(T);
    else if(choice == 3)
        printf("Enter the letter: ");
    scanf(" %c", &letter);
    ListByLetter(T, letter);
};
struct Dictionary *Delete(char X[], struct Dictionary *T) // Delete from tree and balance
{
    struct Dictionary *TR = malloc(sizeof(struct Dictionary));
    if(T == NULL)
    {
        printf("The word is not found!\n");
        return NULL;
    }
    else if(strcmp(X, T->Word) < 0)
    {
        T->Left = Delete(X, T->Left);
    }
    else if(strcmp(X, T->Word) > 0)
    {
        T->Left = Delete(X, T->Right);
    }
    else
    {
        if(T->Left && T->Right)
        {
            TR = findMin(T->Right);
            strcpy(T->Word, TR->Word);
            T->Right = Delete(T->Word, T->Right);
        }
        else
        {
            TR = T;
            if(T->Left == NULL)
                T = T->Right;
            else if(T->Right == NULL)
                T = T->Left;
            free(TR);
        }
    }
    return T;
}
void DeleteMenu(struct Dictionary *T) // Delete options
{
    int choice;
    char letter;
    char word[30];
    printf("Choose an option: \n");
    printf("1- Delete a word\n");
    printf("2- Delete all words that start with a specific letter\n");
    scanf(" %d", &choice);
    if(choice == 1)
        printf("Enter the word: ");
    scanf(" %s", &word);
    T = Delete(word, T);
////else if(choice == 2)
//      printf("Enter the letter: ");
//      scanf(" %c", &letter);
};
void writeOnFile(struct Dictionary *T)
{
    FILE *out;
    out = fopen("Dictionary.data", "w");
    printToFile(T, out);
    fclose(out);
};
void printToFile(struct Dictionary *T, FILE *out)
{
    if(T != NULL)
    {
        printToFile(T->Left, out);
        fprintf(out, "%s: %s / %s * %s", T->Word, T->Meaning, T->Synonym, T->Antonym);
        printToFile(T->Right, out);
    }
};
/* Hashing Functions */
void makeTableEmpty()
{
    for(int i = 0; i < Size; i++)
    {
        hashTable[i] = NULL;
    }
};
int Hash(char *word) // give the word a value
{
    int length = strnlen(word, 30);
    int hash_index = 0;
    for(int i = 0; i < length; i++)
    {
        hash_index += word[i];
        hash_index = (hash_index * word[i]) % Size;
    }
    return hash_index;
};
void printTable() // print on screen
{
    for(int i = 0; i < Size; i++)
    {
        if(hashTable[i] == NULL)
        {
            printf("\t%d\tEMPTY\n", i);
        }
        else
        {
            printf("\t%d", i);
            struct Hashing *h = hashTable[i];
            while (h != NULL)
            {
                printf(" --> {%s:%s/%s* %s}", h->word, h->meaning, h->synonym, h->antonym);
                h = h->next;
            }
            printf("\n");
        }
    }
};
int insertToTable(struct Hashing *w)
{
    if (w == NULL) return 0;
    int index = Hash(w->word);
    w->next = hashTable[index];
    hashTable[index] = w;
    return 1;
};
void *searchInTable(char *word)
{
    int index = Hash(word);
    struct Hashing *h = hashTable[index];
    if (h != NULL && strncmp(h->word, word, Size) != 0)
    {
        h = h->next;
    }
    if(h == NULL)
    {
        printf("The word was not found!\n");
    }
    else
    {
        printf("The word is found!\n");
        printf("\n\tWord: %s, Meaning: %s, Synonym: %s, Antonym: %s\n", h->word, h->meaning, h->synonym, h->antonym);
    }
};
struct Hashing *DeleteFromTable(char *word)
{
    int index = Hash(word);
    struct Hashing *h = hashTable[index];
    struct Hashing *pre = NULL;
    if (h != NULL && strncmp(h->word, word, Size) != 0)
    {
        pre = h;
        h = h->next;
    }
    if (h == 0)
    {
        printf("The word does not exist or was deleted!\n");
        return NULL;
    }
    if (pre == NULL)  // delete head
    {
        hashTable[index] = h->next;
    }
    else
    {
        pre->next = h->next;
    }
    return h;
};
void ReadHashData(struct Hashing *H) // read from file and insert to hash table
{
    char word[30];
    char meaning[80];
    char synonym[30], antonym[30];
    FILE *fptr;
    fptr = fopen("Dictionary.data", "r");
    if(fptr == NULL)
    {
        printf("The file is not found!\n");
    }
    else
    {
        char Line[200];
        while(!feof(fptr))
        {
            fgets(Line, 200, fptr);
            char *token = strtok(Line, ":");
            strcpy(word, token);
            token = strtok(NULL, "/");
            strcpy(meaning, token);
            token = strtok(NULL, "*");
            strcpy(synonym, token);
            token = strtok(NULL, " ");
            strcpy(antonym, token);
            struct Hashing *h = malloc(sizeof(struct Hashing));
            strcpy(h->word, word);
            strcpy(h->meaning, meaning);
            strcpy(h->synonym, synonym);
            strcpy(h->antonym, antonym);
            insertToTable(h);
        }
    }
    fclose(fptr);
};
void HashMenu()
{
    makeTableEmpty();
    struct Hashing *H = (struct Hashing *)malloc(sizeof(struct Hashing));
    ReadHashData(H);
    char word[30];
    char choice;
    do
    {
        system("cls");
        printf("\t\t\t\t\t\tHASH TABLE\t\n");
        printf("Choose an option: \n");
        printf("1- Print hashed table\n");
        printf("2- Print the table size\n");
        printf("3- Print the used hash function\n");
        printf("4- Insert a new record\n");
        printf("5- Search for a word\n");
        printf("6- Delete a specific record\n");
        printf("7- Save the table back to file\n");
        printf("8- Back to main menu\n");
        scanf(" %c", &choice);
        switch(choice)
        {
        case '1':
            printTable();
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '2':
            printf("Table size is: %d\n", Size);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '3':
            printf("h(x) = x mod size\n");
            printf("The hash method used is Separate Chaining\n");
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '5':
            printf("Enter the word: ");
            scanf(" %s", word);
            searchInTable(&word);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '6':
            printf("Enter the word: ");
            scanf(" %s", word);
            DeleteFromTable(&word);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '7':
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '8':
            return;
        default:
            printf("\nINVALID OPTION!!!\n");
            printf("Enter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        }
    }
    while(1);
};
void MainMenu()
{
    struct Dictionary *dic = (struct Dictionary*)malloc(sizeof(struct Dictionary));
    dic = NULL;
    dic = MakeEmpty(dic);
    char word[30];
    char option;
    do
    {
        printf("\t\t\t\t\t\tDICTIONARY SYSTEM\t\n");
        printf("Choose an option: \n");
        printf("1- READ AND CREATE - Read words from dictionary and create tree\n");
        printf("2- INSERT          - Insert new word with its information\n");
        printf("3- UPDATE          - Find a word and update its information\n");
        printf("4- LIST            - Three Options\n");
        printf("5- DELETE          - Two Options\n");
        printf("6- PRINT TO FILE   - Print to file (dictionary.data)\n");
        printf("7- CREATE HASH TABLE\n");
        printf("8- EXIT            - Exit and save to dictionary\n");
        scanf(" %c", &option);
        switch (option)
        {
        case '1':
            dic = ReadDic(dic);
            printf("\n\t\tThe dictionary was read successfully!\n");
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '2':
            dic = insertFromUser(dic);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '3':
            updateDic(dic);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '4':
            ListMenu(dic);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '5':
            DeleteMenu(dic);
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '6':
            writeOnFile(dic);
            printf("\n\tThe data was saved successfully!\n");
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '7':
            HashMenu();
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        case '8':
            system("cls");
            printf("\t\t\t\t\t\tTHANK YOU\n");
            return;
            break;
        default:
            printf("\nINVALID OPTION!!!\n");
            printf("\nEnter anything to continue\n");
            scanf("%s");
            system("cls");
            break;
        }
    }
    while(1);
};
int main()
{
    MainMenu();
    return 0;
};
