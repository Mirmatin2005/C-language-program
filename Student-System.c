#include <stdio.h>
#include <string.h>

//stds: students

#define MAX_STD 100
#define MAX_COURSE 20

struct student_course 
{
    char course_name[255];
    int couse_value;
    float grade;
    int all_courses_values;
};

struct date
{
    int day;
    int month;
    int year;
};

struct student_info
{
    char first_name[255];
    char last_name[255];
    char gender[255];
    char father_name[255];
    long long int studentـnumber; 
    struct date dob; 
    struct student_course courses[MAX_COURSE];
    int number_of_added_course;
};

void read_from_file(struct student_info stds[], int *count_student)
{
    FILE* file = fopen("mir-matin.txt", "r");
    if(file != NULL)
    {
        while(fscanf(file, "%[^\n]\n", stds[*count_student].first_name) == 1) 
        {
            fscanf(file, "%s\n", stds[*count_student].last_name);
            fscanf(file, "%lld\n", &stds[*count_student].studentـnumber);
            fscanf(file, "%s\n", stds[*count_student].gender);
            fscanf(file, "%s\n", stds[*count_student].father_name);
            fscanf(file, "%d/%d/%d\n", &stds[*count_student].dob.day, 
            &stds[*count_student].dob.month, &stds[*count_student].dob.year);
            fscanf(file, "%d\n", &stds[*count_student].number_of_added_course);
            for (int i = 0; i < stds[*count_student].number_of_added_course; i++)
            {
                fscanf(file, "%s\t%d\t%f\n", stds[*count_student].courses[i].course_name, 
                &stds[*count_student].courses[i].couse_value, &stds[*count_student].courses[i].grade);
            }
            fscanf(file, "%d\n", &stds[*count_student].courses->all_courses_values);
            (*count_student)++;
        }
    }
    else
    {
        printf("\n****There is no data in file****\n");
        return;
    }
    fclose(file);
}

void update_file(struct student_info stds[], int* count_student)
{
    FILE* file = fopen("mir-matin.txt", "w");
    if(file != NULL)
    {
        for (int i = 0; i < *count_student; i++)
        {
            fprintf(file, "%s\n", stds[i].first_name);
            fprintf(file, "%s\n", stds[i].last_name);
            fprintf(file, "%lld\n", stds[i].studentـnumber);
            fprintf(file, "%s\n", stds[i].gender);
            fprintf(file, "%s\n", stds[i].father_name);
            fprintf(file, "%d/%d/%d\n", stds[i].dob.day, stds[i].dob.month, stds[i].dob.year);
            fprintf(file, "%d\n", stds[i].number_of_added_course);
            for (int j = 0; j < stds[i].number_of_added_course; j++)
            {
                fprintf(file, "%s\t%d\t%f\n", stds[i].courses[j].course_name, 
                stds[i].courses[j].couse_value, stds[i].courses[j].grade);
            }
            fprintf(file, "%d\n\n", stds[i].courses->all_courses_values);
        }
    }
    else
    {
        printf("\n****There was an error in opening file for writing****\n");
        return;
    }
    fclose(file);
}

void add_student(struct student_info stds[], struct student_info newstd, int* count_student)
{
    if (*count_student < MAX_STD)
    {
        stds[*count_student] = newstd;
        (*count_student)++;
        update_file(stds, count_student);
        printf("\n****The student was added****\n");
    }
    else
    {
        printf("sorry, not enough space to add more students :(\n");
    }
}

void remove_student(struct student_info stds[], int* count_student, int searched_id_to_remove_student)
{
    for (int i = searched_id_to_remove_student; i < *count_student; i++)
    {
        stds[i] = stds[i+1];
        for(int q=0; q<stds[i+1].number_of_added_course; q++)
        {
            stds[i].courses[q] = stds[i+1].courses[q];
        }
    }
    (*count_student)--;
}

void edit_student(struct student_info stds[], int searched_id_to_edit_student, char *new_first_name, 
char *new_last_name, int new_student_number, char *new_gender, char *new_father_name)
{
    strcpy(stds[searched_id_to_edit_student].first_name, new_first_name);
    strcpy(stds[searched_id_to_edit_student].last_name, new_last_name);
    strcpy(stds[searched_id_to_edit_student].gender, new_gender);
    strcpy(stds[searched_id_to_edit_student].father_name, new_father_name);
    stds[searched_id_to_edit_student].studentـnumber = new_student_number;
}

void add_course_to_all(struct student_info stds[], struct student_course courses[], 
char *course_name, int course_value, int* count_student)
{
    for (int i = 0; i < *count_student; i++)
    {
        
        if(stds[i].courses->all_courses_values + course_value <= MAX_COURSE)
        {
            strcpy(stds[i].courses[stds[i].number_of_added_course].course_name, course_name);
            stds[i].courses[stds[i].number_of_added_course].couse_value = course_value;
            stds[i].courses->all_courses_values = stds[i].courses->all_courses_values + course_value;
            stds[i].number_of_added_course++;
            printf("\n****The course was added to student number %d****\n", i+1);
        }
        else
        {
            printf("\n****sorry, the course was not added to student number %d because of course value limit :(****\n", i+1);
        }
    }
}

void add_course_to_one_person(struct student_info stds[], struct student_course courses[], 
char *course_name, int course_value, int searched_id_to_add_course)
{   
    if(stds[searched_id_to_add_course].courses->all_courses_values + course_value <= MAX_COURSE)
    {
        strcpy(stds[searched_id_to_add_course].courses[stds[searched_id_to_add_course].number_of_added_course].course_name, course_name);
        stds[searched_id_to_add_course].courses[stds[searched_id_to_add_course].number_of_added_course].couse_value = course_value;
        stds[searched_id_to_add_course].courses->all_courses_values = stds[searched_id_to_add_course].courses->all_courses_values + course_value;
        stds[searched_id_to_add_course].number_of_added_course++;
        printf("\n****The course was added****\n");
    }
    else
    {
        int course_value_after_adding = stds[searched_id_to_add_course].courses->all_courses_values + course_value;
        printf("\n****sorry, not enough space to add more courses :(****\n");
        printf("****current courses values: %d\tcourses values if you add this course:%d\tlimit is 20****\n", 
        stds[searched_id_to_add_course].courses->all_courses_values, course_value_after_adding);
    }
}

void remove_course (struct student_info stds[], struct student_course courses[], int sellected_course_to_remove, int searched_id_to_remove_course)
{
    for (int i = sellected_course_to_remove-1; i < stds[searched_id_to_remove_course].number_of_added_course; i++)
    {
        stds[searched_id_to_remove_course].courses[i] = stds[searched_id_to_remove_course].courses[i+1];
    }
    stds[searched_id_to_remove_course].courses->all_courses_values = stds[searched_id_to_remove_course].courses->all_courses_values - stds[searched_id_to_remove_course].courses[sellected_course_to_remove-1].couse_value;
    stds[searched_id_to_remove_course].number_of_added_course--;
}

void print_student(struct student_info stds[], struct date dob, 
struct student_course courses[], int count_student)
{
    for (int i = 0; i < count_student; i++) 
    {
        printf("\nStudent %d:\n", i + 1);
        printf("\tFirst name: %s\n", stds[i].first_name);
        printf("\tLast name: %s\n", stds[i].last_name);
        printf("\tStudent number: %lld\n", stds[i].studentـnumber);
        printf("\tGender: %s\n", stds[i].gender);
        printf("\tFather name: %s\n", stds[i].father_name);
        printf("\tDate of birth: %02d/%02d/%02d\n", stds[i].dob.day, 
        stds[i].dob.month, stds[i].dob.year);
        for(int p=0; p<stds[i].number_of_added_course; p++)
        {
            if(stds[i].courses[p].grade != 0)
            {
                printf("\t%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", p+1, stds[i].courses[p].course_name, 
                stds[i].courses[p].couse_value, stds[i].courses[p].grade);
            }
            else
            {
                printf("\t%d. course name: %s\tcourse value: %d\n", p+1, stds[i].courses[p].course_name, 
                stds[i].courses[p].couse_value);          
            }
        }
    }
    printf("\n");
}

void main()
{
    struct student_info stds[MAX_STD];
    struct student_course courses[MAX_COURSE];
    struct date dob;
    struct student_info newstd;
    int count_student = 0;
    int ch;
    printf("\nHellooooo!\n");
    read_from_file(stds, &count_student);
    do
    {
        printf("\n1. Add student.");
        printf("\n2. Remove student.");
        printf("\n3. Edit student.");
        printf("\n4. Add course.");
        printf("\n5. Remove course.");
        printf("\n6. Add course grade.");
        printf("\n7. edit course grade.");
        printf("\n8. See the list of the students.");
        printf("\n9. Exit.\n");
        printf("\nPleas enter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            char first_name[255];
            char last_name[255];
            char gender[255];
            char father_name[255];
            int student_number;
            printf("First name: ");
            scanf("%s", newstd.first_name);
            printf("Last name: ");
            scanf("%s", newstd.last_name);
            do
            {
                printf("What is your gender:(male or female?) ");
                scanf("%s", newstd.gender);
            } while (strcmp(newstd.gender, "male")!=0 && strcmp(newstd.gender, "female")!=0);
            printf("Father name: ");
            scanf("%s", newstd.father_name);
            printf("Student number: ");
            scanf("%lld", &newstd.studentـnumber);
            printf("Date of birth (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &newstd.dob.day, &newstd.dob.month, &newstd.dob.year);
            add_student(stds, newstd, &count_student);    
            break;
        
        case 2:
            int searched_id_to_remove_student;
            long long int student_number_for_remove_student;
            int search_result1 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_remove_student);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_remove_student == stds[i].studentـnumber)
                {
                    searched_id_to_remove_student = i;
                    search_result1 = 1;
                    break;
                }
            }
            if(search_result1 == 0)
            {
                printf("\n****The student dose not exist****\n");
            }
            else
            {
                printf("\nStudent %d:\n", searched_id_to_remove_student+1);
                printf("\tFirst name: %s\n", stds[searched_id_to_remove_student].first_name);
                printf("\tLast name: %s\n", stds[searched_id_to_remove_student].last_name);
                printf("\tStudent number: %lld\n", stds[searched_id_to_remove_student].studentـnumber);
                printf("\tGender: %s\n", stds[searched_id_to_remove_student].gender);
                printf("\tFather name: %s\n", stds[searched_id_to_remove_student].father_name);
                printf("\tDate of birth: %02d/%02d/%02d\n\n", stds[searched_id_to_remove_student].dob.day, 
                stds[searched_id_to_remove_student].dob.month, stds[searched_id_to_remove_student].dob.year);
                int make_sure;
                printf("Are you sure that you want to remove this student?(Yes: 1/No: 2) ");
                scanf("%d", &make_sure);
                if(make_sure == 1)
                {
                    remove_student(stds, &count_student, searched_id_to_remove_student);
                    update_file(stds, &count_student);
                    printf("\n****The student was removed****\n");
                }
                else
                {
                    break;
                } 
            }
            break;

        case 3:
            int searched_id_to_edit_student;
            long long int student_number_for_edit_student;
            int search_result2 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_edit_student);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_edit_student == stds[i].studentـnumber)
                {
                    searched_id_to_edit_student = i;
                    search_result2 = 1;
                    break;
                }
            }
            if(search_result2 == 0)
            {
                printf("\n****The student dose not exist****\n");
            }
            else
            {
                char new_first_name[255];
                char new_last_name[255];
                long long int new_student_number;
                char new_gender[255];
                char new_father_name[255];
                printf("First name: ");
                scanf("%s", new_first_name);
                printf("Last name: ");
                scanf("%s", new_last_name);
                printf("Student number: ");
                scanf("%lld", &new_student_number);
                do
                {
                    printf("What is your gender:(male or female?) ");
                    scanf("%s", new_gender);
                } while (strcmp(new_gender, "male")!=0 && strcmp(new_gender, "female")!=0);
                printf("Father name: ");
                scanf("%s", new_father_name);
                printf("Date of birth (DD/MM/YYYY): ");
                scanf("%d/%d/%d", &stds[searched_id_to_edit_student].dob.day, &stds[searched_id_to_edit_student].dob.month, 
                &stds[searched_id_to_edit_student].dob.year);
                edit_student(stds, searched_id_to_edit_student, new_first_name, new_last_name, 
                new_student_number, new_gender, new_father_name);
                update_file(stds, &count_student);
                printf("\n****The student was edited****\n");
            }
            break;
        
        case 4:
            int searched_id_to_add_course;
            char course_name[255];
            int course_value;
            long long int student_number_for_add_course;
            int search_result3 = 0;
            printf("Enter student number (0 to add all): ");
            scanf("%lld", &student_number_for_add_course);
            if (student_number_for_add_course == 0)
            {
                printf("Enter course name: ");
                scanf("%s", course_name);
                printf("Enter course value: ");
                scanf("%d", &course_value);
                add_course_to_all(stds, courses, course_name, course_value, &count_student);
                update_file(stds, &count_student);
            }
            else
            {
                for (int i = 0; i < count_student; i++)
                {
                    if(student_number_for_add_course == stds[i].studentـnumber)
                    {
                        searched_id_to_add_course = i;
                        search_result3 = 1;
                        break;
                    }
                }
                if(search_result3 == 0)
                {
                    printf("\n****The student dose not exist****\n");
                }
                else
                {
                    printf("Enter course name: ");
                    scanf("%s", course_name);
                    printf("Enter course value: ");
                    scanf("%d", &course_value);
                    add_course_to_one_person(stds, courses, course_name, course_value, searched_id_to_add_course);
                    update_file(stds, &count_student);
                }
            }
            break;
        
        case 5:
            int searched_id_to_remove_course;
            long long int student_number_for_remove_course;
            int search_result4 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_remove_course);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_remove_course == stds[i].studentـnumber)
                {
                    searched_id_to_remove_course = i;
                    search_result4 = 1;
                    break;
                }
            }
            if(search_result4 == 0)
            {
                printf("\n****The student dose not exist****\n");
            }
            else
            {
                for (int i = 0; i < stds[searched_id_to_remove_course].number_of_added_course; i++)
                {
                    if(stds[searched_id_to_remove_course].courses[i].grade != 0)
                    {
                        printf("%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", i+1, stds[searched_id_to_remove_course].courses[i].course_name, 
                        stds[searched_id_to_remove_course].courses[i].couse_value, stds[searched_id_to_remove_course].courses[i].grade);
                    }
                    else
                    {
                        printf("%d. course name: %s\tcourse value: %d\n", i+1, stds[searched_id_to_remove_course].courses[i].course_name, 
                        stds[searched_id_to_remove_course].courses[i].couse_value);          
                    }
                }
                int sellected_course_to_remove;
                printf("\nWhich course do you want to remove? ");
                scanf("%d", &sellected_course_to_remove);
                if (sellected_course_to_remove>=1 && sellected_course_to_remove<=stds[searched_id_to_remove_course].number_of_added_course)
                {
                    remove_course(stds, courses, sellected_course_to_remove, searched_id_to_remove_course);
                    update_file(stds, &count_student);
                    printf("\n****The course was removed****\n");
                }
                else
                {
                    printf("\n****The course dose not exist****\n");
                }
            }
            break;

        case 6:
            int sellected_student_to_add_course_grade;
            long long int student_number_for_add_course_grade;
            int search_result5 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_add_course_grade);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_add_course_grade == stds[i].studentـnumber)
                {
                    sellected_student_to_add_course_grade = i;
                    search_result5 = 1;
                    break;
                }
            }
            if(search_result5 == 0)
            {
                printf("\n****The student dose not exist****\n");
            }
            else
            {
                for (int i = 0; i < stds[sellected_student_to_add_course_grade].number_of_added_course; i++)
                {
                    if(stds[sellected_student_to_add_course_grade].courses[i].grade != 0)
                    {
                        printf("%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", i+1, stds[sellected_student_to_add_course_grade].courses[i].course_name, 
                        stds[sellected_student_to_add_course_grade].courses[i].couse_value, stds[sellected_student_to_add_course_grade].courses[i].grade);
                    }
                    else
                    {
                        printf("%d. course name: %s\tcourse value: %d\n", i+1, stds[sellected_student_to_add_course_grade].courses[i].course_name, 
                        stds[sellected_student_to_add_course_grade].courses[i].couse_value);          
                    }
                }
                int sellected_course_to_add_grade;
                printf("\nChose the course: ");
                scanf("%d", &sellected_course_to_add_grade);
                if (sellected_course_to_add_grade>=1 && sellected_course_to_add_grade<=stds[sellected_student_to_add_course_grade].number_of_added_course)
                {
                    if(stds[sellected_student_to_add_course_grade].courses[sellected_course_to_add_grade].grade != 0)
                    {
                        printf("\n****This course is already graded****\n");
                    }
                    else
                    {
                        float grade;
                        printf("Grade: ");
                        scanf("%f", &grade);
                        stds[sellected_student_to_add_course_grade].courses[sellected_course_to_add_grade].grade = grade;
                        update_file(stds, &count_student);
                        printf("\n****The course graded successfuly****\n");
                    }
                }
                else
                {
                    printf("\n****The course dose not exist****\n");
                }
            }
            break;
        
        case 7:
            int sellected_student_to_edit_course_grade;
            long long int student_number_for_edit_course_grade;
            int search_result6 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_edit_course_grade);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_edit_course_grade == stds[i].studentـnumber)
                {
                    sellected_student_to_edit_course_grade = i;
                    search_result6 = 1;
                    break;
                }
            }
            if(search_result6 == 0)
            {
                printf("\n****The student dose not exist****\n");
            }
            else
            {
                for (int i = 0; i < stds[sellected_student_to_edit_course_grade].number_of_added_course; i++)
                {
                    if(stds[sellected_student_to_edit_course_grade].courses[i].grade != 0)
                    {
                        printf("%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", i+1, stds[sellected_student_to_edit_course_grade].courses[i].course_name, 
                        stds[sellected_student_to_edit_course_grade].courses[i].couse_value, stds[sellected_student_to_edit_course_grade].courses[i].grade);
                    }
                    else
                    {
                        printf("%d. course name: %s\tcourse value: %d\n", i+1, stds[sellected_student_to_edit_course_grade].courses[i].course_name, 
                        stds[sellected_student_to_edit_course_grade].courses[i].couse_value);          
                    }
                }
                int sellected_course_to_edit_grade;
                printf("\nChose the course: ");
                scanf("%d", &sellected_course_to_edit_grade);
                if (sellected_course_to_edit_grade>=1 && sellected_course_to_edit_grade<=stds[sellected_student_to_edit_course_grade].number_of_added_course)
                {
                    if(stds[sellected_student_to_edit_course_grade].courses[sellected_course_to_edit_grade-1].grade == 0)
                    {
                        printf("\n****This course has no grade to edit****\n");
                    }
                    else
                    {
                        float new_grade;
                        printf("Grade: ");
                        scanf("%f", &new_grade);
                        stds[sellected_student_to_edit_course_grade].courses[sellected_course_to_edit_grade-1].grade = new_grade;
                        update_file(stds, &count_student);
                        printf("\n****The course grade edited successfuly****\n");
                    }
                }
                else
                {
                    printf("\n****The course dose not exist****\n");
                }
            }
            break;

        case 8:
            print_student(stds, dob, courses, count_student);
            break;

        case 9:
            printf("\nGoodbye :)\n\n");
            break;
        
        default:
            printf("\n****Invalid choice****\n");
            break;
        }
    } while (ch != 9);
}
