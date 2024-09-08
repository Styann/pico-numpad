#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include "pico/stdlib.h"

bool debounce(uint32_t *timer, const uint32_t ms);

#endif
