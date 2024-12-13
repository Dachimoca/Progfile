#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void show_player(){
        mvprintw(5, 0, "%s", hero.heroname);
        mvprintw(6, 0, "Lv %d\t", hero.lv);
        mvprintw(7, 0, "EXP %d/%d\t", hero.exp,DEFALT_EXP);
        mvprintw(8, 0, "HP %d\t\t\t", hero.hp);
        mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
        mvprintw(10,0, "ATK %d\t\t\t", hero.atk);
        mvprintw(11,0, "DFF %d\t\t\t", hero.dff);
        mvprintw(12,0, "DEX %d\t\t\t", hero.dex);
        mvprintw(13,0, "SCORE %d\t\t\t", hero.score);
        mvprintw(14,0, "MIG %s\t\t\t", hero.mig);
}

void show_monster(int max_x){
        mvprintw(5, max_x/2-10, "%s", monster.monstername);
        mvprintw(6, max_x/2-10, "Lv %d", monster.lv);
        mvprintw(7, max_x/2-10, "EXP %d\t\t\t", monster.exp);
        mvprintw(8, max_x/2-10, "HP %d\t\t\t", monster.hp);
        mvprintw(9, max_x/2-10, "SP %d\t\t\t", monster.sp);
        mvprintw(10, max_x/2-10, "ATK %d\t\t\t", monster.atk);
        mvprintw(11, max_x/2-10, "DFF %d\t\t\t", monster.dff);
        mvprintw(12, max_x/2-10, "DEX %d\t\t\t", monster.dex);
        mvprintw(13,max_x/2-10, "SCORE %d\t\t\t", monster.score);
        mvprintw(14,max_x/2-10, "MIG %s\t\t\t", monster.mig);
}