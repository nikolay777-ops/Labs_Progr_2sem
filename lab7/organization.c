#include "organization.h"

void* create_organization(char name[], char direction[], int danger_level) {
    organization* ptr = (organization*)malloc(sizeof(organization));
    check_mem_alloc(ptr);
    
    if (strlen(name) > 39) { 
        error("The name of an organization must be less than 40 symbols");
    }
    if (strlen(direction) > 59) {
        error("The direction of an organization must be less than 60 symbols");
    }
    if (danger_level > MAX_DANGER_LEVEL || danger_level < MIN_DANGER_LEVEL) {
        char errmsg[50];
        sprintf(errmsg, "Danger level must be from %d to %d", MIN_DANGER_LEVEL, MAX_DANGER_LEVEL);
        error(errmsg);  
    }
    
    strcpy(ptr->name, name);
    strcpy(ptr->direction, direction);
    ptr->danger_level = danger_level;
    
    return ptr;
}

organization* create_organization_copy(organization* org) {
    organization* copy = malloc(sizeof(organization));
    check_mem_alloc(copy);
    
    strcpy(copy->name, org->name);
    strcpy(copy->direction, org->direction);
    copy->danger_level = org->danger_level;
    
    return copy;
}

void print_organization(organization* org) {
    puts("-------------------------");
    puts(org->name);
    puts("Direction:");
    puts(org->direction);
    printf("Danger level: %d\n", org->danger_level);
    puts("-------------------------");
}

organization* read_organization(FILE* fin) {
    organization org;
    fgets_without_newline(org.name, 40, fin);
    
    if (strcmp(org.name, "-endorganizations-") == 0) {
        return NULL;
    }
    
    fgets_without_newline(org.direction, 60, fin);
    fscanf(fin, "%d\n", &org.danger_level);
    return create_organization(org.name, org.direction, org.danger_level);
}

organization* read_organization_from_user() {
    organization org;
    puts("Enter data about the organization:");
    puts("Enter the name of the organization:");
    clear();
    fgets_without_newline(org.name, 40, stdin);
    puts("Enter the direction of the organization:");
    fgets_without_newline(org.direction, 60, stdin);
    puts("Enter the danger level of the organization: ");
    fscanf(stdin, "%d", &org.danger_level);
    return create_organization(org.name, org.direction, org.danger_level);
}

list* read_organizations(const char* filename) {
    FILE* fin = fopen(filename, "r");
    list* orgs = read_organizations_file(fin);
    fclose(fin);
    return orgs;
}

list* read_organizations_file(FILE* fin) {
    char title[100];
    fgets_without_newline(title, 100, fin);
    
    if (strcmp(title, "-organizations-")) {
        error("Organizations file was corrupted. Terminating the program");
    }
    
    list* organizations = create_list(sizeof(organization), free, (creating_copy_func)create_organization_copy);
    char buffer[50];
    
    while (true) {
        organization* org = read_organization(fin);
        
        if (!org) { break; }
        
        push_back(organizations, org);
        fgets_without_newline(buffer, 50, fin);
        
        if (!strcmp(buffer, "-endorganizations-")) {
            break;
        }
    }
    
    return organizations;
}

void write_organization(organization* org, FILE* fout, bool end) {
    fputs_with_newline(org->name, fout);
    fputs_with_newline(org->direction, fout);
    fprintf(fout, "%d\n", org->danger_level);
    
    if (!end) {
        fputs_with_newline("---", fout);
    }
}

void write_organizations(list* organizations, const char* filename) {
    FILE* fout = fopen(filename, "w");
    write_organizations_file(organizations, fout);
    fclose(fout);
}

void write_organizations_file(list* organizations, FILE* fout) {
    fputs_with_newline("-organizations-", fout);
    
    if (organizations) {
        for (item* i = organizations->beginning; i; i = i->next) {
            bool end = i == organizations->ending;
            write_organization(i->data, fout, end);
        }
    }
    
    fputs_with_newline("-endorganizations-", fout);
}
