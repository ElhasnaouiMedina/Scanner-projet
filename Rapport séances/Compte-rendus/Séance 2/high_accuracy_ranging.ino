#include "Seeed_vl53l0x.h"
Seeed_vl53l0x VL53L0X;

void setup() {

    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    Serial.begin(115200);
    Status = VL53L0X.VL53L0X_common_init();
    if (VL53L0X_ERROR_NONE != Status) {
        Serial.println("start vl53l0x mesurement failed!");
        VL53L0X.print_pal_error(Status);
        while (1);
    }

    VL53L0X.VL53L0X_high_accuracy_ranging_init();

    if (VL53L0X_ERROR_NONE != Status) {
        Serial.println("start vl53l0x mesurement failed!");
        VL53L0X.print_pal_error(Status);
        while (1);
    }
}


void loop() {
    int t1 = millis();
    VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    memset(&RangingMeasurementData, 0, sizeof(VL53L0X_RangingMeasurementData_t));
    Status = VL53L0X.PerformSingleRangingMeasurement(&RangingMeasurementData);
    if (VL53L0X_ERROR_NONE == Status) {
        if (RangingMeasurementData.RangeMilliMeter >= 2000) {
            Serial.println("out of range!!");
        } else {
            Serial.print("Measured distance:");
            Serial.print(RangingMeasurementData.RangeMilliMeter);
            Serial.println(" mm");
        }
    } else {
        Serial.print("mesurement failed !! Status code =");
        Serial.println(Status);
    }
    int t2 = millis();
    Serial.print("Time (ms): ");
    Serial.println(t2-t1);
    delay(300);
}
