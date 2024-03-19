/*
 * TWI_Ptivate.h
 *
 *  Created on: Jun 26, 2023
 *      Author: HP
 */

#ifndef TWI_PTIVATE_H_
#define TWI_PTIVATE_H_

#define TWCR     *((volatile u8 *) 0x56)
#define TWINT 7
#define TWEA  6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0

#define TWDR      *((volatile u8 *) 0x23)

#define TWAR      *((volatile u8 *) 0x22)
#define TWGCE 0

#define TWSR        *((volatile u8 *) 0x21)
#define TWPS0 0
#define TWPS1 1

#define TWBR       *((volatile u8 *) 0x20)




#endif /* TWI_PTIVATE_H_ */
