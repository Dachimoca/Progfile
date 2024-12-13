#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void show_title(int max_y,int max_x,int flag){
    /* タイトル表示*/
    if(flag==0){
        mvprintw(max_y / 2 - 9, max_x / 2 - 3, "Vr0.4.7");
        mvprintw(max_y / 2 - 8, max_x / 2 - 22, "┏┓┏━┓┏━┓" );
        refresh();
        usleep(100000);
        mvprintw(max_y / 2 - 7, max_x / 2 - 22, "┃┃┃┃┃┃┃┃┳━┓┳    ┏━┓┏━┓┳━┓");
        refresh();
        usleep(100000);
        mvprintw(max_y / 2 - 6, max_x / 2 - 22, "┃┃┃┃┃┃┃┃┣┫  ┃    ┃　┃┃　┃┣┳┛");
        refresh();
        usleep(100000);
        mvprintw(max_y / 2 - 5, max_x / 2 - 22, "┗┛┗━┛┗━┛┻    ┻━┛┗━┛┗━┛┻┗");
        refresh();
        usleep(100000);
        mvprintw(max_y / 2 - 4, max_x / 2 - 22, "┳━┓┳　┳ ┳┓┏ ┏━┫ ┳━┓┏━┓┳┓┏");
        refresh();
        usleep(100000);
        mvprintw(max_y / 2 - 3, max_x / 2 - 22, "┃　┃┃　┃ ┃┃┃ ┃　┳ ┣━　┃　┃┃┃┃");
        refresh();
        usleep(100000);
        mvprintw(max_y / 2 - 2, max_x / 2 - 22, "┻━┛┗━┛ ┛┗┻ ┗━┫ ┻━┛┗━┛┛┗┻");
        refresh();
        usleep(500000);
        mvprintw(max_y / 2, max_x / 2 - 8, "前回のスコア %d 点",hero.score);
        mvprintw(max_y / 2 + 1, max_x / 2 - 8, "前回の到達階層 %d 層",hero.floor_score);
        
    }else{
        mvprintw(max_y / 2 - 9, max_x / 2 - 3, "Vr0.4.7");
        mvprintw(max_y / 2 - 8, max_x / 2 - 22, "┏┓┏━┓┏━┓" );
        mvprintw(max_y / 2 - 7, max_x / 2 - 22, "┃┃┃┃┃┃┃┃┳━┓┳    ┏━┓┏━┓┳━┓");
        mvprintw(max_y / 2 - 6, max_x / 2 - 22, "┃┃┃┃┃┃┃┃┣┫  ┃    ┃　┃┃　┃┣┳┛");
        mvprintw(max_y / 2 - 5, max_x / 2 - 22, "┗┛┗━┛┗━┛┻    ┻━┛┗━┛┗━┛┻┗");
        mvprintw(max_y / 2 - 4, max_x / 2 - 22, "┳━┓┳　┳ ┳┓┏ ┏━┫ ┳━┓┏━┓┳┓┏");
        mvprintw(max_y / 2 - 3, max_x / 2 - 22, "┃　┃┃　┃ ┃┃┃ ┃　┳ ┣━　┃　┃┃┃┃");
        mvprintw(max_y / 2 - 2, max_x / 2 - 22, "┻━┛┗━┛ ┛┗┻ ┗━┫ ┻━┛┗━┛┛┗┻");
        mvprintw(max_y / 2, max_x / 2 - 8, "前回のスコア %d 点",hero.score);
        mvprintw(max_y / 2 + 1, max_x / 2 - 8, "前回の到達階層 %d 層",hero.floor_score);
    }
}