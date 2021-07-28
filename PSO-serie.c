#include <api.h>
#include <stdlib.h>

/* Função Objetivo */

float fobj (float x1,float x2) {
    return x1*x1 + x2*x2;
}

/* PSO */

int main(){

    /* Inicialização dos parâmetros */

    int n_var = 2;            /* Número de variáveis da função objetivo */
    int n_part = 10;        /* Número de partículas */
    
    float w= 0.641742430504416;    /* Constante da componente inercial */
    float c1 = 1.347659104059274;    /* Constante da componente social */
    float c2 = 1.347659104059274;    /* Constante da componente cognitiva */
    
    int iteracoes = 500;
    int qt_opt = 1;

    int Menor = 0;
    float MenorFun0, MenorFun;
    
    int i, j;
    
        
    /* Inicialização das particulas */
    
    float position[n_part][n_var];
    float veloc[n_part][n_var];
    float pbest[n_part][n_var];
    float gbest[n_var];
    float funcao0[n_part], funcao[n_part];

    
    for(i = 0; i < n_part; i++){
        for(j = 0; j < n_var; j++){
            position[i][j] = rand(1,0,100)/100; /* Atribui valores randomicos entre 0 e 1 */
        }
    }
    
    for(i = 0; i < n_part; i++){
        funcao0[i] = fobj (position[i][0],position[i][1]); /* Vetor com valores da função objetivo aplicando cada valor inicial das particulas */
    }
    
    for(i = 0; i < n_part; i++){
        if (funcao0[i] < funcao0[Menor]){
            Menor = i;
            MenorFun0 = funcao0[i];
        }
    }
    
    for(i = 0; i < n_part; i++){
        for(j = 0; j < n_var; j++){
            veloc[i][j] = 0.1 * position[i][j];  /* Atribui valores iniciais a veloc */
            pbest[i][j] = position[i][j];
        }
    }
    for(j = 0; j < n_var; j++){
            gbest[j] = position[Menor][j];  /* Atribui valores iniciais a veloc */
    }
        
    /* Algoritmo PSO */
    
    int ite = 0;
    float target_error = 1.0;
    float inercial, social, cognitivo = 0.0;
    
    while ((ite < iteracoes) && target_error>10^-12){
        
        /* Atualização da matriz velocidade */
        for(i = 0; i < n_part; i++){
            for(j = 0; j < n_var; j++){
                inercial = w*veloc[i][j];
                social = c1*(rand(1,0,100)/100)*(pbest[i][j]-position[i][j]);
                cognitivo = c2*(rand(1,0,100)/100)*(gbest[j]-position[i][j]);
                veloc[i][j] = inercial + social + cognitivo;
            }
        }
        
        /* Atualização das particulas */
        for(i = 0; i < n_part; i++){
            for(j = 0; j < n_var; j++){
                position[i][j] = position[i][j] + veloc[i][j];
            }
        }
        
        /* Avaliação da função objetivo para os novos valores das particulas */
        for(i = 0; i < n_part; i++){
            funcao[i] = fobj (position[i][0],position[i][1]);
        }
    
        /* Atualizando pbest e o valor da função */
        for(i = 0; i < n_part; i++){
            for(j = 0; j < n_var; j++){
                if (funcao[i] < funcao0[i]){
                    pbest[i][j] = position[i][j];
                    funcao0[i] = funcao[i];
                }
            }
        }
        
        /* Atualizando função */
        for(i = 0; i < n_part; i++){
            if (funcao[i] < funcao[Menor]){
                Menor = i;
                MenorFun = funcao[i];
               }
        }
        
        /* Cálculo da tolerancia */
        target_error = MenorFun - MenorFun0;
        if (target_error < 0){
            target_error = - target_error;
        }

        /* Atualizando gbest e o melhor valor da função */
        for(j = 0; j < n_var; j++){
            if (MenorFun < MenorFun0){
                gbest[j] = pbest[Menor][j];
                MenorFun0 = MenorFun;
            }
        }
        
        /* Imprimindo resultados */
        Echo("Iteração: ");
        Echo(itoa(ite));
        Echo("Melhor Particula: ");
        Echo(itoa(Menor));
        Echo("Função Objetivo: ");
        Echo(itoa(MenorFun));
        ite = ite + 1;
    }
    
    Echo("Melhor resultado da função: ");
    Echo(itoa(MenorFun));
    Echo("Melhor solução: ");
    Echo("x1 = ");
    Echo(itoa(gbest[0]));
    Echo("x2 = ");
    Echo(itoa(gbest[1]));
    
}
