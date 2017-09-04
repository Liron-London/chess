/*
 * debug.h
 *
 *  Created on: Aug 29, 2017
 *      Author: liron
 */

#ifndef DEBUG_H_
#define DEBUG_H_


#define DEBUGMODE 0
#if DEBUGMODE == 1
	#define DEBUG(...) {printf("DEBUG: "); printf(__VA_ARGS__);}
#else
	#define DEBUG(...) {}
#endif


#endif /* DEBUG_H_ */
