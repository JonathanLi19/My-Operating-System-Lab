#include "lib.h"
#include "types.h"
#define N 5

sem_t fk[5];
int times[5];

void philosopher(int i){   // 哲学家编号：0-4
  while(times[i]--){
    printf("%d is thinking\n",i);            // 哲学家在思考
    if(i%2==0){
	sem_wait(&fk[i]);            // 去拿左边的叉子
    sem_wait(&fk[(i+1)%N]);      // 去拿右边的叉子
	}
	else{
		sem_wait(&fk[(i+1)%N]);
		sem_wait(&fk[i]);            // 去拿左边的叉子
	}
	printf("%d is eating\n",i);                 // 吃面条
    sleep(128);
	sem_post(&fk[i]);            // 放下左边的叉子
    sem_post(&fk[(i+1)%N]);      // 放下右边的叉子
	printf("%d end!\n",i);
  }
  return;
}


sem_t mutex,empty,full;
void producer(int i){
	int t=5;
	while(t--){
		sem_wait(&empty);
		sem_wait(&mutex);
		cnt_plus();
		printf("Producer %d put item into buffer,buffer size is %d\n",i,cnt_read());
		sleep(10);
		sem_post(&mutex);
		sem_post(&full);
	}
	exit();
}
void consumer(int i){
	int t=5;
	while(t--){
		sem_wait(&full);
		sem_wait(&mutex);
		cnt_sub();
		printf("Consumer %d take item from buffer,buffer size is %d\n",i,cnt_read());
		sleep(128);
		sem_post(&mutex);
		sem_post(&empty);
	}
	exit();
}


int r_cnt=0;
sem_t w_mutex=1;
sem_t r_mutex=1;
void reader(int i){
	int t=5;
	while(t--){
		//printf("a\n");
		sem_wait(&r_mutex);
		//printf("%d",cnt_read());
		if(cnt_read()==0)sem_wait(&w_mutex);	
		//printf("c\n");
		cnt_plus();
		sem_post(&r_mutex);

		printf("reader %d is reading,cnt= %d\n",i,cnt_read());
		sleep(128);

		sem_wait(&r_mutex);
		cnt_sub();
		if(cnt_read()==0)sem_post(&w_mutex);
		sem_post(&r_mutex);
		sleep(128);
	}
}

void wirter(){
	int t=5;
	while(t--){
		sem_wait(&w_mutex);
		printf("Writer is Writing! cnt= %d\n",cnt_read());
		sleep(128);
		sem_post(&w_mutex);
		sleep(128);
	}
}


int uEntry(void) {

	// 测试scanf	
	int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	int ret = 0;
	while(1){
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4)
			break;
	}
	
	// 测试信号量
	int i = 4;
	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 0);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0) {
		while( i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {
		while( i != 0) {
			i --;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}

	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	
	//哲学家

	//生产者消费者问题

	//读者写者问题
	

	exit(0);
	return 0;
}
