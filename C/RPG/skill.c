/*スキルの情報・使用・操作を格納する場所*/

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

int skill_select(int luck,int s_flag){    
    int max_y, max_x;
    int highlight = 0;  /* 0~8...スキル選択*/
    int ch;
    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    
    while (1) {
        luck = rand()%100+1; /*幸運判定*/
        skill_text(highlight);   /*スキルの説明表示*/
        refresh();
        mvprintw(15, 0, "スキルボックス(zキーまたはENTERキーで使用・xキーで戻る)");
        for (int i = 0; i < 8; i++) {
            if (highlight == i) {
                attron(A_REVERSE);
                mvprintw(i + 16, 0, " %s\t\t\t\t\t\t\t", hero.skillbox[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i + 16, 0, " %s\t\t\t\t\t\t\t", hero.skillbox[i]);
            }
        }
        
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
            if(hero.skillbox[highlight]==NULL){
                return 0;
            }
            if(strcmp(hero.skillbox[highlight],"[★]スラッシュ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_slash(max_x,5,1.5,1,highlight,"無");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]連撃")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=6){
                            hero.sp-=6;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            mvprintw(2, 1, "%sは連撃を放った!\t\t\t\t\t\t\t",hero.heroname);
                            refresh();
                            sleep(1);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
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
            }else if(strcmp(hero.skillbox[highlight],"[★]ドレイン")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=7){
                            hero.sp-=7;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            mvprintw(2, 1, "%sはドレインを放った!\t\t\t\t\t\t\t",hero.heroname);
                            refresh();
                            sleep(1);
                            int uphp = hero_attack(luck,max_x);
                            hero.hp+=uphp;
                            mvprintw(3,1,"hpを%d回復！\t\t\t\t\t\t\t\t",uphp);
                            mvprintw(8, 0, "HP %d\t\t", hero.hp);
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
            }else if(strcmp(hero.skillbox[highlight],"[★]毒撃")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=5){
                            hero.sp-=5;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            monster.hp -= 1;
                            mvprintw(2, 1, "%sは毒撃を放った! %d のダメージ!\t\t\t\t\t\t\t\t\t",hero.heroname,1);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            if(luck<=70){
                                int damage = rand()%90+10;
                                monster.hp -= damage;
                                mvprintw(3, 1, "追撃! %d のダメージ!\t\t\t\t\t\t\t\t", damage);
                                refresh();
                                sleep(1);
                            }
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
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
                            break;
                        }
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]幸運スラッシュ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=7){
                            hero.sp-=7;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            monster.hp -= 77;
                            mvprintw(2, 1, "%sは幸運スラッシュを放った! %d のダメージ!\t\t\t\t\t\t\t",hero.heroname,77);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            if(luck<=7){
                                monster.hp -= 777;
                                mvprintw(3, 1, "追撃! %d のダメージ!\t\t\t\t\t\t\t\t", 777);
                                refresh();
                                sleep(1);
                            }
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t");
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
                            break;
                        }
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]ファイア")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,7,1.1,highlight,"火");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]ウォーター")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,8,1.1,highlight,"水");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]アイス")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,9,1.1,highlight,"氷");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]サンダー")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,10,1.1,highlight,"雷");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★]ヒール")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_heal(17,10,highlight,0);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]スラッシュ・改")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_slash(max_x,18,2.0,1,highlight,"無");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]守りの一撃")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=20){
                            hero.sp-=20;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            refresh();
                            int damage = (int)((hero.dff*3 - monster.dff/2)+rand()%10+1);
                            if(damage<=0)damage=rand()%3+1;
                            monster.hp -= damage;
                            (int)(hero.dff /= 2);
                            if(hero.dff<=0){
                                hero.dff=0;
                            }
                            mvprintw(2, 1, "%sは守りの一撃を放った! %d のダメージ!\t\t\t\t\t\t\t\t\t",hero.heroname, damage);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            if(monster.hp<0){
                                monster.hp=0;
                                }
                            mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
                            mvprintw(11,0, "DFF %d\t\t", hero.dff);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★]3連撃")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=24){
                            hero.sp-=24;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            mvprintw(2, 1, "%sは3連撃を放った!\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★]一太刀")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        (int)(hero.dex/=2);
                        if(hero.dex<=0){
                            hero.dex=0;
                        }
                        skill_slash(max_x,45,3.0,1,highlight,"無");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]加速する拳")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        (int)(hero.dex+=50);
                        skill_slash(max_x,30,1.5,1,highlight,"無");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]アドレナリン")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,16,15,"ATK",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]プロテクト")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,16,15,"DFF",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]スピルリナ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,16,15,"DEX",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]ダウン")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,16,15,"ATK",2,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]ブレイク")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,16,15,"DFF",2,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]スロウ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,16,15,"DEX",2,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★]ヒーリング")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_heal(37,20,highlight,0);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]命削り")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.hp>1){
                            int hppw=(int)(hero.hp/=2);
                            (int)(hero.hp/=2);
                            if(hero.hp<=0){
                                hero.hp=1;
                            }
                            mvprintw(8, 0, "HP %d\t\t\t", hero.hp);
                            int damage = (int)((hppw*3 - monster.dff/2)+rand()%10+1);
                            if(damage<=0)damage=rand()%3+1;
                            monster.hp -= damage;
                            mvprintw(2, 1, "%sは命削りを放った! %d のダメージ!\t\t\t\t\t\t\t\t\t",hero.heroname, damage);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
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
                            break;
                        }
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]5連撃")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=30){
                            hero.sp-=30;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            mvprintw(2, 1, "%sは5連撃を放った!\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
                            hero_attack(luck,max_x);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★]一撃必殺")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_slash(max_x,50,5.0,1,highlight,"無");
                        if(monster.hp>0){
                        monster_attack(luck,max_x);
                        }
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]魔剣斬り")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=(int)(hero.sp/2) && hero.sp>0){
                            int damage = (int)((hero.atk/20) * (hero.sp/20));
                            monster.hp -= damage;
                            (int)(hero.sp/=2);
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            refresh();
                            mvprintw(2, 1, "%sは魔剣斬りを放った! %d のダメージ!\t\t\t\t\t\t\t\t\t",hero.heroname, damage);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            if(monster.hp<0){
                                monster.hp=0;
                                }
                            mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
                            refresh();
                            sleep(1);
                            checkstatus();
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ガトリング砲")==0){
                skill_10shot(max_x);
            }else if(strcmp(hero.skillbox[highlight],"[★★★]フレイム")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,28,1.8,highlight,"火");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ストーム")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,29,1.8,highlight,"水");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ブリザード")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,30,1.8,highlight,"氷");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ライトニング")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,31,1.8,highlight,"雷");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ドーピング")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,36,50,"ATK",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]プロテクション")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,36,50,"DFF",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]スピリチャ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,36,50,"DEX",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★]EXPブースト")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>0){
                            hero.sp=0;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            refresh();
                            monster.exp*=2;
                            mvprintw(2, 1, "%sはEXPブーストを放った!\t\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3,1,"敵の経験値が2倍に上昇！\t\t\t\t\t\t\t\t\t\t\t\t");
                            mvprintw(12,0, "DEX %d", hero.dex);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ラッキーハンド")==0){
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
                            mvprintw(2, 1, "%sはラッキーハンドを使った!\t\t\t\t\t\t\t\t",hero.heroname);
                            refresh();
                            sleep(1);
                            search();
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★]ケアリー")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_heal(67,40,highlight,0);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]火炎斬り")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=75){
                            skill_slash(max_x,75,2.5,1,highlight,"火");
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]水撃斬り")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=80){
                            skill_slash(max_x,80,2.5,1,highlight,"水");
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]氷穴斬り")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=85){
                            skill_slash(max_x,85,2.5,1,highlight,"氷");
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]雷撃斬り")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=90){
                            skill_slash(max_x,90,2.5,1,highlight,"雷");
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]キャノン砲")==0){
                skill_20shot(max_x);
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]ボルケニオン")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,58,3.5,highlight,"火");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]ポセシアン")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,59,3.5,highlight,"水");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]レイシオン")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,60,3.5,highlight,"氷");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]メガサンダー")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,61,3.5,highlight,"雷");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]スロットマシン")==0){
                skill_slot(max_x,max_y);
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]減衰")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,80,50,"全ステータス",2,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]SCOREブースト")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=200){
                            hero.sp-=200;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            refresh();
                            (int)(hero.score*=1.5);
                            mvprintw(2, 1, "%sはSCOREブーストを放った!\t\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3,1,"SCOREが1.5倍に上昇！\t\t\t\t\t\t\t\t\t\t\t\t");
                            mvprintw(13,0, "SCORE %d", hero.score);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]HP・SPチェンジ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=70){
                            hero.sp-=70;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            mvprintw(2, 1, "%sはHP・SPチェンジを使った!\t\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3, 1, "%sのHP・SPを変換した!\t\t\t\t\t\t\t\t",hero.heroname);
                            int tmp=hero.hp;
                            hero.hp=hero.sp;
                            hero.sp=tmp;
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]ATK・DFFチェンジ")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=70){
                            hero.sp-=70;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            mvprintw(2, 1, "%sはATK・DFFチェンジを使った!\t\t\t\t\t\t\t\t",hero.heroname);
                            refresh();
                            sleep(1);
                            int tmp=hero.atk;
                            hero.atk=hero.dff;
                            hero.dff=tmp;
                            mvprintw(2, 1, "%sのATK・DFFを変換した!\t\t\t\t\t\t\t\t",hero.heroname);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★]ケミスト")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_heal(117,80,highlight,0);
                    default:
                    }
                 break;
                }
            }
            
            
            
            else if(strcmp(hero.skillbox[highlight],"[★★★★★]最後の一撃")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.hp>=2){
                            hero.hp=1;
                            show_player();
                            refresh();
                            int damage = (int)((hero.atk*10 - monster.dff/2)+rand()%10+1);
                            if(damage<=0)damage=rand()%3+1;
                            monster.hp -= damage;
                            mvprintw(2, 1, "%sは最後の一撃を放った! %d のダメージ!\t\t\t\t\t\t\t\t\t",hero.heroname, damage);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            if(monster.hp<0){
                                monster.hp=0;
                                }
                            mvprintw(8, max_x/2-10, "HP %d\t\t", monster.hp);
                            refresh();
                            sleep(1);
                        }else{
                            mvprintw(2, 1, "HPが不足しています\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            break;
                        }
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]邪気払い")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=230){
                            hero.sp-=230;
                            show_player();
                            refresh();
                        /*ラスボスパッシブスキルを解除*/
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]無限攻撃")==0){
                int keepcnt = 1;
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                    ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp >= 350){
                            hero.sp -= 350;
                            mvprintw(9, 0, "SP %d\t\t\t", hero.sp);
                            refresh();
                            mvprintw(2, 1, "%sは無限攻撃を放った!\t\t\t\t\t\t\t\t\t", hero.heroname);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            while (1) {
                                int keeprnd = rand() % 100 + 1;
                                mvprintw(3, 1, "%d > %d", keepcnt, keeprnd);
                                mvprintw(4, 1, "%d回目！\t\t\t\t\t\t\t\t\t", keepcnt);
                                refresh();
                                usleep(250000);
                                int damage = (int)((hero.atk - monster.dff / 2) + rand() % 10 + 1) + (keepcnt * keeprnd);
                                if(damage <= 0) damage = rand() % 3 + 1;
                                monster.hp -= damage;
                                mvprintw(2, 1, "%d のダメージ!\t\t\t\t\t\t\t\t\t", damage);
                                mvprintw(8, max_x / 2 - 10, "HP %d\t\t", monster.hp);
                                refresh();
                                usleep(250000);
                                refresh();
                                if(monster.hp <= 0){
                                    monster.hp = 0;
                                    mvprintw(8, max_x / 2 - 10, "HP %d\t\t", monster.hp);
                                    mvprintw(4, 1, "%d回命中した！\t\t\t\t\t\t\t\t\t", keepcnt);
                                    refresh();
                                    sleep(1);
                                    break;
                                }
                                if(keepcnt >= keeprnd){
                                    mvprintw(4, 1, "%d回命中した！\t\t\t\t\t\t\t\t\t", keepcnt);
                                    refresh();
                                    sleep(1);
                                    break;
                                }
                                keepcnt++;
                            }
                        } else {
                            mvprintw(2, 1, "SPが不足しています\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            break;
                        }
                    default:
                        break;
                    }
                    break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]魔力補充")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_heal(1000,40,highlight,1);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]神力")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,120,100,"ATK",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]神守")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,120,100,"DFF",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]神速")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_updown(max_x,120,100,"DEX",1,highlight);
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]必要EXP削減")==0){
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
                            (int)(DEFALT_EXP*=0.9);
                            mvprintw(2, 1, "%sは必要EXP削減を放った!\t\t\t\t\t\t\t\t",hero.heroname);
                            mvprintw(3,1,"必要EXPが10％減少した！\t\t\t\t\t\t\t\t\t\t\t\t");
                            show_player();
                            mvprintw(13,0, "SCORE %d", hero.score);
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
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]アルティメット")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_magic(max_x,hero.sp,7.7,highlight,"無");
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]核")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        if(hero.sp>=1000){
                            hero.sp-=1000;
                            mvprintw(9, 0, "SP %d\t\t", hero.sp);
                            monster.hp -= 1000;
                            mvprintw(2, 1, "%sは核を放った! %d のダメージ!\t\t\t\t\t\t\t\t\t",hero.heroname,1000);
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t");
                            refresh();
                            sleep(1);
                            if(luck<=30){
                                int damage = monster.hp;
                                monster.hp -= damage;
                                mvprintw(3, 1, "核爆発によって相手は即死した! %d のダメージ!\t\t\t\t\t\t\t\t", damage);
                                refresh();
                                sleep(1);
                            }
                            mvprintw(3, 1, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
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
                            break;
                        }
                    default:
                    }
                 break;
                }
            }else if(strcmp(hero.skillbox[highlight],"[★★★★★]メディケイド")==0){
                mvprintw(2, 1, "スキルを使用しますか？zキーまたはENTERキーで実行xキーキャンセル");
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        skill_heal(117,160,highlight,0);
                    default:
                    }
                 break;
                }
            }
            return 1; /*battle関数へと戻る*/
            case 'x':
            /*使用していない場合*/
                return 0; /*battle関数へと戻る*/
            default:
                /*それ以外の場合*/
                return 0; /*battle関数へと戻る*/
            }
    refresh();
    usleep(10000);
    }
}