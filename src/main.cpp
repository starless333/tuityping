#include<ncurses.h>
#include<bits/stdc++.h>
// const definitions
#define BUFFER_SIZE 15
#define FILE "../misc/words.dat"
#define LIMIT 10
#define WORDS_SIZE 100
using namespace std;


// function definitions;
void menu(void);
void print_centered(const char*);
void get_words(void);
void zen(void);
void timer(void);
void word(void);
void settings(void);
void stats(int words, float time);


WINDOW *window;
const char BS = static_cast<char>(8);
int row, col;
vector<string> most_common;

int main(void)
{

    //make sure that prior to calling menu that the screen is clear. ie call clear() prior to menu() call.
    get_words();
    window = initscr();
    raw();
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

// Source: https://ubuntuforums.org/showthread.php?t=1626888
// big thanks to them for the code!
void backspace()
{
  nocbreak();
  getyx(window, row, col);
  move(row, col-1);
  delch();
  cbreak();
  refresh();
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
    addstr("This is zen mode. Type freely and once you press ` your zen stats shall show!\n\n");
    noecho();

    bool get = true;
    clock_t start_time, end_time;
    bool run = true;
    int words = 0;
    char prev = ' ', c;
    while(run) {
        c = static_cast<char>(getch());
        if(get) { start_time = clock(); get = false;}

        switch(c) {
            case static_cast<char>(127):
            case BS: {
                backspace();
                break;
            }
            case '`': {
                end_time = clock();
                run = false;
                break;
            }
            default: addch(c);
        }
        if(c == ' ' && prev != ' ') words++;
        prev = c;
    }
    if(c != ' ') words++;

    clear();
    stats(words, float(end_time-start_time));
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
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0,WORDS_SIZE-1); // define the range
    // distr(gen) will produce a random number in that range.

    string test;


    for(int i = 0; i < LIMIT; i++ ) {
        string partial = most_common[distr(gen)] + " ";
        test.append(partial);
    }
    test.append("\n");

    printw(test.c_str());
    refresh();
    getch();

    return;
}
//***********************************************************888*/
void settings(){
    clear();
}
//***********************************************************888*/
void stats(int words, float time) {
    printw("WORDS: %d\nTIME: %.2fs\n", words, time/1000.0f);
    printw("WORDS PER MINUTE: %.2f\n", static_cast<float> (words)/(time/1000.0f)*60);
}
