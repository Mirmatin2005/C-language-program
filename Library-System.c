#include <stdio.h>
#include <string.h>

#define MAX_BOOK 100

struct Book
{
    char title[100];
    char author[100];
    int year;
};

// function to add book
void addBook(struct Book books[], struct Book newBook, int *count)
{
    if(*count < MAX_BOOK)
    {
        books[*count]=newBook;
        (*count)++;
    }
    else
    {
        printf("Cannot add more books, reached maximum limit of %d books.\n", MAX_BOOK);
    }
}

// function to remove book
void removebook(struct Book books[], int *count, int n)
{
    for (int i = n-1; i < *count; i++)
    {
        books[i] = books[i+1];
    }
    (*count)--;
}

// function to edit book
void editbook(struct Book books[], int m, char *new_title, char *new_author, int new_year)
{
    strcpy(books[m-1].title, new_title);
    strcpy(books[m-1].author, new_author);
    books[m-1].year = new_year;
}

// function to print result
void printBooks(struct Book books[], int count)
{
    for (int i = 0; i < count; i++) 
    {
        printf("\nBook %d:\n", i + 1);
        printf("\tTitle: %s\n", books[i].title);
        printf("\tAuthor: %s\n", books[i].author);
        printf("\tPublication Year: %d\n\n", books[i].year);
    }
}

void main()
{
    struct Book books[MAX_BOOK];
    struct Book newBook;
    int count = 0;

    int ch; // parametr to chose a number in menu
    printf("\nHellooooo!\n");
    do
    {
        printf("\n1. Add book.");
        printf("\n2. Remove book.");
        printf("\n3. Edit book.");
        printf("\n4. See the list of the books.");
        printf("\n5. Exit.\n");
        printf("\nPleas enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            char title[100];
            char author[100];
            int year;
            printf("Title: ");
            scanf("%s", newBook.title);
            printf("Author: ");
            scanf("%s", newBook.author);
            printf("Year: ");
            scanf("%d", &newBook.year);
            addBook(books, newBook, &count);  
            printf("\n****The book was added****\n");  
            break;
        
        case 2:
            int n; // parametr to chose a book that we want to remove
            for (int i = 0; i < count; i++)
            {
                printf("\n%d. %s", i+1, books[i].title);
            }
            printf("\n\nWhich book do you want to remove? ");
            scanf("%d", &n);
            if (n>=1 && n<=count)
            {
                removebook(books, &count, n);
                printf("\n****The book was removed****\n");
            }
            else
            {
                printf("\n****The book dose not exist****\n");
            }
            break;

        case 3:
            int m; // parametr to chose a book that we want to edit
            for (int i = 0; i < count; i++)
            {
                printf("\n%d. %s", i+1, books[i].title);
            }
            printf("\n\nWhich book do you want to edit? ");
            scanf("%d", &m);
            if (m>=1 && m<=count)
            {
                char new_title[100];
                char new_author[100];
                int new_year;
                printf("New title: ");
                scanf("%s", new_title);
                printf("New author: ");
                scanf("%s", new_author);
                printf("New year: ");
                scanf("%d", &new_year);
                editbook(books, m, new_title, new_author, new_year);
                printf("\n****The book was edited****\n");
            }
            else
            {
                printf("\n****The book dose not exist****\n");
            }
            break;
        
        case 4:
            printBooks(books, count);
            break;

        case 5:
            printf("\nGoodbye :)\n\n");
            break;
        
        default:
            printf("\n****Invalid choice****\n");
            break;
        }
    } while (ch != 5);
}