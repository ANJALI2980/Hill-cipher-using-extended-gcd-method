#include<stdio.h>
#include<string.h>
#include<math.h>
int alpha=65;
int adjMatrix[10][10];
int fac[10][10];
char *encrypt(char *input,int key[][10],int len,int n);
int * matrixmult(int key[][10],int vect [][10],int len,int n);
char *decrypt(char *cipher,int key[][10],int len,int n);
int determinant(int [][10], int);
void adjoint(int matrix[][10]);
int gcd(int a,int b,int x,int y);
int main()
{
    int n,key[10][10],i,j,len;
    char input[100],cipher[100];
    printf("\nEnter plain text:");
    scanf("%s",input);
    len=strlen(input);
    printf("enter n");
    scanf("%d",&n);
    printf("Enter key:\n");
    for(i=0;i<n;i++){
    for(j=0;j<n;j++){
    scanf("%d",&key[i][j]);
    }}
    char *ciphe=encrypt(input,key,len,n);
    printf("ciphertext:%s",ciphe);
    printf("\n");
    for(i=0;i<len;i++)cipher[i]=*(ciphe+i);
    cipher[len]='\0';
    char *plain=decrypt(cipher,key,len,n);
    printf("\nplainText:%s\n",plain);
return 0;
}
char* encrypt(char *input,int key[][10],int len,int n){
     int i,k=0,j,arrIndex[100]={0},vect[10][10]={0};
     char cipher[100]={0};
     int *cip;
     for(i=0;i<len;i++)
    {
        arrIndex[i]=(int)input[i]-alpha;
    }
    for(i=0;i<(int)len/n;i++){
    for(j=0 ;j<n&&k<len;j++,k++){
    vect[i][j]=arrIndex[k];
    }}
    cip=matrixmult(key,vect,len,n);
    for(j=0;j<len;j++){
    *(cip+j)=*(cip+j)%26;
    *(cip+j)=*(cip+j)+65;
    cipher[j]=(char)*(cip+j);
    }
    return cipher;
}
int* matrixmult(int key[][10],int vect [][10],int len,int n){
    int i,j,k,l=0,cipher[100]={0};
    int d=len/n;
    for(k=0;k<d;k++){
    for(i=0;i<n&&l<len;i++,l++){
    for(j=0;j<n;j++){
    cipher[l]+=key[i][j]*vect[k][j];
    }}}
return cipher;
}
char *decrypt(char *cipher,int key[][10],int len,int n){
int i,j,k=0,vect[10][10]={0},arrIndex[100]={0},inv[10][10]={0},m,d;
int *text;
char plain[100]={0};

for(i=0;i<len;i++)
    {
        arrIndex[i]=(int)cipher[i]-alpha;

    }
    for(i=0;i<(int)(len/n);i++){
    for(j=0;j<n && k<len;j++,k++){
    vect[i][j]=arrIndex[k];
    }}

    //finding det inverse
    d = determinant(key, n);
    if(d<0)d=(-1)*d;
    printf("\ndet=%d",d);
    m=gcd(d,26,0,1);
    if(m<0)m=m+26;
    printf("\ngcd=%d",m); //DET INVERSE
    adjoint(key);
    for(i=0;i<n;i++){
    for(j=0;j<n;j++){
    if(adjMatrix[i][j]<0)adjMatrix[i][j]=adjMatrix[i][j]+26;
    adjMatrix[i][j]=adjMatrix[i][j]%26;
    inv[i][j]=adjMatrix[i][j]*m;
    inv[i][j]=inv[i][j]%26;
    }}

    text=matrixmult(inv,vect,len,n);
    for(j=0;j<len;j++){
    *(text+j)=*(text+j)%26;
    *(text+j)=*(text+j)+65;
    plain[j]=(char)*(text+j);
    }



return plain;
}
int determinant(int a[10][10], int k)
{
  int s = 1, det = 0, b[10][10];
  int i, j, m, n, c;
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinant(b, k - 1));
          s = -1 * s;
          }
    }

    return (det);
}
int gcd(int a,int b,int x,int y){
int x1,y1,m;
if(a==1){
return y;
}
x1=y;
y1=(x-((b/a)*y))%26;
m=gcd(b%a,a,x1,y1);
return m;
}
void adjoint(int matrix[][10])
{
    int temp;
    int tmp;
    int flag=0;

    for(temp=0;temp<2;temp++)
    {
        for(tmp=0;tmp<2;tmp++)
        {
            if(temp!=tmp)
                adjMatrix[temp][tmp]=(-matrix[temp][tmp])+26;
            else if(temp==tmp && flag==0)
            {
                flag=1;
                adjMatrix[temp][tmp]=matrix[temp+1][tmp+1];
                adjMatrix[temp+1][tmp+1]=matrix[temp][tmp];
            }
        }
    }

}

