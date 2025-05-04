#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
	}
	//printf("Test from threads\n");
	//sleep(3);
	//printf("Ending thread\n");
}

void	*routine2()
{
	sleep(2);
	printf("Value of x: %d\n", x);
}

int	main(int argc, char *argvp[])
{
	pthread_t p1, p2, p3, p4;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
	{
		return 1;
	}
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
	{
		return 2;
	}
	if (pthread_create(&p3, NULL, &routine, NULL) != 0)
	{
		return 3;
	}
	if (pthread_create(&p4, NULL, &routine, NULL) != 0)
	{
		return 4;
	}
	if (pthread_join(p1, NULL) != 0)
	{
		return 5;
	}
	if (pthread_join(p2, NULL) != 0)
	{
		return 6;
	}
	if (pthread_join(p3, NULL) != 0)
	{
		return 7;
	}
	if (pthread_join(p4, NULL) != 0)
	{
		return 8;
	}
	pthread_mutex_destroy(&mutex);
	printf("Value of x: %d\n", x);
	return 0;
}
