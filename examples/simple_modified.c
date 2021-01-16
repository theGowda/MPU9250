#include "../MPU9250.h"

int main()
{
    MPU9250 mpu;

    if (!mpu.setup(0x68))
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
            print_roll_pitch_yaw();
            for (int k = 0; k <= 1000; k++)
                ;
        }
    }
}

void print_roll_pitch_yaw()
{
    printf("Yaw, Pitch, Roll: %0.2f, %0.2f, %0.2f\n", mpu.getYaw(), mpu.getPitch(), mpu.getRoll());
}