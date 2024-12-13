#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void skill_10shot(int max_x){
	int ch;
mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=60){
                            hero.sp-=60;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            int max_attack = rand()%10+1;
                            refresh();
                            mvprintw(2, 1, "%sはガトリング砲を放った!\t\t\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            int cnt=1;
                            for(int i=max_attack;i<10;i++){
                                if(monster.hp>0){
                                    mvprintw(3, 1, "%d回目！\t\t\t\t\t\t\t\t\t",cnt);
                                    int damage = (int)((hero.atk*2 - monster.dff/2)+rand()%10+1)/cnt;
                                    if(damage<=0)damage=rand()%3+1;
                                    monster.hp -= damage;
                                    refresh();
                                    if(monster.hp<0){
                                        monster.hp=0;
                                    }
                                    sleep(1);
                                    mvprintw(2, 1, "%d のダメージ!\t\t\t\t\t\t\t\t\t", damage);
                                    mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
                                    refresh();
                                    sleep(1);
                                    cnt++;
                                }
                            if(monster.hp<0){
                                break;
                                }
                            }
                            mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
                            refresh();
                            sleep(1);
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