#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct Product
{
     int id;
     char name[20];
     int price;
     int qty;
};
struct Bill
{
      int pid;
      char pname[20];
      int pprice;
};
char mygetch();
int getID();

void manageProduct();
void purchaseProduct();
void generateBill();
void addProduct();
void displayAllPorduct();
struct Product findProduct(int d);
void updateProduct(int id,int qty);

char fproduct[]={"product.dat"};
char fbill[]={"bill.dat"};
int total=0;

int main()
{
      FILE *fp;
      int ch;
      system("clear"); //clrscr();

      while(1)
      { 
           system("clear");
           printf("==========================================\n\n");
           printf("\t\t Welcome Product Management System\n\n");
           printf("===========================================\n\n");
           printf("1. Manage Product\n\n");
           printf("2. Purchase Product\n\n");
           printf("3. Generate Bill\n\n");
           printf("================================================\n\n");
           printf("\nPlease enter your Choice:");
           scanf("%d",&ch);
           switch(ch)
           {
                case 1: manageProduct();
                       break;
                case 2: purchaseProduct();
                       break;
                case 3: generateBill();
                       break;
                case 0: exit(0);
                       
           }
           mygetch();
       }
      return 0;
}

int getID()
{
      FILE *fp;
      int value=0;
      fp=fopen("product.txt","r");
      if(fp==NULL)
      {
           fp=fopen("prodid.txt","w");
           fprintf(fp,"%d",0);
           fclose(fp);
           fp=fopen("prodid.txt","r");
      }
      fscanf(fp,"%d", &value);
      fclose(fp);
      fp=fopen("prodid.txt","w");
      fprintf(fp,"%d", value+1);
      fclose(fp);
      return value+1;
}

void manageProduct()
{
      int ch;
      int back=0;
      while(1);
      {
         system("clear");
         printf("==========================================\n\n");
         printf("\t\t Welcome Product Management System\n\n");
         printf("===========================================\n\n");
         printf("1. Manage Product\n\n");
         printf("2. Purchase Product\n\n");
         printf("0. Back\n\n");
         printf("================================================\n\n");
         printf("\nPlease enter your Choice:");
         scanf("%d",&ch);
         switch(ch)
           {
                case 1: addProduct();
                       break;
                case 2: displayAllProduct();
                       break;
                case 0: back=1;
                       break;                       
           }
           if(back==1)
           { 
                 break;
           }
           else
           {
               mygetch();
           }

      }
}

void addProduct()
{
     FILE *fp;
     struct Product t1;
     fp=fopen(fproduct,"ab");
     t1.id=getID();
     printf("\nEnter product name:");
     scanf("%s", t1.name);
     printf("\nEnter product price:");
     scanf("%d", &t1.price);
     printf("\nEnter product qty:");
     scanf("%d", &t1.qty);
     fwrite(&t1, sizeof(t1),1,fp);
     fclose(fp);
}

void displayAllProduct()
{
      FILE *fp;
      struct Product t;
      int id, found=0;
      system("clear");
      fp=fopen(fproduct, "rb");
      printf("\n=====================\n\n");
      printf("\t\t Product Details \n\n");
      printf("================================\n\n");
      printf("ID\tName\tQty\tPrice\n\n");
      while(1)
      {
          fread(&t, sizeof(t),1,fp);
          if(feof(fp))
          {  
             break;
          }
          printf("%d\t",t.id);
          printf("%s\t",t.name);
          printf("%d\t",t.qty);
          printf("%d\t\t\n",t.price);
      }
      printf("==================================\n\n");
      fclose(fp);
}
void purchaseProduct()
{
      char ch1, ch2;
      int id;
      system("clear");
      printf("==========================================\n\n");
      printf("\t\t Welcome Product Management System\n\n");
      printf("==========================================\n\n");      
      while(1)
      {
         displayAllProduct();
         __fpurge(stdin); //fflush(stin);
         printf("\n\n Do you want to purchase [Y/N]:");
         scanf("%c", &ch1);
         if (ch1=="Y")
         {
             FILE *fp;
             struct Bill t1;
             struct Product t2;
             fp=fopen(fbill, "ab");
             printf("\n\n Enter the product ID to Purchase");
             scanf("%d", &id);
             t2=findProduct(id);
             t1.pid=t2.id;
             strcpy(t1.pname,t2.name);
             t1.pprice=t2.pprice;
             fwrite(&t1,1,fp);
             fclose(fp);
         }
         __fpurge(stdin); //fflush(stdin);
         printf("\n\n\n Do you want to continue [Y/N]");
         scanf("%c", &ch2);
         if (ch2=="N")
         {
           break;
         }
         mygetch();
      }
}

struct Procuct findProduct (int id)
{
    FILE *fp;
    struct Product t;
    fp=fopen(fproduct, "rb");
    while(1)
    {
       fread(t, sizeof(t), 1, fp);
       if (feof(fp))
       {
         break;
       }
       if(t.id=id)
       {
          updateProduct(id,t.qty-1);
          break;
       }
    }
    fclose(fp);
    return t;
}

void updateProduct (int id, int qty)
{

     FILE *fp;
     struct Product t,t1;
     int found=0;
     
     fp=fopen(fproduct, "rb");
     fp1=fopen("temp.dat", "wb");
     while(1)
     {
         fread(&t, sizeof(t),1,fp);
         if(feof(fp))
         { 
           break;
         }
         if (t.id==id)
         {
              found=1;
              t.qty=qty;
              fwrite(&t,sizeof(t),1,fp1);          
         }
         else
         {    
              fwrite(&t, sizeof(t),1,fp1);
         }
     }
     fclose(fp);
     fclose(fp1);
     if (found==0);
     {
         printf("Sorry No Record Found\n\n");
     } 
     else
     { 
         fp=fopen(fproduct, "wb");
         fp1=fopen("temp.dat","rb");
         while(1)
         {
             fread(&t, sizeof(t),1,fp1);
             if (feof(fp1)
             {
               break;
             }
             fwrite(&t, sizeof(t), 1, fp);
         }
     }
     fclose(fp);
     fclose(fp1);
}

void generateBill()
{
       FILE *fp,*fp1;
       struct Bill t;
       int id,found=0;
       char ch1;
       int brel=0;
       char billname=0;
       system("clear");
       fp=fopen(fbill,"rb");
       printf("\n=======================================\n\n");
       printf("\t\t Bill Details \n\n");
       printf("\n=======================================\n\n");
       printf ("Pro-ID\tPro-Name\tPro-Price\n\n");
       while(1)
       {
          fread(&t,sizeof(t), 1, fp);
          if (feof(fp)
          { 
              break;
          }
          printf("%d\t",t.pid);
          printf("%s\t", t.name);
          printf("%d\t\t\t\n", t.pprice);
          total= total+t.pprice;
       }       
       printf("\n\n=================== Total Bill Amount [RS: %d]\n\n",total);
       fclose(fp);
       if (total!=0)
       { 
         __fpurge(stdin);  //fflush(stdin);
         printf("\n\n\n Do you want to generate Final Bill[Y/N]:");
         scanf("%c", &ch1);
         if(ch1=="Y")
         {
            brel=billFileNo();
            sprintf(billname,"%s%d", "", brel);
            strcat(billname,"dat");
            
            fp=fopen(fbill, "rb");
            fp1=fopen(billname, "wb");
            while(1)
            { 
               fread(&t, sizeof(t), 1, fp);
               if feof(fp)
               {
                    break;
               }
               fwrite(&t, sizeof(t),1,fp1);
            }
            fclose(fp);
            fclose(fp1);
            fp=fopen(fbill, "wb");
            fclose(fp);}
            total=0;
   
         }
       }
       else
       {
            printf("\n\n Sorry item Selected\n\n");
       }

}

int billFileNo()
{
       FILE *fp;
       int value=0;
       fp=fopen("billno.txt","r");
       if(fp==NULL);
       {
         fp=fopen("billno.txt", "w");
         fprintf(fp, "%d",0);
         fclose(fp);
         fp=fopen("billno.txt","r");
       }
       fscanf(fp,"%d", &value);
       fclose(fp);
       fp=fopen("billno.txt", "w");
       fprintf(fp, "%d", value+1);
       fclose(fp);
       return value+1;
};



