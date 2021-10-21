#include "updateFlowRate.h"
#define GTT_FACTOR 20
#define MEMSIZE 10
void updateFlowRate(unsigned long *ticMemPtr, int flowrateIndex, float *flowRatePtr) {
    unsigned long sum = 0;
    double avgTimeMS = 0;
    int i = 0;

    for (i = 0; i < flowrateIndex; i++) {
//        Serial.print("The value is  "); Serial.println(*(ticMemPtr + i));
//        if (*(ticMemPtr + i) != 0) {
//            
//        }
        sum += *(ticMemPtr + i);
    }
    avgTimeMS =  (double) sum / flowrateIndex; // calculates the average drop time
    *flowRatePtr = 3600000.0 / ((double) GTT_FACTOR * avgTimeMS);
}
