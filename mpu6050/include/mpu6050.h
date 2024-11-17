/**
 * This file defines the API to access the MPU6050.
 */

#ifndef _MPU6050_H_
#define _MPU6050_H_

/// @brief Structure to store the state of the MPU
typedef struct {
    /// @brief Raw reading of the accelerometer
    int16_t accel_raw[3];

    /// @brief Raw reading of the gyroscope
    int16_t gyro_raw[3];

    /// @brief Raw reading of the temperature
    int16_t temp_raw;

    /// @brief Gyroscope offsets (calibrated) to adjust the raw values
    /// @todo Do we need float here?
    int16_t gyro_calib[3];

    // Factor to multiply the raw gyroscope reading to get physical angular velocity (in degrees per seconds)
    float gyro_conv_factor;

    /// @brief Acceleration calibrated offset
    /// @todo Do we need float here?
    int16_t accel_calib[3];

    /// @brief Factor to multiply the raw accelerometer reading to get physical acceleration (in g)
    float accel_conv_factor;

} mpu6050_t;

/// @brief Initialize the MPU6050 module
/// @return HAL I2C status
/// @todo Add configuration options such as scale (range), ...
HAL_StatusTypeDef mpu6050_init(mpu6050_t *mpu);

/// @brief Read the raw accelerometer data (only) from the sensor
/// The new reading is going to be updated in the input structure
HAL_StatusTypeDef mpu6050_read_gyro_raw(mpu6050_t *mpu);

/// @brief Read all sensor data (gyro, accel, temperature)
HAL_StatusTypeDef mpu6050_read_accel_raw(mpu6050_t *mpu);

/// @brief Read the raw gyroscope data (only) from the sensor
HAL_StatusTypeDef mpu6050_read_all_raw(mpu6050_t *mpu);

/// @brief Convert raw accelerometer data to physical acceleration
/// @param accel A pointer to output three floats
void mpu6050_get_physical_acceleration(mpu6050_t *mpu, float *accel);

/// @brief Convert raw gyroscope data to physical angular velocity
/// @param ang_velo A pointer to outut three floats
void mpu6050_get_physical_angular_velocity(mpu6050_t *mpu, float *ang_velo);

/// @brief Convert raw sensor data to temperature in degree Celsius
/// @param temp A pointer to one float
void mpu6050_get_physical_temperature(mpu6050_t *mpu, float *temp);

/// @brief Calibrate the gyroscope
HAL_StatusTypeDef mpu6050_calibrate_gyro(mpu6050_t *mpu);

/// @brief Calibrate the accelerometer
HAL_StatusTypeDef mpu6050_calibrate_accelerometer(mpu6050_t *mpu);

/// @brief Read all sensor data and adjust them by the calibration
HAL_StatusTypeDef mpu6050_read_all_calib(mpu6050_t *mpu);

#endif

