/*
Просмотр и поиск
информации по всем полям. Установление связей между
преступниками и между организациями. Анализ, кто мог совершить
данное преступление. Выборка «завязавших» в архив; удаление –
только после смерти.
*/

#include "application.h"

static list* crimes = NULL;
static list* criminals = NULL;
static list* archive_of_criminals = NULL;
static list* organizations = NULL;

void load_data() {
    crimes = read_crimes("crimes.txt");
    organizations = read_organizations("organizations.txt");
    criminals = read_criminals("criminals.txt");
    archive_of_criminals = read_criminals("archive_criminals.txt");
}

void write_data_in_files() {
    write_crimes(crimes, "crimes.txt");
    write_criminals(criminals, "criminals.txt");
    write_criminals(archive_of_criminals, "archive_criminals.txt");
    write_organizations(organizations, "organizations.txt");
}

void free_data() {
    delete_list(crimes);
    delete_list(criminals);
    delete_list(organizations);
    
    if (archive_of_criminals) {
        delete_list(archive_of_criminals);
    }
}

void view_criminals() {
    puts("\n\n\n--------------------------");
    puts("The list of criminals:");
    puts("--------------------------\n\n\n");
    
    for (item* i = criminals->beginning; i; i = i->next) {
        print_criminal(i->data);
    }
    
    puts("\n\n\n");
}

void view_crimes() {
    puts("\n\n\n--------------------------");
    puts("The list of crimes:");
    puts("--------------------------\n\n\n");
    
    for (item* i = crimes->beginning; i; i = i->next) {
        print_crime(i->data);
    }
    
    puts("\n\n\n");
}

void view_organizations() {
    puts("\n\n\n--------------------------");
    puts("The list of organizations:");
    puts("--------------------------\n\n\n");
    
    for (item* i = organizations->beginning; i; i = i->next) {
        print_organization(i->data);
    }
    
    puts("\n\n\n");
}

void search_crimes_by_place() {
    puts("\n\n\n");
    
    puts("Enter the place: ");
    char place[50];
    fgets_without_newline(place, 50, stdin);
    tolower_str(place);
    
    for (item* i = crimes->beginning; i; i = i->next) {
        crime* cr = i->data;
        char* cr_place = strdup(cr->place);
        tolower_str(cr_place);
        
        if (strcmp(cr_place, place) == 0) {
            print_crime(i->data);
        }
        
        free(cr_place);
    }
    
    puts("\n\n\n"); 
}

list* get_list_of_participants() {
    puts("Enter the participants. Enter \'-\' to stop: ");
    list* participants = create_list(sizeof(participant), free, (creating_copy_func)create_participant_copy);
    
    participant buffer;
    fgets_without_newline(buffer, 100, stdin);
    tolower_str(buffer);
    
    while (strcmp(buffer, "-")) {
        push_back(participants, create_participant(buffer));
        fgets_without_newline(buffer, 100, stdin);
        tolower_str(buffer);
    }
    
    return participants;
}

void search_crimes_by_participants() {
    puts("\n\n\n");
    list* participants = get_list_of_participants();
   
    for (item* i = crimes->beginning; i; i = i->next) {
        crime* cr = i->data;
        list* current_cr_participants = cr->participants;
        
        bool current_crime_is_shown = false;
        
        for (item* j = current_cr_participants->beginning; j && !current_crime_is_shown; j = j->next) {
            char* current_p = strdup(j->data);
            tolower_str(current_p);
            
            for (item* k = participants->beginning; k && !current_crime_is_shown; k = k->next) {
                if (strstr(current_p, k->data) == 0) {
                    print_crime(i->data);
                    current_crime_is_shown = true;
                }
            }
            
            free(current_p);
        }
    }
    
    puts("\n\n\n"); 
    delete_list(participants);
}

void search_crimes_by_aftermath() {
    puts("\n\n\n");
    
    puts("Enter the aftermath: ");
    char aftermath[200];
    fgets_without_newline(aftermath, 200, stdin);
    tolower_str(aftermath);
    
    for (item* i = crimes->beginning; i; i = i->next) {
        crime* cr = i->data;
        char* cr_aftermath = strdup(cr->aftermath);
        tolower_str(cr_aftermath);
        
        if (strstr(cr_aftermath, aftermath)) {
            print_crime(i->data);
        }
        
        free(cr_aftermath);
    }
    
    puts("\n\n\n"); 
}

void search_crimes_by_comments() {
    puts("\n\n\n");
    
    puts("Enter the comments: ");
    char comments[300];
    fgets_without_newline(comments, 300, stdin);
    tolower_str(comments);
    
    for (item* i = crimes->beginning; i; i = i->next) {
        crime* cr = i->data;
        char* cr_comments = strdup(cr->specialists_comments);
        tolower_str(cr_comments);
        
        if (strstr(cr_comments, comments)) {
            print_crime(cr);
        }
        
        free(cr_comments);
    }
    
    puts("\n\n\n");
}

void search_crimes() {
    list* funcs = create_list(sizeof(func*), free, create_function_copy);
    list* puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    
    push_back(funcs, create_function(search_crimes_by_place));
    push_back(funcs, create_function(search_crimes_by_aftermath));
    push_back(funcs, create_function(search_crimes_by_comments));
    push_back(funcs, create_function(search_crimes_by_participants));
    
    push_back(puncts, create_punct("Search by place"));
    push_back(puncts, create_punct("Search by aftermath"));
    push_back(puncts, create_punct("Search by specialists' comments"));
    push_back(puncts, create_punct("Search by participants"));
    
    menu* search_menu = create_menu(funcs, puncts);
    delete_list(funcs);
    delete_list(puncts);
    
    puts("\n\n\n");
    execute_menu(search_menu);
    puts("\n\n\n");
    
    delete_menu(search_menu);
}

void search_criminals_by_name() { 
    puts("\n\n\n");
    
    puts("Enter the name: ");
    char name[50];
    fgets_without_newline(name, 50, stdin);
    tolower_str(name);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_name = strdup(cr->name);
        tolower_str(cr_name);
        
        if (strstr(cr_name, name)) {
            print_criminal(cr);
        }
        
        free(cr_name);
    }
    
    puts("\n\n\n");
}

void search_criminals_by_nickname() { 
    puts("\n\n\n");
    
    puts("Enter the nickname: ");
    char nickname[50];
    fgets_without_newline(nickname, 50, stdin);
    tolower_str(nickname);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_nickname = strdup(cr->nickname);
        tolower_str(cr_nickname);
        
        if (strstr(cr_nickname, nickname)) {
            print_criminal(cr);
        }
        
        free(cr_nickname);
    }
    
    puts("\n\n\n");
}

void search_criminals_by_kind_of_crimes() {
    puts("\n\n\n");
    
    puts("Enter the kind of crimes: ");
    char kind_of_crimes[50];
    fgets_without_newline(kind_of_crimes, 50, stdin);
    tolower_str(kind_of_crimes);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_kind_of_crimes = strdup(cr->kind_of_crimes);
        tolower_str(cr_kind_of_crimes);
        
        if (strstr(cr_kind_of_crimes, kind_of_crimes)) {
            print_criminal(cr);
        }
        
        free(cr_kind_of_crimes);
    }
    
    puts("\n\n\n");
}

void search_criminals_by_height() { 
    puts("\n\n\n");
    
    puts("Enter the minimum and maximum height (in cm) of the criminal: ");
    float min_h, max_h;
    int err = scanf("%f %f", &min_h, &max_h);
    
    while (err != 2 || min_h < MIN_HEIGHT_CM || min_h > MAX_HEIGHT_CM 
                    || max_h < MIN_HEIGHT_CM || max_h > MAX_HEIGHT_CM
                    || min_h > max_h) {
        puts("Please enter valid numbers");
        clear();
        err = scanf("%f %f", &min_h, &max_h);
    }
    
    clear();
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        
        if (cr->height_cm >= min_h && cr->height_cm <= max_h) {
            print_criminal(cr);
        }
    }
    
    puts("\n\n\n");
}

void search_criminals_by_weight() { 
    puts("\n\n\n");
    
    puts("Enter the minimum and maximum weight (in kg) of the criminal: ");
    float min_w, max_w;
    int err = scanf("%f %f", &min_w, &max_w);
    
    while (err != 2 || min_w < MIN_WEIGHT_KG || min_w > MAX_WEIGHT_KG 
                    || max_w < MIN_WEIGHT_KG || max_w > MAX_WEIGHT_KG
                    || min_w > max_w) {
        puts("Please enter valid numbers");
        clear();
        err = scanf("%f %f", &min_w, &max_w);
    }
    
    clear();
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        
        if (cr->weight_kg >= min_w && cr->weight_kg <= max_w) {
            print_criminal(cr);
        }
    }
    
    puts("\n\n\n");
}

void search_criminals_by_hair_color() { 
    puts("\n\n\n");
    
    puts("Enter the hair color: ");
    char hair_color[20];
    fgets_without_newline(hair_color, 20, stdin);
    tolower_str(hair_color);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_hair_color = strdup(cr->hair_color);
        tolower_str(cr_hair_color);
        
        if (strstr(cr_hair_color, hair_color)) {
            print_criminal(cr);
        }
        
        free(cr_hair_color);
    }
    
    puts("\n\n\n");
}

void search_criminals_by_special_signs() { 
    puts("\n\n\n");
    
    puts("Enter the special signs: ");
    char special_signs[200];
    fgets_without_newline(special_signs, 200, stdin);
    tolower_str(special_signs);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_special_signs = strdup(cr->special_signs);
        tolower_str(cr_special_signs);
        
        if (strstr(cr_special_signs, special_signs)) {
            print_criminal(cr);
        }
        
        free(cr_special_signs);
    }
    
    puts("\n\n\n");
}

void search_criminals_by_citizenship() { 
    puts("\n\n\n");
    
    puts("Enter the criminal's citizenship: ");
    char citizenship[30];
    fgets_without_newline(citizenship, 30, stdin);
    tolower_str(citizenship);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_citizenship = strdup(cr->citizenship);
        tolower_str(cr_citizenship);
        
        if (strstr(cr_citizenship, citizenship)) {
            print_criminal(cr);
        }
        
        free(cr_citizenship);
    }
    
    puts("\n\n\n");
}

void search_criminals_by_languages() { 
    puts("\n\n\n");
    
    puts("Enter the criminal's languages: ");
    char languages[100];
    fgets_without_newline(languages, 100, stdin);
    tolower_str(languages);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* cr = i->data;
        char* cr_languages = strdup(cr->languages);
        tolower_str(cr_languages);
        
        if (strstr(cr_languages, languages)) {
            print_criminal(cr);
        }
        
        free(cr_languages);
    }
    
    puts("\n\n\n");
}

menu* create_search_criminals_menu() {
    list* funcs = create_list(sizeof(func*), free, create_function_copy);
    list* puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    
    push_back(funcs, create_function(search_criminals_by_name));
    push_back(funcs, create_function(search_criminals_by_nickname));
    push_back(funcs, create_function(search_criminals_by_citizenship));
    push_back(funcs, create_function(search_criminals_by_hair_color));
    push_back(funcs, create_function(search_criminals_by_height));
    push_back(funcs, create_function(search_criminals_by_weight));
    push_back(funcs, create_function(search_criminals_by_special_signs));
    push_back(funcs, create_function(search_criminals_by_languages));
    push_back(funcs, create_function(search_criminals_by_kind_of_crimes));
    
    push_back(puncts, create_punct("Search by name"));
    push_back(puncts, create_punct("Search by nickname"));
    push_back(puncts, create_punct("Search by citizenship"));
    push_back(puncts, create_punct("Search by hair color"));
    push_back(puncts, create_punct("Search by height"));
    push_back(puncts, create_punct("Search by weight"));
    push_back(puncts, create_punct("Search by special signs"));
    push_back(puncts, create_punct("Search by languages"));
    push_back(puncts, create_punct("Search by kind of crimes"));
    
    menu* search_menu = create_menu(funcs, puncts);
    delete_list(funcs);
    delete_list(puncts);
    
    return search_menu;
}

void search_criminals() {
    menu* search_menu = create_search_criminals_menu();
    
    puts("\n\n\n");
    execute_menu(search_menu);
    puts("\n\n\n");
    
    delete_menu(search_menu);
}

void search_organizations_by_name() {
    puts("\n\n\n");
    
    puts("Enter the name of the organization: ");
    char name[40];
    fgets_without_newline(name, 40, stdin);
    tolower_str(name);
    
    for (item* i = organizations->beginning; i; i = i->next) {
        organization* org = i->data;
        char* org_name = strdup(org->name);
        tolower_str(org_name);
        
        if (strstr(org_name, name)) {
            print_organization(org);
        }
        
        free(org_name);
    }
    
    puts("\n\n\n");
}

void search_organizations_by_direction() {
    puts("\n\n\n");
    
    puts("Enter the direction of the organization: ");
    char dir[60];
    fgets_without_newline(dir, 60, stdin);
    tolower_str(dir);
    
    for (item* i = organizations->beginning; i; i = i->next) {
        organization* org = i->data;
        char* org_dir = strdup(org->direction);
        tolower_str(org_dir);
        
        if (strstr(org_dir, dir)) {
            print_organization(org);
        }
        
        free(org_dir);
    }
    
    puts("\n\n\n");
}

void search_organizations_by_danger_level() {
    puts("\n\n\n");
    
    puts("Enter the minimum and maximum danger level of the organization: ");
    int min_dl, max_dl;
    int err = scanf("%d %d", &min_dl, &max_dl);
    clear();
    
    while (err != 2 || min_dl < MIN_DANGER_LEVEL || min_dl > MAX_DANGER_LEVEL 
                    || max_dl < MIN_DANGER_LEVEL || max_dl > MAX_DANGER_LEVEL
                    || max_dl < min_dl) {
        puts("Please enter valid numbers");
        clear();
        err = scanf("%d %d", &min_dl, &max_dl);
    }
    
    for (item* i = organizations->beginning; i; i = i->next) {
        organization* org = i->data;
        
        if (org->danger_level >= min_dl && org->danger_level <= max_dl) {
            print_organization(org);
        }
    }
    
    puts("\n\n\n");
}

void search_organizations() {
    list* funcs = create_list(sizeof(func*), free, create_function_copy);
    list* puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    
    push_back(funcs, create_function(search_organizations_by_name));
    push_back(funcs, create_function(search_organizations_by_direction));
    push_back(funcs, create_function(search_organizations_by_danger_level));
    
    push_back(puncts, create_punct("Search by name"));
    push_back(puncts, create_punct("Search by direction"));
    push_back(puncts, create_punct("Search by danger level"));
    
    menu* search_menu = create_menu(funcs, puncts);
    delete_list(funcs);
    delete_list(puncts);
    
    puts("\n\n\n");
    execute_menu(search_menu);
    puts("\n\n\n");
    
    delete_menu(search_menu);
}

void view_and_search() {
    list* funcs = create_list(sizeof(func*), free, create_function_copy);
    list* puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    
    push_back(funcs, create_function(view_crimes));
    push_back(funcs, create_function(view_criminals));
    push_back(funcs, create_function(view_organizations));
    push_back(funcs, create_function(search_crimes));
    push_back(funcs, create_function(search_criminals));
    push_back(funcs, create_function(search_organizations));
    
    push_back(puncts, create_punct("View crimes"));
    push_back(puncts, create_punct("View criminals"));
    push_back(puncts, create_punct("View organizations"));
    push_back(puncts, create_punct("Search crimes"));
    push_back(puncts, create_punct("Search criminals"));
    push_back(puncts, create_punct("Search organizations"));
    
    menu* view_and_search_menu = create_menu(funcs, puncts);
    delete_list(funcs);
    delete_list(puncts);
    
    puts("\n\n\n");
    execute_menu(view_and_search_menu);
    puts("\n\n\n");
    
    delete_menu(view_and_search_menu);
}

void make_connections() {
    puts("\n\n\n");
    
    puts("Enter the name of the organization: ");
    char name[40];
    fgets_without_newline(name, 40, stdin);
    tolower_str(name);
    
    puts("---------------------------------");
    puts("Criminals that are listed in this organization");
    puts("---------------------------------");
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* current_criminal = i->data;
        
        if (current_criminal->organizations) {
            for (item* j = current_criminal->organizations->beginning; j; j = j->next) {
                organization* org = j->data;
                char* curr_org_name = strdup(org->name);
                tolower_str(curr_org_name);
                
                if (strstr(curr_org_name, name)) {
                    print_criminal(current_criminal);
                }
                
                free(curr_org_name);
            }
        }
    }
    
    puts("\n\n\n");
}

void who_could_do_this() {
    puts("\n\n\n");
    
    puts("Where the crime was?");
    char place[50];
    fgets_without_newline(place, 50, stdin);
    tolower_str(place);
    
    puts("---------------------------------------------");
    puts("Maybe that was one of the next criminals");
    puts("---------------------------------------------");
    
    for (item* i = criminals->beginning; i; i = i->next) {
        criminal* current_criminal = i->data;
        bool current_criminal_is_shown = false;
        
        for (item* j = current_criminal->crimes->beginning; j && !current_criminal_is_shown; j = j->next) {
            crime* current_crime = j->data;
            char* current_place = strdup(current_crime->place);
            tolower_str(current_place);
            
            if (strstr(current_place, place)) {
                current_criminal_is_shown = true;
                print_criminal(current_criminal);
            }
            
            free(current_place);
        }
    }
    
    puts("\n\n\n");
}

void archive() {
    puts("\n\n\n");
    
    int index = 1;
    
    for (item* i = criminals->beginning; i; i = i->next) {
        printf("index: %d\n", index);
        print_criminal_name(i->data);
        index++;
        puts("\n");
    }
    
    puts("Please enter the index of the criminal you want to archive: ");
    int deleting_index = 0;
    int err = scanf("%d", &deleting_index);
    clear();
    
    while (err != 1 || deleting_index < 1 || deleting_index > num_items(criminals)) {
        puts("Please enter a valid number");
        err = scanf("%d", &deleting_index);
        clear();
    }
    
    deleting_index--;
    item* deleting_item = get_item_by_index(criminals, deleting_index);
    push_back(archive_of_criminals, create_criminal_copy(deleting_item->data));
    erase(criminals, deleting_item->prev);
    
    puts("\n\n\n");
}

void delete() {
    puts("\n\n\n");
    int index = 1;
    
    for (item* i = criminals->beginning; i; i = i->next) {
        printf("index: %d\n", index);
        print_criminal_name(i->data);
        index++;
        puts("\n");
    }
    
    puts("Please enter the index of the criminal you want to delete: ");
    int deleting_index = 0;
    int err = scanf("%d", &deleting_index);
    clear();
    
    while (err != 1 || deleting_index < 1 || deleting_index > num_items(criminals)) {
        puts("Please enter a valid number");
        err = scanf("%d", &deleting_index);
        clear();
    }
    
    deleting_index--;
    item* deleting_item = get_item_by_index(criminals, deleting_index);
    erase(criminals, deleting_item->prev);
    
    puts("\n\n\n");
}

void view_archive() {
    puts("\n\n\n");
    puts("The archive:\n");
    
    for (item* i = archive_of_criminals->beginning; i; i = i->next) {
        print_criminal_name(i->data);
    }
    
    puts("\n\n\n");
}

void restore() {
    puts("\n\n\n");
    
    puts("The archive:\n");
    int index = 1;
    
    for (item* i = archive_of_criminals->beginning; i; i = i->next) {
        printf("index: %d\n", index);
        print_criminal_name(i->data);
        puts("\n");
        index++;
    }
    
    puts("Please enter the index of the criminal you want to restore: ");
    int restoring_index = 0;
    int err = scanf("%d", &restoring_index);
    clear();
    
    while (err != 1 || restoring_index < 1 || restoring_index > num_items(archive_of_criminals)) {
        puts("Please enter a valid number");
        err = scanf("%d", &restoring_index);
        clear();
    }
    
    restoring_index--;
    
    item* restoring_item = get_item_by_index(archive_of_criminals, restoring_index);
    push_back(criminals, create_criminal_copy(restoring_item->data));
    erase(archive_of_criminals, restoring_item->prev);
    
    puts("\n\n\n");
}

void work_with_archive() {
    list* archive_menu_functions = create_list(sizeof(func*), free, create_function_copy);
    push_back(archive_menu_functions, create_function(view_archive));
    push_back(archive_menu_functions, create_function(restore));
    
    list* archive_menu_puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    push_back(archive_menu_puncts, create_punct("View the archive"));
    push_back(archive_menu_puncts, create_punct("Restore a criminal"));
    
    menu* archive_menu = create_menu(archive_menu_functions, archive_menu_puncts);
    delete_list(archive_menu_puncts);
    delete_list(archive_menu_functions);
    
    execute_menu(archive_menu);
    delete_menu(archive_menu);
}

void add_crime() {
    puts("\n\n\n");
    push_back(crimes, read_crime_from_user());
    puts("\n\n\n");
}

void add_criminal() {
    puts("\n\n\n");
    push_back(criminals, read_criminal_from_user());
    puts("\n\n\n");
}

void add_organization() {
    puts("\n\n\n");
    push_back(organizations, read_organization_from_user());
    puts("\n\n\n");
}

void delete_crime_in_list() {
    puts("\n\n\n");
    int index = 1;
    
    for (item* i = crimes->beginning; i; i = i->next) {
        printf("index: %d\n", index);
        print_crime(i->data);
        index++;
        puts("\n");
    }
    
    puts("Please enter the index of the crime you want to delete: ");
    int deleting_index = 0;
    int err = scanf("%d", &deleting_index);
    clear();
    
    while (err != 1 || deleting_index < 1 || deleting_index > num_items(crimes)) {
        puts("Please enter a valid number");
        err = scanf("%d", &deleting_index);
        clear();
    }
    
    deleting_index--;
    item* deleting_item = get_item_by_index(crimes, deleting_index);
    
    erase(crimes, deleting_item->prev);
    
    puts("\n\n\n");
}

void delete_organization_in_list() {
    puts("\n\n\n");
    int index = 1;
    
    for (item* i = organizations->beginning; i; i = i->next) {
        printf("index: %d\n", index);
        print_organization(i->data);
        index++;
        puts("\n");
    }
    
    puts("Please enter the index of the organization you want to delete: ");
    int deleting_index = 0;
    int err = scanf("%d", &deleting_index);
    clear();
    
    while (err != 1 || deleting_index < 1 || deleting_index > num_items(organizations)) {
        puts("Please enter a valid number");
        err = scanf("%d", &deleting_index);
        clear();
    }
    
    deleting_index--;
    item* deleting_item = get_item_by_index(organizations, deleting_index);
    
    erase(organizations, deleting_item->prev);
    
    puts("\n\n\n");
}

void run() {
    load_data();
    
    list* main_menu_functions = create_list(sizeof(func*), free, create_function_copy);
    push_back(main_menu_functions, create_function(view_and_search));
    push_back(main_menu_functions, create_function(make_connections));
    push_back(main_menu_functions, create_function(who_could_do_this));
    push_back(main_menu_functions, create_function(archive));
    push_back(main_menu_functions, create_function(delete));
    push_back(main_menu_functions, create_function(work_with_archive));
    push_back(main_menu_functions, create_function(add_crime));
    push_back(main_menu_functions, create_function(add_organization));
    push_back(main_menu_functions, create_function(add_criminal));
    push_back(main_menu_functions, create_function(delete_crime_in_list));
    push_back(main_menu_functions, create_function(delete_organization_in_list));
    
    list* main_menu_puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    push_back(main_menu_puncts, create_punct("View and search"));
    push_back(main_menu_puncts, create_punct("Make connections between criminals and organizations"));
    push_back(main_menu_puncts, create_punct("Who could do this?"));
    push_back(main_menu_puncts, create_punct("Archive criminals"));
    push_back(main_menu_puncts, create_punct("Delete criminals"));
    push_back(main_menu_puncts, create_punct("Work with the archive of criminals"));
    push_back(main_menu_puncts, create_punct("Add a crime"));
    push_back(main_menu_puncts, create_punct("Add an organization"));
    push_back(main_menu_puncts, create_punct("Add a criminal"));
    push_back(main_menu_puncts, create_punct("Delete a crime"));
    push_back(main_menu_puncts, create_punct("Delete an organization"));
    
    menu* main_menu = create_menu(main_menu_functions, main_menu_puncts);
    delete_list(main_menu_functions);
    delete_list(main_menu_puncts);
    
    execute_menu(main_menu);
    delete_menu(main_menu);
    
    write_data_in_files();
    free_data();
}
