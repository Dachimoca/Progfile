#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void start_game_screen(int argc, char **argv) {
    int max_y, max_x;
    int ch;
    int title_flag=0;   /*タイトル描画フラグ*/
    int highlight = 0;  /* 0: START, 1: EXIT*/
    FILE *fp;                   /*ファイルポインタ*/
    DEFALT_EXP = 100;

    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    
    if(max_y<26 || max_x<85){
        int ch;
        while(1){
        getmaxyx(stdscr, max_y, max_x);
        mvprintw(0,0, "!!SCREEN_ERROR!!");
        mvprintw(1,0, "画面サイズ26 x 85以上に設定してください");
        mvprintw(2,0, "現在のサイズ %d x %d",max_y,max_x);
        mvprintw(3,0, "zキーまたはENTERを押すと終了します");
        mvprintw(4,0, "!!SCREEN_ERROR!!");
        refresh();
        usleep(10000);
            ch=getch();
            if(ch=='z' || ch=='\n'){
                break;
            }
        }
        return;
    }

    /* メニュー項目の表示位置*/
    int start_y = max_y - 4;
    int start_x = max_x / 2 - 18;
    int continue_y = max_y - 4;
    int continue_x = max_x / 2 - 8;
    int help_y = max_y - 4;
    int help_x = max_x / 2 + 5;
    int exit_y = max_y - 4;
    int exit_x = max_x / 2 + 14;
    

    while (1) {
        clear();
        show_title(max_y,max_x,title_flag);
        title_flag=1;

        /* メニュー表示*/
        if (highlight == 0) {
            attron(A_REVERSE);
            mvprintw(start_y, start_x, "[START]");
            attroff(A_REVERSE);
            mvprintw(continue_y, continue_x, "[CONTINUE]");
            mvprintw(help_y, help_x, "[HELP]");
            mvprintw(exit_y, exit_x, "[EXIT]");
            mvprintw(help_y-1, help_x-18, "新しいデータでスタートする");
        }else if(highlight == 1){
            attron(A_REVERSE);
            mvprintw(continue_y, continue_x, "[CONTINUE]");
            attroff(A_REVERSE);
            mvprintw(start_y, start_x, "[START]");
            mvprintw(help_y, help_x, "[HELP]");
            mvprintw(exit_y, exit_x, "[EXIT]");
            mvprintw(help_y-1, help_x-18, "前回のデータでスタートする");
        }else if(highlight == 2){
            attron(A_REVERSE);
            mvprintw(help_y, help_x, "[HELP]");
            attroff(A_REVERSE);
            mvprintw(start_y, start_x, "[START]");
            mvprintw(continue_y, continue_x, "[CONTINUE]");
            mvprintw(exit_y, exit_x, "[EXIT]");
            mvprintw(help_y-1, help_x-15, "ヘルプ画面を表示する");
        }else {
            mvprintw(start_y, start_x, "[START]");
            mvprintw(continue_y, continue_x, "[CONTINUE]");
            mvprintw(help_y, help_x, "[HELP]");
            mvprintw(help_y-1, help_x-13, "ゲームを終了する");
            attron(A_REVERSE);
            mvprintw(exit_y, exit_x, "[EXIT]");
            attroff(A_REVERSE);
        }
        mvprintw(help_y+1, help_x-22, "矢印キーで選択しzキーまたはENTERで実行");
        /* 入力処理*/
        ch = getch();
        switch (ch) {
            case KEY_RIGHT:
                highlight = (highlight + 1) % 4;
                break;
            case KEY_LEFT:
                highlight = (highlight - 1) % 4;
            if(highlight<0){
                highlight=3;
            }
                break;
            case 'z':
            case '\n':
                title_flag=0;
                if (highlight == 0) {
                    /* START選択時の処理*/
                    start_flag=1;
                    floor_check=0;
                    hub(argc,argv);
                    exit(0);
                }else if(highlight == 1){
                    if(argc == 2 && start_flag == -1){
                        for (int i = 1; i < argc; i++) {
                            if ((fp = fopen(argv[i], "r")) == NULL) { // ファイルを開く
                                mvprintw(help_y-1, help_x-18, "ファイルを開けませんでした");
                                refresh();
                                sleep(1);
                            } else {
                                loadgame(argc,argv,fp);
                                mvprintw(help_y-1, help_x-12, "ファイル読み込み成功！");
                                fclose(fp); // ファイルを閉じる
                                refresh();
                                sleep(1);
                                start_flag=0;
                                DEFALT_EXP=hero.exp_line;
                                hub(argc,argv);
                            }
                        }
                    }else if (start_flag == -1){
                        mvprintw(help_y-1, help_x-18, "読み込むデータが存在しません");
                        refresh();
                        sleep(1);
                    }else{
                    start_flag=0;
                    DEFALT_EXP=hero.exp_line;
                    hub(argc,argv);
                    exit(0);
                    }
                }else if(highlight == 2){
                    help();
                    break;
                }else {
                    /* EXIT選択時の処理*/
                    endwin();
                    printf("Game Exit!\n");
                    exit(0);
                }
                break;
            default:
                break;
        }

        refresh();
        usleep(10000);
    }
}