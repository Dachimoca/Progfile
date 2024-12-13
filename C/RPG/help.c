#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>
#include "func.h"

void help(void){
    int max_y, max_x;
    int ch;
    int selectpage=1;
    int allpage=2;
    
        /* 画面サイズ取得*/
    getmaxyx(stdscr, max_y, max_x);
    help_1(max_x,max_y,selectpage,allpage);
    
    while (1) {
        /* 入力処理*/
        ch = getch();
        switch (ch) {
            case 'x':
            return;
            case KEY_RIGHT:
            if(selectpage==1){
            selectpage++;
            help_2(max_x,max_y,selectpage,allpage);
                
            }else{
                selectpage=1;
                help_1(max_x,max_y,selectpage,allpage);
            }
            break;
            default:
                break;
        }
    refresh();
    usleep(100000);  /* 0.1秒待機*/
    }
    
    
}

void help_1(int max_x,int max_y,int selectpage,int allpage){
    clear();
    mvprintw(0, 0, "ゲームの操作方法");
    mvprintw(1, 0, "↑↓←→キー・・・操作・選択キー");
    mvprintw(2, 0, "「z」「ENTER」キー・・・実行キー");
    mvprintw(3, 0, "「x」キー・・・キャンセルキー");
    mvprintw(5, 0, "用語解説");
    mvprintw(6, 0, "Lv・・・レベル");
    mvprintw(7, 0, "EXP・・・経験値");
    mvprintw(8, 0, "HP・・・体力");
    mvprintw(9, 0, "SP・・・魔力");
    mvprintw(10, 0, "ATK・・・攻撃力");
    mvprintw(11, 0, "DFF・・・防御力");
    mvprintw(12, 0, "DEX・・・素早さ");
    mvprintw(14, 0, "ゲーム目標");
    mvprintw(15, 0, "＜100層目に潜むラスボスを討伐する＞");
    mvprintw(17, 0, "戦闘システムについて");
    mvprintw(18, 0, "行動順は、DEXが高い順になる");
    mvprintw(19, 0, "プレイヤーは「攻撃」「防御」「技能選択」「アイテム」の4つから選択して行動を行う");
    mvprintw(20, 0, "ダメージ計算は「(自身のATK - 敵のDFF/2)+1～10」となる");
    mvprintw(21, 0, "ダメージ計算にてダメージが0以下になった場合、1～3のダメージとなる");
    mvprintw(22, 0, "5％の確率でクリティカルダメージとなり、2倍のダメージを与えられる");
    mvprintw(23, 0, "敵のHPが0になると勝利、自身のHPが0になると敗北となる");
    
    mvprintw(25, 0, "→キーで次ページへ page数 %d / %d",selectpage,allpage);
    
    mvprintw(0, max_x/2+7, "＊注意事項＊");
    mvprintw(1, max_x/2+7, "キーを連打・長押し等の動作を行うと");
    mvprintw(2, max_x/2+7, "挙動がおかしくなります！");
    mvprintw(3, max_x/2+7, "また、起動中に画面サイズを変更すると");
    mvprintw(4, max_x/2+7, "UIがおかしくなる危険性があります！");
    mvprintw(max_y-1, max_x-21, "xキーでタイトルに戻る");
}
void help_2(int max_x,int max_y,int selectpage,int allpage){
                clear();
                mvprintw(0, 0, "ゲームシステムについて①");
                mvprintw(1, 0, "『アイテム』");
                mvprintw(2, 0, "アイテムには、通常アイテムとパッシブアイテムの2種類存在します。各層の探索時に10％の確率で");
                mvprintw(3, 0, "パッシブアイテムを獲得できます。このアイテムを所持していると戦闘中に効果を発揮します。");
                mvprintw(5, 0, "『スキル』");
                mvprintw(6, 0, "戦闘中に稼いだ経験値が一定値に達するとレベルアップします。レベルが3の倍数ごとに1つランダムな");
                mvprintw(7, 0, "スキルを習得することができます。スキルは攻撃・魔法・補助・回復など50種類以上存在します。");
                mvprintw(8, 0, "また、スキルごとにランクが存在しており★～★★★★★となっています。");
                mvprintw(9, 0, "『セーブとロード』");
                mvprintw(10, 0, "メイン画面の項目にて、「セーブ」を実行すると現在のデータをセーブすることができます。");
                mvprintw(11, 0, "セーブデータはプレイヤーの名前が書かれたテキストファイルで保存され次回起動時に");
                mvprintw(12, 0, "「./rpg プレイヤー名.txt」と入力するとスタート画面の「CONTINUE」実行時に読み込むことができます。");
                mvprintw(13, 0, "『武器について』");
                mvprintw(14, 0, "工事中");
                
                mvprintw(25, 0, "→キーで次ページへ page数 %d / %d",selectpage,allpage);
                
                mvprintw(max_y-1, max_x-21, "xキーでタイトルに戻る");
}