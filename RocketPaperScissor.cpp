
// RocketPaperScissor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

enum enGameChoice { stone = 1, Papper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
    short RoundNumber = 0;
    enGameChoice Player1Choices;
    enGameChoice Computer2Choices;
    enWinner Winner;
    string WinnerName;
};

// property of game result.
struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short Computer2WinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";

};

int RandomNumberInRange(int from, int to) {
    int RandomNumber = rand() % (to - from + 1) + from;
    return RandomNumber;
}
enGameChoice ReadPlayer1Choice() {
    short Choice = 1;
    do {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice >3);
    return (enGameChoice)Choice;

}

enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumberInRange(1, 3);
}

string ChoiceName(enGameChoice Choice) {
    string arrWinnerName[3] = { "Stone"  , "Scissors" , "Papper" };
    return arrWinnerName[Choice - 1];

}

void SetWinnerScreenColor(enWinner Winner) {
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo) {

    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choices) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.Computer2Choices) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
    cout << "__________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.Winner);
}

string WinnerName(enWinner Winner) {
    string arrWinnerName[3] = { "Player1"  , "Computer" , "No Winner" };
    return arrWinnerName[Winner - 1];

}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

    if (RoundInfo.Player1Choices == RoundInfo.Computer2Choices) {
        return enWinner::Draw;
    }

    switch (RoundInfo.Player1Choices)
    {
    case enGameChoice::stone:
        if (RoundInfo.Computer2Choices == enGameChoice::Papper) {
            return enWinner::Computer;

        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.Computer2Choices == enGameChoice::stone) {
            return enWinner::Computer;

        }
        break;
    }
    return enWinner::Player1;
}


enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {
    if (Player1WinTimes > ComputerWinTimes) {
        return enWinner::Player1;
    }
    else if (ComputerWinTimes > Player1WinTimes) {
        return enWinner::Computer;
    }
    else return enWinner::Draw;
}



stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short Computer2WinTimes, short DrawTimes) {

    stGameResults GameResults;
    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = Computer2WinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, Computer2WinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;


}

stGameResults PlayGame(short HowManyRounds) {

    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, Computer2WinTimes = 0, DrawTimes = 0;
    for (short GameRound = 0; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choices = ReadPlayer1Choice();
        RoundInfo.Computer2Choices = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        // increase determination times
        if (RoundInfo.Winner == enWinner::Player1) {
            Player1WinTimes++;
        }
        else if (RoundInfo.Winner == enWinner::Computer) {
            Computer2WinTimes++;
        }
        else {
            DrawTimes++;
        }

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, Computer2WinTimes, DrawTimes);



};

void ResetScreen() {
    system("cls");
    system("color 0F");
}

short ReadHowManyRounds() {
    short GameRounds = 1;
    do {
        cout << "How many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}
string  Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}


void ShowFinalGameResults(stGameResults GameResults) {
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << GameResults.Computer2WinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetWinnerScreenColor(GameResults.GameWinner);

}

void startGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGameResults GameResult = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResult);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
};




int main()
{

    startGame();

    std::cout << "Hello World!\n";
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
