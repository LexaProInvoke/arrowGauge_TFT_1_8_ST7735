#include "ESP8266.h"
#define MAX_BUFFER_SIZE 100
char buffer[MAX_BUFFER_SIZE];
volatile uint32_t buffer_index = 0;

void USARTinit()
{
	RCC->APB1ENR |= (0b100000000000000000);
	RCC->AHB1ENR |= (0b1000);
	   GPIOD->MODER &=	~(0b11110000000000);
	   GPIOD->MODER |=	(0b10100000000000);
	   GPIOD->AFR[0] &= ~(0b1111111100000000000000000000);
	   GPIOD->AFR[0] |= (0b0111011100000000000000000000);

	   USART2->CR1 = USART_CR1_UE;
	   USART2->BRR = 42000000 / 9600;
	   USART2->CR1 &= ~USART_CR1_M; // 8 бит данных
	   USART2->CR1 &= ~USART_CR1_PCE; // Без бита контроля четности
	   USART2->CR2 &= ~USART_CR2_STOP;
	   // Включаем передатчик и приемник USART2
	   USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;

	   // Включаем USART2
	   USART2->CR1 |= USART_CR1_UE;
	   USART2->CR2 = 0;
	   USART2->CR3 = 0;

	   USART2->CR1 |= USART_CR1_RXNEIE; // Разрешаем прерывание по приему данных

	   NVIC_SetPriority(USART2_IRQn, 0); // Устанавливаем приоритет прерывания USART2
	   NVIC_EnableIRQ(USART2_IRQn); // Разрешаем прерывание USART2
}
