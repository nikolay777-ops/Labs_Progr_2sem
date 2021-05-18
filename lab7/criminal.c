#include "criminal.h"

// LCOV_EXCL_START
void check_criminal_data(const char* name, const char* nickname, const char* citizenship, const char* hair_color,
                         const char* languages, const char* special_signs, float height_cm, float weight_kg, 
                         const char* kind_of_crimes, list* crimes) {
    check("name", strlen(name) >= 50);
    check("nickname", strlen(nickname) >= 50);
    check("citizenship", strlen(citizenship) >= 30);
    check("hair color", strlen(hair_color) >= 20);
    check("weight", weight_kg < MIN_WEIGHT_KG || weight_kg > MAX_WEIGHT_KG);
    check("height", height_cm < MIN_HEIGHT_CM || height_cm > MAX_HEIGHT_CM);
    check("special signs", strlen(special_signs) >= 200);
    check("languages", strlen(languages) >= 100);
    check("kind of crimes", strlen(kind_of_crimes) >= 50);
    check("crimes", crimes == NULL);
}
// LCOV_EXCL_STOP

void* create_criminal(const char* name, const char* nickname, const char* citizenship, const char* hair_color,
                      const char* languages, const char* special_signs, float height_cm, float weight_kg, 
                      const char* kind_of_crimes, list* crimes, list* organizations) {
    check_criminal_data(name, nickname, citizenship, hair_color, languages, special_signs, height_cm, weight_kg, kind_of_crimes, crimes);
    
    criminal* ptr = (criminal*)malloc(sizeof(criminal));
    check_mem_alloc(ptr);
    
    strcpy(ptr->name, name);
    strcpy(ptr->nickname, nickname);
    strcpy(ptr->citizenship, citizenship);
    strcpy(ptr->hair_color, hair_color);
    strcpy(ptr->languages, languages);
    strcpy(ptr->special_signs, special_signs);
    strcpy(ptr->kind_of_crimes, kind_of_crimes);
    
    ptr->height_cm = height_cm;
    ptr->weight_kg = weight_kg;
    
    ptr->crimes = create_list_copy(crimes);
    if (!organizations) { 
        ptr->organizations = NULL;
        return ptr;
    }
    
    ptr->organizations = create_list_copy(organizations);
    return ptr;
}

criminal* create_criminal_copy(criminal* cr) {
    criminal* ptr = malloc(sizeof(criminal));
    check_mem_alloc(ptr);
    
    strcpy(ptr->name, cr->name);
    strcpy(ptr->nickname, cr->nickname);
    strcpy(ptr->citizenship, cr->citizenship);
    strcpy(ptr->hair_color, cr->hair_color);
    strcpy(ptr->languages, cr->languages);
    strcpy(ptr->special_signs, cr->special_signs);
    strcpy(ptr->kind_of_crimes, cr->kind_of_crimes);
    
    ptr->height_cm = cr->height_cm;
    ptr->weight_kg = cr->weight_kg;
    
    ptr->crimes = create_list_copy(cr->crimes);
    if (!cr->organizations) { 
        ptr->organizations = NULL;
        return ptr;
    }
    
    ptr->organizations = create_list_copy(cr->organizations);
    
    return ptr;
}

void delete_criminal(criminal* cr) {
    if (cr->organizations) {
        delete_list(cr->organizations);
    }
    
    delete_list(cr->crimes);
    free(cr);
}

void print_criminal(criminal* cr) {
    puts("----------------------------------");
    printf("%s, aka %s\n", cr->name, cr->nickname);
    printf("Kind of crimes: %s\n", cr->kind_of_crimes);
    printf("Height: %f cm\nWeight: %f kg\n", cr->height_cm, cr->weight_kg);
    printf("%s hair color\n", cr->hair_color);
    printf("Citizenship: %s\n", cr->citizenship);
    printf("Special signs: %s\n", cr->special_signs);
    printf("Languages: %s\n", cr->languages);
    puts("--------------------------");
    puts("Crimes:");
    
    for (item* i = cr->crimes->beginning; i; i = i->next) {
        print_crime(i->data);
    }
    if (cr->organizations) {
        puts("Is listed in these organizations:");
        
        for (item* i = cr->organizations->beginning; i; i = i->next) {
            print_organization(i->data);
        }
    }
    
    puts("----------------------------------");
}

void print_criminal_name(criminal* cr) {
    puts("----------------------------------");
    printf("%s, aka %s\n", cr->name, cr->nickname);
    puts("----------------------------------");
}

criminal* read_criminal(FILE* fin) {
    criminal new_criminal;
    
    fgets_without_newline(new_criminal.name, 50, fin);
    
    if (strcmp(new_criminal.name, "-endcriminals-") == 0) {
        return NULL;
    }
    
    fgets_without_newline(new_criminal.nickname, 50, fin);
    fscanf(fin, "%f\n", &new_criminal.height_cm);
    fscanf(fin, "%f\n", &new_criminal.weight_kg);
    fgets_without_newline(new_criminal.hair_color, 20, fin);
    fgets_without_newline(new_criminal.special_signs, 200, fin);
    fgets_without_newline(new_criminal.citizenship, 30, fin);
    fgets_without_newline(new_criminal.languages, 100, fin);
    fgets_without_newline(new_criminal.kind_of_crimes, 50, fin);
    new_criminal.crimes = read_crimes_file(fin);
    new_criminal.organizations = read_organizations_file(fin);
    
    criminal* created_criminal = create_criminal(
        new_criminal.name, new_criminal.nickname, new_criminal.citizenship, 
        new_criminal.hair_color, new_criminal.languages,
        new_criminal.special_signs, new_criminal.height_cm, new_criminal.weight_kg, 
        new_criminal.kind_of_crimes, new_criminal.crimes, new_criminal.organizations
    );
    
    delete_list(new_criminal.crimes);
    delete_list(new_criminal.organizations);
    return created_criminal;
}

criminal* read_criminal_from_user() {
    criminal new_criminal;
    
    puts("Enter the name of the criminal:");
    fgets_without_newline(new_criminal.name, 50, stdin);
    puts("Enter the nickname of the criminal:");
    fgets_without_newline(new_criminal.nickname, 50, stdin);
    printf("Enter the height of the criminal (in cm, from %f to %f):\n", MIN_HEIGHT_CM, MAX_HEIGHT_CM);
    fscanf(stdin, "%f", &new_criminal.height_cm);
    printf("Enter the weight of the criminal (in kg, from %f to %f):\n", MIN_WEIGHT_KG, MAX_WEIGHT_KG);
    fscanf(stdin, "%f", &new_criminal.weight_kg);
    clear();
    puts("Enter the hair color of the criminal:");
    fgets_without_newline(new_criminal.hair_color, 20, stdin);
    puts("Enter the special signs of the criminal:");
    fgets_without_newline(new_criminal.special_signs, 200, stdin);
    puts("Enter the citizenship of the criminal:");
    fgets_without_newline(new_criminal.citizenship, 30, stdin);
    puts("Enter the languages of the criminal:");
    fgets_without_newline(new_criminal.languages, 100, stdin);
    puts("Enter the criminal's kind of crimes:");
    fgets_without_newline(new_criminal.kind_of_crimes, 50, stdin);
    
    puts("Enter the crimes:");
    new_criminal.crimes = create_list(sizeof(crime), (deleting_item_data_func)delete_crime, (creating_copy_func)create_crime_copy);
    
    while (true) {
        push_back(new_criminal.crimes, read_crime_from_user());
        puts("Do you want to stop? (y/n)");
        char ch = getchar();
        clear();
        
        if (ch == 'y') {
            break;
        }
    }
    
    puts("Is the criminal listed in some organizations? (y/n)");
    char ch = getchar();
    clear();
    
    if (ch == 'y') {
        puts("Enter the organizations ():");
        new_criminal.organizations = create_list(sizeof(organization), free, (creating_copy_func)create_organization_copy);
        
        while (true) {
            push_back(new_criminal.organizations, read_organization_from_user());
            puts("Do you want to stop? (y/n)");
            char ch = getchar();
            clear();
            
            if (ch == 'y') {
                break;
            }
        }
    }
    else {
        new_criminal.organizations = NULL;
    }
    
    criminal* created_criminal = create_criminal(
        new_criminal.name, new_criminal.nickname, new_criminal.citizenship, 
        new_criminal.hair_color, new_criminal.languages,
        new_criminal.special_signs, new_criminal.height_cm, new_criminal.weight_kg, 
        new_criminal.kind_of_crimes, new_criminal.crimes, new_criminal.organizations
    );
    
    delete_list(new_criminal.crimes);
    if (new_criminal.organizations) { delete_list(new_criminal.organizations); }
    return created_criminal;
}

list* read_criminals_file(FILE* fin) {
    char title[100];
    fgets_without_newline(title, 100, fin);
    
    if (strcmp(title, "-criminals-")) {
        error("Criminals file was corrupted. Terminating the program");
    }
    
    list* criminals = create_list(sizeof(criminal), (deleting_item_data_func)delete_criminal, (creating_copy_func)create_criminal_copy);
    char buffer[50];
    
    while (true) {
        criminal* cr = read_criminal(fin);
        if (!cr) { break; }
        
        push_back(criminals, cr);
        fgets_without_newline(buffer, 50, fin);
        
        if (!strcmp(buffer, "-endcriminals-")) {
            break;
        }
    }
    
    return criminals;
}

list* read_criminals(const char* filename) {
    FILE* fin = fopen(filename, "r");
    list* criminals = read_criminals_file(fin);
    fclose(fin);
    return criminals;
}

void write_criminal(criminal* cr, FILE* fout, bool end) {
    fputs_with_newline(cr->name, fout);
    fputs_with_newline(cr->nickname, fout);
    fprintf(fout, "%f\n", cr->height_cm);
    fprintf(fout, "%f\n", cr->weight_kg);
    fputs_with_newline(cr->hair_color, fout);
    fputs_with_newline(cr->special_signs, fout);
    fputs_with_newline(cr->citizenship, fout);
    fputs_with_newline(cr->languages, fout);
    fputs_with_newline(cr->kind_of_crimes, fout);
    
    write_crimes_file(cr->crimes, fout);
    write_organizations_file(cr->organizations, fout);
    
    if (!end) {
        fputs_with_newline("---", fout);
    }
}

void write_criminals(list* criminals, const char* filename) {
    FILE* fout = fopen(filename, "w");
    write_criminals_file(criminals, fout);
    fclose(fout);
}

void write_criminals_file(list* criminals, FILE* fout) {
    fputs_with_newline("-criminals-", fout);
    
    for (item* i = criminals->beginning; i; i = i->next) {
        bool end = i == criminals->ending;
        write_criminal(i->data, fout, end);
    }
    
    fputs_with_newline("-endcriminals-", fout);
}
