/*バトルの動作・描画を行う場所*/

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void set_monster(char *name, int floor, int exp, int hp_mod, int sp_mod, int atk_mod, int dff_mod, int dex_mod) {
    monster = (Monster){
        name,
        floor,
        exp,
        floor * (rand() % hp_mod + (int)(floor / 4)+1),
        floor * (rand() % sp_mod + (int)(floor / 4)+1),
        floor * (rand() % atk_mod + (int)(floor / 4)+1),
        floor * (rand() % dff_mod + (int)(floor / 4)+1),
        floor * (rand() % dex_mod + (int)(floor / 4)+1),
    };
    monster.score = (monster.lv + monster.exp + monster.hp + monster.sp + monster.atk + monster.dff + monster.dex);
    srand(time(NULL));
    int Rd = rand() % 4 + 1;
    if(Rd==1){
        monster.mig = "火";
    }else if(Rd==2){
        monster.mig = "水";
    }else if(Rd==3){
        monster.mig = "氷";
    }else if(Rd==4){
        monster.mig = "雷";
    }
}

void create_monster(int floor) {
    srand(time(NULL));
    if(floor % 100 == 0) {
        set_monster("ラスボス", floor, 77777777,floor * (rand() % 6) + 5000,floor * (rand() % 6) + 5000,floor * (rand() % 6) + 5,floor * (rand() % 6) + 5,floor * (rand() % 6) + 5);
    } else if (floor % 5 == 0) {
        if (floor < 20) {
            set_monster("弱小ボスモンスター", floor, floor * (rand() % 60 + 60),floor * (rand() % 10) + 10, rand() % 10 + 3, rand() % 7 + 5, rand() % 7 + 5, rand() % 7 + 5);
        } else if (floor < 40) {
            set_monster("中堅ボスモンスター", floor, floor * 100 + 100,floor * (rand() % 20) + 20, rand() % 10 + 3, rand() % 7 + 9, rand() % 7 + 9, rand() % 7 + 9);
        } else if (floor < 60) {
            set_monster("強敵ボスモンスター", floor, floor * 300 + 500,floor * (rand() % 30) + 40, rand() % 10 + 3, rand() % 9 + 12, rand() % 9 + 12, rand() % 9 + 12);
        } else if (floor < 80) {
            set_monster("最強ボスモンスター", floor, floor * 500 + 2000,floor * (rand() % 40) + 80, rand() % 10 + 3, rand() % 10 + 15, rand() % 10 + 15, rand() % 10 + 15);
        } else if (floor < 100) {
            set_monster("真のボスモンスター", floor, floor * 2000 + 16000,floor * (rand() % 50) + 160, rand() % 10 + 3, rand() % 11 + 18, rand() % 11 + 18, rand() % 11 + 18);
        } else {
            set_monster("伝説のボスモンスター", floor, floor * 10000 + (floor * 999), rand() % (floor * 22) + 650, rand() % floor + 10, rand() % (int)(floor / 4) + 18, rand() % (int)(floor / 4) + 18, rand() % (int)(floor / 4) + 18);
        }
    } else {
        if (floor < 10) {
            set_monster("弱虫なモンスター", floor, floor * 12 + 8, rand() % 1 + 10, rand() % 1 + 10, rand() % 1 + 7, rand() % 1 + 7, rand() % 1 + 7);
        } else if (floor < 20) {
            set_monster("元気なモンスター", floor, floor * 16 + 5, rand() % 3 + 15, rand() % 3 + 15, rand() % 2 + 7, rand() % 2 + 7, rand() % 2 + 7);
        } else if (floor < 30) {
            set_monster("普通なモンスター", floor, floor * 28 + 9, rand() % 5 + 20, rand() % 5 + 15, rand() % 3 + 8, rand() % 3 + 8, rand() % 3 + 8);
        } else if (floor < 40) {
            set_monster("優れたモンスター", floor, floor * 30 + 13, rand() % 7 + 25, rand() % 7 + 10, rand() % 4 + 11, rand() % 4 + 11, rand() % 4 + 11);
        } else if (floor < 50) {
            set_monster("強いモンスター", floor, floor * 36 + 60, rand() % 10 + 25, rand() % 9 + 10, rand() % 5 + 13, rand() % 5 + 13, rand() % 5 + 13);
        } else if (floor < 60) {
            set_monster("強靭なモンスター", floor, floor * 380 + 125, rand() % 10 + 25, rand() % 9 + 10, rand() % 6 + 15, rand() % 6 + 15, rand() % 6 + 15);
        } else if (floor < 70) {
            set_monster("恐ろしいモンスター", floor, floor * 400 + 300, rand() % 50 + 125, rand() % 9 + 10, rand() % 7 + 17, rand() % 7 + 17, rand() % 7 + 17);
        } else if (floor < 80) {
            set_monster("優秀なモンスター", floor, floor * 420 + 1330, rand() % 75 + 185, rand() % 9 + 10, rand() % 9 + 19, rand() % 9 + 19, rand() % 9 + 19);
        } else if (floor < 90) {
            set_monster("最強のモンスター", floor, floor * 450 + 2530, rand() % 100 + 200, rand() % 9 + 10, rand() % 11 + 21, rand() % 11 + 21, rand() % 11 + 21);
        } else if (floor < 100) {
            set_monster("ラスボスの側近", floor, floor * 480 + 5060, rand() % 100 + 250, rand() % 14 + 10, rand() % 14 + 23, rand() % 14 + 23, rand() % 14 + 23);
        } else {
            set_monster("裏面モンスター", floor, floor * 480 + (floor * 100), rand() % (floor * 2) + 250, rand() % floor + 10, rand() % (int)(floor / 5) + 23, rand() % (int)(floor / 5) + 23, rand() % (int)(floor / 5) + 23);
        }
    }
}

void battle(int floor,int argc, char **argv) {
    create_monster(floor);

    int max_y, max_x;
    int ch;
    int luck = rand()%100+1; /*幸運判定*/
    int highlight = 0;  /* 0: 攻撃, 1: 防御,2:技能選択,3:アイテム*/
    int dff_flag = 0;  /*防御判定*/
    
    battle_flag=1;

    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    
    clear();
    show_player();
    show_monster(max_x);
    mvprintw(0, 0, "<ログ>");
    mvprintw(2, 1, "%s が現れた！\t\t\t",monster.monstername);
    refresh();
    sleep(1);
    /*パッシブアイテムの効果確認*/
    check_passive(luck,max_x);
    show_player();
    show_monster(max_x);
    refresh();
    while (1) {
        if (hero.hp <= 0) {
            mvprintw(3, 1, "GAME OVER...\t\t\t\t\t\t");
            refresh();
            sleep(2);
            floor_check = 0;
            battle_flag = 0;
            start_flag=-1;
            highlight=1;
            hero.exp_line = DEFALT_EXP;
            start_game_screen(argc,argv);
            return;
        }else if (monster.hp<=0){
            hero.exp += monster.exp;
            mvprintw(3, 1, "%sを倒した!\t\t\t\t\t",monster.monstername);
            refresh();
            sleep(1);
            check_level(max_y,max_x);  /*レベルアップ確認*/
            
            mvprintw(3, 1, "SCORE %d 点を獲得！\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t",monster.score);
            hero.score+=monster.score;
            mvprintw(13,0, "SCORE %d\t\t\t", hero.score);
            refresh();
            sleep(1);
            floor_check = 0;
            battle_flag = 0;
            highlight=1;
            return;
        }
        int skill_flag=0,item_flag=0;
        srand(time(NULL));
        clear();

        /* ログ表示枠*/
        mvprintw(0, 0, "<ログ>");
        mvprintw(2, 1, "zキーまたはENTERキーで行動を選択してください\t\t\t");

        /* プレイヤーとモンスター情報表示*/
        show_player();
        show_monster(max_x);

        /* 戦闘メニュー表示*/
        if (highlight == 0) {
            attron(A_REVERSE);
            mvprintw(15,0, "「攻撃」");
            attroff(A_REVERSE);
            mvprintw(15,15, "「防御」");
            mvprintw(15,27, "「技能選択」");
            mvprintw(15,45, "「アイテム」");
        } else if(highlight == 1) {
            attron(A_REVERSE);
            mvprintw(15,15, "「防御」");
            attroff(A_REVERSE);
            mvprintw(15,0, "「攻撃」");
            mvprintw(15,27, "「技能選択」");
            mvprintw(15,45, "「アイテム」");
        }else if(highlight == 2) {
            attron(A_REVERSE);
            mvprintw(15,27, "「技能選択」");
            attroff(A_REVERSE);
            mvprintw(15,0, "「攻撃」");
            mvprintw(15,15, "「防御」");
            mvprintw(15,45, "「アイテム」");
        }else {
            attron(A_REVERSE);
            mvprintw(15,45, "「アイテム」");
            attroff(A_REVERSE);
            mvprintw(15,0, "「攻撃」");
            mvprintw(15,15, "「防御」");
            mvprintw(15,27, "「技能選択」");
        }

        /* 入力処理*/
        ch = getch();
        if (hero.dex >= monster.dex) {  /* プレイヤーが先手*/
            
            switch (ch) {
                case KEY_RIGHT:
                    highlight = (highlight + 1) % 4;
                    break;
                case KEY_LEFT:
                    highlight = (highlight + 3) % 4;
                    break;
                case 'z':
                case '\n':
                    if (highlight == 0) {  /* 攻撃*/
                        hero_attack(luck,max_x);
                        if(monster.hp>0){
                        monster_attack(luck,max_x);
                        }
                } else if(highlight==1) {  /* 防御*/
                        dff_flag=1;
                        hero_defense(luck,dff_flag);
                        if(monster.hp>0){
                        monster_attack(luck,max_x);
                        }
                }else if(highlight == 2){   /*技能選択*/
                    skill_flag=skill_select(luck,skill_flag);
                }else if(highlight ==3){   /*アイテム*/
                    item_flag=item(battle_flag,item_flag);
                }
                if((monster.hp>0 && item_flag==1)|| (monster.hp>0 && skill_flag==1)){
                    monster_attack(luck,max_x);
                }
                    break;
                default:
                    break;
            }
          
        } else {  /* モンスターが先手*/
            switch (ch) {
                case KEY_RIGHT:
                    highlight = (highlight + 1) % 4;
                    break;
                case KEY_LEFT:
                    highlight = (highlight + 3) % 4;
                    break;
                case 'z':
                case '\n':
                    if(monster.hp>0){
                            monster_attack(luck,max_x);
                        }
                    if (highlight == 0 && hero.hp>0) {  /* 攻撃*/
                        if(hero.hp>0){
                            hero_attack(luck,max_x);
                        }
                } else if(highlight == 1 && hero.hp>0) {  /* 防御*/
                        if(hero.hp>0){
                            dff_flag=1;
                            hero_defense(luck,dff_flag);
                        }
                    }else if(highlight == 2 && hero.hp>0){   /*技能選択*/
                        if(hero.hp>0){
                            skill_flag=skill_select(luck,skill_flag);
                        }
                }else if(highlight ==3 && hero.hp>0){   /*アイテム*/
                        item_flag=item(battle_flag,item_flag);
                }
                    break;
                default:
                    break;
            }
        }
        if(dff_flag==1){ /* 防御状態の解除*/
            dff_flag=0;
            hero.dff/=2;
        }
        /* HPのチェック*/
        if (hero.hp <= 0) {
            mvprintw(3, 1, "GAME OVER...\t\t\t\t\t\t");
            refresh();
            sleep(2);
            floor_check = 0;
            battle_flag = 0;
            start_flag=-1;
            highlight=1;
            hero.exp_line = DEFALT_EXP;
            start_game_screen(argc,argv);
            return;
        } else if (monster.hp <= 0) {
            hero.exp += monster.exp;
            mvprintw(3, 1, "%sを倒した!\t\t\t\t\t",monster.monstername);
            refresh();
            sleep(1);
            check_level(max_y,max_x);  /*レベルアップ確認*/
            
            mvprintw(3, 1, "SCORE %d 点を獲得！\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t",monster.score);
            hero.score+=monster.score;
            mvprintw(13,0, "SCORE %d\t\t\t", hero.score);
            refresh();
            sleep(1);
            floor_check = 0;
            battle_flag = 0;
            highlight=1;
            return;
        }
        item_flag=0;
        refresh();
        usleep(10000);
    }
}

void checkstatus(){
    if(hero.hp<=0){
        hero.hp=0;
    }else if (hero.sp<=0){
        hero.sp=0;
    }else if (hero.atk<=0){
        hero.atk=0;
    }else if (hero.dff<=0){
        hero.dff=0;
    }else if (hero.dex<=0){
        hero.dex=0;
    }
    
    if(monster.hp<=0){
        monster.hp=0;
    }else if (monster.sp<=0){
        monster.sp=0;
    }else if (monster.atk<=0){
        monster.atk=0;
    }else if (monster.dff<=0){
        monster.dff=0;
    }else if (monster.dex<=0){
        monster.dex=0;
    }
}


int hero_attack(int luck,int max_x){
    luck = rand()%100+1; /*幸運判定*/
    int damage = (hero.atk/2 - monster.dff/2)+rand()%10+1;
    if(damage<=0)damage=(int)(rand() % hero.atk + 1)/10;
    if(luck<=5){
        damage*=2;
        mvprintw(2, 1, "クリティカル！\t\t\t\t\t\t\t\t");
        refresh();
        sleep(1);
    }
    monster.hp -= damage;
    mvprintw(2, 1, "%sの攻撃! %d のダメージ!\t\t\t\t",hero.heroname, damage);
    mvprintw(3, 1, "\t\t\t\t\t\t\t\t");
    if(monster.hp<0){
        monster.hp=0;
    }
    mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
    refresh();
    sleep(1);
    
    return damage;
}

void hero_defense(int luck,int dff_flag){
    int defense = hero.dff * 2;
    hero.dff = defense;
    mvprintw(2, 1, "%sは防御した!\t\t\t\t\t",hero.heroname);
    mvprintw(11, 0, "DFF %d\t\t", hero.dff);
    refresh();
    sleep(1);
}

void monster_attack(int luck,int max_x){
    luck = rand()%100+1; /*幸運判定*/
                int damage = (monster.atk/2 - hero.dff/2)+rand()%10+1;
                if(damage<=0)damage=(int)(rand() % monster.atk + 1)/10;
                        if(luck<=5){
                            damage*=2;
                            mvprintw(2, 1, "クリティカル！\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                        }
                    hero.hp -= damage;
                    mvprintw(2, 1, "%sの攻撃! %d のダメージ!\t\t\t\t",monster.monstername, damage);
                    mvprintw(3, 1, "\t\t\t\t\t\t\t\t");
                    if(hero.hp<0){
                            hero.hp=0;
                        }
                mvprintw(8, 0, "HP %d\t\t", hero.hp);
                refresh();
                sleep(1);
}

void check_level(int max_y,int max_x){
    
    while(hero.exp >= DEFALT_EXP){
        srand(time(NULL));
            if (hero.exp >= DEFALT_EXP) {
                hero.lv++;
                hero.exp -=DEFALT_EXP;
                if(hero.exp<0)hero.exp=0;
                (int)(DEFALT_EXP*=1.13);
                mvprintw(2, 1, "レベルアップ! Lv %d に上がった!\t\t\t\t", hero.lv);
                refresh();
                sleep(1);
                int uphp =  (rand() % hero.lv + 4)*(rand() % 4+1) ;
                int upsp =  rand() % hero.lv + 4;
                int upatk = rand() % hero.lv + 2;
                int updff = rand() % hero.lv + 2;
                int updex = rand() % hero.lv + 2;
                hero.hp +=uphp;
                hero.sp +=upsp;
                hero.atk +=upatk;
                hero.dff +=updff;
                hero.dex +=updex;
                show_player();
                mvprintw(3, 1, "hpが 「%d」 UP!,spが 「%d」 UP!,atkが 「%d」 UP!,dffが 「%d」 UP!,dexが 「%d」 UP!",uphp,upsp,upatk,updff,updex);
                refresh();
                sleep(1);
                if(hero.lv % 3 == 0){
                    random_skill(hero.lv,max_y,max_x);
                }
                }
            }
}