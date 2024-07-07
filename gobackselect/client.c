Stop and wait
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int nframe;
    printf("enter the no of frames : ");
    scanf("%d",&nframe);
    int cur_pack = 1;
    int ack; 
    while (cur_pack <= nframe)
    {   		 
   	 printf("\nSender sent packet %d \n", cur_pack);

   	 // Simulate packet transmission (with probability of 25% loss)
   	 if (rand() % 4 != 0) //receive packet {
	printf("Receiver received %d\n", cur_pack);
   	     	printf("Receiver sends ack for packet %d\n",cur_pack);
   		ack = 1;
   	 }
   	 else //packet lost   	 {
   	     	 ack = 0;
   		printf("Packet %d is lost.\n", cur_pack);
   	 }
   	 // Check if ACK received (with probability of 25% loss)
   	 if (ack) {
   	 	if (rand() % 4 != 0){
   	     	// Sender receives ACK
   	     	printf("Sender received ACK for packet %d.\n", cur_pack);
   	     	printf("packet %d sent successfully\n\n",cur_pack);
   		cur_pack++;
   	    	}
   	 	else{
   	     	printf("ACK lost.\n");
   	 	}
   	 }
    }

   	 return 0;
}
Go back n arq 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define wsize 4
#define nframes 8
int main(){
    int error[nframes];
    int count = 0, start = 0;
    int nerrors = rand() % 3 + 2;
    for(int i=0; i<nframes;i++){
   	 error[i]=0;
    }
    for(int i=0;i<nerrors;i++){
   	 int e = rand() % 8;
   	 error[e] = 1;
    }
    while(count<nframes){
   	 printf("\nsending frames : ");
   	 for(int i=start; i<start+wsize && i<nframes; i++){
   		 printf("%d ",i+1);
   	 }
   	 printf("\n");
   	 if(error[count]){
   		 printf("error in frame %d.. retransmiting window\n",count+1);
   		 error[count] = 0;
   	 }else{
   		 printf("frame %d acknowledged\n",count+1);
   		 count++;
   		 start++;
   	 }
    }
}