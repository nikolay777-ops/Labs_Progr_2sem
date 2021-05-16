#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdio.h>
#include <string.h>

#include "check.h"
#include "list.h"
#include "organization.h"
#include "crime.h"
#include "criminal.h"
#include "menu.h"

void run();
void load_data();
void write_data_in_files();
void free_data();
void view_criminals();
void view_crimes();
void view_organizations();
void search_crimes_by_place();
list* get_list_of_participants();
void search_crimes_by_participants();
void search_crimes_by_aftermath();
void search_crimes_by_comments();
void search_crimes();

void search_criminals_by_name();
void search_criminals_by_nickname();
void search_criminals_by_kind_of_crimes();
void search_criminals_by_height();
void search_criminals_by_weight();
void search_criminals_by_hair_color();
void search_criminals_by_special_signs();
void search_criminals_by_citizenship();
void search_criminals_by_languages();
menu* create_search_criminals_menu();
void search_criminals();

void search_organizations_by_name();
void search_organizations_by_direction();
void search_organizations_by_danger_level();
void search_organizations();

void view_and_search();
void make_connections();
void who_could_do_this();
void archive();
void delete();
void view_archive();
void restore();
void work_with_archive();

void add_crime();
void add_criminal();
void add_organization();
void delete_crime_in_list();
void delete_organization_in_list();

#endif // APPLICATION_H
