/*スタート画面関数一覧*/
void help(void);
void help_1(int max_x,int max_y,int selectpage,int allpage);
void help_2(int max_x,int max_y,int selectpage,int allpage);
void start_game_screen(int argc, char **argv);
void show_title(int max_y,int max_x,int flag);
void create_heroname(int max_x,int max_y);

/*ハブ関数一覧*/
void hub(int argc, char **argv);
void shop_event(int max_x,int max_y);
void heal_event(int max_x,int max_y);
void damage_event(int max_x,int max_y);
void lucky_event(int max_x,int max_y);
void savegame(int max_x,int max_y);
void show_menu(int max_x,int max_y,int highlight);
void loadgame(int argc, char **argv,FILE *fp);

/*プレイヤー・モンスター情報描画関数一覧*/
void show_player();
void show_monster(int max_x);

/*戦闘関数一覧*/
void battle(int floor,int argc, char **argv);
void check_passive(int luck,int max_x);
void set_monster(char *name, int floor, int exp, int hp_mod, int sp_mod, int atk_mod, int dff_mod, int dex_mod);
void create_monster(int floor);
int hero_attack(int luck,int max_x);
void hero_defense(int luck,int dff_flag);
void monster_attack(int luck,int max_x);
void check_level();
void checkstatus();

/*探索関数一覧*/
void search(void);
void passive_search(void);

/*アイテム関数一覧*/
int item(int flag,int i_flag);
void xp_bottle(char* name);
void heal(char* name,char* str);
void luckey(char* name,char* str);
void delete_item(char* itemname,int max_y,int max_x);
void book(char* name,char* str);
void item_text(int highlight);


/*スキル関数一覧*/
int skill_select(int luck,int s_flag);
void skill_10shot(int max_x);
void skill_20shot(int max_x);
void skill_slot(int max_x,int max_y);
void skill_heal(int cost,int heal,int highlight,int mode);
void skill_slash(int max_x,int spcost,double mul,int mode,int highlight,char* mig);
int skill_mig(int damage,char* mig);
void skill_magic(int max_x,int spcost,double mul,int highlight,char* mig);
void skill_updown(int max_x,int spcost,int num,char* name,int mode,int highlight);
void skill_text(int highlight);
void random_skill(int lv,int max_y,int max_x);
void delete_skill(char* skillname,int max_y,int max_x);
