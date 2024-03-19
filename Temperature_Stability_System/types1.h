/*
 * types.h
 *
 *  Created on: 28 Mar 2022
 *      Author: Omnia
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char      u8;
typedef unsigned short int u16;
typedef unsigned long int  u32;
typedef signed char        s8;
typedef signed short int   s16;
typedef signed long int    s32;
typedef float              f32;
typedef double             f64;
typedef long double        f96;

#define OK   1
#define NOK  2
#define NULL_Pointer 3
#define NULL 0

#define IDLE 1
#define BUSY 2
#define BUSY_FUNC 3

#define PWM 1
#define NON_PWM 2

#endif /* TYPES_H_ */
