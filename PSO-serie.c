#include <api.h>
#include <stdlib.h>

/* Definindo as constantes */
#define w 	1  	/* Constante da componente inercial */
#define c1	2	/* Constante da componente social */
#define c2	2	/* Constante da componente cognitiva */

Message position, veloc, pbest, gbest;
/* Função objetivo */

int fobj (int x1, int x2){
	return (2*x1 + 3*x2 - 5);
}

/* PSO */

void main(){

	/* Inicialização dos parâmetros */

	int n_var = 2;
    	int n_part = 10;
    	    
    	int iteracoes = 500;
    
    	int Menor = 0;
   	int MenorFun0 =0, MenorFun=0;
   	int funcao0[n_part], funcao[n_part];
    
    	int i, j;
    
    	Echo("Início do PSO: ");
    	Echo(itoa(GetTick()));
    	
    	/* Inicializando os valores das particulas */
    	
    	for(i=0; i < MSG_SIZE; i++){ /* MSG_SIZE é definido no api.h como sendo 128 */
            position.msg[i] = rand(GetTick(),2,100); /* Define os valores de position randomicamente entre 0 e 1 */
        }
        
        /* Inicializando o vetor funcao0 com os valores das particulas iniciais */
        
        for (i=0; i < n_part; i++){
        	funcao0[i] = fobj(position.msg[2*i],position.msg[2*i+1]);
        }
        
        /* Guardando o menor valor da função e a partícula de menor valor */
        
        for (i=0; i < n_part; i++){
        	if (funcao0[i] < funcao0[Menor]){
        		Menor = i;
        		MenorFun0 = funcao0[i];
        	}
        }
        
        /* Inicializando os valores de veloc, pbest e gbest */
        
        for (i=0; i < n_var*n_part; i++){
        	veloc.msg[i] = 0;
        	pbest.msg[i] = position.msg[i];
        }
        
        for (i=0; i < n_var; i++){
        	gbest.msg[i] = position.msg[2*Menor+i];
        }
        
        /* Algoritmo do PSO */
        
        int ite = 0;
        int target_error = 1;
        int inercial = 0;
        int social = 0;
        int cognitivo = 0;
        
        while ((ite < iteracoes) && (target_error >= 1)){
        
        	/* Atualizando o vetor veloc */
        	for (i=0; i < n_var*n_part; i++){
        		inercial = w * veloc.msg[i];
        		social = c1 * (rand(GetTick(),2,100)%5) * (pbest.msg[i] - position.msg[i]);
        		if (i % 2 == 0){
        			cognitivo = c2 * (rand(GetTick(),2,100)%5) * (gbest.msg[0] - position.msg[i]);
        		}
        		else{
        			cognitivo = c2 * (rand(GetTick(),2,100)%5) * (gbest.msg[1] - position.msg[i]);
        		}
        		veloc.msg[i] = inercial + social + cognitivo;
        	}
        	
        	/* Atualizando as particulas */
        	for (i=0; i < n_var*n_part; i++){
        		position.msg[i] = position.msg[i] + veloc.msg[i];
        	}
        	
        	/* Avaliação da função objetivo para os novos valores das particulas */
        	for (i=0; i < n_part; i++){
        		funcao[i] = fobj(position.msg[2*i],position.msg[2*i+1]);
        	}
        	
        	for (i=0; i < n_part; i++){
        		if (funcao[i] < funcao0[i]){
        			for (j=0; j < n_part; j++){
        				pbest.msg[2*i+j] = position.msg[2*i+j];
        			}
        			funcao0[i] = funcao[i];
        		}
        	}
        	
        	/* Atualizando o menor valor da função e a melhor particula */
        	for (i=0; i < n_part; i++){
        		if (funcao[i] < funcao[Menor]){
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
        	
        	/* Imprimindo os resultados */
        	Echo("Iteracao: ");
        	Echo(itoa(ite));
        	Echo("Melhor Particula: ");
        	Echo(itoa(Menor));
        	Echo("Valor da funcao objetivo: ");
        	Echo(itoa(MenorFun0));
        	Echo("==================================");
        	ite = ite + 1;
        }
        
        Echo("Melhor resultado da funcao: ");
        Echo(itoa(MenorFun0));
        Echo("Melhor solucao: ");
        Echo("X1 = ");
        Echo(itoa(gbest.msg[0]));
        Echo("X2 = ");
        Echo(itoa(gbest.msg[1]));     
}
