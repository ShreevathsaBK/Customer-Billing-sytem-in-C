#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

time_t t;
int n,p,Index;

char num[25];
char cost[25][5];
char items[25][30];

char names[25][30];
char phone[25][12];

FILE * fptrbill;
FILE * fptritems;
FILE * fptralpha;
FILE * fptrcost;
FILE * fptrnames;
FILE * fptrphone;

int n_digits(int);
void replace_line(char [], int);
void delete_line(char [], int);

void items_input();
void display();
void purchase_and_display_bill();
void menu();
void add_item();

void account_input();
void accounting();
void create_account();
void account_menu();
void display_accounts();
int search_account(char []);
void edit_phone(char []);
void delete_account(char []);


int main()
{
    char select;
    printf("\n  ==========================================================\n");
    printf("          WELCOME TO CUSTOMER BILLING SYSTEM                  \n");
    printf("  ==========================================================\n");
    printf("\n\tPress [Enter] to continue");
    getchar();
    system("cls");

    while(1)
    {
        printf("\n");
        menu();
        scanf(" %c", &select);
        if (select == '1')
        {
            items_input();
            system("cls");
            display();
            purchase_and_display_bill();
        }
        else if (select == '2')
        {
            items_input();
            system("cls");
            add_item();
        }

        else if (select == '3')
        {
            char alpha;
            items_input();
            system("cls");
            display();
            printf("Enter the alphabet to edit corresponding item: ");
            scanf(" %c", &alpha);
            for(int i=0; i<n; i++)
            {
                if(num[i]==alpha)
                {
                    replace_line("items.txt", i+1);
                    printf("Now enter new cost\n");
                    replace_line("cost.txt", i+1);
                }
            }
        }
        else if(select == '4')
        {
            char alpha;
            items_input();
            system("cls");
            display();
            printf("Enter the alphabet to delete corresponding item: ");
            scanf(" %c", &alpha);
            for(int i=0; i<n; i++)
            {
                if(num[i]==alpha)
                {
                    delete_line("items.txt", i+1);
                    delete_line("cost.txt", i+1);
                }
            }
        }

        else if (select == '5')
        {
            items_input();
            system("cls");
            display();
        }
        else if(select =='6')
        {
            char c;
            account_input();
            system("cls");
            account_menu();
            scanf(" %c", &c);
            if(c=='1')
            {
                system("cls");
                display_accounts();
            }
            else if(c=='2')
            {
                char old_phone[12];
                system("cls");
                printf("Enter old phone number: ");
                scanf("%s", old_phone);
                if(search_account(old_phone))
                {
                    replace_line("phone.txt", Index + 1);
                    printf("----PHONE NUMBER CHANGED SUCCESSFULLY----\n");
                }
                else
                    printf("%s number does not exist\n",old_phone);
            }
            else if(c=='3')
            {
                char phone_no[12];
                system("cls");
                printf("Enter your phone number to delete account: ");
                scanf("%s", phone_no);
                if(search_account(phone_no))
                {
                    delete_line("names.txt", Index + 1);
                    delete_line("phone.txt", Index + 1);
                    printf("----%s YOUR ACCOUNT HAS BEEN DELETED----\n",names[Index]);
                }
                else
                    printf("%s number does not exist\n", phone_no);
            }

            else if(c=='4')
                system("cls");
        }
        else if (select == '7')
        {
            system("cls");
            break;

        }
    }
    return 0;
}

int n_digits(int n)
{
    int count = 0 ;
    while(n)
    {
        n = n/10;
        count++;
    }
    return count;
}


void items_input()
{

    int j = 0;
    fptrcost = fopen("cost.txt", "r");
    while(!feof(fptrcost))
    {
        fgets(cost[j], sizeof(cost[j]), fptrcost);
        j++;
    }
    n = j;
    fclose(fptrcost);



    fptralpha = fopen("alphabets.txt", "r");
    while(!feof(fptralpha))
    {
        fgets(num, 25, fptralpha);
    }
    fclose(fptralpha);



    int i = 0, len;
    fptritems = fopen("items.txt", "r");
    while(!feof(fptritems))
    {
        fgets(items[i], sizeof(items[i]), fptritems);
        len = strlen(items[i])+1;
        for(int z=0; z<len; z++)
        {
            if(items[i][z]=='\n')
                items[i][z]='\0';
        }
        i++;
    }
    fclose(fptritems);
}

void account_input()
{
    int j = 0, len1;
    fptrnames = fopen("names.txt", "r");
    while(!feof(fptrnames))
    {
        fgets(names[j], sizeof(names[j]), fptrnames);
        len1 = strlen(names[j]) + 1;
        for(int y=0; y<len1; y++)
        {
            if(names[j][y]=='\n')
                names[j][y]='\0';
        }
        j++;
    }
    p = j;
    fclose(fptrnames);

    int i = 0,len;
    fptrphone = fopen("phone.txt", "r");
    while(!feof(fptrphone))
    {
        fgets(phone[i], sizeof(phone[i]), fptrphone);
        len = strlen(phone[i]) + 1;
        for(int z=0; z<len; z++)
        {
            if(phone[i][z]=='\n')
                phone[i][z]='\0';
        }
        i++;
    }
    fclose(fptrphone);
}

void menu()
{
    printf("   SELECT A TASK TO PERFORM \n");
    char tasks[7][30]={
        "\t1: Goto purchasing items",
        "\t2: Add item to the list",
        "\t3: Edit item in the list",
        "\t4: Delete item from list",
        "\t5: Display",
        "\t6: Go to accounting",
        "\t7: Quit"
        };
    for(int i=0; i<7; i++)
        printf("%s\n", tasks[i]);
}

void account_menu()
{
    printf("   SELECT A TASK TO PERFORM \n");
    char tasks[4][25]={
        "\t1: Display",
        "\t2: Edit phone number",
        "\t3: Delete account",
        "\t4: quit"
        };
        for(int i=0; i<4; i++)
            printf("%s\n", tasks[i]);
}
void display()
{
    items_input();
    printf("------------------------------------------\n");
    printf("|No | item                       |cost\n");
    printf("------------------------------------------\n");
    for(int i=0; i<n; i++)
    {
        int spaces;
        printf("| %c | %s",num[i], items[i]);
        spaces = 27 - strlen(items[i]);
        for(int j=0; j<spaces; j++)
            printf(" ");
        printf("|%s", cost[i]);
    }
    printf("\n");
    printf("------------------------------------------\n");
}

void purchase_and_display_bill()
{
    int i=0, qty, qty_arr[15], price_arr[15], bill_cost[25], qty_count=0;
    char bill_item[25][20], ch;
    float total_amount,gst,total_cost,discount,change,amount_paid;

    int hours, minutes, dd, mm, yy;
    time(&t);
    struct tm *local = localtime(&t);
    dd = local->tm_mday;
    mm = local->tm_mon;
    yy = local->tm_year;
    hours = local->tm_hour;
    minutes = local->tm_min;

    printf("select items and enter quantity(press q to quit)\n");
    while(1)
    {
        qty_count++;
        if(qty_count==8)
        {
            qty_count = 0;
            system("cls");
            display();
        }
        printf("item %d : ",i+1);
        scanf(" %c", &ch);
        if (ch=='q')
            break;
        else
        {
            printf("quantity: ");
            scanf("%d", &qty);
            qty_arr[i] = qty;
            for(int j=0; j<n; j++)
            {
                if(ch==num[j])
                {
                    total_cost += atoi(cost[j])*qty;
                    strcpy(bill_item[i],items[j]);
                    bill_cost[i] = atoi(cost[j])*qty;
                    price_arr[i] = atoi(cost[j]);
                }
            }
            i++;
        }
        printf("\n");
    }



    discount = 0.05*total_cost;
    gst = (total_cost - discount) * (0.09);
    total_amount = (total_cost - discount) + 2*gst;

    system("cls");
    printf("\nTOTAL AMOUNT IS = %.2f\n", total_amount);
    printf("ENTER THE AMOUNT PAID: ");
    printf("\n");
    scanf("%f", &amount_paid);
    change = amount_paid - total_amount;

    account_input();
    accounting();



    fptrbill = fopen("bill.txt", "w");
    fprintf(fptrbill,"                  ADS Super Market\n");
    fprintf(fptrbill,"         J K Towers, 4th Cross, Sangam Circle,\n");
    fprintf(fptrbill,"        Jayanagar, Bengaluru, Karnataka, 560011\n");
    fprintf(fptrbill,"              Ph no: 9856742564/9856471254\n");
    fprintf(fptrbill,"--------------------------------------------------\n");
    fprintf(fptrbill,"Date: %02d-%02d-%d                      Time: %d:%02d\n",dd,mm,yy+1900,hours,minutes);
    fprintf(fptrbill,"--------------------------------------------------\n");
    fprintf(fptrbill,"Item                       Qty  Rate      Amount\n");
    fprintf(fptrbill,"--------------------------------------------------\n");
    for(int k=0; k<i; k++)
    {
        int spaces;
        fprintf(fptrbill,"%s", bill_item[k]);
        spaces = 27 - strlen(bill_item[k]);
        for(int j=0; j<spaces; j++)
            fprintf(fptrbill," ");

        if(n_digits(bill_cost[k])==2)
            fprintf(fptrbill," %d    %d        %.2f \n", qty_arr[k], price_arr[k] ,(float)bill_cost[k]);
        else if(n_digits(bill_cost[k])==3)
            fprintf(fptrbill," %d    %d       %.2f \n", qty_arr[k], price_arr[k] ,(float)bill_cost[k]);
    }
    fprintf(fptrbill,"--------------------------------------------------\n");

    if(n_digits(total_cost)==3)
        fprintf(fptrbill,"\t Total cost                       %.2f\n", total_cost);
    else if(n_digits(total_cost)==4)
        fprintf(fptrbill,"\t Total cost                      %.2f\n", total_cost);

    if(n_digits(gst)==3)
    {
        fprintf(fptrbill,"\t Discount @ 5%%                   -%.2f\n",discount);
        fprintf(fptrbill,"\t Central GST @ 9%%                 %.2f\n",gst);
        fprintf(fptrbill,"\t State GST @ 9%%                   %.2f\n",gst);
    }
    if(n_digits(gst)==2)
    {
        fprintf(fptrbill,"\t Discount @ 5%%                    -%.2f\n",discount);
        fprintf(fptrbill,"\t Central GST @ 9%%                  %.2f\n",gst);
        fprintf(fptrbill,"\t State GST @ 9%%                    %.2f\n",gst);
        }


    fprintf(fptrbill,"--------------------------------------------------\n");
    if(n_digits(total_amount)==4)
        fprintf(fptrbill,"\t Net Amount                      %.2f\n", total_amount);
    else if(n_digits(total_amount)==3)
        fprintf(fptrbill,"\t Net Amount                       %.2f\n", total_amount);

    fprintf(fptrbill,"--------------------------------------------------\n");
    fprintf(fptrbill,"Payment details:\n");
    fprintf(fptrbill,"Cash tendered: %.2f\n", amount_paid);
    fprintf(fptrbill,"Tender change: %d\n", (int)change);
    fprintf(fptrbill,"Total items:   %d\n",i);
    fprintf(fptrbill,"Customer name: %s\n", names[Index]);
    fprintf(fptrbill,"Phone number:  %s\n", phone[Index]);
    fprintf(fptrbill,"--------------------------------------------------\n");
    fprintf(fptrbill,"               THANK YOU VISIT AGAIN\n");
    fprintf(fptrbill,"--------------------------------------------------\n");
    fclose(fptrbill);

}

void add_item()
{
    char n_item[20];
    int n_cost;
    printf("Enter the new item: ");
    scanf(" %[^\n]", n_item);
    printf("Enter the cost: ");
    scanf("%d", &n_cost);
    fptritems = fopen("items.txt","a");
    fptrcost = fopen("cost.txt","a");
    fputc('\n', fptritems);
    fputc('\n', fptrcost);
    fprintf(fptritems,"%s", n_item);
    fprintf(fptrcost,"%d", n_cost);
    fclose(fptritems);
    fclose(fptrcost);

}

void replace_line(char filename[], int line)
{
    char lines[25][30];
    char new_line[25];
    FILE * fptr;
    FILE * fptrtemp;
    fptr = fopen(filename, "r");
    fptrtemp = fopen("temp.txt", "a");
    int i=0,j=0;

    while(!feof(fptr))
    {
        fgets(lines[j],sizeof(lines[j]),fptr);
        j++;
    }

    while(i<line-1)
    {
        fprintf(fptrtemp, lines[i]);
        i++;
    }

    printf("Enter new data: ");
    scanf(" %[^\n]", new_line);
    fprintf(fptrtemp, new_line);
    i++;

    if(i<j)
        fputc('\n', fptrtemp);

    while(i<j)
    {
        fprintf(fptrtemp, lines[i]);
        i++;
    }
    fclose(fptr);
    fclose(fptrtemp);
    remove(filename);
    rename("temp.txt",filename);
}

void delete_line(char filename[], int line)
{
    char lines[25][30];
    FILE * fptr;
    FILE * fptrtemp;
    fptr = fopen(filename, "r");
    fptrtemp = fopen("temp.txt", "a");
    int i=0,count=0;

    while(!feof(fptr))
    {
        fgets(lines[count],sizeof(lines[count]),fptr);
        count++;
    }

    if(line == count)
    {
        int len;
        len = strlen(lines[count-2]);
        for(int k=0; k<len; k++)
            {
                if(lines[count-2][k]=='\n')
                {
                    lines[count-2][k]='\0';
                }
            }
    }

    while(i<line-1)
    {
        fprintf(fptrtemp, lines[i]);
        i++;
    }
    i++;
    while(i<count)
    {
        fprintf(fptrtemp, lines[i]);
        i++;
    }
    fclose(fptr);
    fclose(fptrtemp);
    remove(filename);
    rename("temp.txt",filename);

 }

void accounting()
{
    char phone_no[12];
    char name[30];
    int check;
    while(1)
    {
        printf("Enter your phone number: ");
        scanf("%s", phone_no);
        check = strlen(phone_no);
        if(check==10)
            break;
        else
            printf("----ENTER VALID NUMBER----\n\n");
    }
    if(search_account(phone_no))
    {
        printf("----ACCOUNT FOUND----\n");
        printf("Account holder name: %s\n", names[Index]);
    }
    else
    {
        printf("\t----ACCOUNT NOT FOUND----\n");
        printf("Enter your name: ");
        scanf("%s", name);
        create_account(name, phone_no);
        Index = p-1;
        printf("\t----ACCOUNT CREATED----\n");


    }
}

int search_account(char phone_no[])
{
    int i;
    int found = 0;
    for(i=0; i<p; i++)
    {
        if(strcmp(phone_no, phone[i])==0)
        {
            found = 1;
            Index = i;
        }
    }

    if(found)
        return 1;
    return 0;
}


void create_account(char name[], char phone_no[])
{
    fptrnames = fopen("names.txt", "a");
    fseek(fptrnames,0,SEEK_END);
    if(ftell(fptrnames)!=0)
        fputc('\n',fptrnames);
    fprintf(fptrnames, name);
    fclose(fptrnames);

    fptrphone = fopen("phone.txt", "a");
    fseek(fptrphone,0,SEEK_END);
    if(ftell(fptrphone)!=0)
        fputc('\n',fptrphone);
    fprintf(fptrphone, phone_no);
    fclose(fptrphone);
    account_input();
}

void display_accounts()
{
    int spaces;
    printf("---------------------------------\n");
    printf("   Name\t\t   Phone\n");
    printf("---------------------------------\n");
    for(int i=0; i<p; i++)
    {
        printf("%d) %s",i+1, names[i]);
        spaces = 17 - strlen(names[i]);
        for(int j=0; j<spaces; j++)
            printf(" ");
        printf("%s\n", phone[i]);

    }
    printf("---------------------------------\n");
}
