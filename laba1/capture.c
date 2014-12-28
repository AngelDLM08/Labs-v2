#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
int x,y,px,py,i,j;
    printf("Ввод:\n");
   
    FILE *wfile;
    
    wfile =fopen("t.pnm","wt");
    char temp[100];
    
    int *answersdec;
    int anstest=1; 

    
    
    gets(temp);
    
    px=atoi(strtok(temp," "));
    py=atoi(strtok(NULL," "));
    x=atoi(strtok(NULL," "));
    y=atoi(strtok(NULL," "));
 
    answersdec=(int*)malloc(y*sizeof(int));
    
    for (i=0;i<y;i++){
        sscanf((strtok(NULL," ")),"%x",&answersdec[i]);
        if(answersdec[i]>x) anstest=0;
        }

    if(anstest){    
        printf("x=%d y=%d px=%d py=%d\n",x,y,px,py);
    
        fputs("P1\n",wfile);
        int xlen=x*px+x-1;
        int ylen=y*py+y-1;
        fprintf(wfile,"%d %d\n",xlen,ylen);

        int **ansmatr;
        ansmatr=(int**)malloc((ylen)*sizeof(int*));
        for(i=0;i<ylen;i++){
            ansmatr[i]=(int*)malloc((xlen)*sizeof(int));                
            }

            int checkx, checky;

            if((py) % 2==0) checky=py/2;
            else checky=py/2+1;

            if((px) % 2==0) checkx=px/2;
            else checkx=px/2+1;
        for(i=0;i<ylen;i++){
            for(j=0;j<xlen;j++){
                if(((i+1)%(py+1)==0)||((j+1)%(px+1)==0)) {
                    //printf("%d mod (%d+1)=%d  %d mod (%d+1)=%d",i,py, i%(py+1),i,px,(j%(px+1)));
                    ansmatr[i][j]=1;
                    
                }
                else {
                    if(((i+1)%(py+1)==checky)&&((j+1)%(px+1)==checkx)&&((j/(px+1)+1)==answersdec[i/(py+1)])) {
                        ansmatr[i][j]=1;
                        
                        
                    }

                    else {
                        ansmatr[i][j]=0; 
                        
                    }
                }
                fprintf(wfile,"%d ",ansmatr[i][j]);
                printf("%d ",ansmatr[i][j]);
            }
            printf("\n");
            fprintf(wfile,"\n");

        }

        
        /*int k; int kl; int klx; int kly;
        char ansout[100];
        char anstempout[100]={0};
        int outansw[4]={0};
        for (k=0; k<y; k++){
            for (kly=0;kly<y;kly++) {outansw[kly]=0;}
            for (kly=0;kly<py;kly++){
                for (kl=sizeof(answersdec[k]);kl>=0; kl--){
                    for (klx=0;klx<px;klx++){
                        sprintf(anstempout,"%d ",answersdec[k]&(1<<kl)?1:0);
                    }
                }
            }
            
            sprintf(ansout,"%d %d %d %d",outansw[0],outansw[1],outansw[2],outansw[3]);
            sprintf(ansout,"\n");
            fputs(ansout,wfile);
        }*/
    }       
    else printf("Не верный номер ответа введен.");
    fclose(wfile);



return 0;
};
