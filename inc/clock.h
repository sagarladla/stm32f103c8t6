#pragma once

/**
 * 
 * @file: clock.h
 * @description: Clock configuration and management
 * @author: Sagarrajvarman Ladla
 * @note: This file contains functions declarations to initialize and manage the system clock.
 * 
 */

void sys_clock_init(void);
void periph_clock_init(void);
void sys_clock_update(void);
unsigned int get_system_clock(void);
