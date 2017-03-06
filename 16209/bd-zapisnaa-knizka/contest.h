#pragma once

#include "linked_list.h"
#include <stdio.h>

typedef Node CONTEST;

typedef struct Сontestant
{
	char	*name;
	char	*team;
	int	elo;
} Сontestant;


void print_сontestant(Node *node);

void fprint_сontestant(FILE *file, Node *node);

void CONTEST_registration(CONTEST *contest_name, char *name, char *team, int elo);

void CONTEST_show_players(CONTEST *contest_name);

void CONTEST_filter_by_team(CONTEST *contest_name, char *team);

//
// @param elo: -/+ ~ меньше/больше
//
void CONTEST_filter_by_elo(CONTEST *contest_name, int elo);

int CONTEST_player_id(CONTEST *contest_name, char *name);

void CONTEST_delete_player(CONTEST **contest_name, char *name);

void CONTEST_load(FILE *file, CONTEST *contest_name);

void CONTEST_save(FILE *file, CONTEST *contest_name);
