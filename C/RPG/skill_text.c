#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "gameconfig.h" /*ゲームデータが格納されているヘッダ*/
#include "func.h" /*すべての関数の宣言が格納されているヘッダ*/


void skill_text(int highlight){
    
    if(hero.skillbox[highlight]==NULL){
        mvprintw(3,0,"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
        return;
    }
    
    if(strcmp(hero.skillbox[highlight],"[★]スラッシュ")==0){
        mvprintw(3, 1, "消費SP5 ATKの1.5倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]連撃")==0){
        mvprintw(3, 1, "消費SP6 2回攻撃を行う\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]ドレイン")==0){
        mvprintw(3, 1, "消費SP8 攻撃を行い、与えたダメージ分のHPを回復\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]毒撃")==0){
        mvprintw(3, 1, "消費SP5 1ダメージ与え、70％の確率で10～100の防御貫通ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]幸運スラッシュ")==0){
        mvprintw(3, 1, "消費SP7 77ダメージ与え、7％の確率で777のダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]ファイア")==0){
        mvprintw(3, 1, "消費SP7 火属性の小ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]ウォーター")==0){
        mvprintw(3, 1, "消費SP8 水属性の小ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]アイス")==0){
        mvprintw(3, 1, "消費SP9 氷属性の小ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]サンダー")==0){
        mvprintw(3, 1, "消費SP10 雷属性の小ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]スラッシュ・改")==0){
        mvprintw(3, 1, "消費SP18 ATKの2倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]守りの一撃")==0){
        mvprintw(3, 1, "消費SP20 自身のDFFを半分消費し、減少前のDFF3倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]3連撃")==0){
        mvprintw(3, 1, "消費SP24 3回攻撃を行う\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]一太刀")==0){
        mvprintw(3, 1, "消費SP45 自身のDEXを半分減少させ、ATKの3倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]加速する拳")==0){
        mvprintw(3, 1, "消費SP30 自身のDEXを+50上昇させ、ATKの1.5倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]アドレナリン")==0){
        mvprintw(3, 1, "消費SP16 自身のATKを+15～30増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]プロテクト")==0){
        mvprintw(3, 1, "消費SP16 自身のDFFを+15～30増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]スピルリナ")==0){
        mvprintw(3, 1, "消費SP16 自身のDEXを+15～30増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]ダウン")==0){
        mvprintw(3, 1, "消費SP16 敵のATKを-15～30減少(戦闘終了まで)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]ブレイク")==0){
        mvprintw(3, 1, "消費SP16 敵のDFFを-15～30減少(戦闘終了まで)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]スロウ")==0){
        mvprintw(3, 1, "消費SP16 敵のDEXを-15～30減少(戦闘終了まで)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]命削り")==0){
        mvprintw(3, 1, "消費HP半分 消費したHPの3倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]5連撃")==0){
        mvprintw(3, 1, "消費SP30 5回攻撃を行う\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]一撃必殺")==0){
        mvprintw(3, 1, "消費SP50 敵にATKの5倍ダメージを与える。その後1ターン行動不能\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]魔剣斬り")==0){
        mvprintw(3, 1, "消費SP半分 敵に(ATK/10 x SP/10)の防御貫通ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ガトリング砲")==0){
        mvprintw(3, 1, "消費SP60 敵に1～10回の2倍ダメージを与える。与えるダメージは徐々に減少する\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]フレイム")==0){
        mvprintw(3, 1, "消費SP28 火属性の中ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ストーム")==0){
        mvprintw(3, 1, "消費SP29 水属性の中ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ブリザード")==0){
        mvprintw(3, 1, "消費SP30 氷属性の中ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ライトニング")==0){
        mvprintw(3, 1, "消費SP31 雷属性の中ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ドーピング")==0){
        mvprintw(3, 1, "消費SP36 自身のATKを+50～100増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]プロテクション")==0){
        mvprintw(3, 1, "消費SP36 自身のDFFを+50～100増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]スピリチャ")==0){
        mvprintw(3, 1, "消費SP36 自身のDEXを+50～100増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]EXPブースト")==0){
        mvprintw(3, 1, "消費SP全て 敵がドロップする経験値を2倍にする\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ラッキーハンド")==0){
        mvprintw(3, 1, "消費SP80 ランダムにアイテムを1つ獲得\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]火炎斬り")==0){
        mvprintw(3, 1, "消費SP75 (ATK+SP)/2の3.1倍ダメージを与える(火属性)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]水撃斬り")==0){
        mvprintw(3, 1, "消費SP80 (ATK+SP)/3の4.2倍ダメージを与える(水属性)\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]氷穴斬り")==0){
        mvprintw(3, 1, "消費SP85 (ATK+SP)/4の5.3倍ダメージを与える(氷属性)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]雷撃斬り")==0){
        mvprintw(3, 1, "消費SP90 (ATK+SP)/5の6.4倍ダメージを与える(雷属性)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]キャノン砲")==0){
        mvprintw(3, 1, "消費SP120 敵に1～20回の3倍ダメージを与える。与えるダメージは徐々に減少する\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]ボルケニオン")==0){
        mvprintw(3, 1, "消費SP58 火属性の大ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]ポセシアン")==0){
        mvprintw(3, 1, "消費SP59 水属性の大ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]レイシオン")==0){
        mvprintw(3, 1, "消費SP60 氷属性の大ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]メガサンダー")==0){
        mvprintw(3, 1, "消費SP61 雷属性の大ダメージを与える(Lvに応じてダメージ量が変化)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]スロットマシン")==0){
        mvprintw(3, 1, "消費SP100 確率で何かいいことが起きる\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]減衰")==0){
        mvprintw(3, 1, "消費SP80 敵の全ステータスを50～100減少\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]SCOREブースト")==0){
        mvprintw(3, 1, "消費SP200 スコアを1.5倍増加\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]HP・SPチェンジ")==0){
        mvprintw(3, 1, "消費SP70 HPとSPを入れ替える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]ATK・DFFチェンジ")==0){
        mvprintw(3, 1, "消費SP70 ATKとDFFを入れ替える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]最後の一撃")==0){
        mvprintw(3, 1, "消費HP1になるまで ATKの10倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]邪気払い")==0){
        mvprintw(3, 1, "消費SP230 特定の状態を解除する\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]無限攻撃")==0){
        mvprintw(3, 1, "消費SP350 1～100回分の攻撃を行う。攻撃するごとに終了確率が1％増加\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]魔力補充")==0){
        mvprintw(3, 1, "消費HP1000 SPを回復させる(Lvに応じて回復量が増加する)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]神力")==0){
        mvprintw(3, 1, "消費SP120 自身のATKを+100～200増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]神守")==0){
        mvprintw(3, 1, "消費SP120 自身のDFFを+100～200増加(永続)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]神速")==0){
        mvprintw(3, 1, "消費SP120 自身のDEXを+100～200増加(永続)\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]必要EXP削減")==0){
        mvprintw(3, 1, "消費SP100 レベルアップに必要なEXPを10％削減する\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]アルティメット")==0){
        mvprintw(3, 1, "消費SP全て 消費したSPの7.7倍ダメージを与える\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]核")==0){
        mvprintw(3, 1, "消費SP1000 敵に1000の防御貫通ダメージを与え、30％の確率で相手を即死させる\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★]ヒール")==0){
        mvprintw(3, 1, "消費SP17 HPを小回復(Lvに応じて回復量が増加する)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★]ヒーリング")==0){
        mvprintw(3, 1, "消費SP37 HPを中回復(Lvに応じて回復量が増加する)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★]ケアリー")==0){
        mvprintw(3, 1, "消費SP67 HPを大回復(Lvに応じて回復量が増加する)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★]ケミスト")==0){
        mvprintw(3, 1, "消費SP117 HPを特大回復(Lvに応じて回復量が増加する)\t\t\t\t\t\t\t\t\t\t");
    }else if(strcmp(hero.skillbox[highlight],"[★★★★★]メディケイド")==0){
        mvprintw(3, 1, "消費SP187 HPを極大回復(Lvに応じて回復量が増加する)\t\t\t\t\t\t\t\t\t\t");
    }
}