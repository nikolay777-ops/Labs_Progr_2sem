#include "crime.h"

void* create_crime(const char* place, const char* aftermath, const char* comments, list* participants) {
    check("place", strlen(place) >= 50);
    check("aftermath", strlen(aftermath) >= 200);
    check("comments", strlen(comments) >= 300);
    
    crime* ptr = (crime*)malloc(sizeof(crime));
    check_mem_alloc(ptr);
    strcpy(ptr->place, place);
    strcpy(ptr->aftermath, aftermath);
    strcpy(ptr->specialists_comments, comments);
    
    // the crime object will have a COPY of the participants list
    ptr->participants = create_list_copy(participants);
    
    return ptr;
}

void* create_participant(const char* name) {
    check("name", strlen(name) >= 100);
    char* ptr = (char*)malloc(sizeof(char[100]));
    check_mem_alloc(ptr);
    strcpy(ptr, name);
    return ptr;
}

void* create_participant_copy(const char* p) {
    return strdup(p);
}

crime* create_crime_copy(crime* cr) {
    crime* copy = malloc(sizeof(crime));
    check_mem_alloc(copy);
    strcpy(copy->place, cr->place);
    strcpy(copy->aftermath, cr->aftermath);
    strcpy(copy->specialists_comments, cr->specialists_comments);
    copy->participants = create_list_copy(cr->participants);
    return copy;
}

// LCOV_EXCL_START
void delete_crime(crime *cr) {
    delete_list(cr->participants);
    free(cr);
}
// LCOV_EXCL_STOP

crime* read_crime_from_user() {
    crime* new_crime = (crime*)malloc(sizeof(crime));
    check_mem_alloc(new_crime);
    
    puts("Enter the data about the crime:");
    puts("Enter the crime place: ");
    fgets_without_newline(new_crime->place, 50, stdin);
    new_crime->participants = create_list(sizeof(char[100]), (deleting_item_data_func)free, (creating_copy_func)create_participant_copy);
    
    puts("Enter the participants of the crime. Enter \'-\' to stop:");
    // read all participants
    char buffer[300];
    fgets_without_newline(buffer, 100, stdin);
    
    while (strcmp(buffer, "-") != 0) {
        push_back(new_crime->participants, create_participant(buffer));
        fgets_without_newline(buffer, 100, stdin);
    }
    
    puts("Enter the aftermath of the crime:");
    fgets_without_newline(new_crime->aftermath, 200, stdin);
    puts("Enter the specialists' comments:");
    fgets_without_newline(new_crime->specialists_comments, 300, stdin);
    
    crime* created_crime = create_crime(new_crime->place, new_crime->aftermath, new_crime->specialists_comments, new_crime->participants);
    delete_crime(new_crime);
    
    return created_crime;
}

crime* read_crime(FILE* fin) {
    crime* new_crime = (crime*)malloc(sizeof(crime));
    check_mem_alloc(new_crime);
    
    fgets_without_newline(new_crime->place, 50, fin);
    new_crime->participants = create_list(sizeof(char[100]), (deleting_item_data_func)free, (creating_copy_func)create_participant_copy);
    
    // read all participants
    char buffer[300];
    fgets_without_newline(buffer, 100, fin);
    
    while (strcmp(buffer, "-") != 0) {
        push_back(new_crime->participants, create_participant(buffer));
        fgets_without_newline(buffer, 100, fin);
    }
    
    fgets_without_newline(new_crime->aftermath, 200, fin);
    fgets_without_newline(new_crime->specialists_comments, 300, fin);
    
    crime* created_crime = create_crime(new_crime->place, new_crime->aftermath, new_crime->specialists_comments, new_crime->participants);
    delete_crime(new_crime);
    
    return created_crime;
}

list* read_crimes(const char* filename) {
    FILE* fin = fopen(filename, "r");
    list* crimes = read_crimes_file(fin);
    fclose(fin);
    return crimes;
}

list* read_crimes_file(FILE* fin) {
    char title[100];
    fgets_without_newline(title, 100, fin);
    
    if (strcmp(title, "-crimes-")) {
        printf("%s\n", title);
        error("Crimes file was corrupted. Terminating the program");
    }
    
    list* crimes = create_list(sizeof(crime), (deleting_item_data_func)delete_crime, (creating_copy_func)create_crime_copy);
    
    while (true) {
        push_back(crimes, read_crime(fin));
        char buffer[50];
        fgets_without_newline(buffer, 50, fin);
        
        if (!strcmp(buffer, "-endcrimes-")) {
            break;
        }
    }
    
    return crimes;
}

void write_crimes(list* crimes, const char* filename) {
    FILE* fout = fopen(filename, "w");
    write_crimes_file(crimes, fout);
    fclose(fout);
}

void write_crime(crime* cr, FILE* fout, bool end) {
    fputs_with_newline(cr->place, fout);
    
    for (item* i = cr->participants->beginning; i; i = i->next) {
        fputs_with_newline(i->data, fout);
    }
    
    fputs_with_newline("-", fout);
    fputs_with_newline(cr->aftermath, fout);
    fputs_with_newline(cr->specialists_comments, fout);
    
    if (!end) {
        fputs_with_newline("---", fout);
    }
}

void write_crimes_file(list* crimes, FILE* fout) {
    fprintf(fout, "-crimes-\n");
    
    for (item* i = crimes->beginning; i; i = i->next) {
        bool end = i == crimes->ending;
        write_crime(i->data, fout, end);
    }
    
    fputs_with_newline("-endcrimes-", fout);
}

void print_crime(crime* cr) {
    puts("------------------------------------");
    printf("Place: %s\n", cr->place);
    puts("Participants:");
    
    for (item* i = cr->participants->beginning; i; i = i->next) {
        const char* name = i->data;
        puts(name);
    }
    
    puts("Aftermath:");
    puts(cr->aftermath);
    puts("Specialists' comments:");
    puts(cr->specialists_comments);
    puts("------------------------------------");
}
