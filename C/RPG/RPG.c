/*メイン処理する場所*/

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

Hero hero;
Monster monster;

int DEFALT_EXP = 20;
int floor_check = 0;
int battle_flag = 0;

int main(int argc, char **argv) {
    srand(time(NULL));
    setlocale(LC_ALL, ""); /* locale として環境変数を利用 */
    /* 画面表示*/
    initscr();
    /* カーソルキーを利用*/
    keypad(stdscr, TRUE);
    /* 入力文字を出力しない*/
    noecho();
    /* 入力を即座に取得*/
    cbreak();
    /* カーソルの削除*/
    curs_set(0);
    /* タイトル画面の表示*/
    start_game_screen(argc,argv);
    /* 終了処理*/
    endwin();
    return 0;
}
