#include<stdio.h>
#include<stdlib.h>
struct node
{
    unsigned distance[20];
    unsigned from[20];
}rt[10];
int main()
{
int n;
int costmatrix[20][20];
printf("Enter the no of nodes\n");
scanf("%d",&n);
printf("Enter the cost matrix\n");
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        scanf("%d",&costmatrix[i][j]);
        costmatrix[i][i]=0;
        rt[i].distance[j]=costmatrix[i][j];
        rt[i].from[j]=j;
    }
}
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        for(int k=0;k<n;k++)
        {
            if(rt[i].distance[j]>costmatrix[i][k]+rt[k].distance[j])
            {
                rt[i].distance[j]=rt[i].distance[k]+rt[k].distance[j];
                rt[i].from[j]=k;
                
            }
        }
    }
}
for(int i=0;i<n;i++)
{
    printf("For router %d\n",i+1);
    for(int j=0;j<n;j++)
    {
        printf("From router %d through %d distance is %d\n",j+1,rt[i].from[j]+1,rt[i].distance[j]);
    }
}
}
