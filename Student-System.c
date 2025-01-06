#include <stdio.h>
#include <string.h>

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

void remove_student(struct student_info stds[], struct date dob, int* count_student, int n)
{
    for (int i = n-1; i < *count_student; i++)
    {
        stds[i] = stds[i+1];
        for(int q=0; q<stds[i+1].number_of_added_course; q++)
        {
            stds[i].courses[q] = stds[i+1].courses[q];
        }
    }
    (*count_student)--;
}

void edit_student(struct student_info stds[], int m, char *new_first_name, 
char *new_last_name, int new_student_number, char *new_gender, char *new_father_name)
{
    strcpy(stds[m-1].first_name, new_first_name);
    strcpy(stds[m-1].last_name, new_last_name);
    strcpy(stds[m-1].gender, new_gender);
    strcpy(stds[m-1].father_name, new_father_name);
    stds[m-1].studentـnumber = new_student_number;
}

void add_course_to_all(struct student_info stds[], struct student_course courses[], 
char *course_name, int course_value, int* count_student)
{
    for (int l = 0; l < *count_student; l++)
    {
        stds[l].courses->all_courses_values = stds[l].courses->all_courses_values + course_value;
        if(stds[l].courses->all_courses_values <= MAX_COURSE)
        {
            strcpy(stds[l].courses[stds[l].number_of_added_course].course_name, course_name);
            stds[l].courses[stds[l].number_of_added_course].couse_value = course_value;
            stds[l].number_of_added_course++;
            printf("\n****The course was added to student number %d****\n", l+1);
        }
        else
        {
            stds[l].courses->all_courses_values = stds[l].courses->all_courses_values - course_value;
            printf("\n****sorry, the course was not added to student number %d because of course value limit :(****\n", l+1);
        }
    }
}

void add_course_to_one_person(struct student_info stds[], struct student_course courses[], 
char *course_name, int course_value, int k)
{
    stds[k-1].courses->all_courses_values = stds[k-1].courses->all_courses_values + course_value; 
    if(stds[k-1].courses->all_courses_values <= MAX_COURSE)
    {
        strcpy(stds[k-1].courses[stds[k-1].number_of_added_course].course_name, course_name);
        stds[k-1].courses[stds[k-1].number_of_added_course].couse_value = course_value;
        stds[k-1].number_of_added_course++;
        printf("\n****The course was added****\n");
    }
    else
    {
        int course_value_before_adding = stds[k-1].courses->all_courses_values - course_value;
        stds[k-1].courses->all_courses_values = stds[k-1].courses->all_courses_values - course_value;
        printf("\n****sorry, not enough space to add more courses :(****\n");
        printf("****current courses values: %d\tcourses values if you add this course:%d\tlimit is 20****\n", course_value_before_adding, 
        stds[k-1].courses->all_courses_values);
    }
}

void remove_course (struct student_info stds[], struct student_course courses[], int b, int o)
{
    for (int i = b-1; i < stds[o-1].number_of_added_course; i++)
    {
        stds[o-1].courses[i] = stds[o-1].courses[i+1];
    }
    stds[o-1].courses->all_courses_values = stds[o-1].courses->all_courses_values - stds[o-1].courses[b-1].couse_value;
    stds[o-1].number_of_added_course--;
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
            printf("What is your gender:(male or female?) ");
            scanf("%s", newstd.gender);
            printf("Father name: ");
            scanf("%s", newstd.father_name);
            printf("Student number: ");
            scanf("%lld", &newstd.studentـnumber);
            printf("Date of birth (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &newstd.dob.day, &newstd.dob.month, &newstd.dob.year);
            add_student(stds, newstd, &count_student);    
            break;
        
        case 2:
            int n;
            long long int student_number_for_remove_student;
            int search_result1 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_remove_student);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_remove_student == stds[i].studentـnumber)
                {
                    n = i+1;
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
                printf("\nStudent %d:\n", n);
                printf("\tFirst name: %s\n", stds[n-1].first_name);
                printf("\tLast name: %s\n", stds[n-1].last_name);
                printf("\tStudent number: %lld\n", stds[n-1].studentـnumber);
                printf("\tGender: %s\n", stds[n-1].gender);
                printf("\tFather name: %s\n", stds[n-1].father_name);
                printf("\tDate of birth: %02d/%02d/%02d\n\n", stds[n-1].dob.day, 
                stds[n-1].dob.month, stds[n-1].dob.year);
                int make_sure;
                printf("Are you sure that you want to remove this student?(Yes: 1/No: 2) ");
                scanf("%d", &make_sure);
                if(make_sure == 1)
                {
                    remove_student(stds, dob, &count_student, n);
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
            int m;
            long long int student_number_for_edit_student;
            int search_result2 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_edit_student);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_edit_student == stds[i].studentـnumber)
                {
                    m = i+1;
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
                printf("Gender(male or female): ");
                scanf("%s", new_gender);
                printf("Father name: ");
                scanf("%s", new_father_name);
                printf("Date of birth (DD/MM/YYYY): ");
                scanf("%d/%d/%d", &stds[m-1].dob.day, &stds[m-1].dob.month, 
                &stds[m-1].dob.year);
                edit_student(stds, m, new_first_name, new_last_name, 
                new_student_number, new_gender, new_father_name);
                update_file(stds, &count_student);
                printf("\n****The student was edited****\n");
            }
            break;
        
        case 4:
            int k;
            char course_name[255];
            int course_value;
            long long int student_number_for_add_course;
            int search_result3 = 0;
            printf("Enter student number (0 to add all): ");
            scanf("%lld", &student_number_for_add_course);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_add_course == stds[i].studentـnumber)
                {
                    k = i+1;
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
                add_course_to_one_person(stds, courses, course_name, course_value, k);
                update_file(stds, &count_student);
            }
            if (student_number_for_add_course == 0)
            {
                printf("Enter course name: ");
                scanf("%s", course_name);
                printf("Enter course value: ");
                scanf("%d", &course_value);
                add_course_to_all(stds, courses, course_name, course_value, &count_student);
                update_file(stds, &count_student);
            }
            break;
        
        case 5:
            int o;
            long long int student_number_for_remove_course;
            int search_result4 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_remove_course);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_remove_course == stds[i].studentـnumber)
                {
                    o = i+1;
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
                for (int i = 0; i < stds[o-1].number_of_added_course; i++)
                {
                    if(stds[o-1].courses[i].grade != 0)
                    {
                        printf("%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", i+1, stds[o-1].courses[i].course_name, 
                        stds[o-1].courses[i].couse_value, stds[o-1].courses[i].grade);
                    }
                    else
                    {
                        printf("%d. course name: %s\tcourse value: %d\n", i+1, stds[o-1].courses[i].course_name, 
                        stds[o-1].courses[i].couse_value);          
                    }
                }
                int b;
                printf("\nWhich course do you want to remove? ");
                scanf("%d", &b);
                if (b>=1 && b<=stds[o-1].number_of_added_course)
                {
                    remove_course(stds, courses, b, o);
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
            int h;
            long long int student_number_for_add_course_grade;
            int search_result5 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_add_course_grade);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_add_course_grade == stds[i].studentـnumber)
                {
                    h = i+1;
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
                for (int i = 0; i < stds[h-1].number_of_added_course; i++)
                {
                    if(stds[h-1].courses[i].grade != 0)
                    {
                        printf("%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", i+1, stds[h-1].courses[i].course_name, 
                        stds[h-1].courses[i].couse_value, stds[h-1].courses[i].grade);
                    }
                    else
                    {
                        printf("%d. course name: %s\tcourse value: %d\n", i+1, stds[h-1].courses[i].course_name, 
                        stds[h-1].courses[i].couse_value);          
                    }
                }
                int g;
                printf("\nChose the course: ");
                scanf("%d", &g);
                if (g>=1 && g<=stds[h-1].number_of_added_course)
                {
                    if(stds[h-1].courses[g-1].grade != 0)
                    {
                        printf("\n****This course is already graded****\n");
                    }
                    else
                    {
                        float grade;
                        printf("Grade: ");
                        scanf("%f", &grade);
                        stds[h-1].courses[g-1].grade = grade;
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
            int z;
            long long int student_number_for_edit_course_grade;
            int search_result6 = 0;
            printf("Enter student number: ");
            scanf("%lld", &student_number_for_edit_course_grade);
            for (int i = 0; i < count_student; i++)
            {
                if(student_number_for_edit_course_grade == stds[i].studentـnumber)
                {
                    z = i+1;
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
                for (int i = 0; i < stds[z-1].number_of_added_course; i++)
                {
                    if(stds[z-1].courses[i].grade != 0)
                    {
                        printf("%d. course name: %s\tcourse value: %d\tgrade: %.2f\n", i+1, stds[z-1].courses[i].course_name, 
                        stds[z-1].courses[i].couse_value, stds[z-1].courses[i].grade);
                    }
                    else
                    {
                        printf("%d. course name: %s\tcourse value: %d\n", i+1, stds[z-1].courses[i].course_name, 
                        stds[z-1].courses[i].couse_value);          
                    }
                }
                int x;
                printf("\nChose the course: ");
                scanf("%d", &x);
                if (x>=1 && x<=stds[z-1].number_of_added_course)
                {
                    if(stds[z-1].courses[x-1].grade == 0)
                    {
                        printf("\n****This course has no grade to edit****\n");
                    }
                    else
                    {
                        float new_grade;
                        printf("Grade: ");
                        scanf("%f", &new_grade);
                        stds[z-1].courses[x-1].grade = new_grade;
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