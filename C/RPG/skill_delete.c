#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void delete_skill(char* skillname,int max_y,int max_x){
    int ch;
    int highlight = 0;  /* 0~8...スキル選択*/
    mvprintw(15, 1, "スキルボックス(zキーで選択したスキルを削除・xキーで技を習得しない)");
    mvprintw(24, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    mvprintw(25, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    mvprintw(26, 1, "覚えようとしているスキル %s",skillname);
    refresh();
    while (1) {
        for (int i = 0; i < 8; i++) {
            if (highlight == i) {
                attron(A_REVERSE);
                mvprintw(i + 16, 0, " %s\t\t\t\t\t\t\t", hero.skillbox[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i + 16, 0, " %s\t\t\t\t\t\t\t", hero.skillbox[i]);
            }
        }
        
        skill_text(highlight);   /*スキルの説明表示*/
        
        /* 入力処理*/
        ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight + 7) % 8;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % 8;
                break;
            case 'z':
            case '\n':
                char* delete_skill = hero.skillbox[highlight];
                hero.skillbox[highlight]=skillname;
                mvprintw(3,0, "%s を忘れて %s を習得！\t\t\t\t\t\t\t\t\t\t\t\t",delete_skill,skillname);
                mvprintw(4,0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                refresh();
                sleep(1);
                for (int j = 0; j < 11; j++) {
                    mvprintw(j + 15, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                }
                return;
            default:
                mvprintw(3,1, "スキル習得をキャンセルしました\t\t\t\t\t\t\t\t\t\t\t\t");
                refresh();
                sleep(1);
                for (int j = 0; j < 11; j++) {
                    mvprintw(j + 15, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                }
                return;
        }
    }
}
