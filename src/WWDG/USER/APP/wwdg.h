#ifndef __WWDG_H_
#define __WWDG_H_

#include "HAL_device.h"

void init_WWDG_exit(void);
void Wwdg_reset_ON(unsigned char ucTcnt, unsigned char ucWcnt);

#endif /* __WWDG_H_ */
