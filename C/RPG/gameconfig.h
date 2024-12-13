

/*プレイヤーの情報*/
typedef struct {
    char heroname[128];   /* 名前(128文字)*/
    int lv;             /* レベル*/
    int exp;            /* 取得経験値*/
    int hp;             /* 体力*/
    int sp;             /* 魔力*/
    int atk;            /* 攻撃*/
    int dff;            /* 防御*/
    int dex;            /* 素早さ*/
    int score;          /* ゲームスコア */
    int floor_score;    /*到達階層*/
    int exp_line;    /*必要経験値*/
    char* itembox[8];  /* アイテムボックス */
    char* skillbox[8]; /* スキルボックス */
    char* mig;            /*弱点属性*/
} Hero;

/* 敵の情報 */
typedef struct {
    char *monstername;  /* 名前(32文字)*/
    int lv;                /* レベル*/
    int exp;               /* 獲得経験値*/
    int hp;                /* 体力*/
    int sp;                /* 魔力*/
    int atk;               /* 攻撃*/
    int dff;               /* 防御*/
    int dex;               /* 素早さ*/
    int score;         /* 獲得できるゲームスコア */
    char* mig;            /*弱点属性*/
} Monster;

extern Hero hero;          /*Hero型のhero変数を作成*/
extern Monster monster;    /*Monster型のmonster変数を作成*/

extern int DEFALT_EXP; /* 初期必要経験値*/
extern int floor_check; /*階層探索チェッカー*/
extern int battle_flag; /*戦闘判定チェッカー*/
extern int start_flag; /*開始判定チェッカー*/

