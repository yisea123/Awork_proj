#ifndef __SCCB_H
#define __SCCB_H

#define SCCB_ID    0x42

void sccb_init(void);
void sccb_start(void);
void sccb_stop(void);
void sccb_no_ack(void);
uint8_t sccb_wr_byte(uint8_t dat);
uint8_t sccb_rd_byte(void);
uint8_t sccb_wr_reg(uint8_t reg,uint8_t data);
uint8_t sccb_rd_reg(uint8_t reg);
uint8_t sccb_modify_reg (uint8_t reg, uint8_t mask, uint8_t value);
#endif













