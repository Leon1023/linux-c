/*名称：pthread.c
 *功能：创建了 3 个线程，为了更好地描述线程之间的并行执行，让 3 个线程重用
 *      同一个执行函数。每个线程都有 5 次循环（可以看成 5 个小任务），每次
 *      循环之间会随机等待 1～10s 的时间，意义在于模拟每个任务的到达时间是
 *      随机的，并没有任何特定规律。3个线程的执行顺序由互斥锁控制。
 *知识：pthread_create();pthread_join();pthread_exit();pthread_cancel().
*       pthread_mutex_init(),pthread_mutex_destroy(),pthread_mutex_lock
 *作者：赵陈亮
 *邮箱：liangzc1124@163.com
 *日期：2018.03.13
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//the header file for sleep

#define THREAD_NUMBER 3 //how many threads to run in the same time
#define REPEAT_NUMBER 5 //how many tasks of every pthread to running
#define DELAY_TIME_LEVEL 10.0 // the max time range to delay

pthread_mutex_t mutex;  //定义一个互斥锁

//the function of the pthread to run with
void *thr_fun(void *arg)
{
  int thr_num = (int)arg;//which to identfied the pthread
  int count = 0,res=0;         //the task counter
  int delay_time = 0;

  res = pthread_mutex_lock(&mutex);
  if(res){
	printf("thread %d locked failed!\n",thr_num);
	pthread_exit(NULL);
  }
  printf("thread %d starting!\n",thr_num);
  for(count=0;count<REPEAT_NUMBER;count++){
	delay_time = (int)(rand()*DELAY_TIME_LEVEL/RAND_MAX)+1;//range from 1 to 10
	sleep(delay_time);
	printf("\tthread %d:job %d delay %d seconds\n",thr_num,count,delay_time);
  }
  printf("pthread %d finished!\n",thr_num);
  pthread_exit(NULL);//pthread exit!
}

int main(void)
{
  pthread_t pthread[THREAD_NUMBER];//creat a list which to store pthread ID
  int no=0,res;
  void *thread_ret;

  srand(time(NULL));//for rand()

  pthread_mutex_init(&mutex,NULL);//互斥锁的初始化

 //creat multi pthreads 
  for(no=0;no<THREAD_NUMBER;no++){
	res = pthread_create(&pthread[no],NULL,thr_fun,(void *)no);
	if(res){
	  printf("creat pthread %d failt!\n",no);
	  exit(res);
	}
  }
   
  printf("creat pthread successfull! Waiting for it to finish...\n");

  for(no=0;no<THREAD_NUMBER;no++){
	res = pthread_join(pthread[no],&thread_ret);
	if(!res){
	  printf("pthred %d joined!\n",no);
	}
	else{
	  printf("pthread %d failed to join\n",no);
	}
	pthread_mutex_unlock(&mutex);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
