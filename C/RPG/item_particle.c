#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h"
#include "func.h"

void xp_bottle(char* name){
    int upexp;
    if (strcmp(name,"経験値ドリンク(小)")==0){
            int rd = rand() % 100 + 1;
            if(rd<=80){
        upexp = rand()%100+1;
        }else{
            mvprintw(25,0,"失敗...経験値を獲得できなかった");
            refresh();
            sleep(1);
            return;
        }
    }else if (strcmp(name,"経験値ドリンク(中)")==0){
            int rd = rand() % 100 + 1;
            if(rd<=60){
        upexp = rand()%300+50;
                }else{
            mvprintw(25,0,"失敗...経験値を獲得できなかった");
            refresh();
            sleep(1);
            return;
        }
    }else if (strcmp(name,"経験値ドリンク(大)")==0){
            int rd = rand() % 100 + 1;
            if(rd<=40){
        upexp = rand()%700+100;
                }else{
            mvprintw(25,0,"失敗...経験値を獲得できなかった");
            refresh();
            sleep(1);
            return;
        }
    }else if (strcmp(name,"経験値ドリンク(極大)")==0){
            int rd = rand() % 100 + 1;
            if(rd<=20){
        upexp = rand()%4000+1000;
                }else{
            mvprintw(25,0,"失敗...経験値を獲得できなかった");
            refresh();
            sleep(1);
            return;
        }
    }
    mvprintw(25,0,"%dexpを獲得！",upexp);
    hero.exp+=upexp;
    refresh();
    sleep(1);
}

void heal(char* name, char* str) {
    int up;
    if(strcmp(str, "hp") == 0) {
        if(strcmp(name, "HP回復剤(小)") == 0) {
            up = (rand() % (1 * hero.lv)) + (2 * hero.lv);
        } else if (strcmp(name, "HP回復剤(中)") == 0) {
            up = (rand() % (2 * hero.lv)) + (3 * hero.lv);
        } else if (strcmp(name, "HP回復剤(大)") == 0) {
            up = (rand() % (3 * hero.lv)) + (4 * hero.lv);
        }
        hero.hp += up;
    } else if(strcmp(str, "sp") == 0) {
        if(strcmp(name, "SP回復剤(小)") == 0) {
            up = (rand() % (1 * hero.lv)) + (2 * hero.lv);
        } else if (strcmp(name, "SP回復剤(中)") == 0) {
            up = (rand() % (2 * hero.lv)) + (3 * hero.lv);
        } else if (strcmp(name, "SP回復剤(大)") == 0) {
            up = (rand() % (3 * hero.lv)) + (4 * hero.lv);
        }
        hero.sp += up;
    }
    mvprintw(25, 0, "%sを%d回復！", str, up);
    refresh();
    sleep(1);
}

void book(char* name, char* str) {
    if(strcmp(str, "全ステータス") == 0) {
        int up = rand() % 10 + 1;
        mvprintw(25, 0, "%sが%d上昇！", str, up);
        hero.hp += up;
        hero.sp += up;
        hero.atk += up;
        hero.dff += up;
        hero.dex += up;
        refresh();
        sleep(1);
    } else {
        int up = rand() % 5 + 1;
        mvprintw(25, 0, "%sが%d上昇！", str, up);
        if(strcmp(str, "hp") == 0) {
            hero.hp += up;
        } else if (strcmp(str, "sp") == 0) {
            hero.sp += up;
        } else if (strcmp(str, "atk") == 0) {
            hero.atk += up;
        } else if (strcmp(str, "dff") == 0) {
            hero.dff += up;
        } else if (strcmp(str, "dex") == 0) {
            hero.dex += up;
        }
        refresh();
        sleep(1);
    }
}

void luckey(char* name, char* str) {
    if(strcmp(str, "全ステータス") == 0) {
        int luck = rand() % 100 + 1;
        if(luck <= 40) {
            mvprintw(25, 0, "運試し成功！%sが1.1倍に上がった！", str);
            hero.hp = (int)(hero.hp * 1.1);
            hero.sp = (int)(hero.sp * 1.1);
            hero.atk = (int)(hero.atk * 1.1);
            hero.dff = (int)(hero.dff * 1.1);
            hero.dex = (int)(hero.dex * 1.1);
        } else {
            mvprintw(25, 0, "運試し失敗...%sが0.9倍になった", str);
            hero.hp = (int)(hero.hp * 0.9);
            hero.sp = (int)(hero.sp * 0.9);
            hero.atk = (int)(hero.atk * 0.9);
            hero.dff = (int)(hero.dff * 0.9);
            hero.dex = (int)(hero.dex * 0.9);
        }
        refresh();
        sleep(1);
    } else {
        int luck = rand() % 100 + 1;
        if(luck <= 40) {
            mvprintw(25, 0, "運試し成功！%sが1.2倍に上がった！", str);
            if(strcmp(str, "hp") == 0) {
                hero.hp = (int)(hero.hp * 1.2);
            } else if (strcmp(str, "sp") == 0) {
                hero.sp = (int)(hero.sp * 1.2);
            } else if (strcmp(str, "atk") == 0) {
                hero.atk = (int)(hero.atk * 1.2);
            } else if (strcmp(str, "dff") == 0) {
                hero.dff = (int)(hero.dff * 1.2);
            } else if (strcmp(str, "dex") == 0) {
                hero.dex = (int)(hero.dex * 1.2);
            }
        } else {
            mvprintw(25, 0, "運試し失敗...%sが0.8倍になった", str);
            if(strcmp(str, "hp") == 0) {
                hero.hp = (int)(hero.hp * 0.8);
            } else if (strcmp(str, "sp") == 0) {
                hero.sp = (int)(hero.sp * 0.8);
            } else if (strcmp(str, "atk") == 0) {
                hero.atk = (int)(hero.atk * 0.8);
            } else if (strcmp(str, "dff") == 0) {
                hero.dff = (int)(hero.dff * 0.8);
            } else if (strcmp(str, "dex") == 0) {
                hero.dex = (int)(hero.dex * 0.8);
            }
        }
        refresh();
        sleep(1);
    }
}