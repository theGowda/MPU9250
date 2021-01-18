#include "../MPU9250.h"

typedef MPU9255 IMU;

void print_roll_pitch_yaw(IMU *mpu)
{
    printf("Yaw, Pitch, Roll: %0.2f, %0.2f, %0.2f\n", mpu->getYaw(), mpu->getPitch(), mpu->getRoll());
}

int main()
{
    IMU mpu;
    struct timeval ts;
    long newTime = 0;
    long oldTime = 0;

    I2CDevice dev;
    dev.bus = 1;
    dev.addr = 0x68;
    dev.iaddr_bytes = 1;
    dev.page_bytes = 1;

    memset(&dev, 0, sizeof(dev));
    int bus;

    /* Open i2c bus /dev/i2c-0 */
    if ((bus = i2c_open("/dev/i2c-1")) == -1) {
        printf("Could not open i2c bus");
    }
    else
    {
        if (!mpu.setup(0x68, &dev))
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
                gettimeofday(&ts, NULL);
                newTime = ts.tv_usec * 1000;
                if((newTime - oldTime)>25){
                    print_roll_pitch_yaw(&mpu);
                    gettimeofday(&ts, NULL);
                    oldTime = ts.tv_usec * 1000;
                }
            }
        }
    }
    i2c_close(bus);
}