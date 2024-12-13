#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/

void check_passive(int luck, int max_x) {
    for (int i = 0; i < 8; i++) {
        if (hero.itembox[i] == NULL) {
            continue;  // nullポインタを避ける
        }
        if (strcmp(hero.itembox[i], "[♦]聖なる葉っぱ") == 0) {
            hero.hp += 10;
        } else if (strcmp(hero.itembox[i], "[♦]頑丈な鉛") == 0) {
            hero.dff += 5;
            hero.dex -= 5;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦]鋭利な石") == 0) {
            hero.atk += 3;
            hero.dff -= 3;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦]激怒の指輪") == 0) {
            hero.atk +=7;
        } else if (strcmp(hero.itembox[i], "[♦]堅実な指輪") == 0) {
            hero.dff +=7;
        } else if (strcmp(hero.itembox[i], "[♦]鮮明な指輪") == 0) {
            hero.dex +=7;
        } else if (strcmp(hero.itembox[i], "[♦]銅の指輪") == 0) {
            hero.score += 10;
        } else if (strcmp(hero.itembox[i], "[♦]銀の指輪") == 0) {
            hero.score += 50;
        } else if (strcmp(hero.itembox[i], "[♦]金の指輪") == 0) {
            hero.score += 100;
        } else if (strcmp(hero.itembox[i], "[♦]プラチナの指輪") == 0) {
            hero.score = (int)(hero.score * 1.1);
        } else if (strcmp(hero.itembox[i], "[♦]乱数生成機") == 0) {
            int rd = rand() % 20 + 1;
            if (rd < 10) {
                rd *= -1;
            } else {
                rd -= 10;
            }
            hero.hp += rd;
            hero.sp += rd;
            hero.atk += rd;
            hero.dff += rd;
            hero.dex += rd;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦]拳銃") == 0) {
            monster.hp -= 10;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦]栄養ドリンク") == 0) {
            hero.hp += 20;
        } else if (strcmp(hero.itembox[i], "[♦♦]水晶玉") == 0) {
            hero.sp += 5;
        } else if (strcmp(hero.itembox[i], "[♦♦]唐辛子") == 0) {
            hero.atk += 4;
        } else if (strcmp(hero.itembox[i], "[♦♦]鋼の鎧") == 0) {
            hero.dff += 4;
        } else if (strcmp(hero.itembox[i], "[♦♦]俊足の靴") == 0) {
            hero.dex += 4;
        } else if (strcmp(hero.itembox[i], "[♦♦]アサルトライフル") == 0) {
            monster.hp -= 20;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦]成長促進剤") == 0) {
            hero.exp += 50;
        } else if (strcmp(hero.itembox[i], "[♦♦]棘の鎧") == 0) {
            hero.dff += 6;
            hero.hp -= 12;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦]興奮剤") == 0) {
            hero.atk += 6;
            hero.hp -= 12;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦]ダイヤモンドの指輪") == 0) {
            hero.score += 10000;
        } else if (strcmp(hero.itembox[i], "[♦♦]魔鉱石") == 0) {
            hero.sp +=10;
        } else if (strcmp(hero.itembox[i], "[☠]呪いの仮面") == 0) {
            hero.hp -= 5;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦♦]小さな杖") == 0) {
            monster.hp -= (int)(hero.sp * 0.5);
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦♦]優しい本") == 0) {
            if (hero.atk <= 500) {
                hero.hp += 30;
            }
        } else if (strcmp(hero.itembox[i], "[♦♦♦]チタンの鎧") == 0) {
            hero.dff += 8;
        } else if (strcmp(hero.itembox[i], "[♦♦♦]ジェットパック") == 0) {
            hero.dex += 8;
        } else if (strcmp(hero.itembox[i], "[♦♦♦]スナイパーライフル") == 0) {
            monster.hp -= 100;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦♦]スコア換算機") == 0) {
            if (hero.score >= 1000000) {
                hero.hp += 10;
                hero.sp += 10;
                hero.atk += 10;
                hero.dff += 10;
                hero.dex += 10;
            }
        } else if (strcmp(hero.itembox[i], "[♦♦♦]のびしろドリンク") == 0) {
            hero.exp += 100;
        } else if (strcmp(hero.itembox[i], "[♦♦♦]悲痛の仮面") == 0) {
            hero.atk += 10;
            hero.dff += 10;
            hero.hp -= 50;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦♦]金塊") == 0) {
            hero.score += 10000;
        } else if (strcmp(hero.itembox[i], "[♦♦♦]追撃の手袋") == 0) {
            hero_attack(luck, max_x);
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦♦]魔力吸血の結晶") == 0) {
            monster.sp -= 10;
            hero.sp += 10;
            checkstatus();
        } else if (strcmp(hero.itembox[i], "[♦♦♦]ミスリルの指輪") == 0) {
            hero.score = (int)(hero.score * 1.2);
        }
    }
    refresh();
    usleep(100000);
}
