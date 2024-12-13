#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h"
#include "func.h"

void item_text(int highlight) {
    if (hero.itembox[highlight] == NULL) {
        mvprintw(3, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        return;
    }
    
    if (strcmp(hero.itembox[highlight], "経験値ドリンク(小)") == 0) {
        mvprintw(2, 1, "80％の確率でexpを1～100獲得\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "経験値ドリンク(中)") == 0) {
        mvprintw(2, 1, "60％の確率でexpを50～350獲得\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "経験値ドリンク(大)") == 0) {
        mvprintw(2, 1, "40％の確率でexpを100～800獲得\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "経験値ドリンク(極大)") == 0) {
        mvprintw(2, 1, "20％の確率でexpを1000～5000獲得\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "HP回復剤(小)") == 0) {
        mvprintw(2, 1, "hpを小回復(Lvで増加量が変わる)\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "HP回復剤(中)") == 0) {
        mvprintw(2, 1, "hpを中回復(Lvで増加量が変わる)\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "HP回復剤(大)") == 0) {
        mvprintw(2, 1, "hpを大回復(Lvで増加量が変わる)\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "SP回復剤(小)") == 0) {
        mvprintw(2, 1, "spを小回復(Lvで増加量が変わる)\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "SP回復剤(中)") == 0) {
        mvprintw(2, 1, "spを中回復(Lvで増加量が変わる)\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "SP回復剤(大)") == 0) {
        mvprintw(2, 1, "spを大回復(Lvで増加量が変わる)\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "体力の書") == 0) {
        mvprintw(2, 1, "hpを1～5上昇\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "魔力の書") == 0) {
        mvprintw(2, 1, "spを1～5上昇\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "力の書") == 0) {
        mvprintw(2, 1, "atkを1～5上昇\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "守りの書") == 0) {
        mvprintw(2, 1, "dffを1～5上昇\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "速さの書") == 0) {
        mvprintw(2, 1, "dexを1～5上昇\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "全知の書") == 0) {
        mvprintw(2, 1, "全ステータスを1～10回復\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "体力の運試し") == 0) {
        mvprintw(2, 1, "40％の確率でhp1.2倍・60％の確率でhp0.8倍\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "魔力の運試し") == 0) {
        mvprintw(2, 1, "40％の確率でsp1.2倍・60％の確率でsp0.8倍\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "力の運試し") == 0) {
        mvprintw(2, 1, "40％の確率でatk1.2倍・60％の確率でatk0.8倍\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "守りの運試し") == 0) {
        mvprintw(2, 1, "40％の確率でdff1.2倍・60％の確率でdff0.8倍\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "速さの運試し") == 0) {
        mvprintw(2, 1, "40％の確率でdex1.2倍・60％の確率でdex0.8倍\t\t\t\t\t\t\t\t\t\t");
    } else if (strcmp(hero.itembox[highlight], "全知の運試し") == 0) {
        mvprintw(2, 1, "40％の確率で全ステ1.1倍・60％の確率で全ステ0.9倍\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]聖なる葉っぱ") == 0) {
        mvprintw(2, 1, "戦闘開始時、HP+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]頑丈な鉛") == 0) {
        mvprintw(2, 1, "戦闘開始時、DFF+5 DEX-5(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]鋭利な石") == 0) {
        mvprintw(2, 1, "戦闘開始時、ATK+3 DFF-3(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]激怒の指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、ATK+7(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]堅実な指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、DFF+7(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]鮮明な指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、DEX+7(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]銅の指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCORE+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]銀の指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCORE+50(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]金の指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCORE+100(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]プラチナの指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCOREx1.1(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]乱数生成機") == 0) {
        mvprintw(2, 1, "戦闘開始時、全ステータス-10～+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦]拳銃") == 0) {
        mvprintw(2, 1, "戦闘開始時、敵のHP-10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]栄養ドリンク") == 0) {
        mvprintw(2, 1, "戦闘開始時、HP+20(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]水晶玉") == 0) {
        mvprintw(2, 1, "戦闘開始時、SP+5(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]唐辛子") == 0) {
        mvprintw(2, 1, "戦闘開始時、ATK+4(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]鋼の鎧") == 0) {
        mvprintw(2, 1, "戦闘開始時、DFF+4(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]俊足の靴") == 0) {
        mvprintw(2, 1, "戦闘開始時、DEX+4(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]アサルトライフル") == 0) {
        mvprintw(2, 1, "戦闘開始時、敵のHP-20(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]成長促進剤") == 0) {
        mvprintw(2, 1, "戦闘開始時、EXP+50(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]棘の鎧") == 0) {
        mvprintw(2, 1, "戦闘開始時、DFF+6 HP-12(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]興奮剤") == 0) {
        mvprintw(2, 1, "戦闘開始時、ATK+6 HP-12(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]ダイヤモンドの指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCORE+1000(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦]魔鉱石") == 0) {
        mvprintw(2, 1, "戦闘開始時、SP+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[☠]呪いの仮面") == 0) {
        mvprintw(2, 1, "戦闘開始時、HP-5 捨てることができない\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]小さな杖") == 0) {
        mvprintw(2, 1, "戦闘開始時、敵にSPの0.5倍ダメージ(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]優しい本") == 0) {
        mvprintw(2, 1, "戦闘開始時にATKが500以下の時、HP+30(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]チタンの鎧") == 0) {
        mvprintw(2, 1, "戦闘開始時、DFF+8(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]ジェットパック") == 0) {
        mvprintw(2, 1, "戦闘開始時、DEX+8(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]スナイパーライフル") == 0) {
        mvprintw(2, 1, "戦闘開始時、敵のHP-100(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]スコア換算機") == 0) {
        mvprintw(2, 1, "戦闘開始時にSCOREが100万以上の時 全ステ+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]のびしろドリンク") == 0) {
        mvprintw(2, 1, "戦闘開始時、EXP+100(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]悲痛の仮面") == 0) {
        mvprintw(2, 1, "戦闘開始時、HP-50 ATK・DFF+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]金塊") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCORE+10000(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]追撃の手袋") == 0) {
        mvprintw(2, 1, "戦闘開始時、先制攻撃1回(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]魔力吸血の結晶") == 0) {
        mvprintw(2, 1, "戦闘開始時、敵SP-10 自分のSP+10(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else if (strcmp(hero.itembox[highlight], "[♦♦♦]ミスリルの指輪") == 0) {
        mvprintw(2, 1, "戦闘開始時、SCOREx1.2(zキー入力で捨てる事が出来る)\t\t\t\t\t\t\t\t\t\t");
    }else {
        mvprintw(3, 0, "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    }
}