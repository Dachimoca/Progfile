#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void skill_slot(int max_x,int max_y){
    int ch;
    
    mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=100){
                            hero.sp-=100;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            refresh();
                            mvprintw(2, 1, "%sはスロットマシンを使った!\t\t\t\t\t\t\t\t",hero.heroname);
                            refresh();
                            sleep(1);
                            int rd = rand() % 100 + 1;
                            if(rd>50){
                                mvprintw(2, 1, "何も起きなかった...\t\t\t\t\t\t\t\t");
                                refresh();
                                sleep(1);
                            }else if(rd<50){
                                hero.atk+=100;
                                hero.dff+=100;
                                mvprintw(2, 1, "ATKとDFFが+100上昇!\t\t\t\t\t\t\t\t");
                                refresh();
                                sleep(1);
                            }else if(rd<40){
                                hero.score+=10000;
                                mvprintw(2, 1, "SCOREが10000点上昇!\t\t\t\t\t\t\t\t");
                                refresh();
                                sleep(1);
                            }else if(rd<30){
                                int damage = 7777;
                                monster.hp -= damage;
                                mvprintw(2, 1, "ラッキー！%d のダメージ!\t\t\t\t", damage);
                                mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                                if(monster.hp<0){
                                    monster.hp=0;
                                    }
                                mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
                                refresh();
                                sleep(1);
                            }else if(rd<20){
                                hero.exp+=10000;
                                mvprintw(2, 1, "EXPを10000点獲得!\t\t\t\t\t\t\t\t");
                                refresh();
                                sleep(1);
                            }else if(rd<10){
                                (int)(hero.hp*=1.2);
                                (int)(hero.sp*=1.2);
                                mvprintw(2, 1, "HPとSPが1.2倍上昇!\t\t\t\t\t\t\t\t");
                                refresh();
                                sleep(1);
                            }
                        }else{
                            mvprintw(2, 1, "SPが不足しています\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            break;
                        }
                    default:
                    }
                 break;
                }
                }