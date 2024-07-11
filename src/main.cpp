#include<ncurses.h>
#include<bits/stdc++.h>

using namespace std;

//function/global variable declarations.
void menu(void), print(string), zen(void),
     word(void), clearF(), backspace(),
     stats(int, int, float, float, bool),
     print_word_center(string,string),
     stat_print(int, string); // silly code.
string f(char);
vector<string> generate_random(int);
//f is a function just to help my plebian java brain.

int row;
int ROWK, COLK;
#define BS 8
#define FILE "../misc/data.dat"


int main(void) {
  srand(static_cast<unsigned int>(time(0)));
  row = 10;
  initscr();
  //keypad mode doesn't allow the backspace function to work because keypad includes backspace as a special key... because it is!
  noecho();
  raw();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  cbreak();
  getmaxyx(stdscr,ROWK,COLK);
  menu();
  //if it is not one of those simply end the window.

  endwin();
  return EXIT_SUCCESS;
}

void menu() {
  clearF();
  stat_print(10,"Welcome to Tui-Typing!\n");
  stat_print(12,"1. Zen Mode\n");
  stat_print(14,"2. Word Mode\n");
  stat_print(16,"Q. Quit:)  \n");
  char c = static_cast<char>(getch());
  if(c == '1') {
    zen();
  } else if(c == '2') {
    word();
  }
  //if it is not one of those simply end the window.



  // print("Is the best Code Geass Character!\n");
}
//** ***********************************************************8 */

void zen(){
    clear();
    move(3,6);
    bool get = true;
    time_t start_time, end_time;
    scrollok(stdscr,TRUE);
    bool run = true;
    int words = 0;
    char prev = ' ', c;
    int ctr = 0;
    while(run) {
        int currR, currY, maxR, maxY;
        getyx(stdscr, currR, currY);
        getmaxyx(stdscr, maxR,maxY);
        if(currY == maxY-7) {
          if(currR+1 >= maxR) {
            scroll(stdscr);
            wmove(stdscr,maxR-1, 6);
          } else {
            move(currR+1, 6);
          }
        }
        c = static_cast<char>(getch());
        ctr++;
        if(get) { time(&start_time); get = false;}
        switch(c) {
            case static_cast<char>(127):
            case BS: {
                backspace();
                break;
            }
            case static_cast<char>(10): {
              if(currR+1 >= maxR) {
                scroll(stdscr);
                wmove(stdscr,maxR-1, 6);
              } else {
                move(currR+1, 6);
              }

              break;
            }
            case '`': {
                run = false;
                time(&end_time);
                break;
            }
            default: addch(c);
        }
        if(c == ' ' && prev != ' ') words++;
        prev = c;
    }
    if(c != ' ') words++;
    else words--;
    clear();
    stats(ctr,words, float(end_time-start_time), 1, false);
    char response = static_cast<char>( getch() );
    if(response == '1') menu();
    return;
}

//***********************************************************888*/
void word() {
    clearF();
    keypad(stdscr, FALSE);
    // if you wanna change this go right ahead!;
    int k = 10;
    vector<string> words = generate_random(k);
    string word;
    for(int i = 0; i < k; i++ ) {
      word.append(words[i]);
      word.append(" ");
    }
    string red_green;
    for(size_t i = 0; i < word.size(); i++ ) red_green.push_back(' ');
    word.append("\n");
    print_word_center(word, red_green);
    int i = 0;
    int accuracy = 0;
    char c;
    bool run = true, get = true;
    time_t start_time, end_time;
    bool dont_increment = false;

    while(run) {
        c = static_cast<char>(getch());
        if(get) { time(&start_time); get = false;}
        if(i == static_cast<int>(word.size())-3)   {
          time(&end_time);
          break;
        }
        if(c == word[i]) {
          red_green[i] = 'g';
          print_word_center(word, red_green);
        } else {
          red_green[i] = 'r';
          print_word_center(word,red_green);
        }

        switch(c) {
            case static_cast<char>(127):
            case BS: {
                backspace();
                if(i != 0) {
                  red_green[i-1] = ' ';
                  red_green[i] = ' ';
                }
                dont_increment = true;
                print_word_center(word, red_green);
                break;
            }
            case '`': {
                menu();
                return;
            }
            default: {
            }
        }
        wrefresh(stdscr);
        if(!dont_increment) {
            i++;
        } else {
            dont_increment = false;
            i--;
            if(i < 0) i = 0;
        }
        accuracy++;
    }
    //this is to prevent excessive backspaces that could potentially be marked as quickness!!!
    if(accuracy < 0) accuracy = 0;
    clear();
    if(1-i/accuracy <= .001) {
        stats(static_cast<int>(word.size()),10, float(end_time-start_time),1, true);
    }else {
        stats(static_cast<int>(word.size()),10, float(end_time-start_time),static_cast<float>(i-2)/static_cast<float>(accuracy), true);
    }
    char response = static_cast<char>(getch());
    if(response == '1') menu();
    return;
}

void clearF() {
  clear();
  int ccc;
  getmaxyx(stdscr, row, ccc);
  row/=2;
}
// Source: https://ubuntuforums.org/showthread.php?t=1626888
// big thanks to them for the code!
void backspace()
{
  nocbreak();
  getyx(stdscr,ROWK, COLK);
  move(ROWK,COLK-1);
  delch();
  cbreak();
  refresh();
}

// REMINDER: YOU NEED TO CHANGE PRINTW into print(); Simply find an equivalent for String.format() for C++.
//***********************************************************888*/
void stats(int len,int w, float time,float accuracy, bool printpp) {
    float comp = static_cast<float>(len)/4.7f;
    // The way monkeytype calculates is it takes the total number of characters typed (len) and divides by 5 then converts to mins
    // MonkeyType uses 5 because that is approximately what is the average length of a word. 4.7 (Google) is the average allegedly.
    // to_string may be lesser known than just string so i will append the std::/
    string words_str = "WORDS: " + std::to_string(w) + "\n";
    string accuracy_str = "ACCURACY: " + std::to_string(accuracy*100) + "%\n";
    string raw_str = "RAW: " + std::to_string(comp*60.0f/(time)) + "\n";
    string wpm_str = "WPM: " + std::to_string(comp/time *60.0f * accuracy) + "\n";
    if(printpp) {
      stat_print(10,words_str);
      stat_print(12,accuracy_str);
      stat_print(14,raw_str);
      stat_print(16,wpm_str);
      stat_print(19,"would you like to do another test? 1 (yes) 2 (no)\n");
    } else {
      stat_print(13,wpm_str);
      stat_print(16,"would you like to do another test? 1 (yes) 2 (no)\n");
    }
}
//** **************************************************************** */

void stat_print(int r,string text) {
  int center_col = getmaxx(stdscr)/2;
  int half_len = static_cast<int>(text.size())/2;
  int adjusted_col = center_col - half_len;
  mvwprintw(stdscr,r,adjusted_col, text.c_str());
}

//** **********************************************************888 *//
// reservoir sampling!
// more info at : https://en.wikipedia.org/wiki/Reservoir_sampling
vector<string> generate_random(int k) {
  ifstream file(FILE);
  if (!file.is_open()) {
    throw runtime_error("Unable to open file");
  }
  vector<string> reservoir(k);
  string word;
  int count = 0;
  while (count < k && file >> word) {
    reservoir[count] = word;
    count++;
  }
  int i = k;
  while (file >> word) {
    int j = rand() % (i + 1);
    if (j < k) {
      reservoir[j] = word;
    }
    i++;
  }
  file.close();
  return reservoir;
}

void print_word_center(string text, const string colors) {
    int rowR, colR;
    getmaxyx(stdscr, rowR, colR); // Get the number of rows and columns
    rowR = 10;
    int start_col = (colR - static_cast<int>(text.length())) / 2; // Calculate starting column

    // Move to the starting column for centered text
    int start_row = rowR / 2;
    mvwprintw(stdscr, start_row, start_col-1, " ");

    // Print each character with appropriate color
    for (size_t i = 0; i < text.length(); ++i) {
        if (colors[i] == 'g') {
            wattron(stdscr, COLOR_PAIR(1));
            waddch(stdscr, text[i]);
            wattroff(stdscr, COLOR_PAIR(1));
        } else if (colors[i] == 'r') {
            wattron(stdscr, COLOR_PAIR(2));
            waddch(stdscr, text[i]);
            wattroff(stdscr, COLOR_PAIR(2));
        } else {
            waddch(stdscr, text[i]); // Default color if neither 'g' nor 'r'
        }
    }

    wrefresh(stdscr); // Refresh the window to show the text
}
