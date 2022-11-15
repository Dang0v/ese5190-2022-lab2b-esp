#ifndef APDS9960_H
#define APDS9960_H

#define ENABLE_REG      _u(0x80)
#define PDATA_REG       _u(0x9C)
#define CDATA_REG_L     _u(0x94)
#define CDATA_REG_H     _u(0x95) 
#define RDATA_REG_L     _u(0x96)
#define RDATA_REG_H     _u(0x97)
#define GDATA_REG_L     _u(0x98)
#define GDATA_REG_H     _u(0x99)
#define BDATA_REG_L     _u(0x9A)
#define BDATA_REG_H     _u(0x9B)

#define CONFIG_REG_1    _u(0x8F)
#define CONFIG_REG_2    _u(0x90)
#define CONFIG_REG_3    _u(0x9F)
#define ALS_TIME_REG    _u(0x81)


void APDS9960_init();

void read_proximity(int32_t* proximity);
void read_rgbc(int32_t* r, int32_t* g, int32_t* b, int32_t* c);


#endif