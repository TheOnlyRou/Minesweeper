#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <math.h>

typedef struct
{
    char Name[50];
    int Difficult;
    long Score;
}Player;

typedef struct
{
    int Hours;
    int Minutes;
    int Seconds;
}Time;

typedef struct
{
    int Day;
    int Month;
    int Year;
}Date;

typedef struct
{
    int Difficulty;
    char Name[50];
    Time TimeTaken;
    Date SaveDate;
}SavedGame;



SYSTEMTIME DateTime;
char GameBoard[14][14];
int MinesBoard[14][14];
Player PlayersArray[100];
SavedGame SavedGames[100];
int LastPlayer=0,LastGame=0,Difficulty,Lose=0,Win=0;

int CheckInt(char *n)
{
    if(isdigit(n)!=1 || (n>47&&n<58))
        return 1;
    else
        return 0;
}

void center(const char *s, int width)
{
    int length = strlen(s);
    int i;
    for (i=0; i<=(width-length)/2; i++)
    {
        fputs(" ", stdout);
    }
    fputs(s,stdout);
    i += length;
    for (; i<=width; i++)
    {
        fputs(" ", stdout);
    }
}

void ShowAdjMines(int row, int col)
{
    
}

void QuickMaffs(int row, int col)
{
    AdjMines=0;
    if(MinesBoard[row][col]==1)
        Lose=1;
    if(MinesBoard[row+1][col]==1)
        AdjMines++;
    if(MinesBoard[row][col+1]==1)
        AdjMines++;  
    if(MinesBoard[row-1][col]==1)
        AdjMines++;
    if(MinesBoard[row][col-1]==1)
        AdjMines++;
    if(MinesBoard[row+1][col+1]==1)
        AdjMines++;
    if(MinesBoard[row+1][col-1]==1)
        AdjMines++;
    if(MinesBoard[row-1][col+1]==1)
        AdjMines++;
    if(MinesBoard[row-1][col-1]==1)
        AdjMines++;
        
    if(AdjMines==0)
        ShowAdjMines(row,col);
    else
        GameBoard[row][col]=AdjMines;
}

void CreateMines();
{
    int i,j,Mines,MineFactor,randrow,randcol;
    if(Difficulty==1)
        MineFactor=64;
    else if(Difficulty==2)
        MineFactor=100;
    else if(Difficulty==3)
        MineFactor=144;
    else if(Difficulty==4)
        MineFactor=196;
    Mines=1+(MineFactor/10);
    srand(time(0));
    switch(Difficulty)
        {
            case 1:
                while(Mines>0)
                {
                    randrow=rand()%8;
                    randcol=rand()%8;
                    MinesBoard[randrow][randcol]=1;
                    Mines--;
                }
                break;
            case 2:
                while(Mines>0)
                {
                    randrow=rand()%10;
                    randcol=rand()%10;
                    MinesBoard[randrow][randcol]=1;
                    Mines--;
                }
                break;
            case 3:
                while(Mines>0)
                {
                    randrow=rand()%12;
                    randcol=rand()%12;
                    MinesBoard[randrow][randcol]=1;
                    Mines--;
                }
                break;
            case 4:
                while(Mines>0)
                {
                    randrow=rand()%14;
                    randcol=rand()%14;
                    MinesBoard[randrow][randcol]=1;
                    Mines--;
                }
                break;                
        }
}

void ChooseDifficulty()
{
    do{
        printf("Please pick one of the following difficulties:\n\n");
            printf(" 1- Easy (8x8)\n");
            printf(" 2- Normal (10x10)\n");
            printf(" 3- Hard (12x12)\n");
            printf(" 4- Master (14x14)\n");
        scanf("%d",&Difficulty);
        if(Difficulty>4 || Difficulty<1 || CheckInt(Difficulty)==0)
            printf("Please enter an integer (1-4) that corresponds to your difficulty of choice!\n");
    }while(Difficulty>4 || Difficulty<1 || CheckInt(Difficulty)==0);
}

void MinesBoardBuild()
{
    int i=0,j=0;
    switch(Difficulty)
        {
        case 1:
                for(i=0;i<8;i++)
                {
                    for(j=0;j<8;j++)
                    {
                        MinesBoard[i][j] = 0;
                    }
                }
                break;
        case 2:
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                        MinesBoard[i][j] = 0;
                    }
                }
                break;
        case 3:
                for(i=0;i<12;i++)
                {
                    for(j=0;j<12;j++)
                    {
                        MinesBoard[i][j] = 0;
                    }
                }
                break;
        case 4:
                for(i=0;i<14;i++)
                {
                    for(j=0;j<14;j++)
                    {
                        MinesBoard[i][j] = 0;
                    }
                }
                break;
    }

}

void BoardBuild()
{
    int i=0,j=0;
    switch(Difficulty)
    {
        case 1:
                for(i=0;i<8;i++)
                {
                    for(j=0;j<8;j++)
                    {
                        GameBoard[i][j] = 'X';
                    }
                }
                break;
        case 2:
                for(i=0;i<10;i++)
                {
                    for(j=0;j<10;j++)
                    {
                       GameBoard[i][j] = 'X';
                    }
                }
                break;
        case 3:
                for(i=0;i<12;i++)
                {
                    for(j=0;j<12;j++)
                    {
                       GameBoard[i][j] = 'X';
                    }
                }
                break;
        case 4:
                for(i=0;i<14;i++)
                {
                    for(j=0;j<14;j++)
                    {
                        GameBoard[i][j] = 'X';
                    }
                }
                break;
    }
}

void PrintBoard()
{
    int i,j;
    switch(Difficulty)
        {
        case 1:
                printf("   0  1  2  3  4  5  6  7\n");
                for(i=0;i<8;i++)
                {
                    printf("%-2d ",i);
                    for(j=0;j<8;j++)
                    {
                        printf("%c  ",GameBoard[i][j]);
                    }
                    printf("\n");
                }
                break;
        case 2:
                printf("   0  1  2  3  4  5  6  7  8  9\n");
                for(i=0;i<10;i++)
                {
                    printf("%-2d ",i);
                    for(j=0;j<10;j++)
                    {
                        printf("%c ",GameBoard[i][j]);
                    }
                    printf("\n");
                }
                break;
        case 3:
                printf("   0  1  2  3  4  5  6  7  8  9  10 11\n");
                for(i=0;i<12;i++)
                {
                    printf("%-2d ",i);
                    for(j=0;j<12;j++)
                    {
                        printf("%c ",GameBoard[i][j]);
                    }
                    printf("\n");
                }
                break;
        case 4:
                printf("   0  1  2  3  4  5  6  7  8  9  10 11 12 13\n");
                for(i=0;i<14;i++)
                {
                    printf("%-2d ",i);
                    for(j=0;j<14;j++)
                    {
                        printf("%c  ",GameBoard[i][j]);
                    }
                    printf("\n");
                }
                break;
    }
}

void WelcomeMessage()
{
    system("cls");
    char Hi[50]="Welcome to Minesweeper";
    center(Hi, 100);
    printf("\n\nMinesweeper is a single-player puzzle video game. The objective of the game is to clear a rectangular board\ncontaining hidden \"mines\" or bombs without detonating any of them, with help from clues about the number of\nneighboring mines in each field. The game originates from the 1960s, and has been written for many computing\nplatforms in use today. It has many variations and offshoots.\n");
    printf("\n\nPress Any Key to Continue\n");
    getch();
}

void CreatePlayer()
{
    system("cls");
    Player temp;
    int i=0;
    int checkid=1;
    printf("Please enter the surname:\n");
    fflush(stdin);
    fgets(temp.Name,sizeof(temp.Name),stdin);
    temp.Name[strlen(temp.Name) - 1] = 0;
    strcpy(PlayersArray[LastPlayer-1].Name,temp.Name);
}

void Start()
{
    system("cls");
    SavedGame New;
    int Moves=0,choice,openrow,opencol,markrow,markcol,Flags=0,QMarks=0;
    char YesNo;
    clock_t StartTimer,EndTimer;
    double TimePassed,TimeTaken;
    GetSystemTime(&DateTime);
    New.SaveDate.Day=DateTime.wDay;
    New.SaveDate.Month=DateTime.wMonth;
    New.SaveDate.Year=DateTime.wYear;
    StartTimer=clock();
    while(Win==0 && Lose==0)
    {
        EndTimer=clock()-StartTimer;
        TimePassed=((double)EndTimer)/CLOCKS_PER_SEC;
        printf("\nTime Taken: %.2f \t\t\t\t\t Number of Moves: %d\n\n\n",TimePassed,Moves);
        PrintBoard();
        printf("\n\nActions:\n");
        printf("1- Open a cell \t 2- Mark a cell \t 3- Save \t 4- Exit to Main Menu\n\n");
        do
        {
            scanf("%d",choice);
            if(choice>4 || choice<1 || CheckInt(choice)==0)
                printf("Please enter an integer (1-3) that corresponds to your action of choice!");
        }while(choice>4 || choice<1 || CheckInt(choice)==0);
        switch(choice)
        {
            case 1:
                    printf("Please enter the order of the cell you want to open\nRows first, columns second (ex: 1 enter 4 enter)\n");
                    scanf("%d",&openrow);
                    scanf("%d",&opencol);
                    if(Moves==0)
                        CreateMines();
                    QuickMaffs(openrow,opencol);
                    CheckWin();
                    break;
            case 2:
                    printf("Please enter the order of the cell you want to open\nRows first, columns second (ex: 1 enter 4 enter)\n");
                    scanf("%d",&markrow);
                    scanf("%d",&markcol);
                    MarkCell();
                    break;
            case 3:
                    SaveGame();
                    break;
            case 4:
                    printf("Are you sure? All unsaved changes will be lost! (Y/N)");
                    do{
                    scanf(" %c",&YesNo);
                    if(YesNo!= 'Y' && YesNo!='N' && YesNo!= 'y' && YesNo!='n')
                    printf("Please enter Y or N\n");
                    }while(YesNo!= 'Y' && YesNo!='N' && YesNo!= 'y' && YesNo!='n');
                    if(YesNo=='n' || YesNo== 'N')
                        break;
                    else if(YesNo=='y' || YesNo== 'Y')
                        MainMenu();
                    break;
        }
        Moves++;
    }
}

void SetupGame()
{
    CreatePlayer();
    ChooseDifficulty();
    MinesBoardBuild();
    BoardBuild();
    Start();
    MainMenu();
}
void LoadGame()
{
    int i=0;
    printf("# \t Player Name \t Date ");
    for(i=0;i<LastGame-1;i++)
    printf("%d\t %-20s \t %d/%d/%d\n",i+1,SavedGames[i].Name,SavedGames[i].SaveDate.Day,SavedGames[i].SaveDate.Month,SavedGames[i].SaveDate.Year);
    printf("\n\nPress Any Key to Continue\n");
    getch();
}
void Howtoplay()
{
    system("cls");
    center("How To Play?!",100);
    printf("\n\n\n");
    printf("Each Minesweeper game starts out with a grid of unmarked squares. After clicking one of these squares,\nsome of the squares will disappear, some will remain blank, and some will have numbers on them.It's\nyour job to use the numbers to figure out which of the blank squares have mines and which are safe to\nclick.");
    printf("\n\nPress Any Key to Continue\n");
    getch();
    MainMenu();
}
void Leaderboards()
{
    system("cls");
    int i=0;
    center("Leaderboards",100);
    printf("\n\n");
    printf("Rank \t Name \t\t\t Score\n");
    for(i=0;i<LastPlayer-1;i++)
    printf("%d\t %-20s \t %ld\n",i+1,PlayersArray[i].Name,PlayersArray[i].Score);
    printf("\n\nPress Any Key to Continue\n");
    getch();
    MainMenu();
}


void MainMenu()
{
    system("cls");
    int input1;
        printf("Date: %d/%d/%d ",DateTime.wDay,DateTime.wMonth,DateTime.wYear);
    if((DateTime.wHour+2)<12)
        printf("Current Time: %d:%d AM \n \n",(DateTime.wHour+2),DateTime.wMinute);
    else if((DateTime.wHour+2)==12)
        printf("Current Time: %d:%d PM \n \n",(DateTime.wHour+2),DateTime.wMinute);
    else if((DateTime.wHour+2)>24)
        printf("Current Time: %d:%d AM \n \n",(24-DateTime.wHour),DateTime.wMinute);
    else
        printf("Current Time: %d:%d PM \n \n",DateTime.wHour-10,DateTime.wMinute);

    printf("Please choose an action (1-5): \n");
    printf(" 1- Start a new game\n");
    printf(" 2- Load a saved game\n");
    printf(" 3- How to Play\n");
    printf(" 4- Leaderboards\n");
    printf(" 5- Exit\n");

    do{
        scanf("%d",&input1);
        if((input1<1) || (input1>5) || (CheckInt(input1)==0))
    {
    printf("%d",input1);
    printf("Please enter an integer (1-5) that corresponds to your action of choice!\n");
    }
    else{
    switch(input1)
    {
        case 1:
            SetupGame(); /* Calls a function that manages books */
            break;
        case 2:
            LoadGame(); /* Calls a function that manages members */
            break;
        case 3:
            Howtoplay(); /* Calls a function that manages borrowings */
            break;
        case 4:
            Leaderboards(); /* Calls a function that manages administrative actions */
            break;
        case 5:
            exit(0);
			break;
    }}
    }while(input1<1 || input1>5 || CheckInt(input1)==0);
}

int main()
{
    int i,flag=0,c1=0,c2=0;
    FILE *f,*j;
    GetSystemTime(&DateTime);
    for(i=0;i>100;i++)
        PlayersArray[i].Score=0;
    for(i=0;i>100;i++)
        SavedGames[i].Difficulty=0;

    f=fopen("Leaderboards.txt", "r");
    if (f != NULL)
    {
        while(flag==0){
         fscanf(f, "%d,%[^,],%ld",&PlayersArray[c1].Difficult,PlayersArray[c1].Name,&PlayersArray[c1].Score);
         fscanf(f, "\n");
         if(PlayersArray[c1].Score==0)
            flag=1;
         c1++;
         LastPlayer++;
        }
         fclose(f);
    } else
        printf("Error opening the file!\n");
    flag=0;
    j=fopen("SavedGames.txt", "r");

    if (j != NULL)
    {
        while(flag==0)
        {
        fscanf(j,"%d,%[^,],%d,%d,%d,%d,%d,%d\n",&SavedGames[c2].Difficulty,SavedGames[c2].Name,&SavedGames[c2].TimeTaken.Hours,&SavedGames[c2].TimeTaken.Minutes,&SavedGames[c2].TimeTaken.Seconds,&SavedGames[c2].SaveDate.Day,&SavedGames[c2].SaveDate.Month,&SavedGames[c2].SaveDate.Year);
        if(SavedGames[c2].Difficulty==0)
            flag=1;
        else
        {
            switch(SavedGames[c2].Difficulty)
            {
                case 1:
                    for(i=0;i<8;i++)
                    {
                            fscanf(j,"%c %c %c %c %c %c %c %c\n",GameBoard[i][0],GameBoard[i][1],GameBoard[i][2],GameBoard[i][3],GameBoard[i][4],GameBoard[i][5],GameBoard[i][6],GameBoard[i][7]);
                            fscanf(j,"%d %d %d %d %d %d %d %d\n",&MinesBoard[i][0],&MinesBoard[i][1],&MinesBoard[i][2],&MinesBoard[i][3],&MinesBoard[i][4],&MinesBoard[i][5],&MinesBoard[i][6],&MinesBoard[i][7]);
                    }
                    break;
                case 2:
                    for(i=0;i<10;i++)
                    {
                            fscanf(j,"%c %c %c %c %c %c %c %c %c %c\n",GameBoard[i][0],GameBoard[i][1],GameBoard[i][2],GameBoard[i][3],GameBoard[i][4],GameBoard[i][5],GameBoard[i][6],GameBoard[i][7],GameBoard[i][8],GameBoard[i][9]);
                            fscanf(j,"%d %d %d %d %d %d %d %d %d %d\n",&MinesBoard[i][0],&MinesBoard[i][1],&MinesBoard[i][2],&MinesBoard[i][3],&MinesBoard[i][4],&MinesBoard[i][5],&MinesBoard[i][6],&MinesBoard[i][7],&MinesBoard[i][8],&MinesBoard[i][9]);
                    }
                    break;
                case 3:
                    for(i=0;i<12;i++)
                    {
                            fscanf(j,"%c %c %c %c %c %c %c %c %c %c %c %c\n",GameBoard[i][0],GameBoard[i][1],GameBoard[i][2],GameBoard[i][3],GameBoard[i][4],GameBoard[i][5],GameBoard[i][6],GameBoard[i][7],GameBoard[i][8],GameBoard[i][9],GameBoard[i][10],GameBoard[i][11]);
                            fscanf(j,"%d %d %d %d %d %d %d %d %d %d %d %d\n",&MinesBoard[i][0],&MinesBoard[i][1],&MinesBoard[i][2],&MinesBoard[i][3],&MinesBoard[i][4],&MinesBoard[i][5],&MinesBoard[i][6],&MinesBoard[i][7],&MinesBoard[i][8],&MinesBoard[i][9],&MinesBoard[i][10],&MinesBoard[i][11]);
                    }
                    break;
                case 4:
                    for(i=0;i<14;i++)
                    {
                            fscanf(j,"%c %c %c %c %c %c %c %c %c %c %c %c\n",GameBoard[i][0],GameBoard[i][1],GameBoard[i][2],GameBoard[i][3],GameBoard[i][4],GameBoard[i][5],GameBoard[i][6],GameBoard[i][7],GameBoard[i][8],GameBoard[i][9],GameBoard[i][10],GameBoard[i][11],GameBoard[i][12],GameBoard[i][13]);
                            fscanf(j,"%d %d %d %d %d %d %d %d %d %d %d %d\n",&MinesBoard[i][0],&MinesBoard[i][1],&MinesBoard[i][2],&MinesBoard[i][3],&MinesBoard[i][4],&MinesBoard[i][5],&MinesBoard[i][6],&MinesBoard[i][7],&MinesBoard[i][8],&MinesBoard[i][9],&MinesBoard[i][10],&MinesBoard[i][11],&MinesBoard[i][12],&MinesBoard[i][13]);
                    }
                    break;
            }
            c2++;
            LastGame++;
        }
        }
         fclose(j);
    } else
        printf("Error opening the file!\n");

    WelcomeMessage();
    MainMenu();
}
