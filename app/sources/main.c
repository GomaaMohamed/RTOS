#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "STK_interface.h"
#include "GPIO_interface.h"
#include "OS_interface.h"

stack_t Task1_Stack;
task_t Task1;

stack_t Task2_Stack;
task_t Task2;

mutex_t mutex;

static void task1function(void)
{
	u8 flag = 1;
	while(1){
        
		//OS_SVC_delayTask(1);
		if (flag == 1)
		{
			GPIO_setPinValue(GPIOA, GPIO_PIN0, GPIO_HIGH);
			flag = 0;
	   }
	   else{
		   //OS_SVC_lockMutex(&mutex,-1);
		   GPIO_setPinValue(GPIOA, GPIO_PIN0, GPIO_LOW);
		   flag = 1;
		   //OS_SVC_releaseMutex(&mutex);
	   }
	   
		}
}

static void task2function(void)
{
	u8 flag = 1;
	while (1)
	{
	   
	   //OS_SVC_delayTask(1);
	   if (flag == 1)
	   {
		   //OS_SVC_lockMutex(&mutex,-1);
		   GPIO_setPinValue(GPIOA, GPIO_PIN1, GPIO_HIGH);
		   flag = 0;
		   //OS_SVC_releaseMutex(&mutex);
	   }
	   else{
		   GPIO_setPinValue(GPIOA, GPIO_PIN1, GPIO_LOW);
		   flag = 1;
	   }
	   
	}
}


int main(void)
{
	
	RCC_enableClock(RCC_APB2, RCC_IOPA);
	GPIO_setPinDirection(GPIOA, GPIO_PIN0, GPIO_OUTPUT_2MHZ_PP);
	GPIO_setPinDirection(GPIOA, GPIO_PIN1, GPIO_OUTPUT_2MHZ_PP);

	OS_init();

	OS_SVC_createTask(&Task1, &Task1_Stack, 0, task1function);
	OS_SVC_createTask(&Task2, &Task2_Stack, 0, task2function);

	OS_SVC_createMutex(&mutex,1);

	OS_SVC_startScheduler();
	__get_BASEPRI();

	while (1)
	{

	}
	return 0;
}

