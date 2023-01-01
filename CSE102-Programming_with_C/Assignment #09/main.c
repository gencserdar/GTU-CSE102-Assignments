#include <stdio.h>
#include <stdlib.h>

union Person //personal informations
{
  char name[50];
  char address[50];
  int phone;
};
union Loan //loan informations
{
  float arr[3]; //in order: amount,interestrate,period
};
struct BankAccount //bank account database for 50 customers
{
  union Person Customer;
  union Loan Loans[3]; //3 loans limit
};
struct BankAccount acc[50]; 

void listCustomers(); //list customer names stored into struct
int addCustomer(int); //enter customer to the struct and txt file
int newLoan(); //check if the customer can take loan, enter to the struct if they can
void addLoan(int, int, float); //print loan info into the txt file
float calculateLoan(float amount, int period, float interestRate); //calculate debt
void getReport(int); //print customer report or loan report

int main()
{
  printf("============================================\nWelcome to the Bank Management System");
  int op,i=0,id,control=1;
  float res1,res2,res3;
  do
  {
    printf("\n============================================\n\t1. List All Customers\n\t2. Add New Customer\n\t3. New Loan Application\n\t4. Report Menu\n\t5. Exit System\nChoice: ");
    scanf("%d", &op);
    int op2=0;
    switch(op)
    {
      case 1:
        listCustomers(i);
        break;
      case 2:
        i=addCustomer(i);
        break;
      case 3:
        id = newLoan();
        if (id!=0)
        {
          res1 = calculateLoan(acc[id-1].Loans[0].arr[0],acc[id-1].Loans[0].arr[2],1.0 + acc[id-1].Loans[0].arr[1]); //debt of 1st loan
          control=1;

          if (acc[id-1].Loans[1].arr[0]!='\0')
          {
            res2 = calculateLoan(acc[id-1].Loans[1].arr[0],acc[id-1].Loans[1].arr[2],1.0 + acc[id-1].Loans[1].arr[1]); //debt of 2nd loan
            control=2;
          }

          if (acc[id-1].Loans[2].arr[0]!='\0')
          {
            res3 = calculateLoan(acc[id-1].Loans[2].arr[0],acc[id-1].Loans[2].arr[2],1.0 + acc[id-1].Loans[2].arr[1]); //debt of 3rd loan
            control=3;
          }

          if (control==1) //if only has 1 loan
          {
            printf("\nLoans = [%f]\n", res1); 
            addLoan(id,1,res1);
          }
          else if (control==2) //if has 2 loans
          {
            printf("\nLoans = [%f + %f] => %f\n",res1,res2,res1+res2); //total debt from 2 loans
            addLoan(id,2,res2);
          }
          else if (control==3) //if has 3 loans
          { 
            printf("\nLoans = [%f + %f + %f] => %f\n",res1,res2,res3,res1+res2+res3); //total debt from 3 loans 
            addLoan(id,3,res3);
          }
        }
        break;
      case 4:
        do
        {
          printf("\tSelect report\n\t\t1. Customer Report\n\t\t2. Loan Report\n\tChoice: ");
          scanf("%d",&op2);
          if (op2==1)
            getReport(1);
          else if (op2==2)
            getReport(2);
          else printf("\nINVALID OPERATION TRY AGAIN\n");
        }while (op2!=1 && op2!=2);
        break;
      case 5:
        break;
      default: printf("\nINVALID OPERATION TRY AGAIN\n");
    }
  }while(op!=5);
}

int addCustomer(int i)
{
  /*i + 1 = id*/
  FILE*fp=fopen("customer.txt","a+");
  for (int k=0; k<50; k++)
  {
    if (acc[k].Customer.name[0]=='\0') //check if the id is used or empty
    {
      i=k; //set id
      break;
    }    
    else if(k==49) //final customer
    {
      i=k;
      printf("\nMAX CAPACITY OF CUSTOMERS HAS BEEN REACHED\n");
    }
  }
  /*set and save phone no*/
  printf("Enter the customer phone number: ");
  scanf("%d",&acc[i].Customer.phone);
  fprintf(fp,"%d\n%d\n",i+1,acc[i].Customer.phone);

  /*set and save adress*/
  printf("Enter the customer address: ");
  fflush(stdin);
  scanf(" %[^\n]%*c",acc[i].Customer.address);
  fprintf(fp,"%s\n",acc[i].Customer.address);

  /*set and save name*/
  printf("Enter the customer name: ");
  fflush(stdin);
  scanf(" %[^\n]%*c",acc[i].Customer.name);
  fprintf(fp,"%s\n",acc[i].Customer.name);
  fclose(fp);
  return i+1;
}

void listCustomers(int i)
{
  for (int k=0;k<i;k++)
  {
    printf("ID: %d\n\tNAME: %s\n",k+1,acc[k].Customer.name);
  }
}

void getReport(int op)
{
  int id,k,j,num,loan_no,control,q;
  float total,month;
  char str[100];
  do
  {
    printf("\nEnter the ID number of the customer for the information.\n");
    scanf("%d",&id);
    if (acc[id-1].Customer.name[0]=='\0') printf("THERE ARE NO CUSTOMERS WITH THIS ID, TRY AGAIN\n");
  }while (acc[id-1].Customer.name[0]=='\0'); //id validity
  FILE*fp2=fopen("customer.txt","r");
  FILE*fp3=fopen("loans.txt","r");
  switch(op)
  {
    case 1:
      while(fscanf(fp2,"%d",&k)!= '\0')
      {
        if (k==id) //find and print information about the customer with entered id
        {
          printf("Customer ID = %d\n",k);
          fscanf(fp2,"%d",&num);
          printf("Customer Phone = %d\n",num);
          fscanf(fp2," %[^\n]%*c",str);
          printf("Customer Address = %s\n",str);
          fscanf(fp2," %[^\n]%*c",str);
          printf("Customer Name = %s\n",str);
          break;
        }
        else
        {
          fscanf(fp2,"%d",&num);
          fscanf(fp2," %[^\n]%*c",str);
          fscanf(fp2," %[^\n]%*c",str);
        }
      }
      fclose(fp2);
      break;
    case 2:
      do 
      { 
        printf("Select Loan no: ");
        scanf("%d",&loan_no);
        if (acc[id-1].Loans[loan_no-1].arr[0]=='\0') printf("INVALID LOAN NO\n");
      }while (acc[id-1].Loans[loan_no-1].arr[0]=='\0'); //loan no validity
      while(fscanf(fp3,"%d %d %f",&j, &q, &total)!= '\0')
      {
        if (j==id && q==loan_no) //find and print information about loan details of the customer with entered id
        {
          printf("Customer ID = %d\t",j);

          printf("Loan no: %d\n",q);

          printf("Total Credit Value= %f\n",total);

          month = acc[id-1].Loans[loan_no-1].arr[2];
          for (int p=1; p<=month; p++)
          {
            printf("\t%d. Month Installment = %f\n",p, total/month);
          }
          break;
        }
      }
      fclose(fp3);
      break;
    
  }
}

int newLoan()
{
  int id;
  do
  {
    printf("\nEnter the ID of the customer: ");
    scanf("%d",&id);
    if (acc[id-1].Customer.name[0]=='\0') printf("THERE ARE NO CUSTOMERS WITH THIS ID, TRY AGAIN\n");
  }while (acc[id-1].Customer.name[0]=='\0'); //id validty

  //find loan no and enter the loan informations
  if (acc[id-1].Loans[0].arr[0]!='\0')
  {
    if (acc[id-1].Loans[1].arr[0]!='\0')
    {
      if (acc[id-1].Loans[2].arr[0]!='\0')
      {
        printf("\nMaximum Loan Limit has reached.\n");
        return 0;
      }
      else
      {
        printf("Enter the amount: ");
        scanf("%f", &acc[id-1].Loans[2].arr[0]);
        printf("Enter the interest rate: ");
        scanf("%f", &acc[id-1].Loans[2].arr[1]);
        printf("Enter the period: ");
        scanf("%f", &acc[id-1].Loans[2].arr[2]);
      }
    }
    else
    {
      printf("Enter the amount: ");
      scanf("%f", &acc[id-1].Loans[1].arr[0]);
      printf("Enter the interest rate: ");
      scanf("%f", &acc[id-1].Loans[1].arr[1]);
      printf("Enter the period: ");
      scanf("%f", &acc[id-1].Loans[1].arr[2]);
    }
  }
  else
  {
    printf("Enter the amount: ");
    scanf("%f", &acc[id-1].Loans[0].arr[0]);
    printf("Enter the interest rate: ");
    scanf("%f", &acc[id-1].Loans[0].arr[1]);
    printf("Enter the period: ");
    scanf("%f", &acc[id-1].Loans[0].arr[2]);
  }
  return id;
}

float calculateLoan(float amount, int period, float interestRate)
{
  if (period!=0) return (interestRate*calculateLoan(amount,period-1,interestRate)); //amount * (1+interestRate)^period recursive 
  else return amount;
}

void addLoan(int id, int loan_no, float amount)
{
  FILE*file = fopen("loans.txt", "a+");
  fprintf(file,"%d %d %f\n",id,loan_no,amount);
  fclose(file);
}
