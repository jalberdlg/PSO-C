#include <api.h>
#include <stdlib.h>
#include "pso.h"	/* Constantes definidas no pso.h */

/* Definindo as variáveis Message */

Message position, veloc, pbest, gbest;

/* Atualização velocidade
	x1 - position
	x2 - veloc
	x3 - pbest
	x4 - gbest
*/

int veloc_atual (int x1, int x2, int x3, int x4){
	int inercial, social, cognitivo;
	
	inercial = w * x2;
      	social = c1 * (rand(GetTick(),2,100)%5) * (x3 - x1);
      	cognitivo = c2 * (rand(GetTick(),2,100)%5) * (x4 - x1);
      	
      	x2 = inercial + social + cognitivo;
	return x2;
}

/* Velocidade */

void main(){
	
	int i;
	
	Echo("Início do Velocidade: ");
    	Echo(itoa(GetTick()));
    	
	Receive(&position, pso1);
	Receive(&gbest, pso1);
	
	/* Inicializando os valores de veloc e pbest */
	for (i=0; i < n_var*n_part; i++){
        	veloc.msg[i] = 0;
        	pbest.msg[i] = position.msg[i];
        }
        
        /* Atualizando os vetores veloc e position */
      	for (i=0; i < n_var*n_part; i++){
      		veloc.msg[i] = veloc_atual (position.msg[i], veloc.msg[i], pbest.msg[i], gbest.msg[i%2]);
      		position.msg[i] = position.msg[i] + veloc.msg[i];
      	}
      	
      	Send(&position, best);
	Send(&veloc, best);
	
	/* ---------------------------------------------------- */
	Receive(&position, best);
	Receive(&veloc, best);
	Receive(&pbest, best);
	Receive(&gbest, best);
	
	/* Atualizando os vetores veloc e position */
      	for (i=0; i < n_var*n_part; i++){
      		veloc.msg[i] = veloc_atual (position.msg[i], veloc.msg[i], pbest.msg[i], gbest.msg[i%2]);
      		position.msg[i] = position.msg[i] + veloc.msg[i];
      	}
	
	Send(&position, best);
	Send(&veloc, best);
	    
}
