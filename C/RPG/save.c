#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void savegame(int max_x, int max_y) {
    // ファイル名を作成
    char filename[256];
    snprintf(filename, sizeof(filename), "%s.txt", hero.heroname);
    
    // ファイルを開く
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }
    
    // プレイヤー情報を書き込む
    fprintf(fp, "%s\n", hero.heroname);    // 名前
    fprintf(fp, "%d\n", hero.lv);          // レベル
    fprintf(fp, "%d\n", hero.exp);         // 取得経験値
    fprintf(fp, "%d\n", hero.hp);          // HP
    fprintf(fp, "%d\n", hero.sp);          // SP
    fprintf(fp, "%d\n", hero.atk);         // ATK
    fprintf(fp, "%d\n", hero.dff);         // DFF
    fprintf(fp, "%d\n", hero.dex);         // DEX
    fprintf(fp, "%d\n", hero.score);       // SCORE
    fprintf(fp, "%d\n", hero.floor_score); // 到達階層
    fprintf(fp, "%d\n", hero.exp_line);    // 必要経験値
    fprintf(fp, "%s\n", hero.mig);          // 属性

    // アイテムボックスの内容を書き込む
    for (int i = 0; i < 8; i++) {
        if (hero.itembox[i] != NULL) {
            fprintf(fp, "%s\n", hero.itembox[i]);
        } else {
            fprintf(fp, "\n");
        }
    }

    // スキルボックスの内容を書き込む
    for (int i = 0; i < 8; i++) {
        if (hero.skillbox[i] != NULL) {
            fprintf(fp, "%s\n", hero.skillbox[i]);
        } else {
            fprintf(fp, "\n");
        }
    }

    // ファイルを閉じる
    fclose(fp);
    
    mvprintw(max_y - 5, max_x / 2 - 12, "info:セーブ完了！\t\t\t\t\t");
    refresh();
    sleep(1);
}