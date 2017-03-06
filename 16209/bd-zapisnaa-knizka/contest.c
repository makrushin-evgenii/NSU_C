#define _CRT_SECURE_NO_WARNINGS 1

#include "contest.h"

void print_сontestant(Node *node)
{
	struct Сontestant *temp = node->data;
	printf("%8s %16s %6d\n", *temp);
}

void fprint_сontestant(FILE *file, Node *node)
{
	struct Сontestant *temp = node->data;
	fprintf(file, "%s %s %d\n", *temp);
}

void CONTEST_registration(CONTEST *contest_name, char *name, char *team, int elo)
{
	Сontestant *new_player = (Сontestant *)malloc(sizeof(Сontestant));
	new_player->elo = elo;
	new_player->name = name;
	new_player->team = team;

	list_push(contest_name, node_new(new_player));
}

void CONTEST_show_players(CONTEST *contest_name)
{
	list_foreach(contest_name, print_сontestant);
}

void CONTEST_filter_by_team(CONTEST *contest_name, char *team)
{
	Node *head = contest_name;

	if (head == NULL)
		return;

	while (head)
	{
		struct Сontestant *temp = head->data;
		if (strcmp(temp->team, team) == 0)
			print_сontestant(head);

		head = head->next;
	}
}

//
// @param elo: -/+ ~ меньше/больше
//
void CONTEST_filter_by_elo(CONTEST *contest_name, int elo)
{
	Node *head = contest_name;

	if (head == NULL)
		return;

	while (head)
	{
		struct Сontestant *temp = head->data;
		if ((temp->elo >= elo && elo > 0) || (temp->elo <= -elo && elo < 0))
			print_сontestant(head);

		head = head->next;
	}
}

int CONTEST_player_id(CONTEST *contest_name, char *name)
{
	int player_n = 0;

	Node *head = contest_name;
	if (head == NULL)
		return;
	while (head)
	{
		struct Сontestant *temp = head->data;
		if (strcmp(temp->name, name) == 0)
			break;
		head = head->next;
		++player_n;
	}

	return player_n;
}

void CONTEST_delete_player(CONTEST **contest_name, char *name)
{
	int n = CONTEST_player_id(*contest_name, name);
	list_pop_nth(contest_name, n);
}

void CONTEST_load(FILE *file, CONTEST *contest_name)
{
	int n = 0;
	fscanf(file, "%d", &n);

	while (n--)
	{
		char *name = (char*)malloc(32);
		char *team = (char*)malloc(32);
		int elo = 0;

		fscanf(file, "%s%s%d\n", name, team, &elo);
		CONTEST_registration(contest_name, name, team, elo);
	}
}

void CONTEST_save(FILE *file, CONTEST *contest_name)
{
	Node *head = contest_name;

	if (head == NULL)
		return;

	fprintf(file, "%d\n", list_length(head));

	while (head)
	{
		fprint_сontestant(file, head);
		head = head->next;
	}
}
