#define _CRT_SECURE_NO_WARNINGS 1


#include <stdio.h>
#include <string.h>
#include <crtdbg.h>  
#include <assert.h>
#include "linked_list.h"

typedef Node CONQUEST;

typedef struct Quaker
{
	char *name;
	char *team;
	int elo;
} Quaker;

void print_quaker(Node *node)
{
	struct Quaker *temp = node->data;
	printf("%8s %16s %6d\n", *temp);
}

void fprint_quaker(FILE *file, Node *node)
{
	struct Quaker *temp = node->data;
	fprintf(file, "%s %s %d\n", *temp);
}

void CONQUEST_registration(CONQUEST *contest_name, char *name, char *team, int elo)
{
	Quaker *new_player = (Quaker *) malloc(sizeof(Quaker));
	new_player->elo = elo;
	new_player->name = name;
	new_player->team = team;

	list_push(contest_name, node_new(new_player));
}

void CONQUEST_show_players(CONQUEST *contest_name)
{
	list_foreach(contest_name, print_quaker);
}

void CONQUEST_filter_by_team(CONQUEST *contest_name, char *team)
{
	Node *head = contest_name;

	if(head == NULL)
		return;

	while (head)
	{
		struct Quaker *temp = head->data;
		if (strcmp(temp->team, team) == 0)
			print_quaker(head);

		head = head->next;
	}
}

//
// @param elo: -/+ ~ меньше/больше
//
void CONQUEST_filter_by_elo(CONQUEST *contest_name, int elo)
{
	Node *head = contest_name;

	if (head == NULL)
		return;

	while (head)
	{
		struct Quaker *temp = head->data;
		if ((temp->elo >= elo && elo > 0) || (temp->elo <= -elo && elo < 0))
			print_quaker(head);

		head = head->next;
	}
}

int CONQUEST_player_id(CONQUEST *contest_name, char *name)
{
	int player_n = 0;

	Node *head = contest_name;
	if (head == NULL)
		return;
	while (head)
	{
		struct Quaker *temp = head->data;
		if (strcmp(temp->name, name) == 0)
			break;
		head = head->next;
		++player_n;
	}

	return player_n;
}

void CONQUEST_delete_player(CONQUEST **contest_name, char *name)
{
	int n = CONQUEST_player_id(*contest_name, name);
	list_pop_nth(contest_name, n);
}

void CONQUEST_load(FILE *file, CONQUEST *contest_name)
{
	int n = 0;
	fscanf(file, "%d", &n);
	
	while (n--)
	{
	    char *name = (char*)malloc(32);
	    char *team = (char*)malloc(32);
	    int elo = 0;

	    fscanf(file, "%s%s%d\n", name, team, &elo);
	    CONQUEST_registration(contest_name, name, team, elo);
	}
}

void CONQUEST_save(FILE *file, CONQUEST *contest_name)
{
	Node *head = contest_name;

	if (head == NULL)
		return;

	fprintf(file, "%d\n", list_length(head));

	while (head)
	{
		fprint_quaker(file, head);
		head = head->next;
	}
}


int main()
{
	CONQUEST *QuakeCon2004 = NULL;

	//CONQUEST_registration(&QuakeCon2004, "Cooller", "Mousesports", 9000);
	//CONQUEST_registration(&QuakeCon2004, "Fatal1ty", "-", 3622);
	//CONQUEST_registration(&QuakeCon2004, "k1llsen", "-", 3441);
	//CONQUEST_registration(&QuakeCon2004, "av3k", "SeriousGaming", 2222);
	//CONQUEST_registration(&QuakeCon2004, "Cypher", "Titan", 3748);
	//CONQUEST_registration(&QuakeCon2004, "Polosaty", "NiP", 3524);
	//CONQUEST_registration(&QuakeCon2004, "Strenx", "fnatic", 2732);

	//FILE *db = fopen("playerlist.txt", "w");
	//CONQUEST_save(db, QuakeCon2004);
	//fclose(db);

	FILE *db = fopen("playerlist.txt", "r");
	CONQUEST_load(db, &QuakeCon2004);
	fclose(db);
	
	printf("all:\n");
	CONQUEST_show_players(QuakeCon2004);			// участники
	printf("\nno team:\n");
	CONQUEST_filter_by_team(QuakeCon2004, "-");		// участники без команды
	printf("\nelo > 3000:\n");
	CONQUEST_filter_by_elo(QuakeCon2004, +3000);		// ELO выше N
	printf("\nelo < 3000:\n");
	CONQUEST_filter_by_elo(QuakeCon2004, -3000);		// ELO ниже N

	printf("\n Av3k had been arrested =( :\n");		// удаление участника
	CONQUEST_delete_player(&QuakeCon2004, "av3k");
	CONQUEST_show_players(QuakeCon2004);
	

	return 0;
}
