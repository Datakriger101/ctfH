/*
 * This is the first version of the kinda finished game, v1 if you want. 
 *
 */

#include <iomanip>
#include <iostream>
//#include "moveFunc2028.h"   // Declaration, maybe later for better overview.
#include <vector>
#include <cstdlib>      // for rand() func
#include <fstream>      // File access shit

/*
 *  global var
 */


const int MAXCHAR = 200;

/*
    Class
*/

class Game
{
    private:
        std::vector<int> b;
        std::string name;
        bool lost;
        bool win;

    public:
        // void readFile();
        void startup();
        void displayName();
        void displayStatus();
        void displayBoard();
        void playGame();

        void moveMenu();
        int newRandNumber();
        void removeNumber(int nr);

        bool checkValidChar(char t);
        bool checkLoss();
        bool checkNoMoves(int nr0, int nr1, int nr2, int nr3);
        bool checkWin();

        //Better way to do this?
        bool moveUp();
        bool moveLeft();
        bool moveDown();
        bool moveRight();

        bool move(int nr0, int nr1, int nr2, int nr3);

        void toFile(std::ofstream & out);

        Game(); //constructor to make to board
        Game(std::ifstream & in);
};

/*
    Decalation of Functions
*/

void menu();
void new_game();
void play_game();
void show_games();

void writeToFile();
bool readFromFile();

bool fileExists(const std::string &name);

std::vector<Game *> gGames;

/*
 *  other funcs
 */

    char r_char(std::string txt);
    std::string r_string(std::string txt);
    int r_int(std::string txt);
    int r_int_bet(std::string txt, int min, int max);
    bool y_or_no(std::string txt);

/*
 *  The Game
 */

int main()
{
    char input;

    bool readFile = readFromFile();

    menu();
    input = r_char("What operation do you want to execute");

    while (input != 'Q')
    {
        switch (input)
        {
        case 'N' : new_game();      break;
        case 'P' : play_game();     break;
        case 'S' : show_games();    break;
        }

        menu();

        input = r_char("What operation do you want to execute");
    }
            std::cout << "\nokei\n";

    writeToFile();

}

bool Game::checkWin(){
    for(int i = 0; i < 16; i++){
        if(b[i] == 2048)
        {
            return true;
        }
    }
    
    return false;
}

Game::Game()
{
    this->name = r_string("What is the name of the game");
    this->lost = false;

    for (int i = 0; i < 16; i++) b.push_back(0);
    
}

Game::Game(std::ifstream & in)
{
    int numb;

    in >> numb;
    if(numb == 1){
        lost = true;
        win = false;
    } else if(numb == 2) 
    {
        win = true;
        lost = false;
    }else 
    {
        win = false;
        lost = false;
    }

    for(int i = 0; i < 16; i++){
        in >> numb;
        b.push_back(numb);
    }
    in.ignore();
    getline(in, name);
}

/*
    Move functions, fuck dette kan ta tid. 
*/

void Game::toFile(std::ofstream & out)
{   
    if(win)
    {
        out << "2";

    }else if(lost)
    {
        out << "1";

    }else
    {
        out << "0";
    }
    
    for(int i = 0; i < 16; i++){
        out << " " << b[i];
    }
    out << " " << name << "\n";
}

bool Game::moveUp()
{
    bool check = false;

    for(int i = 0; i < 4 ; i++){
        if(!check){
            check = move(i, i+4, i+8, i+12);
        }else
            move(i, i+4, i+8, i+12);
    }
    return(check);
}

bool Game::moveLeft()
{
    bool check = false;

    for(int i = 0; i <= 12; i+=4){
        if(!check){
            check = move(i, i+1, i+2, i+3);
        }else
            move(i, i+1, i+2, i+3);
    }
    return(check);
}

bool Game::moveDown()
{
    bool check = false;

    for(int i = 12; i <= 15; i++){
        if(!check){
            check = move(i, i-4, i-8, i-12);
        }else
            move(i, i-4, i-8, i-12);
    }
    return(check);
}

bool Game::moveRight()
{
    bool check = false;
    
    for(int i = 3; i <= 15; i+=4){
        if(!check){
            check = move(i, i-1, i-2, i-3);
        }else
            move(i, i-1, i-2, i-3);
    }
    return(check);
}

bool Game::move(int nr3, int nr2, int nr1, int nr0)
{
    bool move = true;
    bool check = false;
    int ant = 0;

    if(b[nr3] == 0 && b[nr2] == 0 && b[nr1] == 0 && b[nr0] == 0) move = false;

    //Move right line1R
    while(move){

        if(b[nr3] == 0){
            b[nr3] = b[nr2]; b[nr2] = 0;
            b[nr2] = b[nr1]; b[nr1] = 0;
            b[nr1] = b[nr0]; b[nr0] = 0;
            check = true;
        }
        if(b[nr2] == 0){
            b[nr2] = b[nr1]; b[nr1] = 0;
            b[nr1] = b[nr0]; b[nr0] = 0;
            check = true;
        }
        if(b[nr1] == 0){
            b[nr1] = b[nr0]; b[nr0] = 0;
            check = true;
        }

        if(ant == 3){
            move = false;
        }else ant++;
    }

    if(b[nr2] == b[nr3] && b[nr3] != 0){                      // 2 høyre er lik
        b[nr3] = b[nr2] + b[nr3]; b[nr2] = 0;
        check = true;

        if(b[nr0] == b[nr1] && b[nr1] != 0){                  // 2 venstre også lik
            b[nr2] = b[nr0] + b[nr1]; b[nr1] = b[nr0] = 0;

        }else{                                          // bare 2 høyre var lik
            b[nr2] = b[nr1]; b[nr1] = b[nr0]; b[nr0] = 0;
        }

    }else if(b[nr1] == b[nr2] && b[nr2] != 0){                // 2 midten var lik
        b[nr2] = b[nr2] + b[nr1]; 
        b[nr1] = b[nr0]; b[nr0] = 0;
        check = true;

    }else if(b[nr0] == b[nr1] && b[nr1] != 0){
        b[nr1] = b[nr1] + b[nr0]; b[nr0] = 0;
        check = true;
    }
    return(check);
}

void Game::playGame()
{
    int temp_nr;
    bool valid;
    
    win = checkWin();

    if(!lost && !win){ 
        temp_nr = newRandNumber();
	    std::cout << "\033[2J\033[1;1H";
        displayBoard();
        moveMenu();
    
        char input = r_char("What operation u want to do");
        
        while (input != 'Q' && !lost && !win)
        {
            //legge til at hvis ingen posisjoner er 0, så vill spilles avsluttes.

            if (checkValidChar(input))
            {
                std::cout << "\nValid - " << input << "\n";

                switch(input){
                    case 'W' : valid = moveUp(); break;
                    case 'A' : valid = moveLeft(); break;
                    case 'S' : valid = moveDown(); break;
                    case 'D' : valid = moveRight(); break;
                }   

                if(valid){temp_nr = newRandNumber();};    //bare nytt nummer hvis noe har beveget seg.
                
                std::cout << "\033[2J\033[1;1H";
                displayBoard();

            }
            else
                std::cout << "\nInvalid input, try another char\n";


            // Put these into the if under???
            lost = checkLoss();
            win = checkWin();
            
            if(lost){
                std::cout << "\nThe game has ended!" << std::endl;
            } else if(win)
            {  
                std::cout << "\nYou won the game :)\n";
            }else{
                input = r_char("What operation u want to do");
            }
                


        }
            removeNumber(temp_nr);
    }else

    if(win)
    {
        std::cout << "\nYou have allready won the game\n";
        displayBoard();

    }else if(lost)
    {
        std::cout << "\nThis game has ended!" << std::endl;
        displayBoard();

    } //else something else?
}

bool Game::checkNoMoves(int nr3, int nr2, int nr1, int nr0)
{
    bool playable = false;     //false == not lost / true == lost
    int ant = 0;

    if(b[nr2] == b[nr3] && b[nr3] != 0){
        playable = true;

        if(b[nr0] == b[nr1] && b[nr1] != 0){
            //b[nr2] = b[nr0] + b[nr1]; b[nr1] = b[nr0] = 0;

        }else{
            //b[nr2] = b[nr1]; b[nr1] = b[nr0]; b[nr0] = 0;
        }

    }else if(b[nr1] == b[nr2] && b[nr2] != 0){
        playable = true;

    }else if(b[nr0] == b[nr1] && b[nr1] != 0){
        playable = true;
    }

    return(playable);
}

bool Game::checkLoss(){
    int ant = 0;

    for(int i = 0; i < 16; i++){
        if(b[i] != 0){
            ant++;
        }
    }

    // Are there possible moves?
    if(ant == 16){

        std::cout << "1-";
        for(int i = 0; i < 4; i++){
            std::cout << "2-";
            if(checkNoMoves(i, i+4, i+8, i+12)) return false;   // not lost
        }
        for(int i = 0; i <= 12; i+=4){
            std::cout << "3-";
            if(checkNoMoves(i, i+1, i+2, i+3)) return false;    // and not lost
        }
        for(int i = 12; i <= 15; i++){
            std::cout << "4-";
            if(checkNoMoves(i, i-4, i-8, i-12)) return false;   // nope
        }
        for(int i = 3; i <= 15; i+=4){
            std::cout << "5-";
            if(checkNoMoves(i, i-1, i-2, i-3)) return false;    // no
        }
            
    }else
        return false;       // Not enough numbers on board

    return true;            // Game Over!
}

int Game::newRandNumber()
{
    int pos, nr;

    do{
        pos = rand() % 16;
    }while(b[pos] != 0);
    nr = rand() % 2;
    b[pos] = (nr % 2 == 1) ? 2 : 4;

    return pos; //Returns the posision on board that might be deleted if no moves are played
}

void Game::removeNumber(int nr)
{
    b[nr] = 0;
}

bool Game::checkValidChar(char t)
{
    return ((t == 'W' || t == 'A' || t == 'S' || t == 'D') ? true : false);
}

void Game::displayBoard()
{
    std::cout << "- - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "| " << std::setw(5) << b[0] << " | " << std::setw(5) << b[1] << " | " << std::setw(5) << b[2] << " | " << std::setw(5) << b[3] << " |" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "| " << std::setw(5) << b[4] << " | " << std::setw(5) << b[5] << " | " << std::setw(5) << b[6] << " | " << std::setw(5) << b[7] << " |" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "| " << std::setw(5) << b[8] << " | " << std::setw(5) << b[9] << " | " << std::setw(5) << b[10] << " | " << std::setw(5) << b[11] << " |" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "| " << std::setw(5) << b[12] << " | " << std::setw(5) << b[13] << " | " << std::setw(5) << b[14] << " | " << std::setw(5) << b[15] << " |" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - -" << std::endl;
}
void Game::displayName()
{
    std::cout << std::left << std::setw(10) << this->name;
}

void Game::displayStatus()
{
    
    int _1 = 100; //d
    int _2 = 52;  //4
    int _3 = 109; //m
    int _4 = 110;  //n
    int _5 = 95; //_
    int _6 = 121; //y
    int _7 = 48;  //0
    int _8 = 117; //u
    // _
    // 4
    int _9 = 114; //r
    int _10 = 51; //3
    // _
    // 4
    //_
    int _11 = 99; //c
    // r
    // 4
    int _12 = 122; //z
    // y
    // _
    int _13 = 103; //g
    // m
    // 3
    // r


    std::cout << ((lost) ? " - x" : "");

    if(win)
    {
    std::cout << "- CTFkom{";
    std::cout << char (_1);
    std::cout << char (_2);
    std::cout << char (_3);
    std::cout << char (_4);
    std::cout << char (_5); // --- _
    std::cout << char (_6);
    std::cout << char (_7);
    std::cout << char (_8);
    std::cout << char (_5); // --- _
    std::cout << char (_2); 
    std::cout << char (_9);
    std::cout << char (_10);
    std::cout << char (_5); // --- _
    std::cout << char (_2);
    std::cout << char (_5); // --- _
    std::cout << char (_11);
    std::cout << char (_9);
    std::cout << char (_2);
    std::cout << char (_12);
    std::cout << char (_6);
    std::cout << char (_5); // --- _
    std::cout << char (_13);
    std::cout << char (_2);
    std::cout << char (_3);
    std::cout << char (_10);
    std::cout << char (_9);
    std::cout << "}";
    }else
    {
        std::cout << "";
    }
    //std::cout << ((win) ? " - CTFkom{d4mn_y0u_4r3_4_cr4zy_g4m3r}" : "");
}



void Game::moveMenu()
{
    std::cout << "\nup - W | left - A | down - S | D - right";
}

/*
    Functions, main
*/

void writeToFile()
{
    std::ofstream out("database.dta");

    if(out){
        out << gGames.size() << "\n";

        if(gGames.size() == 0)
        {
            std::cout << "\nNo data has been written!\n";
            
        }else
        {
            for(int i = 0; i < gGames.size(); i++){
                gGames[i]->toFile(out);
            }
            std::cout << "\nData has been written to file!\n";
        }

    }else
        std::cout << "\nCan't WRITE to file!\n";
}

bool readFromFile()
{
    int nr;
    Game* newG;
    std::ifstream in("database.dta");

    in >> nr; in.ignore(); //Neste linje??

    if(in)
    {
        for(int i = 0; i < nr; i++){
            newG = new Game(in);
            gGames.push_back(newG);
            return true;
        }
        
    }else
    {
        if(fileExists("database.dta"))
        {
            std::cout << "\nFile does not have any content!\n";
        }else
        {
            std::cout << "\nFile does not exist\n";
        }
    }

    return false;
}

// For å gi beskjed om fil finnes, sjekk function over.
bool fileExists(const std::string &name)
{
    if(FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    }else
        return false;
}

void new_game()
{

    Game *new_G = new Game();

    std::cout << "\ncheck 1" << std::endl;

    // temp->startup();
    gGames.push_back(new_G);
}

void play_game()
{
    int nr;
    if (!gGames.empty())
    {
        show_games();
        nr = r_int_bet("Whitch game do you want to play", 0, gGames.size());
        if (nr)
        {
            gGames[nr - 1]->playGame();
        }
        else
            std::cout << "\nNo games will be played!" << std::endl;
    }
    else
        std::cout << "No games to play" << std::endl;
}

// Maybe unnecessary
void show_games()
{
    if (!gGames.empty())
    {
        std::cout << "\n\tX means the game has ended, no more moves!\n\n";
        
        for (int i = 0; i < gGames.size(); i++)
        {
            std::cout << "\n"
                      << i + 1 << ". ";
            gGames[i]->displayName();
            //if(gGames[i].lost) //MORE
            gGames[i]->displayStatus();
        }
    }
    else
        std::cout << "\nNo games to show" << std::endl;

    std::cout << "\n";
}
    

void menu()
{
    std::cout << "\nPossble operations:\n";
    std::cout << "\n\tN - new game";
    std::cout << "\n\tS - show running games";
    std::cout << "\n\tP - play existing game";
    std::cout << "\n\tQ - Quit and save game/s";
}

char r_char(std::string txt);
std::string r_string(std::string txt);
int r_int(std::string txt);
int r_int_bet(std::string txt, int min, int max);
bool y_or_no(std::string txt);

char r_char(std::string txt){
    char input;
    std::cout << std::endl << txt << " :";
    std::cin >> input; std::cin.ignore(MAXCHAR, '\n'); //Må være '' ettersom "" forteller at det er en flere char
    return(toupper(input));
}

//This just kinda works 
std::string r_string(std::string txt){
    std::string name;
    std::cout << std::endl << txt << ": ";
    getline(std::cin, name);
    return name;
}

int r_int(std::string txt){
    int nr;
    std::cout << std::endl << txt << ":";
    std::cin >> nr; std::cin.ignore(MAXCHAR, '\n');
    return nr;
}

int r_int_bet(std::string txt, int min, int max){
    int nr;
    while(nr < min || nr > max){
        std::cout << std::endl << txt << "(" << min << " - " << max << "): ";
        std::cin >> nr; std::cin.ignore(MAXCHAR, '\n');
    }
    return nr;
}

bool y_or_n(std::string txt){
    char input;
    std::cout << std::endl << txt << ": ";
    std::cin >> input; std::cin.ignore(MAXCHAR, '\n');
    if(input == 'Y' || input == 'y')
        return true;
    else
        return false;
}
