#include<ncurses.h>
#include<bits/stdc++.h>


// const definitions
#define BUFFER_SIZE 15
#define LIMIT 10
#define WORDS_SIZE 100

// doing this for ease of typing. I know it isn't good practice (see https://github.com/starless333/gentemp !);
using namespace std;


// function definitions;
void menu(void); // prints the menu.
void print_centered(const char*); // needs to be fixed admittedly.
void zen(void); // zen mode implementation.
void timer(void); // timer mode implementation.
void word(void); // word mode implementation.
void settings(void); // Still contemplating how to implement.
void stats(int words, float time); // displays those juicy stats.

// just some stuff that will be needed globally.
WINDOW *window; // for backspace();
const char BS = static_cast<char>(8); // for ease of use.
int row, col; // for dimensions of terminal if ever needed.



// Thanks to https://www.espressoenglish.net/the-100-most-common-words-in-english/ for a list of 100 words. May not be accurate.
vector<string> most_common = {"time", "year", "people", "way", "day", "man", "thing", "woman", "life", "child", "world", "school", "state", "family", "student", "group", "country", "problem", "hand", "part", "place", "case", "week", "company", "system", "program", "question", "work", "government", "number", "night", "point", "home", "water", "room", "mother", "area", "money", "story", "fact", "month", "lot", "right", "study", "book", "eye", "job", "word", "business", "issue", "side", "kind", "head", "house", "service", "friend", "father", "power", "hour", "game", "line", "end", "member", "law", "car", "city", "community", "name", "president", "team", "minute", "idea", "kid", "body", "information", "back", "parent", "face", "others", "level", "office", "door", "health", "person", "art", "war", "history", "party", "result", "change", "morning", "reason", "research", "girl", "guy", "moment", "air", "teacher", "force", "education"};

int main(void)
{
    //make sure that prior to calling menu that the screen is clear. ie call clear() prior to menu() call.
    window = initscr();
    if(!has_colors()) {
        cerr << "your terminal does not support colors. If you don't care about the colors simply remove this line in main.cpp.\n";
        exit(EXIT_FAILURE);
    }
    start_color();
    raw();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    cbreak();
    getmaxyx(stdscr, row, col);
    menu();
    endwin();

    return EXIT_SUCCESS;
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

// Zen mode is practically fully functioning!;
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
    noecho();
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0,WORDS_SIZE-1); // define the range
    // distr(gen) will produce a random number in that range.

    string test;


    for(int i = 0; i < LIMIT; i++ ) {
        string partial = most_common[distr(gen)] + " ";
        test.append(partial);
    }

    printw(test.c_str());
    refresh();
    addch('\n');

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);  

    //RAW = 10/(time/1000)*60;
    //WPM = RAW*accuracy/i;
    //i = test.size() by the end of iteration;
    int i = 0;
    int accuracy = 0;
    char c;
    bool run = true, get = true;
    clock_t start_time, end_time;
    while(run) {
        if(i == static_cast<int>(test.size()-1))   {
            end_time = clock();
            break;
        }
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
            // by default we compare the current character to the
            default: {
                if(c == test[i]) {
                    accuracy++;
                    wattron(window,COLOR_PAIR(1));
                    waddch(window,c);
                    wattroff(window,COLOR_PAIR(1));
                } else {
                    wattron(window,COLOR_PAIR(2));
                    waddch(window,c);
                    wattroff(window,COLOR_PAIR(2));
                }
            }
        }
        wrefresh(window);
        i++;
    }

    clear();
    stats(10, float(end_time-start_time));
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
