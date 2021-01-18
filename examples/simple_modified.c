#include "../MPU9250.h"
#include <time.h>
typedef MPU9255 IMU;

void print_roll_pitch_yaw(IMU *mpu)
{
    printf("Yaw, Pitch, Roll: %0.2f, %0.2f, %0.2f\n", mpu->getYaw(), mpu->getPitch(), mpu->getRoll());
}

int main()
{
    IMU mpu;
    clock_t ts1;
    ts1 = clock();
    if (!mpu.setup(0x68))
    {
        while (1)
        {
            printf("MPU connection failed. Please check your connection with `connection_check` example.\n");
            delay(5000);
        }
    }

    while (1)
    {
        if (mpu.update())
        {
            if (clock() - ts1 >= (25 * (CLOCKS_PER_SEC / 1000)))
            {
                print_roll_pitch_yaw(&mpu);
                ts1 = clock();
            }
        }
    }
}