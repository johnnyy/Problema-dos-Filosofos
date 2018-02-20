#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define COMENDO 1
#define MEDITANDO 2
#define FOME 3

pthread_mutex_t Comer;	
typedef struct{
	int id;
	int estado;
	int *palito_esquerdo;
	int *palito_direito;	
}filosofo;

void meditar(filosofo *f){
	if(f->estado == FOME) return;
	f->estado = MEDITANDO;
	printf("Filosofo %d meditando!\n\n",f->id);
	sleep(rand() % 3);
	printf("Filosofo %d terminou de meditar!\n\n",f->id);
	f->estado = FOME;
}

void comer(filosofo *f){
	if(f->estado != FOME) return;
	if(*f->palito_esquerdo == 0 && *f->palito_direito == 0){
		*f->palito_esquerdo = 1;
		printf("Filosofo %d pegou o palito esquerdo!\n",f->id);
		*f->palito_direito = 1;
		printf("Filosofo %d pegou o palito direito!\n",f->id);
		f->estado = COMENDO;
		printf("Filosofo %d esta comendo!\n",f->id);
		sleep(rand() % 3);
		printf("Filosofo %d terminou de comer!\n\n",f->id);
		*f->palito_esquerdo = 0;
		*f->palito_direito = 0;
	}
}

void *gerenciar(void *arg){
	filosofo *f = (filosofo *)(arg);
	while(1){
		pthread_mutex_lock(&Comer);
		comer(f);
		pthread_mutex_unlock(&Comer);
		meditar(f);
	}
}


int main(){
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0;
	filosofo f1, f2, f3, f4, f5;
	pthread_t filosofo1, filosofo2, filosofo3, filosofo4, filosofo5;
	//configurando o filosofo 1
	f1.id = 1;
	f1.estado = FOME;
	f1.palito_direito = &p1;
	f1.palito_esquerdo = &p2;
	
	//configurando o filosofo 2
	f2.id = 2;
	f2.estado = FOME;
	f2.palito_direito = &p2;
	f2.palito_esquerdo = &p3;
	
	//configurando o filosofo 3
	f3.id = 3;
	f3.estado = FOME;
	f3.palito_direito = &p3;
	f3.palito_esquerdo = &p4;
	
	//configurando o filosofo 4
	f4.id = 4;
	f4.estado = FOME;
	f4.palito_direito = &p4;
	f4.palito_esquerdo = &p5;
	
	//configurando o filosofo 5
	f5.id = 5;
	f5.estado = FOME;
	f5.palito_direito = &p5;
	f5.palito_esquerdo = &p1;
	
	
	pthread_create(&filosofo1, NULL, gerenciar, &f1);
	pthread_create(&filosofo2, NULL, gerenciar, &f2);
	pthread_create(&filosofo3, NULL, gerenciar, &f3);
	pthread_create(&filosofo4, NULL, gerenciar, &f4);
	pthread_create(&filosofo5, NULL, gerenciar, &f5);
	
	pthread_join(filosofo1, NULL);
	pthread_join(filosofo2, NULL);
	pthread_join(filosofo3, NULL);
	pthread_join(filosofo4, NULL);
	pthread_join(filosofo5, NULL);
	return 0;
}
