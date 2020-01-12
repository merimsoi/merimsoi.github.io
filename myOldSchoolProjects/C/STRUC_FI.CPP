#include<stdio.h>
typedef struct
{char fname[10];
char lname[15];
}students;
void update_person();
void print_person();
students std,*ptr_std;
main()
{
ptr_std=&std;
update_person();
print_person();
}
void update_person()
{
printf("\n enter first name:");
scanf("%s",ptr_std->fname);
printf("enter last name:");
scanf("%s",std.lname);
}
void print_person()
{
printf("\n first name:%s\n",std.fname);
printf("last name:%s",ptr_std->lname);
}