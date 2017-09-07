/*
 * debug.h
 *
 *  Created on: Aug 29, 2017
 *      Author: liron
 */

#ifndef DEBUG_H_
#define DEBUG_H_


#define DEBUGMODE 2
#if DEBUGMODE == 1
	#define DEBUG(...) {printf("DEBUG: "); printf(__VA_ARGS__);}
#else
	#define DEBUG(...) {}
#endif
#if DEBUGMODE == 2
	#define DEBUG2(...) {printf("DEBUG: "); printf(__VA_ARGS__);}
#else
	#define DEBUG2(...) {}
#endif

#endif /* DEBUG_H_ */
