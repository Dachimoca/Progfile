#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void skill_slash(int max_x,int spcost,double mul,int mode,int highlight,char* mig){
    int damage;
    if(hero.sp>=spcost){
        hero.sp-=spcost;
        mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
        refresh();
        damage = (int)((hero.atk*mul)/2 - monster.dff/2)+rand()%10+1;
        if(damage<=0)damage=(int)(hero.atk/4 + rand() % 6 + 1);
        damage = skill_mig(damage,mig);
        monster.hp -= damage;
        mvprintw(2, 1, "%sは%sを放った! %d のダメージ!\t\t\t\t",hero.heroname,hero.skillbox[highlight], damage);
        mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        if(monster.hp<0){
            monster.hp=0;
        }
        show_player();
        show_monster(max_x);
        refresh();
        sleep(1);
    }else{
        mvprintw(2, 1, "SPが不足しています\t\t\t\t\t");
        refresh();
        sleep(1);
        return;
    }
}

void skill_updown(int max_x, int spcost, int num, char* name, int mode, int highlight) {
    char* updown;
    if(hero.sp >= spcost) {
        hero.sp -= spcost;
        mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
        refresh();
        num = rand() % num + num;
        if(mode == 1) {
            updown = "上昇";
        } else if(mode == 2) {
            updown = "減少";
        }
        if(strcmp(name, "ATK") == 0 && mode == 1) {
            hero.atk += num;
        } else if((mode == 2 && strcmp(name, "ATK") == 0) || strcmp(name, "全ステータス") == 0) {
            monster.atk -= num;
            if(monster.atk <= 0) {
                monster.atk = 0;
            }
        }
        if(strcmp(name, "DFF") == 0 && mode == 1) {
            hero.dff += num;
        } else if((mode == 2 && strcmp(name, "DFF") == 0) || strcmp(name, "全ステータス") == 0) {
            monster.dff -= num;
            if(monster.dff <= 0) {
                monster.dff = 0;
            }
        }
        if(strcmp(name, "DEX") == 0 && mode == 1) {
            hero.dex += num;
        } else if((mode == 2 && strcmp(name, "DEX") == 0) || strcmp(name, "全ステータス") == 0) {
            monster.dex -= num;
            if(monster.dex <= 0) {
                monster.dex = 0;
            }
        }
        
        mvprintw(2, 1, "%sは%sを放った!\t\t\t\t\t\t\t\t", hero.heroname, hero.skillbox[highlight]);
        mvprintw(3, 1, "%sを%d%s！\t\t\t\t\t\t\t\t\t\t\t", name, num, updown);
        if(mode == 1) {
            show_player();
        } else {
            show_monster(max_x);
        }
        refresh();
        sleep(1);
    } else {
        mvprintw(2, 1, "SPが不足しています\t\t\t\t\t");
        refresh();
        sleep(1);
        return;
    }
}

int skill_mig(int damage,char* mig){
    if(strcmp(mig,"火")==0){
            if(strcmp(monster.mig,"水") == 0){
                damage=(int)(damage*1.5);
                mvprintw(2, 1, "ダメージアップ！\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"氷") == 0){
                damage=(int)(damage*0.5);
                mvprintw(2, 1, "ダメージ半減...\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"雷") == 0){
                damage=(int)(damage*0.0);
                mvprintw(2, 1, "ダメージ無効...\t\t\t\t\t\t\t\t");
            }else{
                mvprintw(2, 1, "ヒット！\t\t\t\t\t\t\t\t");
            }
        }else if(strcmp(mig,"水")==0){
            if(strcmp(monster.mig,"火") == 0){
                damage=(int)(damage*0.5);
                mvprintw(2, 1, "ダメージ半減...\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"氷") == 0){
                damage=(int)(damage*0.5);
                mvprintw(2, 1, "ダメージ半減...\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"雷") == 0){
                damage=(int)(damage*2.0);
                mvprintw(2, 1, "ダメージ超アップ！\t\t\t\t\t\t\t\t");
            }else{
                mvprintw(2, 1, "ヒット！\t\t\t\t\t\t\t\t");
            }
        }else if(strcmp(mig,"氷")==0){
            if(strcmp(monster.mig,"火") == 0){
                damage=(int)(damage*2.0);
                mvprintw(2, 1, "ダメージ超アップ！\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"水") == 0){
                damage=(int)(damage*1.5);
                mvprintw(2, 1, "ダメージアップ！\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"雷") == 0){
                damage=(int)(damage*0.5);
                mvprintw(2, 1, "ダメージ半減...\t\t\t\t\t\t\t\t");
            }else{
                mvprintw(2, 1, "ヒット！\t\t\t\t\t\t\t\t");
            }
        }else if(strcmp(mig,"雷")==0){
            if(strcmp(monster.mig,"火") == 0){
                damage=(int)(damage*0.0);
                mvprintw(2, 1, "ダメージ無効...\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"水") == 0){
                damage=(int)(damage*0.5);
                mvprintw(2, 1, "ダメージ半減...\t\t\t\t\t\t\t\t");
            }else if(strcmp(monster.mig,"氷") == 0){
                damage=(int)(damage*1.5);
                mvprintw(2, 1, "ダメージアップ！\t\t\t\t\t\t\t\t");
            }else{
                mvprintw(2, 1, "ヒット！\t\t\t\t\t\t\t\t");
            }
        }else{
                mvprintw(2, 1, "ヒット！\t\t\t\t\t\t\t\t");
        }
    mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    refresh();
    sleep(1);
    return damage;
}

void skill_magic(int max_x,int spcost,double mul,int highlight,char* mig){
    if(hero.sp>=spcost){
        int damage = (int)(((hero.sp+hero.lv)/2)*mul);
        damage = skill_mig(damage,mig);
        hero.sp-=spcost;
        mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
        refresh();
        monster.hp -= damage;
        mvprintw(2, 1, "%sは%sを放った! %d のダメージ!\t\t\t\t",hero.heroname,hero.skillbox[highlight],damage);
        mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        if(monster.hp<0){
            monster.hp=0;
        }
        mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
        refresh();
        sleep(1);
    }else{
        mvprintw(2, 1, "SPが不足しています\t\t\t\t\t");
        refresh();
        sleep(1);
        return;
    }
}

void skill_heal(int cost,int heal,int highlight,int mode){
    if(mode == 0){
        if(hero.sp>=cost){
            hero.sp-=cost;
            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
            refresh();
            int uphp = rand()%((hero.lv+heal)*3)+(int)((heal*hero.lv)/3);
            hero.hp += uphp;
            mvprintw(2, 1, "%sは%sを放った!\t\t\t\t\t\t\t\t",hero.heroname,hero.skillbox[highlight]);
            mvprintw(3,1,"HPを%d回復！\t\t\t\t\t\t\t\t\t\t\t\t\t",uphp);
            mvprintw(8, 0, "HP %d\t\t", hero.hp);
            refresh();
            sleep(1);
        }else{
            mvprintw(2, 1, "SPが不足しています\t\t\t\t\t");
            refresh();
            sleep(1);
            return;
            }
    }else{
            if(hero.hp>=cost){
            hero.hp-=cost;
            mvprintw(8, 0, "HP %d\t\t\t", hero.hp);
            refresh();
            int upsp = rand()%((hero.lv+heal)*3)+(int)((heal*hero.lv)/3);
            hero.sp += upsp;
            mvprintw(2, 1, "%sは%sを放った!\t\t\t\t\t\t\t\t",hero.heroname,hero.skillbox[highlight]);
            mvprintw(3,1,"SPを%d回復！\t\t\t\t\t\t\t\t\t\t\t\t\t",upsp);
            mvprintw(9, 0, "SP %d\t\t", hero.sp);
            refresh();
            sleep(1);
        }else{
            mvprintw(2, 1, "HPが不足しています\t\t\t\t\t");
            refresh();
            sleep(1);
            return;
        }
    }
}