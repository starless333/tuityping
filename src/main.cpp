#include<ncurses.h>
#include<bits/stdc++.h>
// const definitions
#define BUFFER_SIZE 15
#define FILE "../misc/words.dat"


using namespace std;


// function definitions;
void menu(void);
void print_centered(const char*);
void get_words(void);
void zen(void);
void timer(void);
void word(void);
void settings(void);


int row, col;
vector<string> most_common;

int main(void)
{


    //make sure that prior to calling menu that the screen is clear. ie call clear() prior to menu() call.
    get_words();
    initscr();
    cbreak();

    menu();


    getmaxyx(stdscr, row, col);



    endwin();
    return EXIT_SUCCESS;
}



void get_words(void) {
    ifstream file(FILE);
    string contents;
    if(!file.is_open()) {
        cerr << "could not open file.\n";
        exit(EXIT_FAILURE);
    }
    while(file >> contents) {
        most_common.push_back(contents);
    }
    file.close();
}

void print_centered(const char *text) {
    int text_length = static_cast<int>(strlen(text));
    int start_col = (col - text_length) / 2; // Calculate starting column for centered text
    mvprintw(row / 2, start_col, "%s", text); // Print text centered horizontally
    refresh(); // Refresh the screen to display changes
}

void menu() {
    addstr("Welcome to tuityping. Please select a mode you would like:\n");
    refresh();
    addstr("\n1. Zen Mode\n2. Timed Test\n3. Word Test\n\n");
    refresh();
    char c = static_cast<char>(getch());
    switch(c) {
        case '1': {
            zen();
            return;
        }
        case '2': {
            timer();
            return;
        }
        case '3': {
            word();
            return;
        }
        case 'S': {
            settings();
        }
        default: {
            return;
        }
    }
}
void zen(){
    clear();
    addstr("This is zen mode. Type freely and once you press Esc your zen stats shall show!\n");
    getch();
}

//***********************************************************888*/
void timer() {
    erase();
    int secondsLeft = 120;
    do {
        printw("%i", secondsLeft);
        refresh();
        erase();
        secondsLeft--;
        napms(1000);
    } while (secondsLeft > 0);
}
//***********************************************************888*/
void word(){
    clear();
}
//***********************************************************888*/
void settings(){
    clear();
}
//***********************************************************888*/
