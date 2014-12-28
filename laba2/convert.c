#include <stdio.h>
#include <string.h>
#include <stdlib.h>	
int main(int argc, char *argv[]){
	size_t i,j;
	int gs;
	int color_max;
	
	sscanf(argv[2],"%d",&gs);
	
	FILE *ofile,*wf;
	ofile =fopen(argv[1],"r");
	
	/* запрос цветности*/
	char P1[2]={0};
	fscanf(ofile,"%s",P1);
	if(strcmp(P1,"P3")==0){
		wf=fopen("converted.pnm","wt");
		int xlen, ylen;
		int **mat;
		int r,g,b;

		fscanf(ofile,"%d %d",&xlen,&ylen);
		fscanf(ofile, "%d ",&color_max);

		mat=(int**)malloc((ylen)*sizeof(int*));
		for(i=0;i<ylen;i++){
		    mat[i]=(int*)malloc((xlen)*sizeof(int));                
		    }
		fprintf(wf,"P1 \n%d %d\n",xlen,ylen);

		for(i=0;i<ylen;i++){
			for(j=0;j<xlen;j++){
				fscanf(ofile,"%d %d %d",&r,&g,&b);

				if((r+g+b)/3>gs) mat[i][j]=0;
				else mat[i][j]=1;

			}
		}
		
		for(i=0;i<ylen;i++){
			for(j=0;j<xlen;j++)
				fprintf(wf,"%d ",mat[i][j]);
			fprintf(wf,"\n");
		}


		fclose(wf);

	}	
	fclose(ofile);
return 0;
}
