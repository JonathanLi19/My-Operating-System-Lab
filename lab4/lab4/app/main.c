#include "lib.h"
#include "types.h"
#define N 5
sem_t fk[5];
int times[5];
void philosopher(int i)
{   // 哲学家编号：0-4
	while(times[i]--)
	{
		printf("Philosopher %d is thinking\n",i);            // 哲学家在思考
		sleep(128);
		if(i%2==0){
		sem_wait(&fk[i]);            // 去拿左边的叉子
		sleep(128);
		sem_wait(&fk[(i+1)%N]);      // 去拿右边的叉子
		sleep(128);
		}
		else{
			sem_wait(&fk[(i+1)%N]);
			sleep(128);
			sem_wait(&fk[i]);            // 去拿左边的叉子
			sleep(128);
		}
		printf("Philosopher %d is eating\n",i);                 // 吃面条
		sleep(128);
		sem_post(&fk[i]);            // 放下左边的叉子
		sleep(128);
		sem_post(&fk[(i+1)%N]);      // 放下右边的叉子
		sleep(128);
		printf("Philosopher%d end!\n",i);
	}
	return;
}
void producer(int i,sem_t *mutex, sem_t *full, sem_t *empty)
{
	int t=5;
	while(t--){
		printf("Producer %d t: %d\n",i, t);
		sem_wait(empty);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Producer %d: produce\n", i);
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(full);
		sleep(128);
	}
	exit();
}
void consumer(int i,sem_t *mutex, sem_t *full, sem_t *empty)
{
	int t=5;
	while(t--){
		printf("Consumer %d t: %d\n",i, t);
		sem_wait(full);
		sleep(128);
		sem_wait(mutex);
		sleep(128);
		printf("Consumer %d: consume\n", i);
		sleep(128);
		sem_post(mutex);
		sleep(128);
		sem_post(empty);
		sleep(128);
	}
	exit();
}
void reader(int i,sem_t *w_mutex, sem_t *r_mutex){
	int t=1;
	while(t--){
		//printf("a\n");
		printf("Reader %d readcount = %d t=%d\n",i, get_readcount(),t);
		sem_wait(r_mutex);
		sleep(128);
		if(get_readcount()==0)
		{
			sem_wait(w_mutex);	
			sleep(128);
		}
		add_readcount();
		printf("Reader %d enter, readcnt=%d\n",i, get_readcount());
		sleep(128);
		sem_post(r_mutex);
		sleep(128);
		printf("Reader %d is reading!\n",i);
		sem_wait(r_mutex);
		sleep(128);
		decrease_readcount();
		printf("Reader %d leave, readcnt= %d\n",i,get_readcount());
		sleep(128);
		if(get_readcount()==0)
		{
			sem_post(w_mutex);
			sleep(128);
		}
		sem_post(r_mutex);
		sleep(128);
	}
}

void writer(int i , sem_t *w_mutex)
{
	int t=1;
	while(t--){
		sem_wait(w_mutex);
		sleep(128);
		printf("Writer %d is Writing! readcnt= %d\n",i, get_readcount());
		sleep(128);
		sem_post(w_mutex);
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
		//exit();
		sleep(1);
	}

	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	
	//哲学家
	printf("philosopher\n");
	ret = 1;
	for(int i=0;i<5;i++)
	{
		times[i] = 1;
	}
	for (int i = 0; i < 5; i++)
	{
		sem_init(fk + i, 1);
	}
	for (int i = 0; i < 5; i++)
	{
		if(ret > 0)
 			ret = fork();
		else
		{
			printf("ret=%d, pid= %d, Fork error\n",ret, getpid());
			break;
		}		
	}
	if (getpid() > 1)
	{
		philosopher(getpid() - 2);
		sem_destroy(fk +getpid() - 2);
		exit();
	}
	//生产者消费者问题
	/*printf("producer-consumer!\n");
	sem_t mutex, full, empty;
	sem_init(&mutex, 1);
	sem_init(&empty, 5);
	sem_init(&full, 0);
	ret=1;
	for (int i = 0; i < 5; i++)
	{
		if(ret > 0)
 			ret = fork();
		else
		{
			printf("ret=%d, pid= %d, Fork error\n",ret, getpid());
			break;
		}		
	}
	int id = getpid();
	if (id > 1 && id < 6)
	{
		producer(id,&mutex,&full, &empty);
		//producer(id);
	}
	else if (id ==  6)
	{
		consumer(id,&mutex,&full, &empty);
		//consumer(id);
	}*/
	//读者写者问题
	/*printf("read-write\n");
	sem_t w_mutex, r_mutex;
	sem_init(&w_mutex, 1);
	sem_init(&r_mutex, 1);
	ret = 1;
	for (int i = 0; i < 6; i++)
	{
		if(ret > 0)
 			ret = fork();
		else
		{
			//printf("ret=%d, pid= %d, Fork error\n",ret, getpid());
			break;
		}		
	}
	int id = getpid();
	if (id > 1 && id < 5)
	{
		reader(id, &w_mutex,&r_mutex);
	}
	else if (id > 4 && id < 8)
	{
		//printf("%d",&w_mutex);
		writer(id, &w_mutex);
	}*/
	exit(0);
	return 0;
}
