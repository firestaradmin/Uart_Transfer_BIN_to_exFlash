
#ifndef __transfer_BIN_to_EX_FLASH
#define __transfer_BIN_to_EX_FLASH

extern u8 TBEF_uart_recv_finish , TBEF_uart_recving_flag , rTBEF_uart_recv_tim_cnt;
//extern u8 TBEF_recvBuf[400];
//extern u16 TBEF_recvBuf_tail;



void TBEF_uart_receive_process(u8 data);

void TBEF_tim_process(void);
void TBEF_SendACK(u8 ERROR);
void TBEF_clearRecvBuf(void);
u8 TBEF_framePrasing(void);
void TBEF_mainFun(void);
void TBEF_data_CallBack(u8 *dataBuf, u16 len);
#endif


