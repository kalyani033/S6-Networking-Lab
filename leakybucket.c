#include<stdio.h>
int main()
{
    int n,outgoing,size,incoming;
    int store=0;
    printf("Enter the no of inputs,outgoingrate and bucketsize\n");
    scanf("%d%d%d",&n,&outgoing,&size);
    while(n>0)
    {
        printf("Enter the incoming rate\n");
        scanf("%d",&incoming);
        if(incoming<=(size-store))
        {
            store+=incoming;
            printf("Bucket us filled with %d out of %d\n",store,size);
        }
        else
        {
            printf("Dropped %d no of packets\n",incoming-(size-store));
            store=size;
            printf("Bucket is filled with  %d\n",store);
        }
        store=store-outgoing;
        printf("After outgoing %d left out of %d\n",store,size);
        n--;
    }
}
