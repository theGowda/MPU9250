#include "../MPU9250.h"

typedef MPU9255 IMU;

void print_roll_pitch_yaw(IMU *mpu)
{
    printf("Yaw, Pitch, Roll: %0.2f, %0.2f, %0.2f\n", mpu->getYaw(), mpu->getPitch(), mpu->getRoll());
}

int main()
{
    IMU mpu;
    I2CDevice dev;

    if (!mpu.setup(0x68, &dev))
    { // change to your own address
        while (1)
        {
            printf("MPU connection failed. Please check your connection with `connection_check` example.\n");
            //delay(5000);
        }
    }

    while (1)
    {
        if (mpu.update())
        {
            print_roll_pitch_yaw(&mpu);
            for (int k = 0; k <= 1000; k++)
                ;
        }
    }
}