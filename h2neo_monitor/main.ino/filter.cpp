#include "filter.h"

//float calcSlope(int initialPt, int finalPt, float timeBase) {
//    return (finalPt - initialPt) / timeBase;
//}
//
//void derivativeFilter(int *prevPtr, int *currPtr, bool *peakFlagPtr, bool *dropFlagPtr, int slopeThreshold, float timeBase) {
//    float slope = 0.0;
//    if (*prevPtr != *currPtr) {
//        slope = calcSlope(*prevPtr, *currPtr, timeBase);
////        Serial.print("The adcValue is    "); Serial.println(*currPtr);
//        Serial.print("The slope is   "); Serial.println(slope);
////        Serial.print("The threshold is   "); Serial.println(slopeThreshold);
//        if (slope < slopeThreshold) {
//            *peakFlagPtr = 1;
//        }
//        if (*peakFlagPtr && (slope > slopeThreshold)) {
//            *dropFlagPtr = 1;
//            *peakFlagPtr = 0;
//        }
//    }
//    *prevPtr = *currPtr;
//}

float calcMean(float *dataPtr, int len) {
    double sum = 0.0;
    float mean = 0.0;
    int i;
    for (i = 0; i < len; i++) {
        sum += *(dataPtr + i); 
    }
//    Serial.println(sum);
    mean = sum / len;
    return mean;
}

// The actual drop detection calculations
void thresholding(int index, float *inSignalPtr, int *outSignalPtr, float *filteredInPtr, float *avgFilterPtr, int lag,
                  float threshold, float influence, int *triggerPtr, int *peaksPtr, bool *dropFlagPtr) {
//        Serial.println(*(avgFilterPtr + index - 1));  

    if ((fabsf(*(inSignalPtr + index) - *(avgFilterPtr + index - 1)) > threshold) && (*dropFlagPtr == 0)) {

        // If the different between input and average is greater than a threshold value, toggle
//        if (*(inSignalPtr + index) < *(avgFilterPtr + index - 1)) {
           *(outSignalPtr + index) = -1;
           *triggerPtr = 1;
//        }

        *(filteredInPtr + index) = influence * *(inSignalPtr + index) +  (1 - influence) * *(filteredInPtr + index - 1);
//        index++;
    } else {
        *(outSignalPtr + index) = 0;
//        Serial.println(*triggerPtr);
        if(*triggerPtr == 1){
            (*peaksPtr)++;
            *dropFlagPtr = 1; // dropFLG triggers when incrementing # of peaks
//            numDrops += 1;       // may need to change, currently increases number of drops
            //printf("Drops Detected: %d\n", peaks);
        }
        *triggerPtr = 0;

        *(filteredInPtr + index) = *(inSignalPtr + index);
    }
    
    *(avgFilterPtr + index) = calcMean(filteredInPtr + index - lag, lag);
}
