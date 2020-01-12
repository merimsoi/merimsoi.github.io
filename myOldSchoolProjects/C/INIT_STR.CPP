#include<stdio.h>
struct person
{
char name[20];
char address[80];
int age;
char phone[15];
};
struct person phone_rec[]=
{
"mike","alenbi 75",23,"03-5465556",
"sela","givat-shmuel",0,"03-5353302"
};
main()
{int i;
int size=sizeof(phone_rec)/sizeof(struct person);
for(i=0;i<size;i++)
{
puts(phone_rec[i].name);
puts(phone_rec[i].address);
printf("%d\n",phone_rec[i].age);
puts(phone_rec[i].phone);
}}
