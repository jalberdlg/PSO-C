#include <api.h>
#include <stdlib.h>
#include "pso.h"	/* Constantes definidas no pso.h */

/* Definindo as variáveis Message */

Message position, veloc, pbest, gbest, funcao0;

/* Função objetivo */

int fobj (int x1, int x2){
	return (x1 + 3*x2 - 6);
}

/* PSO */

void main(){

	Echo("Início do BEST: ");
    	Echo(itoa(GetTick()));
    	
    	Receive(&position, velocidade);
    	Receive(&veloc, velocidade);
    	Receive(&funcao0, pso1);
    	
    	int i, j;
    	int target_error = 100000000;
    	int funcao[n_part];
    	int Menor = 0;
   	int MenorFun0 = 0, MenorFun = 0;
                
        while (target_error >= 1){
        
        	/* Avaliação da função objetivo para os novos valores das particulas */
        	for (i=0; i < n_part; i++){
        		funcao[i] = fobj(position.msg[2*i],position.msg[2*i+1]);
        	}
        	
        	for (i=0; i < n_part; i++){
        		if (funcao[i] < funcao0.msg[i]){
        			for (j=0; j < n_part; j++){
        				pbest.msg[2*i+j] = position.msg[2*i+j];
        			}
        			funcao0.msg[i] = funcao[i];
        		}
        	}
        	
        	/* Atualizando o menor valor da função e a melhor particula */
        	for (i=0; i < n_part; i++){
        		if (funcao[i] < funcao[0]){
        			Menor = i;
        		 	MenorFun = funcao[i];
        		}
        	}
        	
        	/* Cálculo da tolerância */
        	target_error = MenorFun - MenorFun0;
        	if (target_error < 0){
        		target_error = - target_error;
        	}
        	
        	/* Atualizando gbest e o melhor valor da função */
        	for (i=0; i < n_var; i++){
        		if (MenorFun < MenorFun0){
        			gbest.msg[i] = pbest.msg[2*Menor+i];
        			MenorFun0 = MenorFun;
        		}
        	}
        	
        	Send(&position, velocidade);
        	Send(&veloc, velocidade);
        	Send(&pbest, velocidade);
        	Send(&gbest, velocidade);
        }
        
        Send(&position, pso1);
        Send(&veloc, pso1);
        Send(&pbest, pso1);
        Send(&gbest, pso1);
        
         
}
