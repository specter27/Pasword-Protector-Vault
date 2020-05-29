#include<stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>
#include<string.h>
#include<math.h>
#define desmax 50
#define passmax 20 
#define filenamemax 20

int lzw;    //declaration of global variable

 int Randoms();
 int max(int a,int b);

 int GCD(int a,int b);
 int multiinverse(int a,int m);
 int slc(char *st);

 int modulararithmatic(int m, int *p, int n);
 int *decimaltobinary(int n);
 void store(int t);

 char *encrypter(char *s,int pk,int n,int size ,int arr[]);
  char *decrypter(int n,int d,char *es,int size,int qarr[]);       /*returns the complete decrypted screen*/

int main()
{
    printf("\tPRESS 1 FOR ADDING NEW PASSWORD\n");
    printf("\tPRESS 2 FOR DISPLAYING THE STORED PASSWORD\n");
    int dec=0; //decision variable
    scanf("%d",&dec);


    if(dec==1)   //*********************************************************************************************************
    {
        //  srand(time(0));
        printf("working..\n");
       int arr[]={23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,
                     149 ,151, 157, 163, 167 ,
                     173 ,179 ,181 ,191 ,193, 197 ,199 ,211 ,223 ,227 ,229 ,233 ,239 ,241 ,251 ,257 ,263 ,269 ,271,277,
                     281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433
                     ,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,
                     601,607,613,617,619,631,641,643647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,
                     769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,
                     953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051 };

       int p,q,n,size,soe,toa,x,y,totient,i,k=0;

       srand(time(0));

                     toa=sizeof(arr);  //total size of array
                     soe=sizeof(int);  //size of one element in array

                     size=toa/soe;


                     p=arr[Randoms()];
                     q=arr[Randoms()];
                     n=p*q;
                     x=(p-1);
                     y=(q-1);
                     totient=x*y;                 /* represent the euler totient function phi(n)
                                                      used for calculating the d---(private key)*/


                     
                     int to=max(p,q);
                     int d=0;                        //private key or decryption key ---> (d,n)
                     int h=0;

                      while (true) 
        {

            d=arr[Randoms()];
            if (d<to)
            {
                continue;
            }
              h=GCD(d,totient);
              if(h==1){
                  break;
              }
        }

        int e=multiinverse(d,totient);              //public key or encryption key ---> (e,n)

        getchar();  //used to get the extra newline character left in buffer by the scanf()

        


        printf("\tenter the description for the password\n");
        char des[desmax];                       //this description string buffer
        scanf("%[^\n]%*c", des);               //scanning the string

       char fext[]=".txt";     //this strig will store the extension of file 
       strcat(des,fext);
      
        
       /*---------------------------This will be used to create file with username as te file name---------------------------------------*/
        FILE *file=fopen(des,"w");
        
         //--------------------------Writing in file----------------------------------------------------------------------------
      
        fprintf(file, "%d\n",n);
        fprintf(file, "%d\n",d);


        printf("\t enter the password to be saved \n");


        char ch[passmax];             //this string will stores the password
  
        char *h2=fgets(ch,passmax,stdin); // scanning the string 
  
        int pstlen=slc(h2);        //length of the password string
        
        int sizep=pstlen;           //for convinenece

         int *quotientarr=malloc(sizep*sizeof(int));   /*declaring quotient array as GLOBAL*/

        char arr1[sizep]; 
                              
        char *plain=strcpy(arr1,ch);   /*used for passing plaintext string as function argument*/
       
        // --------------------calling the encrypter------------------------------------------------------------

        char *cipher;                           //used for storing the output string returned from encrypter

        cipher=encrypter(plain,e,n,sizep,quotientarr); 

        printf("plaintext after encryption\n");

        int j=0;

        for(j=0;j<sizep;j++)
          {
          fprintf(file, "%c",*(cipher+j) );      // writing encrypted password in file
          }
          fprintf(file,"\n");
          // fprintf(file,"\n%s\n",header4);      //writing the forth header of the file from a new line

          for (j = 0; j <sizep ; j++)
          {
            fprintf(file,"%d\n",*(quotientarr+j) );     //writing the quotient array in file
           }
            printf("\tYOUR PASSWORD HAS BEEN STORED \n");
            fclose(file);

    }


     else if(dec==2)  //****************************************************************************************************************
     {
       
      getchar();
      printf("\tenter the description to display the password\n");
      char des2[desmax];                   //stores the description string for displaying the corrosponding password
      scanf("%[^\n]%*c", des2);                                     //scanning the string
      char ext[]=".txt";
      strcat(des2,ext);
      FILE *fp=fopen(des2,"r");

      //--------------------variables to be passed------------------------------------------------------------------- 
         int pubkey=0;
         int fl=0;             //number of characters in first line
         int sl=0;            //number of characters in second line
         int tl=0;           //number of characters in third line or the length of encrypted string
         char enystr[passmax];   //stores the encrypted string extracted from file
         int prikey=0;     //stores the private key extracted from file
      //----------------------------------------------------------------------------------------------------------------

      if (fp==NULL)
      {
        printf("NO PASSWORD STROED FOR THE MENTIONED DESCIPTION\n");
        return 1;
      }
      else   
{

        printf("processing.....\n");
        int c3=0;    //number of character in line one
        //-------------------------------------------used for scanning the number of characters in third line-------------------------------------------
          int count3=0;
         while(1)//scan one character at one time
       {
         char c=fgetc(fp);
          int p=c;
          if(p==10)
        {
           count3=count3+1;
           if (count3==3)
           {
              break;
           }
          
        }
         if(count3==2)
        {
          c3=c3+1;
        }
      }
      tl=c3-1;
      rewind(fp);

      //---------------------------------converting the characters in third row to string-------------------------------------------------
      
      
        
      int helper=c3-1;
      int x3=0;           //length of the string in line three
      int count4=0;
      rewind(fp);
     while(1)             //scan one character at one time
     {

       char c=fgetc(fp);
          int p=c;
          if(p==10)
        {
           count4=count4+1;
           if (count4==3)
           {
              break;
           }
          
        }
         if(count4==2)
        {
           while(x3<helper)
           {
           char c=fgetc(fp);
            int p=c-'0';
            enystr[x3]=c;
            if(p==10)
            {
              break;
            }
             x3=x3+1;
           }
           break;
        }
      }

     
      rewind(fp);

       
        //---------------------------used for scanning the number of characters in first line------------------------------------
        int c1=0;
        while(1)//scan one character at one time
       {
         char c=fgetc(fp);
          int p=c;
          if(p==10)
        {
           break;
        }
          else
        {
          c1=c1+1;
        }
      }
      fl=c1;
      
      rewind(fp);
      /*----------------------------------converting the characters in first row to integer value-----------------------------------------------*/
      int a1=0;
      double x1=fl;     //length of the string in line one
      int re1=0;
      int h1=0;
     while(x1>=0) //scan one character at one time
     {
       x1=x1-1;
       char c=fgetc(fp);
       int p=c;
       if(p==10)
       {
         break;
       }
       p=c-'0';
       a1=(int)pow(10.0,x1);
       h1=a1*p;   
       re1=re1+h1;
      }
      pubkey=re1;                  //extracted from file value of n(public key)
      
     
     //---------------------------used for scanning the number of characters in second line----------------------------------------
        
    if ( fseek(fp,0,SEEK_SET)==0){
         int c2=0;
         int count1=0;
         while(1)                    //scan one character at one time
       {
         char c=fgetc(fp);
          int p=c;
          if(p==10)
        {
           count1=count1+1;
           if (count1==2)
           {
              break;
           }
          
        }
         if(count1==1)
        {
          c2=c2+1;
        }
      }
        sl=c2-1;
      
     
    }
    else{
      printf("some error occured\n");
      
    }
    rewind(fp);
 
    //-------------------------converting the characters in second row to integer value--------------------------------------------------
             int a2=0;
             double x2=sl;   //length of the string in line two
             int re2=0;
             int h2=0;
             int count2=0;
    while(1)                  //scan one character at one time
     {

         char c=fgetc(fp);
          int p=c;
          if(p==10)
        {
           count2=count2+1;
           if (count2==2)
           {
              break;
           }
          
        }
         if(count2==1)
        {
           while(x2>=0)
           {
            x2=x2-1;
            c=fgetc(fp);
            int p=c-'0';
            if(p==10)
            {
              break;
            }
           a2=(int)pow(10.0,x2);
           h2=a2*p;   
           re2=re2+h2;
           }
           break;
        }
      }
     
      prikey=re2;
      rewind(fp);   
      

        


   } //closing of the else

   //----------------------------------extracting the quotient array-----------------------------------------------------------  
        int qarr[tl];
        int strlen[tl];
        int a=0;
        int k=0;
        int character=0;
        int j=0;
        double x=0;
        int re=0;
        int h=0;
        int count=0;
  //------------------------------------------populating the strlen[]------------------------------------------------------------------
        while(1)  
     {
     char c=fgetc(fp);  //scan one character at one time
      int p=c;
      if (p==10)
      {
        count=count+1;
      }
      if(count==3)
      {
        while(1)
        {
          if(feof(fp))
          {
            
            break;
          }
             c=fgetc(fp);
             int p=c-'0';
             
             if (p==10||p==-38)
             {
                printf("\n");
                strlen[j]=character;
                qarr[j]=re;
                re=0;
                character=0;
                j=j+1;
                x=0;
                continue;
             }
             a=(int)pow(10.0,x);
             h=a*p;
             re=re+h;
             x=x+1;
             if(p>=0&&p<=9){
             character=character+1;
         }

        }
        break;
      }  
    }
    fclose(fp);//-------------------CLOSING THE FILE---------------------------------------------------------------------------------
    // -----------------------------------------------------final quotient array------------------------------------------------------
     
     int fqarr[tl];
     for ( k = 0; k < tl; k++)
     {
       int result=0;
       int ux=0;
       int u2 =0;
       int h2=0;
       double temp=strlen[k];
       int temp1=qarr[k];

       while(temp1!=0)
       {
          temp=temp-1;
          ux=temp1%10;
          u2=(int)pow(10.0,temp);
          h2=u2*ux;
         result=result+h2;
         temp1=temp1/10;

       }

       fqarr[k]=result;  //storing the result in final quotient array
     }
    

  
    //---------------------------------------------declaring the charcter array to be passed---------------------------------------
     char escpy[tl];
     char *hy=strcpy(escpy,enystr);           // THIS IS TO BE PASSED IN decrypter();
    

    //-------------------------------------------calling the decrpter()----------------------------------------------------------------
      /*values to be passed in decrypter (pubkey,prikey,hy,tl,fqarr)
      */
    char *decryptxt;                //used for storing the output string returned from encrypter

    decryptxt=decrypter(pubkey,prikey,hy,tl,fqarr);  //calling the decrypter function

     printf("your password stored= \n");

     int un=0;
     for(un=0;un<tl;un++){
      printf("%c",*(decryptxt+un));
    }
    printf("\n");


 }  //closing of else if
      


     else//-------------------------------------------------------------------------------------------------------------------------------
     {
        printf("\t******INVALID INPUT********\n");
     }
      printf("decision=%d\n",dec);

    return 0;
}

 //------------------------------------------------------------------------------------------------------------------------------

 int Randoms()   //random number generator
{
   
   int n=0;
   n=rand()%50;
   return n;
}

int max(int a,int b)
{
        int h=0;
        if (a>b)
        {
            h=a;
        }
        else {
            h=b;
        }
        return h;
}

 int GCD(int a,int b)
  /*
                                       example
                                               gcd(54,24)=6
                                               gcd(84,24)=6
                                               gcd(252,105)=21
                                               gcd (36,60)=12
                                               EUCLIDIEAN ALGORITHM( MODIFIED VERSION) ----calculate gcd of two numbers
                                           GCD = multipication of comman factors
                                           the basic is based on the principle that the greatest common divisor of two
                                           numbers does not change if the larger number is replaced by its difference
                                           with the smaller number. For example, 21 is the GCD of 252 and 105 (as 252
                                           = 21 × 12 and 105 = 21 × 5), and the same number 21 is also the GCD of 105
                                            and 252 − 105 = 147. Since this replacement reduces the larger of the two
                                            numbers, repeating this process gives successively smaller pairs of numbers
                                            until the two numbers become equal.*/
        {
            if (a==0)
            {
                return b;
            }
            if (b==0)
            {
                return a;
            }
            if (a==b)
            {
                return a;
            }
            int p=0;
            if (b>a)
            {
                a=a+b;
                b=a-b;
                a=a-b;
            }
            while (b!=0)
            {
                p=a;
                a=b;
                b=p%b;
            }

            return a;
        }
        //-------------------------------------------------------------------------------------------------------------------
        int multiinverse(int a,int m) //------>   multiplicative inverse
     /*returns multipicative inverse of a%m
     * example 20 mod 97 =34
    --------------- Extended Euclidean algorithm--------------------------------*/
     {
         int D=m;
         int div=a;
         int x=0, v=0 , c=0,d=0,r=0,q=0;
         int  y=1,u=1;
         while (r!=1)
         {
             r=D%div;
             q=D/div;
             c=x-u*q;
             d=y-v*q;
             x=u;
             y=v;
             u=c;
             v=d;
             D=div;
             div=r;
         }
         if (c<0)
         {
             c=m+c;
         }
         return c;
         }
          //--------------------------------------------------------------------------------------------------------------------------
         int slc(char *st)  //string length function will return the length of the passed string
         {
          int i=0;
          int count=0;
          for (i = 0;i < desmax; i++)
          {
             char c=st[i];
             int t=c;

             if (t>32&&t<127)
             {
                 count=count+1;
             }
             else{
              break;
             }

          }
          return count;
          

         }
      //-------------------------------------------------decimaltobinary----------------------------------------------------------------

       int *decimaltobinary(int n) {
                                                    /*test cases
                                                    * input=999983
                                                    * output=11110100001000101111*/
        int bin[50];
        int cn=0;
         int i=0;
        int j;
        while (n>0)
        {

            bin[i]=n%2;
            n=n/2;
            i=i+1;
        }
        store(i);
        int *keyinbin=malloc(i*sizeof(int));                //contains binary version of key
                            /*PROBLEM COMING 
                            we cannot simply return the array from a function in C
                            because the array are given ---stack memory--- as they are (local) to the function
                            local to the function gets destroyed when the function returns.
                            You'd be left out with a dangling pointer and using it would invoke undefined behaviour.
                            SOLUTION:
                            1) make the array in the scope program rather than the function
                            by making the arrays (STATIC)
                            static is used with global variables and functions to set their scope to the containing file 
                            but the variable length array cannot be static
                            STATIC variables are stored in HEAP MEMORY

                            2)USE DYNAMIC ALLOCATION*/
        
        
        int k=0;
        for( j=i-1;j>=0;j--)
        {
            keyinbin[k]=bin[j];
            k=k+1;
        }
        return keyinbin;

    }
       
     //---------------------------------------------modulararithmatic-------------------------------------------------------------------
          int modulararithmatic(int m, int *p, int n)
   {                                                      /*this is returning the modulararithmatic character
                                                        values after encrypting the plaintext using the encrption key
                                                         compute c=M^e mod(n)    example
                                                                                          5^12mod(26) =1
                                                                                          2^50mod(17) =4
                                                                                          4^532mod(11)=5
                                                                                          2^341mod(341)=2
                                                                                          3^100,000mod(53)=28
                                                                                                        */
        int c = 1;
        int i = 0;
        int size = lzw;
        while (i != size) {
            int ek=*(p+i);
            c = (c * c) % n;
            if (ek == 1) {
                c = (c * m) % n;
            }
            i = i + 1;
        }
        return c;
    }

    //----------------------------------------helper-------------------------------------------------------------------------------

    void store(int t)
     {
        lzw=t;
     }

     //----------------------------------------encrypter function-----------------------------------------------------------------------

     char *encrypter(char *s,int pk,int n,int size ,int arr[])  /*converts the plaintext in to cipher text--------> returning a string*/
    
    {
        int hh = 0; 
     
        
        int ar = 0;//----------------------------> acsii range
        char *cc=malloc(size*sizeof(char));//array to be returned-------------->modulararithmatic characters 

        while (hh != size) {
            char p = s[hh];
            int q = p; //-------------------------------->gives ascii value of every character in the string
            int result = modulararithmatic(q, decimaltobinary(pk), n);
            arr[hh] = result / 94;//---------------->needed to be saved in  file for every user(ENCODING)
            ar = result % 94 + 33; // -------------------->putting the result in the range of 32-127 ascii code range
            char l = ar;//---------------------->returns the corresponding character (using the ascii code)
            cc[hh]=l;
            hh = hh + 1;
        }
        return cc;
    }
    //------------------------------------decrypter------------------------------------------------------------------------------

    char *decrypter(int n,int d,char *es,int size,int qarr[])/*returns the complete decrypted screen*/
    {
        int i=0;
        int dcc=0;// decrypted character (ascii) code
        char *dca=malloc(size*sizeof(char));  //------->decrypted character array needed to be global as it has to be returned

                 /*heap memory is global and malloc allocates memory out of heap*/
        while (i<size)
        {
            char c=es[i];
            int h=c;  //-------->gives the ascii value of the encrypted characters
            h=(h-33)+94*qarr[i];
            dcc=modulararithmatic(h,decimaltobinary(d),n);
            char dc=dcc;//------>decrypted character
            dca[i]=dc;
            i=i+1;
        }
       //---->decrypted string
        return dca;
    }
