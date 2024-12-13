/*アイテムの情報・操作を格納する場所*/

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h"
#include "func.h"

void search(void) {
    int max_y, max_x;
    int item_flag=0; /*アイテム欄が空いてるかのチェック*/
    char* itemname;
    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    
    srand(time(NULL));
    
    int rd = rand()%22+1;
    
    switch(rd){
    case 1:
        itemname="経験値ドリンク(小)";
        break;
    case 2:
        itemname="経験値ドリンク(中)";
        break;
    case 3:
        itemname="経験値ドリンク(大)";
        break;
    case 4:
        itemname="経験値ドリンク(極大)";
        break;
    case 5:
        itemname="HP回復剤(小)";
        break;
    case 6:
        itemname="HP回復剤(中)";
        break;
    case 7:
        itemname="HP回復剤(大)";
        break;
    case 8:
        itemname="SP回復剤(小)";
        break;
    case 9:
        itemname="SP回復剤(中)";
        break;
    case 10:
        itemname="SP回復剤(大)";
        break;
    case 11:
        itemname="体力の書";
        break;
    case 12:
        itemname="魔力の書";
        break;
    case 13:
        itemname="力の書";
        break;
    case 14:
        itemname="守りの書";
        break;
    case 15:
        itemname="速さの書";
        break;
    case 16:
        itemname="全知の書";
        break;
    case 17:
        itemname="体力の運試し";
        break;
    case 18:
        itemname="魔力の運試し";
        break;
    case 19:
        itemname="力の運試し";
        break;
    case 20:
        itemname="守りの運試し";
        break;
    case 21:
        itemname="速さの運試し";
        break;
    case 22:
        itemname="全知の運試し";
        break;
    default:
        break;
    }
    mvprintw(3,0, "%sを獲得！\t\t\t\t\t\t\t\t\t\t\t\t",itemname);
    refresh();
    sleep(1);
    for(int i=0;i<8;i++){
        if(hero.itembox[i]==NULL){
            hero.itembox[i]=itemname;
            item_flag=1;
            break;
        }
    }
    if(item_flag!=1){
        mvprintw(4,0, "しかし、アイテムボックスに空きがなかった！");
        refresh();
        sleep(1);
        mvprintw(4,0, "削除するアイテムを選んでください\t\t\t\t\t\t\t\t");
        refresh();
        delete_item(itemname,max_y,max_x);
    }
}

int item(int flag,int i_flag) {
    int max_y, max_x;
    int ch;
    int highlight = 0;  /* 0~8...アイテム選択*/

    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);

    while (1) {
        clear();
        
        
        /* ログ表示枠*/
        mvprintw(0, 0, "<ログ>");

        /* プレイヤー情報表示*/
        show_player();
        
        if(battle_flag==1){
        show_monster(max_x);
        }
        
        
        /* アイテム表示*/
        mvprintw(2, 1, "zキーまたはENTERキーで行動を選択してください\t\t\t");
        mvprintw(15, 0, "アイテムボックス(zキーまたはENTERキーで使用・xキーで戻る)");
        for (int i = 0; i < 8; i++) {
            if (highlight == i) {
                attron(A_REVERSE);
                mvprintw(i + 16, 0, " %s ", hero.itembox[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i + 16, 0, " %s ", hero.itembox[i]);
            }
        }
        
        item_text(highlight);   /*アイテムの説明表示*/

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
            if(hero.itembox[highlight]==NULL){
                return 0;
            }
            if(strcmp(hero.itembox[highlight],"経験値ドリンク(小)")==0){
                xp_bottle(hero.itembox[highlight]);
                check_level(max_y,max_x);  /*レベルアップ確認*/
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"経験値ドリンク(中)")==0){
                xp_bottle(hero.itembox[highlight]);
                check_level(max_y,max_x);  /*レベルアップ確認*/
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"経験値ドリンク(大)")==0){
                xp_bottle(hero.itembox[highlight]);
                check_level(max_y,max_x);  /*レベルアップ確認*/
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"経験値ドリンク(極大)")==0){
                xp_bottle(hero.itembox[highlight]);
                check_level(max_y,max_x);  /*レベルアップ確認*/
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"HP回復剤(小)")==0){
                heal(hero.itembox[highlight],"hp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"HP回復剤(中)")==0){
                heal(hero.itembox[highlight],"hp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"HP回復剤(大)")==0){
                heal(hero.itembox[highlight],"hp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"SP回復剤(小)")==0){
                heal(hero.itembox[highlight],"sp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"SP回復剤(中)")==0){
                heal(hero.itembox[highlight],"sp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"SP回復剤(大)")==0){
                heal(hero.itembox[highlight],"sp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"体力の書")==0){
                book(hero.itembox[highlight],"hp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"魔力の書")==0){
                book(hero.itembox[highlight],"sp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"力の書")==0){
                book(hero.itembox[highlight],"atk");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"守りの書")==0){
                book(hero.itembox[highlight],"dff");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"速さの書")==0){
                book(hero.itembox[highlight],"dex");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"全知の書")==0){
                book(hero.itembox[highlight],"全ステータス");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"体力の運試し")==0){
                luckey(hero.itembox[highlight],"hp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"魔力の運試し")==0){
                luckey(hero.itembox[highlight],"sp");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"力の運試し")==0){
                luckey(hero.itembox[highlight],"atk");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"守りの運試し")==0){
                luckey(hero.itembox[highlight],"dff");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"速さの運試し")==0){
                luckey(hero.itembox[highlight],"dex");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight],"全知の運試し")==0){
                luckey(hero.itembox[highlight],"全ステータス");
                hero.itembox[highlight]=NULL;
            }else if(strcmp(hero.itembox[highlight], "[☠]呪いの仮面")!=0){
                mvprintw(2, 1, "%sを捨てますか？zキーまたはENTERキーで実行xキーキャンセル",hero.itembox[highlight]);
                refresh();
                while (1) {
                ch = getch();
                    switch (ch) {
                    case 'z':
                    case '\n':
                        mvprintw(2, 1, "%sを捨てました\t\t\t\t\t\t\t\t",hero.itembox[highlight]);
                        refresh();
                        sleep(1);
                        hero.itembox[highlight]=NULL;
                        break;
                    default:
                        break;
                    }
                break;
                }
            }
            
            if(flag==1){
                return 0; /*battle関数へと戻る*/
            }else{
                return 0; /*battle関数へと戻る*/
            }
            case 'x':
                return 0;
            default:
                break;
        }
        refresh();
        usleep(10000);
    }
}

void delete_item(char* itemname,int max_y,int max_x){
    int ch;
    int highlight = 0;  /* 0~8...アイテム選択*/
    
    while (1) {
        clear();
        mvprintw(0, 0, "<ログ>");
        mvprintw(4,0, "削除するアイテムを選んでください\t\t\t\t\t\t\t\t");
        mvprintw(14, 0, "アイテムボックス(zキーまたはENTERキーでアイテムを交換・xキーでキャンセル)");
        mvprintw(24, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        mvprintw(25, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        mvprintw(26, 0, "獲得しようとしてるアイテム %s",itemname);
        refresh();
        for (int i = 0; i < 8; i++) {
            if (highlight == i) {
                attron(A_REVERSE);
                mvprintw(i + 16, 0, " %s\t\t\t\t\t\t\t\t\t", hero.itembox[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i + 16, 0, " %s\t\t\t\t\t\t\t\t\t", hero.itembox[i]);
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
            if(strcmp(hero.itembox[highlight], "[☠]呪いの仮面") == 0){
                mvprintw(3,0, "[☠]それは捨てることができない。[☠]\t\t\t\t");
                refresh();
                sleep(1);
                mvprintw(3,0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                return delete_item(itemname,max_y,max_x);
            }else{
                char* delete_item = hero.itembox[highlight];
                hero.itembox[highlight]=itemname;
                mvprintw(3,0, "%s を捨てて %s を獲得！\t\t\t\t",delete_item,itemname);
                mvprintw(4,0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                refresh();
                sleep(1);
                for (int j = 0; j < 10; j++) {
                    mvprintw(j + 15, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                }
                return;
            }
            default:
                mvprintw(3,0, "アイテム獲得をキャンセルしました\t\t\t\t\t\t\t\t\t\t\t\t");
                refresh();
                sleep(1);
                for (int j = 0; j < 10; j++) {
                    mvprintw(j + 15, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
                }
                return;
        }
    }
}