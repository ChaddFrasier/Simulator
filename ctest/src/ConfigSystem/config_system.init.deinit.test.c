#ifndef CONFIG_INIT_TEST_C
#define CONFIG_INIT_TEST_C

#include "../../headers/tests.h"
#include "../../../src/ConfigSystem/ConfigSystem.h"
#include <string.h>

TEST{
    if( true ) {
        return PASS;
    } else {
        return FAIL;
    }
    return FAIL;
}
#endif