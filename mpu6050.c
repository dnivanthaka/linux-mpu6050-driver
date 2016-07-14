/*
 * Sample MPU6050 I2C Driver
 *
 *
 */

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/err.h>

#define MPU6050_NAME "mpu6050"
#define MPU6050_I2C_ADDRESS 0x68

static const unsigned short normal_i2c[] = {
    MPU6050_I2C_ADDRESS,
    I2C_CLIENT_END
};

static int mpu6050_i2c_detect(struct i2c_client *client, 
        struct i2c_board_info *info){
    if(client->addr != MPU6050_I2C_ADDRESS)
        return -ENODEV;

    dev_info(&client->dev, "Detected MPU6050\n");

    return 0;
}

static int mpu6050_i2c_probe(struct i2c_client *client, 
        const struct i2c_device_id *id){

    return 0;
}

static int mpu6050_i2c_remove(struct i2c_client *client){
    return 0;
}

static const struct i2c_device_id mpu6050_id[] = {
    {MPU6050_NAME, 0},
    {}
};

MODULE_DEVICE_TABLE(i2c, mpu6050_id);

static struct i2c_driver mpu6050_i2c_driver = {
    .driver = {
        .name = MPU6050_NAME
    },
    .id_table = mpu6050_id,
    .probe    = mpu6050_i2c_probe,
    .remove   = mpu6050_i2c_remove,
    .detect   = mpu6050_i2c_detect,
    .address_list = normal_i2c
};

module_i2c_driver(mpu6050_i2c_driver);

MODULE_AUTHOR("D.N. Amerasinghe <nivanthaka@gmail.com>");
MODULE_DESCRIPTION("Sample MPU6050 I2C bus driver");
MODULE_LICENSE("GPL");
