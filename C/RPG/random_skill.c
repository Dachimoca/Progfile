#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void random_skill(int lv,int max_y,int max_x){
    int skill_flag=0;
    char* skillname;
    
    srand(time(NULL));
    
    
    if(lv<20){
        int rd = rand()%10+1;
    switch(rd){
        case 1:
            skillname="[★]スラッシュ";
            break;
        case 2:
            skillname="[★]連撃";
            break;
        case 3:
            skillname="[★]ドレイン";
            break;
        case 4:
            skillname="[★]毒撃";
            break;
        case 5:
            skillname="[★]幸運スラッシュ";
            break;
        case 6:
            skillname="[★]ファイア";
            break;
        case 7:
            skillname="[★]ウォーター";
            break;
        case 8:
            skillname="[★]アイス";
            break;
        case 9:
            skillname="[★]サンダー";
            break;
        case 10:
            skillname="[★]ヒール";
            break;
        default:
            break;
        }
    }
    if(lv>20 && lv<40){
        int rd = rand()%11+1;
    switch(rd){
        case 1:
            skillname="[★★]スラッシュ・改";
            break;
        case 2:
            skillname="[★★]守りの一撃";
            break;
        case 3:
            skillname="[★★]3連撃";
            break;
        case 4:
            skillname="[★★]一太刀";
            break;
        case 5:
            skillname="[★★]加速する拳";
            break;
        case 6:
            skillname="[★★]アドレナリン";
            break;
        case 7:
            skillname="[★★]プロテクト";
            break;
        case 8:
            skillname="[★★]スピルリナ";
            break;
        case 9:
            skillname="[★★]ブレイク";
            break;
        case 10:
            skillname="[★★]スロウ";
            break;
        case 11:
            skillname="[★★]ヒーリング";
            break;
        default:
            break;
        }
    }
    if(lv>40 && lv<60){
        int rd = rand()%15+1;
    switch(rd){
        case 1:
            skillname="[★★★]命削り";
            break;
        case 2:
            skillname="[★★★]5連撃";
            break;
        case 3:
            skillname="[★★★]一撃必殺";
            break;
        case 4:
            skillname="[★★★]魔剣斬り";
            break;
        case 5:
            skillname="[★★★]ガトリング砲";
            break;
        case 6:
            skillname="[★★★]フレイム";
            break;
        case 7:
            skillname="[★★★]ストーム";
            break;
        case 8:
            skillname="[★★★]ブリザード";
            break;
        case 9:
            skillname="[★★★]ライトニング";
            break;
        case 10:
            skillname="[★★★]ドーピング";
            break;
        case 11:
            skillname="[★★★]プロテクション";
            break;
        case 12:
            skillname="[★★★]スピリチャ";
            break;
        case 13:
            skillname="[★★★]EXPブースト";
            break;
        case 14:
            skillname="[★★★]ラッキーハンド";
            break;
        case 15:
            skillname="[★★★]ケアリー";
            break;
        default:
            break;
        }
    }
    if(lv>=60 && lv<80){
        int rd = rand()%15+1;
    switch(rd){
        case 1:
            skillname="[★★★★]火炎斬り";
            break;
        case 2:
            skillname="[★★★★]水撃斬り";
            break;
        case 3:
            skillname="[★★★★]氷穴斬り";
            break;
        case 4:
            skillname="[★★★★]雷撃斬り";
            break;
        case 5:
            skillname="[★★★★]キャノン砲";
            break;
        case 6:
            skillname="[★★★★]ボルケニオン";
            break;
        case 7:
            skillname="[★★★★]ポセシアン";
            break;
        case 8:
            skillname="[★★★★]レイシオン";
            break;
        case 9:
            skillname="[★★★★]メガサンダー";
            break;
        case 10:
            skillname="[★★★★]スロットマシン";
            break;
        case 11:
            skillname="[★★★★]減衰";
            break;
        case 12:
            skillname="[★★★★]SCOREブースト";
            break;
        case 13:
            skillname="[★★★★]HP・SPチェンジ";
            break;
        case 14:
            skillname="[★★★★]ATK・DFFチェンジ";
            break;
        case 15:
            skillname="[★★★★]ケミスト";
            break;
        default:
            break;
        }
    }
    if(lv>=80){
        int rd = rand()%10+1;
    switch(rd){
        case 1:
            skillname="[★★★★★]最後の一撃";
            break;
        case 2:
            skillname="[★★★★★]邪気払い";
            break;
        case 3:
            skillname="[★★★★★]無限攻撃";
            break;
        case 4:
            skillname="[★★★★★]ダメージ吸収";
            break;
        case 5:
            skillname="[★★★★★]神力";
            break;
        case 6:
            skillname="[★★★★★]神守";
            break;
        case 7:
            skillname="[★★★★★]神速";
            break;
        case 8:
            skillname="[★★★★★]必要EXP削減";
            break;
        case 9:
            skillname="[★★★★★]アルティメット";
            break;
        case 10:
            skillname="[★★★★★]核";
            break;
        case 11:
            skillname="[★★★★★]メディケイド";
            break;
        default:
            break;
        }
    }
    
    mvprintw(3, 1, "%sを習得！\t\t\t\t\t\t\t\t\t\t\t\t",skillname);
    refresh();
    sleep(1);
    for(int i=0;i<8;i++){
        if(hero.skillbox[i]==NULL|| (strcmp(hero.skillbox[i],skillname)==0)){
            hero.skillbox[i]=skillname;
            skill_flag=1;
            break;
        }
    }
    if(skill_flag!=1){
        mvprintw(3,0, "しかし、スキルボックスに空きがなかった！\t\t\t\t\t\t");
        refresh();
        sleep(1);
        mvprintw(4,0, "削除するスキルを選んでください\t\t\t\t\t\t\t\t");
        refresh();
        delete_skill(skillname,max_y,max_x);
        }
}