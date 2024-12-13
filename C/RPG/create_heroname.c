#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void create_heroname(int max_x,int max_y){
        char ch[128];
        mvprintw(max_y / 2 + 2,max_x / 2 - 24, "■■■■■■■■■■■■■■■■■■■■■■■■■");
        refresh();
        usleep(200000);
        mvprintw(max_y / 2 + 3,max_x / 2 - 24, "▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼");
        refresh();
        usleep(200000);
        mvprintw(max_y / 2 + 5,max_x / 2 - 24, "▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲");
        refresh();
        usleep(200000);
        mvprintw(max_y / 2 + 6,max_x / 2 - 24, "■■■■■■■■■■■■■■■■■■■■■■■■■");
        refresh();
        usleep(200000);
        
        
        /*ここで、hero.heroname[128]を標準入力された内容に書き込む*/
        mvprintw(max_y / 2 + 4,max_x / 2 - 24, "あなたの名前は？(ENTERで決定):",ch);
        refresh();
        echo();
        curs_set(1);
        getstr(ch);
        curs_set(0);
        noecho();
    
        // 名前を構造体のメンバにコピーする
        strncpy(hero.heroname, ch, sizeof(hero.heroname) - 1);
        hero.heroname[sizeof(hero.heroname) - 1] = '\0'; // 確実にNULL終端する

        mvprintw(max_y / 2 + 4,max_x / 2 - 24, "あなたの名前は？(ENTERで決定): %s", hero.heroname); // 入力された名前を表示する
        refresh();
        sleep(1);
}