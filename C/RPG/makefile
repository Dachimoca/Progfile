# example of makefile 
CC = gcc
CLAGS = -lncursesw
WALL = -Wall

all: RPG.exe

RPG.exe: RPG.c help.c skill.c item.c battle.c hub.c save.c load.c show_title.c create_heroname.c show_menu.c show_player_monster.c check_passive.c start_game_screen.c item_text.c passive_search.c item_particle.c random_skill.c skill_slot.c skill_text.c skill_particle.c skill_delete.c skill_10shot.c skill_20shot.c
	$(CC) RPG.c help.c skill.c item.c battle.c hub.c save.c load.c show_title.c create_heroname.c show_menu.c show_player_monster.c check_passive.c start_game_screen.c item_text.c passive_search.c item_particle.c random_skill.c skill_slot.c skill_text.c skill_particle.c skill_delete.c skill_10shot.c skill_20shot.c -o RPG.exe $(CLAGS) $(WALL)

clean:
	rm -f *.o *.exe

.PHONY: all clean