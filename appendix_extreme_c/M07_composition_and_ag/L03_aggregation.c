// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * AGGREGATION: It also implies an object that contains another object, but the lifetimes are independent.
 * This means, you can cretaed the contained object before the container is constructed. Need an example? 
 * Of course, you can thing about it like a plant and its fruits, the live of the fruits do not depend on
 * the plant, as they can be picked, ate ... but the plant keeps the same, even when the plant dies, the
 * fruit don't "die" at that instant.
*/