#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void show_menu(int max_x,int max_y,int highlight){
	mvprintw(0, 0, "<ログ>");
        if (highlight == 0) {
            attron(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 - 28, "「戦闘」");
            attroff(A_REVERSE);
            
            mvprintw(max_y - 3, max_x / 2 - 18, "「探索」");
            mvprintw(max_y - 3, max_x / 2 - 9, "「アイテム」");
            mvprintw(max_y - 3, max_x / 2 + 16, "「タイトル」");
            mvprintw(max_y - 3, max_x / 2 + 4, "「セーブ」");
            
            mvprintw(max_y - 5, max_x / 2 - 22, "info:zキーまたはENTERキー入力で敵と戦闘を行います\t\t\t\t\t");
        } else if (highlight == 1) {
            mvprintw(max_y - 3, max_x / 2 - 28, "「戦闘」");
            attron(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 - 18, "「探索」");
            attroff(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 + 16, "「タイトル」");
            mvprintw(max_y - 3, max_x / 2 - 9, "「アイテム」");
            mvprintw(max_y - 3, max_x / 2 + 4, "「セーブ」");
            
            mvprintw(max_y - 5, max_x / 2 - 30, "info:zキーまたはENTERキー入力でイベントが発生します\t\t\t\t\t");
        } else if (highlight == 2) {
            mvprintw(max_y - 3, max_x / 2 - 28, "「戦闘」");
            mvprintw(max_y - 3, max_x / 2 - 18, "「探索」");
            attron(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 - 9, "「アイテム」");
            attroff(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 + 16, "「タイトル」");
            mvprintw(max_y - 3, max_x / 2 + 4, "「セーブ」");
            
            mvprintw(max_y - 5, max_x / 2 - 24, "info:zキーまたはENTERキー入力でアイテム欄を開きます\t\t\t\t\t");
        } else if (highlight == 3) {
            mvprintw(max_y - 3, max_x / 2 - 28, "「戦闘」");
            mvprintw(max_y - 3, max_x / 2 - 18, "「探索」");
            mvprintw(max_y - 3, max_x / 2 - 9, "「アイテム」");
            mvprintw(max_y - 3, max_x / 2 + 16, "「タイトル」");
            attron(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 + 4, "「セーブ」");
            attroff(A_REVERSE);
            
            mvprintw(max_y - 5, max_x / 2 - 22, "info:zキーまたはENTERキー入力でセーブします\t\t\t\t\t");
        } else if (highlight == 4) {
            mvprintw(max_y - 3, max_x / 2 - 28, "「戦闘」");
            mvprintw(max_y - 3, max_x / 2 - 18, "「探索」");
            mvprintw(max_y - 3, max_x / 2 - 9, "「アイテム」");
            mvprintw(max_y - 3, max_x / 2 + 4, "「セーブ」");
            attron(A_REVERSE);
            mvprintw(max_y - 3, max_x / 2 + 16, "「タイトル」");
            attroff(A_REVERSE);
            
            mvprintw(max_y - 5, max_x / 2 - 22, "info:zキーまたはENTERキー入力でタイトルに戻ります\t\t\t\t\t");
        }
}