#include "main.h"

extern uint32_t Time_Cnt1;//esse modificador diz ao compilador que essa variavel foi declarada em outro arquivo de código
extern uint32_t Time_Cnt2;


//Declaração dos protótipos de funções da biblioteca
void Delayus(uint32_t usdelay);
void Delayms(uint32_t msdelay);
void DelayIncCnt(void);

//Definição de macros da biblioteca
#define DELAY_Time_1()				(Time_Cnt1)
#define DELAY_SetTime_1(time)		(Time_Cnt1 = (time))
#define DELAY_Time_2()				(Time_Cnt2)
#define DELAY_SetTime_2(time)		(Time_Cnt2 = (time))




















