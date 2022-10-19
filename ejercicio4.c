#include "stdio.h"
#include "mpi.h"



int main(){
	
	int tag=0;
	MPI_Status estado;
	int nro_procesadores;
	int nro_ejecuta;
	char nombre_procesadores[MPI_MAX_PROCESSOR_NAME];
	int len_nombre;
	
	
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &nro_procesadores);
	MPI_Comm_rank(MPI_COMM_WORLD, &nro_ejecuta);
	MPI_Get_processor_name(nombre_procesadores, &len_nombre);
	
	//printf("%s %d %d \n",nombre_procesadores, nro_procesadores, nro_ejecuta);

	
	int i;
	
	char palabra[9]="peconocer";
	
	int ini=0;
	int fin=8;
	char sw='v';


	if(nro_ejecuta==0){
				
		
		MPI_Send(&ini, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
		MPI_Send(&fin, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
		MPI_Send(&sw, 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
			
		
	}
	for (i=0;i<3;i++){
		if(nro_ejecuta==1){
			MPI_Recv(&ini, 1, MPI_INT,MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &estado);
			MPI_Recv(&fin, 1, MPI_INT,MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &estado);
			MPI_Recv(&sw, 1, MPI_CHAR,MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &estado);
			
			//printf("valor recibidop2 %d %d %c\n",ini,fin,sw);
			
			if(palabra[ini]!=palabra[fin]){
				sw='f';
			}
			ini=ini+1;
			fin=fin-1;
						
			MPI_Send(&ini, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);
			MPI_Send(&fin, 1, MPI_INT, 2, tag, MPI_COMM_WORLD);
			MPI_Send(&sw, 1, MPI_CHAR, 2, tag, MPI_COMM_WORLD);
				
		}
		if(nro_ejecuta==2){
			MPI_Recv(&ini, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &estado);
			MPI_Recv(&fin, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &estado);
			MPI_Recv(&sw, 1, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &estado);
		
			//printf("valor recibidop3 %d %d %c\n",ini,fin,sw);
			if(palabra[ini]!=palabra[fin]){
				sw='f';
			}
			ini=ini+1;
			fin=fin-1;
			
			MPI_Send(&ini, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
			MPI_Send(&fin, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
			MPI_Send(&sw, 1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
				
		}
	}
	
	
	
	
	MPI_Finalize();
	
	printf("%c\n",sw);
	
	return 0;	
	
}
