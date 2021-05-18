#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>

#include "application.h"
#include "check.h"
#include "crime.h"
#include "criminal.h"
#include "list.h"
#include "menu.h"
#include "organization.h"

// list testing ////////////////////////////////////

void* create_int(int a) {
    int* ptr = malloc(sizeof(int));
    *ptr = a;
    return ptr;
}

void* create_int_copy(void* a) {
    void* copy = malloc(sizeof(int));
    check_mem_alloc(copy);
    *((int*)copy) = *((int*)a);
    return copy;
}

void test_create_push_delete_list() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    check_mem_alloc(example);
    delete_list(example);
    
    example = create_list(sizeof(int), free, create_int_copy);
    push_back(example, create_int(60));
    int* data_ptr = example->beginning->data;
    assert(*data_ptr == 60);
    
    push_back(example, create_int(60));
    data_ptr = example->beginning->next->data;
    assert(*data_ptr == 60);
    
    delete_list(example);
}

void test_create_list_copy() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    list* example_copy = create_list_copy(example);
    
    int* data_ptr = example_copy->beginning->data;
    assert(*data_ptr == 65);
    
    delete_list(example_copy);
    delete_list(example);
}

void test_get_by_index() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    assert(*((int*)get_by_index(example, 0)) == *((int*)example->beginning->data));
    
    delete_list(example);
}

void test_get_item_by_index() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    item* i = get_item_by_index(example, 0);
    int* data = i->data;
    
    assert(*data == *((int*)example->beginning->data));
    
    delete_list(example);
}

void test_push_front() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_front(example, create_int(65));
    push_front(example, create_int(60));
    
    assert(*((int*)example->beginning->data) == 60);
    assert(*((int*)example->beginning->next->data) == 65);
    
    delete_list(example);
}

void test_num_items() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    assert(num_items(example) == 2);
    
    delete_list(example);
}

void test_pop_back() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    assert(num_items(example) == 2);
    
    pop_back(example);
    assert(num_items(example) == 1);
    assert(*((int*)example->beginning->data) == 65);
    
    delete_list(example);
}

void test_pop_front() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(60));
    push_back(example, create_int(65));
    assert(num_items(example) == 2);
    
    pop_front(example);
    assert(num_items(example) == 1);
    assert(*((int*)example->beginning->data) == 65);
    
    delete_list(example);
}

void test_insert() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    insert(example, example->beginning, create_int(100));
    
    assert(num_items(example) == 3);
    assert(*((int*)example->beginning->next->data) == 100);
    
    delete_list(example);
}

void test_erase() {
    list* example = create_list(sizeof(int), free, create_int_copy);
    
    push_back(example, create_int(65));
    push_back(example, create_int(60));
    
    erase(example, example->beginning);
    assert(num_items(example) == 1);
    assert(*((int*)example->beginning->data) == 65);
    
    delete_list(example);
}

// end of list testing /////////////////////////////

// check testing ///////////////////////////////////

void test_fgets_without_newline() {
    FILE* estream = fopen("test_text.txt", "w");
    fputs("example example\n\n\n\n\n", estream);
    fclose(estream);
    
    estream = fopen("test_text.txt", "r");
    char str[200];
    fgets_without_newline(str, 200, estream);
    fclose(estream);
    
    assert(str[strlen(str) - 1] != '\n');
    remove("test_text.txt");
}

void test_fputs_with_newline() {
    FILE* estream = fopen("test_text.txt", "w");
    fputs_with_newline("mda", estream);
    fclose(estream);
    
    estream = fopen("test_text.txt", "r");
    fgetc(estream); fgetc(estream); fgetc(estream);
    assert(fgetc(estream) == '\n');
    fclose(estream);
    
    remove("test_text.txt");
}

void test_tolower_str() {
    char str[200] = "WHERE BANANA";
    tolower_str(str);
    assert(!strcmp(str, "where banana"));
}

// end of check testing ////////////////////////////

// test organization ///////////////////////////////

void test_create_organization() {
    organization* org = create_organization("ogogo", "ogogo", 10);
    check_mem_alloc(org);
    assert(org->danger_level == 10);
    assert(!strcmp(org->name, "ogogo"));
    assert(!strcmp(org->direction, "ogogo"));
    free(org);
}

void test_create_organization_copy() {
    organization* org = create_organization("ogogo", "ogogo", 10);
    organization* org_copy = create_organization_copy(org);
    assert(org_copy->danger_level == 10);
    assert(!strcmp(org_copy->name, "ogogo"));
    assert(!strcmp(org_copy->direction, "ogogo"));
    free(org);
    free(org_copy);
}

void test_print_organization() {
    organization* org = create_organization("ogogo", "ogogo", 10);
    
    FILE* estream = fopen("test_text.txt", "w");
    FILE* old_stdout = stdout;
    stdout = estream;
    print_organization(org);
    stdout = old_stdout;
    fclose(estream);
    
    estream = fopen("test_text.txt", "r");
    
    char buffer[256];    
    fgets_without_newline(buffer, 256, estream);
    assert(!strcmp(buffer, "-------------------------"));
    fgets_without_newline(buffer, 256, estream);
    assert(!strcmp(buffer, "ogogo"));
    fgets_without_newline(buffer, 256, estream);
    assert(!strcmp(buffer, "Direction:"));
    fgets_without_newline(buffer, 256, estream);
    assert(!strcmp(buffer, "ogogo"));
    fgets_without_newline(buffer, 256, estream);
    assert(!strcmp(buffer, "Danger level: 10"));
    fgets_without_newline(buffer, 256, estream);
    assert(!strcmp(buffer, "-------------------------"));
    
    fclose(estream);
    free(org);
    remove("test_text.txt");
}

void write_buffer_in_test_file(const char* buffer) {
    FILE* estream = fopen("test_text.txt", "w");
    while (*buffer) {
        fputc(*buffer, estream);
        buffer++;
    }
    
    fclose(estream);
}

void remove_test_files() {
    remove("test_text.txt");
    remove("test_text2.txt");
}

void test_read_organization() {
    write_buffer_in_test_file("jojo org\njojoing\n10\n");
    FILE* estream = fopen("test_text.txt", "r");
    
    organization* org = read_organization(estream);
    
    assert(!strcmp(org->name, "jojo org"));
    assert(!strcmp(org->direction, "jojoing"));
    assert(org->danger_level == 10);
    
    free(org);
    
    fclose(estream);
}

void test_read_organization_from_user() {
    write_buffer_in_test_file("\njojo org\njojoing\n10\n\n");
    FILE* estream = fopen("test_text.txt", "r");
    FILE* old_stdin = stdin;
    stdin = estream;
    organization* org = read_organization_from_user();
    assert(!strcmp(org->name, "jojo org"));
    assert(!strcmp(org->direction, "jojoing"));
    assert(org->danger_level == 10);
    stdin = old_stdin;
    fclose(estream);
    free(org);
}

int fsize(const char* file_name) {
    FILE* fp = fopen(file_name, "r");
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fclose(fp);
    return sz;
}

void test_file_contents(const char* file_name, const char* expected_contents) {
    FILE* estream = fopen(file_name, "r");
    char c = fgetc(estream);
    int i = 0;
    
    while (c != EOF) {
        assert(c == expected_contents[i]);
        i++;
        c = fgetc(estream);
    }
    
    fclose(estream);
}

void test_read_write_organizations() {
    write_buffer_in_test_file("-organizations-\n"
                              "jojo org\n"
                              "jojoing\n"
                              "10\n"
                              "---\n"
                              "ojoj gro\n"
                              "ojojing\n"
                              "1\n"
                              "-endorganizations-\n\n");
    list* orgs = read_organizations("test_text.txt");
    
    organization* first = get_by_index(orgs, 0);
    organization* second = get_by_index(orgs, 1);
    
    assert(!strcmp(first->name, "jojo org"));
    assert(!strcmp(first->direction, "jojoing"));
    assert(first->danger_level == 10);
    assert(!strcmp(second->name, "ojoj gro"));
    assert(!strcmp(second->direction, "ojojing"));
    assert(second->danger_level == 1);
    
    write_organizations(orgs, "test_text.txt");
    delete_list(orgs);
    
    test_file_contents("test_text.txt", "-organizations-\n"
                                        "jojo org\n"
                                        "jojoing\n"
                                        "10\n"
                                        "---\n"
                                        "ojoj gro\n"
                                        "ojojing\n"
                                        "1\n"
                                        "-endorganizations-\n");
}

// end of organization testing /////////////////////

// menu test ///////////////////////////////////////

void fnc() { 
    FILE* estream = fopen("test_text.txt", "w");
    fputs_with_newline("H", estream);
    fclose(estream);
}

void test_create_function_and_copy() {
    void* ptr_to_fnc = create_function(fnc);
    func f = *((func*)ptr_to_fnc);
    f();
    
    FILE* estream = fopen("test_text.txt", "r");
    assert(fgetc(estream) == 'H');
    fclose(estream);
    
    write_buffer_in_test_file("");
    void* ptr_to_fnc_copy = create_function_copy(ptr_to_fnc);
    func f_copy = *((func*)ptr_to_fnc);
    f_copy();
    
    estream = fopen("test_text.txt", "r");
    assert(fgetc(estream) == 'H');
    fclose(estream);
    
    free(ptr_to_fnc_copy);
    free(ptr_to_fnc);
}

void test_create_punct() {
    void* pn = create_punct("Sus");
    
    const char* pn_str = pn;
    assert(!strcmp(pn_str, "Sus"));
    
    free(pn);
}

void menu_fnc() {
    printf("A");
}

void test_create_execute_menu() {
    list* puncts = create_list(sizeof(punct), free, (creating_copy_func)strdup);
    list* funcs = create_list(sizeof(func*), free, create_function_copy);
    
    push_back(funcs, create_function(menu_fnc));
    push_back(puncts, create_punct("Execute menu_fnc()"));
    
    menu* e_menu = create_menu(funcs, puncts);
    
    write_buffer_in_test_file("\n1\n0\n\n");
    FILE* old_stdin = stdin;
    FILE* old_stdout = stdout;
    
    FILE* file_stdin = fopen("test_text.txt", "r");
    FILE* file_stdout = fopen("test_text2.txt", "w");
    
    stdin = file_stdin;
    stdout = file_stdout;
    
    execute_menu(e_menu);
    
    fclose(file_stdin);
    fclose(file_stdout);
    
    test_file_contents("test_text2.txt", "1: Execute menu_fnc()\n"
                                         "0. Back\n"
                                         "A"
                                         "1: Execute menu_fnc()\n"
                                         "0. Back\n");
    
    stdin = old_stdin;
    stdout = old_stdout;
    
    delete_menu(e_menu);
    delete_list(puncts);
    delete_list(funcs);
}

// end of menu testing /////////////////////////////

// test crime //////////////////////////////////////

void test_create_and_copy_participant() {
    void* p = create_participant("A");
    const char* str = p;
    
    assert(!strcmp(str, "A"));
    void* p2 = create_participant_copy(p);
    
    assert(!strcmp(p2, "A"));
    
    free(p);
    free(p2);
}

void test_create_and_copy_crime() {
    list* participants = create_list(sizeof(participant), free, (creating_copy_func)strdup);
    push_back(participants, create_participant("B"));
    
    crime* e_crime = create_crime("A", "B", "C", participants);
    delete_list(participants);
    
    assert(!strcmp(e_crime->place, "A"));
    assert(!strcmp(e_crime->aftermath, "B"));
    assert(!strcmp(e_crime->specialists_comments, "C"));
    assert(!strcmp(e_crime->participants->beginning->data, "B"));
    
    crime* e_crime_2 = create_crime_copy(e_crime);
    
    assert(!strcmp(e_crime_2->place, "A"));
    assert(!strcmp(e_crime_2->aftermath, "B"));
    assert(!strcmp(e_crime_2->specialists_comments, "C"));
    assert(!strcmp(e_crime_2->participants->beginning->data, "B"));    
    
    delete_crime(e_crime);
    delete_crime(e_crime_2);
}

void test_read_crime_from_user() {
    write_buffer_in_test_file("k\nk\n-\nk\nl\n");
    FILE* estream = fopen("test_text.txt", "r");
    FILE* old_stdin = stdin;
    stdin = estream;
    
    crime* cr = read_crime_from_user();
    assert(!strcmp(cr->place, "k"));
    assert(!strcmp(cr->aftermath, "k"));
    assert(!strcmp(cr->specialists_comments, "l"));
    assert(!strcmp(cr->participants->beginning->data, "k"));
    
    delete_crime(cr);
    fclose(estream);
    stdin = old_stdin;
}

void test_read_write_crimes() {
    write_buffer_in_test_file("-crimes-\n"
                              "Nodnol\n"
                              "Jojokololo\n"
                              "Fokorotolo\n"
                              "-\n"
                              "Some apocalypse number 2\n"
                              "The Gordlsiokfod: This was some blin number 2\n"
                              "-endcrimes-\n");
    list* crimes = read_crimes("test_text.txt");
    
    crime* first = crimes->beginning->data;    
    assert(!strcmp(first->place, "Nodnol"));
    
    write_buffer_in_test_file("");
    write_crimes(crimes, "test_text.txt");
    delete_list(crimes);
    test_file_contents("test_text.txt", "-crimes-\n"
                                        "Nodnol\n"
                                        "Jojokololo\n"
                                        "Fokorotolo\n"
                                        "-\n"
                                        "Some apocalypse number 2\n"
                                        "The Gordlsiokfod: This was some blin number 2\n"
                                        "-endcrimes-\n");
    
}

void test_print_crime() {
    FILE* old_stdout = stdout;
    FILE* file_stdout = fopen("test_text.txt", "w");
    stdout = file_stdout;
    
    list* participants = create_list(sizeof(participant), free, (creating_copy_func)strdup);
    push_back(participants, create_participant("B"));
    
    crime* e_crime = create_crime("A", "B", "C", participants);
    delete_list(participants);
    
    print_crime(e_crime);
    fclose(file_stdout);
    
    test_file_contents("test_text.txt",
                       "------------------------------------\n"
                       "Place: A\n"
                       "Participants:\n"
                       "B\n"
                       "Aftermath:\n"
                       "B\n"
                       "Specialists\' comments:\n"
                       "C\n"
                       "------------------------------------\n");
    
    stdout = old_stdout;
    delete_crime(e_crime);
}

// end of crime testing ////////////////////////////

// criminal test ///////////////////////////////////

void test_criminal() {
    list* participants = create_list(sizeof(participant), free, (creating_copy_func)strdup);
    push_back(participants, create_participant("H"));
    
    list* crimes = create_list(sizeof(list), (deleting_item_data_func)delete_crime, (creating_copy_func)create_crime_copy);
    push_back(crimes, create_crime("P", "A", "C", participants));
    delete_list(participants);
    
    list* organizations = create_list(sizeof(organization), free, (creating_copy_func)create_organization_copy);
    push_back(organizations, create_organization("N", "D", MAX_DANGER_LEVEL));
    
    criminal* e_criminal = create_criminal("CN", "NN", "C", "HC", "LN", "SS", 180.0f, 75.0, "KC", crimes, organizations);
    criminal* e_copy = create_criminal_copy(e_criminal);
    delete_list(crimes);
    delete_list(organizations);
    
    assert(!strcmp(e_criminal->name, "CN"));
    assert(!strcmp(e_criminal->nickname, "NN"));
    assert(!strcmp(e_criminal->languages, "LN"));
    
    assert(!strcmp(e_copy->name, "CN"));
    assert(!strcmp(e_copy->nickname, "NN"));
    assert(!strcmp(e_copy->languages, "LN"));
    
    FILE* file_stdout = fopen("test_text.txt", "w");
    FILE* old_stdout = stdout;
    stdout = file_stdout;
    print_criminal(e_criminal);
    fclose(file_stdout);
    
    test_file_contents("test_text.txt", "----------------------------------\n"
                                        "CN, aka NN\n"
                                        "Kind of crimes: KC\n"
                                        "Height: 180.000000 cm\n"
                                        "Weight: 75.000000 kg\n"
                                        "HC hair color\n"
                                        "Citizenship: C\n"
                                        "Special signs: SS\n"
                                        "Languages: LN\n"
                                        "--------------------------\n"
                                        "Crimes:\n"
                                        "------------------------------------\n"
                                        "Place: P\n"
                                        "Participants:\n"
                                        "H\n"
                                        "Aftermath:\n"
                                        "A\n"
                                        "Specialists\' comments:\n"
                                        "C\n"
                                        "------------------------------------\n"
                                        "Is listed in these organizations:\n"
                                        "-------------------------\n"
                                        "N\n"
                                        "Direction:\n"
                                        "D\n"
                                        "Danger level: 10\n"
                                        "-------------------------\n"
                                        "----------------------------------\n");
    
    stdout = fopen("test_text.txt", "w");
    print_criminal_name(e_copy);
    fclose(stdout);
    
    test_file_contents("test_text.txt", "----------------------------------\n"
                                        "CN, aka NN\n"
                                        "----------------------------------\n");    
    
    stdout = old_stdout;
    
    delete_criminal(e_criminal);
    delete_criminal(e_copy);
    
    write_buffer_in_test_file("-criminals-\n"
                              "f\n"
                              "f\n"
                              "200.000000\n"
                              "100.000000\n"
                              "f\n"
                              "f\n"
                              "f\n"
                              "f\n"
                              "f\n"
                              "-crimes-\n"
                              "f\n"
                              "f\n"
                              "-\n"
                              "f\n"
                              "f\n"
                              "-endcrimes-\n"
                              "-organizations-\n"
                              "-endorganizations-\n"
                              "-endcriminals-\n");
    
    list* criminals = read_criminals("test_text.txt");
    
    criminal* cr = criminals->beginning->data;
    assert(!strcmp(cr->name, "f"));
    assert(!strcmp(cr->nickname, "f"));
    
    write_criminals(criminals, "test_text.txt");
    test_file_contents("test_text.txt", "-criminals-\n"
                                        "f\n"
                                        "f\n"
                                        "200.000000\n"
                                        "100.000000\n"
                                        "f\n"
                                        "f\n"
                                        "f\n"
                                        "f\n"
                                        "f\n"
                                        "-crimes-\n"
                                        "f\n"
                                        "f\n"
                                        "-\n"
                                        "f\n"
                                        "f\n"
                                        "-endcrimes-\n"
                                        "-organizations-\n"
                                        "-endorganizations-\n"
                                        "-endcriminals-\n");
    
    delete_list(criminals);
    
    write_buffer_in_test_file("n\n"
                              "n\n"
                              "180\n"
                              "78\n"
                              "h\n"
                              "ss\n"
                              "c\n"
                              "l\n"
                              "k\n"
                              "p\n"
                              "p\n"
                              "-\n"
                              "a\n"
                              "a\n"
                              "y\n"
                              "n\n");
    
    FILE* old_stdin = stdin;
    stdin = fopen("test_text.txt", "r");
    criminal* read_crl = read_criminal_from_user();
    fclose(stdin);
    stdin = old_stdin;
    
    assert(!strcmp(read_crl->name, "n"));
    assert(!strcmp(read_crl->languages, "l"));
    delete_criminal(read_crl);
}

// end of criminal testing /////////////////////////

// application test ////////////////////////////////

void test_application() {
    FILE* old_stdin = stdin;
    stdin = fopen("test_user_input.txt", "r");
    
    run();
    
    fclose(stdin);
    stdin = old_stdin;
}

// ending of application test //////////////////////

#undef main
int main() {
    test_create_push_delete_list();
    test_create_list_copy();
    test_get_by_index();
    test_get_item_by_index();
    test_push_front();
    test_num_items();
    test_pop_back();
    test_pop_front();
    test_insert();
    test_erase();
    
    test_fgets_without_newline();
    test_fputs_with_newline();
    test_tolower_str();
    
    test_create_organization();
    test_create_organization_copy();
    test_print_organization();
    test_read_organization();
    test_read_organization_from_user();
    test_read_write_organizations();
    
    test_create_function_and_copy();
    test_create_punct();
    test_create_execute_menu();
    
    test_create_and_copy_participant();
    test_create_and_copy_crime();
    test_read_crime_from_user();
    test_read_write_crimes();
    test_print_crime();
    
    test_criminal();
    
    test_application();
    
    puts("\n\nAll tests passed");
    remove_test_files();
    
    return 0;
}
