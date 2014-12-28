#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void analyze_straight(int **mat, int xlen, int ylen){
    size_t i,j;
    int max=0;
    int px=0;
    int py=0;
    int *ansmas;

    for(i=0;i<xlen;i++){
        if((mat[0][i]==0&&i<xlen)) max+=1;
        else if(max>px) {px=max; max=0;}
            else max=0;
    }
    max=0;
    for(i=0;i<ylen;i++){        
        if((mat[i][0]==0) && (i<ylen)) max+=1;
        else if(max>py) {py=max; max=0;}
            else max=0;

    }
    ansmas=(int*)malloc((ylen/(py+1))*sizeof(int));

    for(i=0;i<ylen;i++)
        for(j=0;j<xlen;j++){
            if(((i+1)%(py+1)!=0)&&((j+1)%(px+1)!=0)&&(mat[i][j]==1)) {
                ansmas[i/(py+1)]=j/(px+1)+1;
            }

        }

    printf("%d %d %d %d ",px,py,xlen/(px+1)+1,ylen/(py+1)+1);
    for(i=0;i<=ylen/(py+1);i++)
        printf("%#x ",ansmas[i]);
    printf("\n");
}

void analyze_shifted(int **mat, int xlen, int ylen){
    size_t grad;
    int linenum,px,py,max;
    int ln;
    int Ok;
    int linelen[ylen];
    size_t ii;
    int **tempmat;
    size_t nx, ny;
    size_t i,j;

    px=0;
    py=0;
    max=0;  
    
    
    for(grad=0,linenum=0;grad<xlen;grad++){
        //printf("%d\n",grad);
        j=xlen-1-grad;
        i=0;
        Ok=0;
        for(ln=0;i<ylen&&j<xlen;j++,i++,ln++){
            //printf("%d %d \n", i,j );
            if(mat[i][j]==1) {
                max+=1;
                Ok=1;
                }
            else {
                if(max>px) {px=max; max=0;}
                else max=0;

                }
            }
            if(Ok) {linelen[linenum]=ln; linenum++;};

    }

    
    //printf("reversed\n");
    max=0;
    for(grad=0;grad<ylen;grad++){
        for(i=grad,j=0;(int)i>=0&&j<xlen;i--,j++){
            //printf("%d %d \n", i,j );
            if(mat[i][j]==1) {
                max+=1;
                }
            else {
                if(max>py) {py=max; max=0;}
                else max=0;

            }


        }
    }   
    
    //printf("Нижняя диагональ\n");
    
    for(i=1;i<ylen;i++){
        if(ylen-i<=xlen) grad=(xlen-ylen+i);
        else grad=0;
        ii=i;
        Ok=0;

        //printf("%d\n",grad);
        for(j=0,ln=0;j<xlen-grad;j++,ii++,ln++){
            if(mat[ii][j]==1){
                Ok=1;
            }
            //printf("%d %d \n", ii,j );
        }
        if(Ok){linelen[linenum]=ln; linenum++;};

    }

    //создаем временную матрицу для записи прямого изображения
    
    tempmat=(int**)malloc((py)*sizeof(int*));
    for(i=0;i<py;i++){
        tempmat[i]=(int*)malloc((px)*sizeof(int));                
    }

    for(i=0;i<py;i++)
        for(j=0;j<px;j++)
            tempmat[i][j]=0;


    //поворот изображения
    
    for(grad=0,linenum=0;grad<xlen;grad++){
        //printf("%d\n",grad);
        j=xlen-1-grad;
        i=0;
        Ok=0;
        for(ln=0;i<ylen&&j<xlen;j++,i++,ln++){
            //printf("%d %d \n", i,j );
            if(mat[i][j]==1) {
                Ok=1;
                nx=(px-linelen[linenum])/2+ln;
                //printf("(%d -%d)/2+%d = %d\n",px,linelen[linenum],ln,nx);
                ny=linenum;
                //printf("ny=%d nx=%d\n",ny,nx);
                tempmat[ny][nx]=1;
                
                }
            
            }
        if(Ok) {linenum++;};
    }
    
    for(i=1;i<ylen;i++){
        if(ylen-i<=xlen) grad=(xlen-ylen+i);
        else grad=0;
        ii=i;
        Ok=0;

        //printf("%d\n",grad);
        for(j=0,ln=0;j<xlen-grad;j++,ii++,ln++){
            if(mat[ii][j]==1){
                Ok=1;
                nx=(px-linelen[linenum])/2+ln;
                ny=linenum;
                //printf("ny=%d nx=%d\n",ny,nx);
                tempmat[ny][nx]=1;
            }
            //printf("%d %d \n", ii,j );
        }
        if(Ok){linenum++;};

    }
//-----вывод перевернутой матрицы       
    
    for(i=0;i<py;i++){
        for(j=0;j<px;j++)
            printf("%d ",tempmat[i][j]);
        printf("\n");
    }
//анализ прямого изображения
    xlen=px;
    ylen=py;
    analyze_straight(tempmat, xlen, ylen);
}



int main(int argc, char *argv[]){
  char cmd[20];
  char cptre[20]="capture";
  char rcgnz[20]="recognize";
  size_t i,j;


  if (strcmp(argv[1],cptre)==0){
  	int x,y,px,py;
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
                printf("%#x ",ansmatr[i][j]);
            }
            printf("\n");
            fprintf(wfile,"\n");

        }

        
        
    }       
    else printf("Не верный номер ответа введен.");
    fclose(wfile);
} 


else if (strcmp(argv[1],rcgnz)==0) { 
    char type1[20]="straight";
    char type2[20]="shifted";
    if(argc==4){
        FILE *ofile;
        ofile =fopen(argv[3],"r");

        /* запрос цветности и ее игнор */
        char P1[2]={0};
        fscanf(ofile,"%s",P1);

        /* запрос размерности изображения */
        int xlen,ylen;
        char sx[5]={0}; char sy[5]={0};
        fscanf(ofile,"%s %s",sx,sy);
        xlen=atoi(sx); ylen=atoi(sy);
        int **mat;
        size_t i,j;

        /*создание матрицы*/
        mat=(int**)malloc((ylen)*sizeof(int*));

        for(i=0;i<ylen;i++){
            mat[i]=(int*)malloc((xlen)*sizeof(int));                
            }
            

        for(i=0;i<ylen;i++){
            for(j=0;j<xlen;j++){
                fscanf(ofile,"%d",&mat[i][j]);
            }
            
        }

        if((strcmp(argv[2],type1)==0)){
            analyze_straight(mat, xlen, ylen);  
        }
        //повернутое на 45 градусов по часовой стрелке
        if((strcmp(argv[2],type2)==0)){
            analyze_shifted(mat, xlen, ylen);
        }
        fclose(ofile);
    }

    else{
        printf("Не верное число параметров.\n");
    }
}
return 0;
};
