#include <stddef.h>

#include "export.h"
#include "moddef.h"

/* ----- PUBLIC FUNCTIONS ----- */

MOD_EXPORT AERModDef DefineMod(void) {
  return (AERModDef){.constructor = NULL,
                     .destructor = NULL,
                     .registerSprites = NULL,
                     .registerObjects = NULL,
                     .registerObjectListeners = NULL,
                     .roomStepListener = NULL,
                     .roomChangeListener = NULL};
}
