#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h"
#include "func.h"

void passive_search(void){
    int max_y, max_x;
    int item_flag=0; /*アイテム欄が空いてるかのチェック*/
    char* itemname;
    /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    
    srand(time(NULL));
    int rd = rand()%36+1;
    switch(rd){
            case 1:
            itemname="[♦]聖なる葉っぱ";
            break;
            case 2:
            itemname="[♦]頑丈な鉛";
            break;
            case 3:
            itemname="[♦]鋭利な石";
            break;
            case 4:
            itemname="[♦]激怒の指輪";
            break;
            case 5:
            itemname="[♦]堅実な指輪";
            break;
            case 6:
            itemname="[♦]鮮明な指輪";
            break;
            case 7:
            itemname="[♦]銅の指輪";
            break;
            case 8:
            itemname="[♦]銀の指輪";
            break;
            case 9:
            itemname="[♦]金の指輪";
            break;
            case 10:
            itemname="[♦]プラチナの指輪";
            break;
            case 11:
            itemname="[♦]乱数生成機";
            break;
            case 12:
            itemname="[♦]拳銃";
            break;
            case 13:
            itemname="[♦♦]栄養ドリンク";
            break;
            case 14:
            itemname="[♦♦]水晶玉";
            break;
            case 15:
            itemname="[♦♦]唐辛子";
            break;
            case 16:
            itemname="[♦♦]鋼の鎧";
            break;
            case 17:
            itemname="[♦♦]俊足の靴";
            break;
            case 18:
            itemname="[♦♦]アサルトライフル";
            break;
            case 19:
            itemname="[♦♦]成長促進剤";
            break;
            case 20:
            itemname="[♦♦]棘の鎧";
            break;
            case 21:
            itemname="[♦♦]興奮剤";
            break;
            case 22:
            itemname="[♦♦]ダイヤモンドの指輪";
            break;
            case 23:
            itemname="[♦♦]魔鉱石";
            break;
            case 24:
            itemname="[☠]呪いの仮面";
            break;
            case 25:
            itemname="[♦♦♦]小さな杖";
            break;
            case 26:
            itemname="[♦♦♦]優しい本";
            break;
            case 27:
            itemname="[♦♦♦]チタンの鎧";
            break;
            case 28:
            itemname="[♦♦♦]ジェットパック";
            break;
            case 29:
            itemname="[♦♦♦]スナイパーライフル";
            break;
            case 30:
            itemname="[♦♦♦]スコア換算機";
            break;
            case 31:
            itemname="[♦♦♦]のびしろドリンク";
            break;
            case 32:
            itemname="[♦♦♦]悲痛の仮面";
            break;
            case 33:
            itemname="[♦♦♦]金塊";
            break;
            case 34:
            itemname="[♦♦♦]追撃の手袋";
            break;
            case 35:
            itemname="[♦♦♦]魔力吸血の結晶";
            break;
            case 36:
            itemname="[♦♦♦]ミスリルの指輪";
            break;
            default:
        break;
    }
    mvprintw(3,0, "%sを獲得！\t\t\t\t\t\t",itemname);
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
        delete_item(itemname,max_y,max_x);
    }
}