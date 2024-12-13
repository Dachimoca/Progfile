#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void loadgame(int argc, char **argv, FILE *fp) {
    /* プレイヤーデータの読み込み */
    char buffer[128];
    int i = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {
        // 末尾の改行を除去
        buffer[strcspn(buffer, "\n")] = '\0';

        if (i == 0) {
            strncpy(hero.heroname, buffer, sizeof(hero.heroname) - 1);  // プレイヤー名(char[])
            hero.heroname[sizeof(hero.heroname) - 1] = '\0'; // 確実にNULL終端する
        } else if (i == 1) {
            hero.lv = atoi(buffer);     // Lv(int)
        } else if (i == 2) {
            hero.exp = atoi(buffer);    // EXP(int)
        } else if (i == 3) {
            hero.hp = atoi(buffer);     // HP(int)
        } else if (i == 4) {
            hero.sp = atoi(buffer);     // SP(int)
        } else if (i == 5) {
            hero.atk = atoi(buffer);    // ATK(int)
        } else if (i == 6) {
            hero.dff = atoi(buffer);    // DFF(int)
        } else if (i == 7) {
            hero.dex = atoi(buffer);    // DEX(int)
        } else if (i == 8) {
            hero.score = atoi(buffer);  // SCORE(int)
        } else if (i == 9) {
            hero.floor_score = atoi(buffer);    // FLOOR_SCORE(int)
        } else if (i == 10) {
            hero.exp_line = atoi(buffer);   // EXP_LINE(int)
        } else if (i == 11) {
            // Allocate memory for hero.mig and copy the buffer
            hero.mig = (char *)malloc(strlen(buffer) + 1);  // Allocate memory based on the buffer size
            strncpy(hero.mig, buffer, strlen(buffer) + 1);  // Copy the string into hero.mig
        } else if (i >= 12 && i < 20) {
            int idx = i - 12;
            if (strlen(buffer) == 0) {
                hero.itembox[idx] = NULL;  // 空文字列の場合はNULLに設定
            } else {
                hero.itembox[idx] = (char *)malloc(strlen(buffer) + 1);  // 必要なメモリサイズを割り当てる
                strncpy(hero.itembox[idx], buffer, strlen(buffer) + 1);  // 終端のNULL文字を含めてコピーする
            }
        } else if (i >= 20 && i < 28) {
            int idx = i - 20;
            if (strlen(buffer) == 0) {
                hero.skillbox[idx] = NULL;  // 空文字列の場合はNULLに設定
            } else {
                hero.skillbox[idx] = (char *)malloc(strlen(buffer) + 1);  // 必要なメモリサイズを割り当てる
                strncpy(hero.skillbox[idx], buffer, strlen(buffer) + 1);  // 終端のNULL文字を含めてコピーする
            }
        }
        i++;
    }
}