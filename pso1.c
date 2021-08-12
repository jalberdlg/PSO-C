#include <api.h>
#include <stdlib.h>
#include "pso.h"	/* Constantes definidas no pso.h */





/* Definindo as variáveis Message */
	Message position;
	Message veloc;
	Message pbest;
	Message gbest;
	Message funcao0;
	
/* Função objetivo */

int fobj (int x1, int x2){
	return (x1 + 3*x2 - 6);
}

/* PSO */

int main(){
	
	
	/* Inicialização dos parâmetros */

	int Menor = 0;
   	int MenorFun0 =0;
    
    	int i;
    
    	Echo("Início do PSO: ");
    	Echo(itoa(GetTick()));
    	
    	/* Inicializando os valores das particulas */
    	
    	for(i=0; i < MSG_SIZE; i++){ /* MSG_SIZE é definido no api.h como sendo 128 */
        	if (i < n_part*n_var){	
        		position.msg[i] = rand(GetTick(),2,100);
        	}
        	else{
        		position.msg[i] = 0;
        	}
        }
        
        /* Inicializando o vetor funcao0 com os valores das particulas iniciais */
        
        for (i=0; i < MSG_SIZE; i++){
        	if (i < (n_part*n_var / 2)){
        		funcao0.msg[i] = fobj(position.msg[2*i],position.msg[2*i+1]);
        	}
        	else{
        		funcao0.msg[i] = 0;
        	}
        }
        
        /* Guardando o menor valor da função e a partícula de menor valor 2122211707-1247*/
        
        for (i=0; i < MSG_SIZE; i++){
        	if (funcao0.msg[i] < funcao0.msg[Menor]){
        		Menor = i;
        		MenorFun0 = funcao0.msg[i];
        	}
        }
        
        /* Inicializando os valores de veloc, pbest e gbest */
                
        for (i=0; i < MSG_SIZE; i++){
        	if (i < n_var){
        		gbest.msg[i] = position.msg[2*Menor+i];
        	}
        	else{
        		gbest.msg[i] = 0;
        	}
        }
	
	/* Atualização da velocidade */
	Send(&position, velocidade);
	Send(&gbest, velocidade);
	Send(&funcao0, best);
	
	Receive(&position, best);
	Receive(&veloc, best);
	Receive(&pbest, best);
	Receive(&gbest, best);
	
	MenorFun0 = fobj(gbest.msg[0],gbest.msg[1]);
	
	Echo("Melhor resultado da funcao: ");
	Echo(itoa(MenorFun0));
	Echo("Melhor solucao: ");
	Echo("X1 = ");
	Echo(itoa(gbest.msg[0]));
	Echo("X2 = ");
	Echo(itoa(gbest.msg[1]));
	
	Echo("Fim do PSO: ");
	Echo(itoa(GetTick())); 
	   
	
}	
	
	
