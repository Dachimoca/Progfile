/*メイン画面の処理・描画を行う場所*/

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

int start_flag=-1;

/* ゲームのメイン画面となるhub関数*/
void hub(int argc, char **argv) {
    int max_y, max_x;
    int ch;
    int floor; /*階層*/
    int highlight = 0;  /* 0: 戦闘, 1: 探索, 2: アイテム, 3: タイトル*/
    int flag=0;
    
    if(start_flag==0){
        floor=hero.floor_score;
    }else{
        floor=1;
    }
    

    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    /* プレイヤーデータの初期化*/
    if(start_flag==1){
    srand(time(NULL));
        hero = (Hero){
            "",       /*名前*/
            1,             /*レベル*/
            0,              /*経験値*/
            rand()%18 + 9,  /*HP*/
            rand()%18 + 9,  /*SP*/
            rand()%15 + 3,  /*攻撃*/
            rand()%15 + 3,  /*防御*/
            rand()%15 + 3,  /*速度*/
            0,              /*スコア*/
            1,              /*到達階層*/
            DEFALT_EXP      /*初期経験値*/
        };
        srand(time(NULL));
        int Rd = rand() % 4 + 1;
        if(Rd==1){
            hero.mig = "火";
        }else if(Rd==2){
            hero.mig = "水";
        }else if(Rd==3){
            hero.mig = "氷";
        }else if(Rd==4){
            hero.mig = "雷";
        }
        create_heroname(max_x,max_y);
    }
    while (1) {
        clear();

        /* プレイヤー情報表示*/
        show_player();
        

        /*階層の表示*/
        mvprintw(max_y/2, max_x / 2 - 5, "第　%d　層", floor);
        if(floor==100){
            mvprintw(max_y/2+1, max_x / 2 - 5, "最後の部屋");
        }else if(floor%5==0){
            mvprintw(max_y/2+1, max_x / 2 - 5, "BOSS戦");
        }else if(floor>100){
            mvprintw(max_y/2+1, max_x / 2 - 10, "★エクストラステージ★");
        }
        /* メニュー表示*/
        show_menu(max_x,max_y,highlight);

        /* 入力処理*/
        ch = getch();
        switch (ch) {
            case KEY_RIGHT:
                highlight = (highlight + 1) % 5;
                break;
            case KEY_LEFT:
                highlight = (highlight + 4) % 5;  /* 逆方向に移動*/
                break;
            case 'z':
            case '\n':
                if (highlight == 0) {
                    while (1) {
                        if(floor==1){
                            battle(floor,argc,argv);
                            floor++;
                            hero.floor_score++;
                            flag=1;
                            break;
                        }else{
                            mvprintw(max_y - 5,max_x / 2 - 28, "info:階層を選択(zまたはENTERキーで実行。それ以外でキャンセル)\t\t\t\t\t");
                            if (highlight == 0) {
                                attron(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 - 12, "「%d層目」",floor);
                                attroff(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 + 8, "「%d層目」",floor-1);
                            }else{
                                attron(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 + 8, "「%d層目」",floor-1);
                                attroff(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 - 12, "「%d層目」",floor);
                            }
                            flag=0;
                        }
                        /* 戦闘の処理(battle関数を起動させる)*/
                        ch = getch();
                        switch(ch){
                        case KEY_RIGHT:
                            highlight = (highlight + 1) % 2;
                            break;
                        case KEY_LEFT:
                            highlight = (highlight + 1) % 2;  /* 逆方向に移動*/
                            break;
                        case 'z':
                        case '\n':
                            if(highlight==0){
                                battle(floor,argc,argv);
                                floor++;
                                hero.floor_score++;
                                flag=1;
                                break;
                            }else{
                                highlight=0;
                                battle(floor-1,argc,argv);
                                flag=1;
                                break;
                            }
                        default:
                            highlight=0;
                            flag=1;
                            break;
                        }
                        if(flag==1){
                            flag=0;
                            break;
                        }
                    }
                } else if (highlight == 1) {
                    /* 探索の処理(階層探索チェッカーを1にし、search関数を起動させる)*/
                    if(floor_check==0){
                    floor_check = 1;
                        int rd=rand()%10+1;
                        if(rd==1){
                            mvprintw(2, 0, "周囲を探索していると、何か煌めくものが落ちていた．．．");
                            refresh();
                            sleep(1);
                            passive_search();
                        }else if(rd==2){
                            mvprintw(2, 0, "周囲を探索していると、怪しげな出店を見つけた．．．");
                            refresh();
                            sleep(1);
                            shop_event(max_x,max_y);
                        }else if(rd==3){
                            mvprintw(2, 0, "周囲を探索していると、輝く泉を見つけた．．．");
                            refresh();
                            sleep(1);
                            heal_event(max_x,max_y);
                        }else if(rd==4){
                            mvprintw(2, 0, "周囲を探索していると、壁に割れ目がある所を見つけた．．．");
                            refresh();
                            sleep(1);
                            damage_event(max_x,max_y);
                        }else if(rd==5){
                            mvprintw(2, 0, "周囲を探索していると、怪しげな出店を見つけた．．．");
                            refresh();
                            sleep(1);
                            shop_event(max_x,max_y);
                        }else if(rd==6){
                            mvprintw(2, 0, "周囲を探索していると、何かが落ちていた．．．");
                            refresh();
                            sleep(1);
                            search();
                        }else if(rd==7){
                            mvprintw(2, 0, "周囲を探索していると、何かが落ちていた．．．");
                            refresh();
                            sleep(1);
                            search();
                        }else if(rd==8){
                            mvprintw(2, 0, "周囲を探索していると、何かが落ちていた．．．");
                            refresh();
                            sleep(1);
                            search();
                        }else if(rd==9){
                            mvprintw(2, 0, "周囲を探索していると、何かが落ちていた．．．");
                            refresh();
                            sleep(1);
                            search();
                        }else{
                            mvprintw(2, 0, "周囲を探索していると、何かが落ちていた．．．");
                            refresh();
                            sleep(1);
                            search();
                        }
                    }else{
                        mvprintw(2,0, "既に探索済みです");
                        refresh();
                        sleep(1);
                    }
                } else if (highlight == 2) {
                    /* アイテムの処理(item関数を起動させる)*/
                    item(battle_flag,0);
                } else if (highlight == 3) {
                    /* セーブの処理(savegame関数を起動させる)*/
                    int save_flag=1;
                    highlight =0;
                    mvprintw(max_y - 5,0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                    mvprintw(max_y - 5, max_x / 2 - 12, "info:データをセーブしますか？\t\t\t\t\t");
                    refresh();
                    usleep(500000);
                    while(1){
                        if (highlight == 0) {
                                attron(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 - 12, "「はい」");
                                attroff(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 + 8, "「いいえ」");
                            }else{
                                attron(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 + 8, "「いいえ」");
                                attroff(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 - 12, "「はい」");
                            }
                        
                        
                        ch = getch();
                        switch(ch){
                            case KEY_RIGHT:
                                highlight = (highlight + 1) % 2;
                                break;
                            case KEY_LEFT:
                                highlight = (highlight + 1) % 2;  /* 逆方向に移動*/
                                break;
                            case 'z':
                            case '\n':
                            if(highlight==0){
                                hero.exp_line = DEFALT_EXP;
                                savegame(max_x,max_y);
                                save_flag=0;
                                break;
                            }else{
                                save_flag=0;
                                break;
                            }
                            default:
                            break;
                        }
                        if(save_flag!=1){
                            highlight =3;
                            break;
                        }
                    }
                } else if (highlight == 4) {
                    /* タイトル選択時の処理*/
                    highlight =0;
                    mvprintw(max_y - 5,0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                    mvprintw(max_y - 5, max_x / 2 - 12, "info:データをセーブしますか？\t\t\t\t\t");
                    refresh();
                    usleep(500000);
                    while(1){
                        
                        
                        if (highlight == 0) {
                                attron(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 - 12, "「はい」");
                                attroff(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 + 8, "「いいえ」");
                            }else{
                                attron(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 + 8, "「いいえ」");
                                attroff(A_REVERSE);
                                mvprintw(max_y - 4, max_x / 2 - 12, "「はい」");
                            }
                        
                        
                        ch = getch();
                        switch(ch){
                            case KEY_RIGHT:
                                highlight = (highlight + 1) % 2;
                                break;
                            case KEY_LEFT:
                                highlight = (highlight + 1) % 2;  /* 逆方向に移動*/
                                break;
                            case 'z':
                            case '\n':
                            if(highlight==0){
                                hero.exp_line = DEFALT_EXP;
                                savegame(max_x,max_y);
                                start_game_screen(argc,argv);
                                return;
                            }else{
                                hero.exp_line = DEFALT_EXP;
                                start_game_screen(argc,argv);
                                return;
                            }
                            default:
                            break;
                        }
                    }
                }
                break;
            default:
                break;
        }
        refresh();
        usleep(10000);
    }
}

void shop_event(int max_x,int max_y){
    int ch;
    int Rd_item1 = rand() % 10 + 1; //ランダム武器
    int Rd_item2 = rand() % 10 + 1; //ランダム防具
    int Rd_item3 = rand() % 10 + 1; //ランダムアイテム
    int item1_score,item2_score,item3_score; //それぞれの価格
    int flag=0; //購入フラグ
    srand(time(NULL));
    while(1){
        mvprintw(2, 1, "いらっしゃい。ここはスコアで武器や防具を1つ買うことができるぞ。\t\t\t");
        mvprintw(3, 1, "1～3のキーを入力して選んでくれ。(それ以外を入力すると店を出る)\t\t\t");
        refresh();
        sleep(2);
        if(hero.lv<10){
            if(Rd_item1 == 1){
                mvprintw(16,0, "[1] 石の剣 [500 SCORE] (ATK+7)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=500;
            }else if(Rd_item1 == 2){
                mvprintw(16,0, "[1] 石の大剣 [700 SCORE] (ATK+10 DEX-10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=700;
            }else if(Rd_item1 == 3){
                mvprintw(16,0, "[1] 銅の剣 [300 SCORE] (ATK+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=300;
            }else if(Rd_item1 == 4){
                mvprintw(16,0, "[1] 銅の大剣 [400 SCORE] (ATK+7 DEX-7)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=400;
            }else if(Rd_item1 == 5){
                mvprintw(16,0, "[1] 木刀 [100 SCORE] (ATK+3)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=100;
            }else{
                mvprintw(16,0, "[1] 棒切れ [10 SCORE] (ATK+1)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=10;
            }
            
            if(Rd_item2 == 1){
                mvprintw(17,0, "[2] 銀の鎧 [2000 SCORE] (DFF+15)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=2000;
            }else if(Rd_item2 == 2){
                mvprintw(17,0, "[2] 銅の鎧 [1000 SCORE] (DFF+10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=1000;
            }else if(Rd_item2 == 3){
                mvprintw(17,0, "[2] 魔法使いの服 [800 SCORE] (DFF+6 SP+60)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=800;
            }else if(Rd_item2 == 4){
                mvprintw(17,0, "[2] 木の鎧 [500 SCORE] (DFF+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=500;
            }else{
                mvprintw(17,0, "[2] 厚紙 [10 SCORE] (DFF+1)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=10;
            }
            
            if(Rd_item3 == 1){
                mvprintw(18,0, "[3] いやしそう [500 SCORE] (HP+30 SP+30)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=500;
            }else if(Rd_item3 == 2){
                mvprintw(18,0, "[3] 特薬草 [600 SCORE] (HP+120)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=600;
            }else if(Rd_item3 == 3){
                mvprintw(18,0, "[3] 上薬草 [300 SCORE] (HP+60)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=300;
            }else if(Rd_item3 == 4){
                mvprintw(18,0, "[3] 薬草 [100 SCORE] (HP+20)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=100;
            }else{
                mvprintw(18,0, "[3] ミニポーション [30 SCORE] (HP+5 SP+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=30;
            }
            
        }else if(hero.lv>10 && hero.lv<100){
            
            if(Rd_item1 == 1){
                mvprintw(16,0, "[1] 鋼の剣 [5000 SCORE] (ATK+35)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=5000;
            }else if(Rd_item1 == 2){
                mvprintw(16,0, "[1] 鋼の大剣 [7000 SCORE] (ATK+50 DEX-50)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=7000;
            }else if(Rd_item1 == 3){
                mvprintw(16,0, "[1] 金の剣 [3000 SCORE] (ATK+25)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=3000;
            }else if(Rd_item1 == 4){
                mvprintw(16,0, "[1] 金の大剣 [4000 SCORE] (ATK+30 DEX-30)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=4000;
            }else if(Rd_item1 == 5){
                mvprintw(16,0, "[1] やすもの魔剣 [200 SCORE] (ATK+10 SP+10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=200;
            }else if(Rd_item1 == 6){
                mvprintw(16,0, "[1] 炎の杖 [3000 SCORE] (SP+10 MIG=火変換)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=3000;
            }else if(Rd_item1 == 7){
                mvprintw(16,0, "[1] 水流の杖 [3000 SCORE] (SP+10 MIG=水変換)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=3000;
            }else if(Rd_item1 == 8){
                mvprintw(16,0, "[1] 氷山の杖 [3000 SCORE] (SP+10 MIG=氷変換)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=3000;
            }else if(Rd_item1 == 9){
                mvprintw(16,0, "[1] 雷鳴の杖 [3000 SCORE] (SP+10 MIG=雷変換)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=3000;
            }else{
                mvprintw(16,0, "[1] 鉄の剣 [1350 SCORE] (ATK+12)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=1350;
            }
            
            if(Rd_item2 == 1){
                mvprintw(17,0, "[2] 魔鉄鉱の鎧 [42000 SCORE] (DFF+80)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=42000;
            }else if(Rd_item2 == 2){
                mvprintw(17,0, "[2] あぶない鎧 [30000 SCORE] (DFF+100 HP=10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=30000;
            }else if(Rd_item2 == 3){
                mvprintw(17,0, "[2] 癒しの鎧 [25000 SCORE] (DFF-10 HP+100)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=25000;
            }else if(Rd_item2 == 4){
                mvprintw(17,0, "[2] 風の鎧 [12000 SCORE] (DFF+25 DEX+50)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=12000;
            }else if(Rd_item2 == 5){
                mvprintw(17,0, "[2] 鋼の鎧 [10000 SCORE] (DFF+40)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=10000;
            }else if(Rd_item2 == 6){
                mvprintw(17,0, "[2] 金の鎧 [8000 SCORE] (DFF+30)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=8000;
            }else if(Rd_item2 == 7){
                mvprintw(17,0, "[2] 怒りの鎧 [7500 SCORE] (DFF+15 ATK+15)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=7500;
            }else if(Rd_item2 == 8){
                mvprintw(17,0, "[2] 魔導士の服 [8000 SCORE] (DFF+12 SP+120)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=8000;
            }else if(Rd_item2 == 9){
                mvprintw(17,0, "[2] 全知の鎧 [5000 SCORE] (ALL+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=500;
            }else{
                mvprintw(17,0, "[2] 重たい鎧 [3600 SCORE] (DFF+30 DEX-30)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=3600;
            }
            
            if(Rd_item3 == 1){
                mvprintw(18,0, "[3] メガポーション [90000 SCORE] (HP+1500 SP+1500)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=90000;
            }else if(Rd_item3 == 2){
                mvprintw(18,0, "[3] ダイヤモンド [1000000 SCORE] (ALL+77)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=1000000;
            }else if(Rd_item3 == 3){
                mvprintw(18,0, "[3] 怒っているお面 [50000 SCORE] (ATK x 2.0 DEX / 2.0)\t\t\t\t\t\t\t\t\t\t");
                item3_score=50000;
            }else if(Rd_item3 == 4){
                mvprintw(18,0, "[3] 悩んでいるお面 [50000 SCORE] (DFF x 2.0 ATK / 2.0)\t\t\t\t\t\t\t\t\t\t");
                item3_score=50000;
            }else if(Rd_item3 == 5){
                mvprintw(18,0, "[3] 笑っているお面 [50000 SCORE] (DEX x 2.0 DFF / 2.0)\t\t\t\t\t\t\t\t\t\t");
                item3_score=50000;
            }else if(Rd_item3 == 6){
                mvprintw(18,0, "[3] アドレナリン注射 [15000 SCORE] (ATK x 1.5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=15000;
            }else if(Rd_item3 == 7){
                mvprintw(18,0, "[3] プロテイン接種 [15000 SCORE] (DFF x 1.5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=15000;
            }else if(Rd_item3 == 8){
                mvprintw(18,0, "[3] ブースト獲得 [15000 SCORE] (DEX x 1.5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=15000;
            }else if(Rd_item3 == 9){
                mvprintw(18,0, "[3] ハイポーション [9000 SCORE] (HP+150 SP+150)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=9000;
            }else{
                mvprintw(18,0, "[3] ポーション [3000 SCORE] (HP+50 SP+50)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=3000;
            }
            
        }else{
            if(Rd_item1 == 1){
                mvprintw(16,0, "[1] 鉄の剣 [1350 SCORE] (ATK+12)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=1350;
            }else if(Rd_item1 == 2){
                mvprintw(16,0, "[1] 鉄の大剣 [1700 SCORE] (ATK+20 DEX-20)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=800;
            }else if(Rd_item1 == 3){
                mvprintw(16,0, "[1] 銀の剣 [800 SCORE] (ATK+8)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=800;
            }else if(Rd_item1 == 4){
                mvprintw(16,0, "[1] 銀の大剣 [1200 SCORE] (ATK+16 DEX-16)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=1200;
            }else if(Rd_item1 == 5){
                mvprintw(16,0, "[1] 石の剣 [500 SCORE] (ATK+7)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=500;
            }else if(Rd_item1 == 6){
                mvprintw(16,0, "[1] 石の大剣 [700 SCORE] (ATK+10 DEX-10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=700;
            }else if(Rd_item1 == 7){
                mvprintw(16,0, "[1] 銅の剣 [300 SCORE] (ATK+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=300;
            }else if(Rd_item1 == 8){
                mvprintw(16,0, "[1] 銅の大剣 [400 SCORE] (ATK+7 DEX-7)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=400;
            }else if(Rd_item1 == 9){
                mvprintw(16,0, "[1] 木刀 [100 SCORE] (ATK+3)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=100;
            }else{
                mvprintw(16,0, "[1] 棒切れ [10 SCORE] (ATK+1)\t\t\t\t\t\t\t\t\t\t\t\t");
                item1_score=10;
            }

            if(Rd_item2 == 1){
                mvprintw(17,0, "[2] 重たい鎧 [3600 SCORE] (DFF+30 DEX-30)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=3600;
            }else if(Rd_item2 == 2){
                mvprintw(17,0, "[2] 鉄の鎧 [3000 SCORE] (DFF+20)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=3000;
            }else if(Rd_item2 == 3){
                mvprintw(17,0, "[2] 大樹の鎧 [4000 SCORE] (DFF+15 HP+100)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=4000;
            }else if(Rd_item2 == 4){
                mvprintw(17,0, "[2] 豪華な鎧 [10000 SCORE] (DFF+50)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=10000;
            }else if(Rd_item2 == 5){
                mvprintw(17,0, "[2] とげ鎧 [1500 SCORE] (DFF+20 HP-20)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=1500;
            }else if(Rd_item2 == 6){
                mvprintw(17,0, "[2] 銀の鎧 [2000 SCORE] (DFF+15)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=2000;
            }else if(Rd_item2 == 7){
                mvprintw(17,0, "[2] 銅の鎧 [1000 SCORE] (DFF+10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=1000;
            }else if(Rd_item2 == 8){
                mvprintw(17,0, "[2] 魔法使いの服 [800 SCORE] (DFF+6 SP+60)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=800;
            }else if(Rd_item2 == 9){
                mvprintw(17,0, "[2] 木の鎧 [500 SCORE] (DFF+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=500;
            }else{
                mvprintw(17,0, "[2] 厚紙 [10 SCORE] (DFF+1)\t\t\t\t\t\t\t\t\t\t\t\t");
                item2_score=10;
            }
            
            if(Rd_item3 == 1){
                mvprintw(18,0, "[3] ポーション [3000 SCORE] (HP+50 SP+50)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=3000;
            }else if(Rd_item3 == 2){
                mvprintw(18,0, "[3] 赤のブレスレット [1000 SCORE] (ATK+10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=1000;
            }else if(Rd_item3 == 3){
                mvprintw(18,0, "[3] 青のブレスレット [1000 SCORE] (DFF+10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=1000;
            }else if(Rd_item3 == 4){
                mvprintw(18,0, "[3] 黄のブレスレット [1000 SCORE] (ATK+5 DFF+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=1000;
            }else if(Rd_item3 == 5){
                mvprintw(18,0, "[3] 羽の耳飾り [800 SCORE] (DEX+10)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=800;
            }else if(Rd_item3 == 6){
                mvprintw(18,0, "[3] いやしそう [500 SCORE] (HP+30 SP+30)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=500;
            }else if(Rd_item3 == 7){
                mvprintw(18,0, "[3] 特薬草 [600 SCORE] (HP+120)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=600;
            }else if(Rd_item3 == 8){
                mvprintw(18,0, "[3] 上薬草 [300 SCORE] (HP+60)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=300;
            }else if(Rd_item3 == 9){
                mvprintw(18,0, "[3] 薬草 [100 SCORE] (HP+20)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=100;
            }else{
                mvprintw(18,0, "[3] ミニポーション [30 SCORE] (HP+5 SP+5)\t\t\t\t\t\t\t\t\t\t\t\t");
                item3_score=30;
            }
        }

        refresh();

        /* 入力処理 */
        ch = getch();

        switch (ch) {
            case '1':
                if(item1_score <= hero.score){
                    hero.score -= item1_score;
                    if(hero.lv<10){
                        if(Rd_item1 == 1){
                            hero.atk+=7;
                        }else if(Rd_item1 == 2){
                            hero.atk+=10;
                            hero.dex-=10;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 3){
                            hero.atk+=5;
                        }else if(Rd_item1 == 4){
                            hero.atk+=7;
                            hero.dex-=7;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 5){
                            hero.atk+=3;
                        }else{
                            hero.atk+=1;
                        }
                    }else if(hero.lv>10 && hero.lv<100){
                        if(Rd_item1 == 1){
                            hero.atk+=35;
                        }else if(Rd_item1 == 2){
                            hero.atk+=50;
                            hero.dex-=50;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 3){
                            hero.atk+=25;
                        }else if(Rd_item1 == 4){
                            hero.atk+=30;
                            hero.dex-=30;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 5){
                            hero.atk+=10;
                            hero.sp+=10;
                        }else if(Rd_item1 == 6){
                            hero.sp+=10;
                            hero.mig="火";
                        }else if(Rd_item1 == 7){
                            hero.sp+=10;
                            hero.mig="水";
                        }else if(Rd_item1 == 8){
                            hero.sp+=10;
                            hero.mig="氷";
                        }else if(Rd_item1 == 9){
                            hero.sp+=10;
                            hero.mig="雷";
                        }else{
                            hero.atk+=12;
                        }
                    }else{
                        
                        if(Rd_item1 == 1){
                        hero.atk += 12;
                        }else if(Rd_item1 == 2){
                            hero.atk += 20;
                            hero.dex -= 20;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 3){
                            hero.atk += 8;
                        }else if(Rd_item1 == 4){
                            hero.atk += 16;
                            hero.dex -= 16;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 5){
                            hero.atk += 7;
                        }else if(Rd_item1 == 6){
                            hero.atk += 10;
                            hero.dex -= 10;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 7){
                            hero.atk += 5;
                        }else if(Rd_item1 == 8){
                            hero.atk += 7;
                            hero.dex -= 7;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item1 == 9){
                            hero.atk += 3;
                        }else{
                        hero.atk += 1;
                        }
                    }
                    
                    flag = 1;
                    mvprintw(3, 1, "毎度あり！\t\t\t\t\t\t\t\t\t\t\t\t");
                    refresh();
                    sleep(2);
                } else {
                    mvprintw(3, 1, "金が足りないぞ。\t\t\t\t\t\t\t\t\t\t\t\t");
                    refresh();
                    sleep(1);
                }
                break;
            case '2':
                if(item2_score <= hero.score){
                    hero.score -= item2_score;
                    
                    
                    if(hero.lv<10){
                        if(Rd_item2 == 1){
                            hero.dff+=15;
                        }else if(Rd_item2 == 2){
                            hero.dff+=10;
                        }else if(Rd_item2 == 3){
                            hero.dff+=6;
                            hero.sp+=60;
                        }else if(Rd_item2 == 4){
                            hero.dff+=5;
                        }else{
                            hero.dff+=1;
                        }
                    }else if(hero.lv>10 && hero.lv<100){
                        if(Rd_item2 == 1){
                            hero.dff+=80;
                        }else if(Rd_item2 == 2){
                            hero.dff+=100;
                            hero.hp=10;
                        }else if(Rd_item2 == 3){
                            hero.dff-=10;
                            hero.hp+=100;
                            if(hero.dff<0){
                                hero.dff=0;
                            }
                        }else if(Rd_item2 == 4){
                            hero.dff+=25;
                            hero.dex+=50;
                        }else if(Rd_item2 == 5){
                            hero.dff+=40;
                        }else if(Rd_item2 == 6){
                            hero.dff+=30;
                        }else if(Rd_item2 == 7){
                            hero.dff+=15;
                            hero.atk+=15;
                        }else if(Rd_item2 == 8){
                            hero.dff+=12;
                            hero.sp+=120;
                        }else if(Rd_item2 == 9){
                            hero.hp+=5;
                            hero.sp+=5;
                            hero.atk+=5;
                            hero.dff+=5;
                            hero.dex+=5;
                        }else{
                            hero.dff+=30;
                            hero.dex-=30;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }
                    }else{
                        
                        if(Rd_item2 == 1){
                            hero.dff += 30;
                            hero.dex -= 30;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item2 == 2){
                            hero.dff += 20;
                        }else if(Rd_item2 == 3){
                            hero.dff += 15;
                            hero.hp += 100;
                        }else if(Rd_item2 == 4){
                            hero.dff +=50;
                        }else if(Rd_item2 == 5){
                            hero.dff += 20;
                            hero.hp  -= 20;
                            if(hero.hp<0){
                                hero.hp=0;
                            }
                        }else if(Rd_item2 == 6){
                            hero.dff += 15;
                        }else if(Rd_item2 == 7){
                            hero.dff += 10;
                        }else if(Rd_item2 == 8){
                            hero.dff += 6;
                            hero.sp += 60;
                        }else if(Rd_item2 == 9){
                            hero.dff += 5;
                        }else{
                        hero.dff += 1;
                        }
                    }
                    flag = 1;
                    mvprintw(3, 1, "毎度あり！\t\t\t\t\t\t\t\t\t\t\t\t");
                    refresh();
                    sleep(2);
                } else {
                    mvprintw(3, 1, "金が足りないぞ。\t\t\t\t\t\t\t\t\t\t\t\t");
                    refresh();
                    sleep(1);
                }
                break;
            case '3':
                if(item3_score <= hero.score){
                    hero.score -= item3_score;
                    
                    if(hero.lv<10){
                        if(Rd_item3 == 1){
                            hero.hp+=30;
                            hero.sp+=30;
                        }else if(Rd_item3 == 2){
                            hero.hp+=120;
                        }else if(Rd_item3 == 3){
                            hero.hp+=60;
                        }else if(Rd_item3 == 4){
                            hero.hp+=20;
                        }else{
                            hero.hp+=5;
                            hero.sp+=5;
                        }
                    }else if(hero.lv>10 && hero.lv<100){
                        if(Rd_item3 == 1){
                            hero.hp+=1500;
                            hero.sp+=1500;
                        }else if(Rd_item3 == 2){
                            hero.hp+=77;
                            hero.sp+=77;
                            hero.atk+=77;
                            hero.dff+=77;
                            hero.dex+=77;
                        }else if(Rd_item3 == 3){
                            hero.atk*=2;
                            hero.dex=(int)hero.dex/2;
                            if(hero.dex<0){
                                hero.dex=0;
                            }
                        }else if(Rd_item3 == 4){
                            hero.dff*=2;
                            hero.atk=(int)hero.atk/2;
                            if(hero.atk<0){
                                hero.atk=0;
                            }
                        }else if(Rd_item3 == 5){
                            hero.dex*=2;
                            hero.dff=(int)hero.dff/2;
                            if(hero.dff<0){
                                hero.dff=0;
                            }
                        }else if(Rd_item3 == 6){
                            hero.atk=(int)hero.atk*1.5;
                        }else if(Rd_item3 == 7){
                            hero.dff=(int)hero.dff*1.5;
                        }else if(Rd_item3 == 8){
                            hero.dex=(int)hero.dex*1.5;
                        }else if(Rd_item3 == 9){
                            hero.hp+=150;
                            hero.sp+=150;
                        }else{
                            hero.hp+=50;
                            hero.sp+=50;
                        }
                    }else{
                        if(Rd_item3 == 1){
                            hero.hp += 50;
                            hero.sp += 50;
                        }else if(Rd_item3 == 2){
                            hero.atk += 10;
                        }else if(Rd_item3 == 3){
                            hero.dff += 10;
                        }else if(Rd_item3 == 4){
                            hero.atk += 5;
                            hero.dff += 5;
                        }else if(Rd_item3 == 5){
                            hero.dex += 10;
                        }else if(Rd_item3 == 6){
                            hero.hp += 30;
                            hero.sp += 30;
                        }else if(Rd_item3 == 7){
                            hero.hp += 120;
                        }else if(Rd_item3 == 8){
                            hero.hp += 60;
                        }else if(Rd_item3 == 9){
                            hero.hp += 20;
                        }else{
                        hero.hp += 5;
                        }
                    }
                    
                    flag = 1;
                    mvprintw(3, 1, "毎度あり！\t\t\t\t\t\t\t\t\t\t\t\t");
                    refresh();
                    sleep(2);
                } else {
                    mvprintw(3, 1, "金が足りないぞ。\t\t\t\t\t\t\t\t\t\t\t\t");
                    refresh();
                    sleep(1);
                }
            
                break;
            default:
                flag = 1;
                mvprintw(3, 1, "ちっ、ひやかしかよ。\t\t\t\t\t\t\t\t\t\t\t\t");
                refresh();
                sleep(1);
                break;
            
        }

        // 購入完了または店を出る場合の処理
        checkstatus();
        mvprintw(2, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        mvprintw(3, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        mvprintw(16, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        mvprintw(17, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        mvprintw(18, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");

        // flagが立ったらループを抜ける
        if(flag == 1){
            break;
        }
    }
}


void heal_event(int max_x,int max_y){
    int Rd = rand() % 6 + 1;
    mvprintw(3, 1, "HP・SPが%d回復した！\t\t\t\t\t\t\t\t\t",hero.lv * Rd);
    refresh();
    sleep(2);
    hero.hp += (hero.lv * Rd);
    hero.sp += (hero.lv * Rd);
}

void damage_event(int max_x,int max_y){
    mvprintw(3, 1, "中から棘が出てきた！");
    refresh();
    sleep(2);
    hero.hp = (int)hero.hp/2;
    if(hero.hp<0){
        hero.hp=0;
    }
}
