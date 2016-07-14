/*
 * Sample MPU6050 I2C Driver
 *
 *  References 
 *  http://lxr.free-electrons.com/source/include/uapi/asm-generic/errno-base.h
 *  http://lxr.free-electrons.com/source/Documentation/i2c/writing-clients
 */

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/err.h>

#define MPU6050_NAME "mpu6050"
#define MPU6050_I2C_ADDRESS 0x68

#define MPU6050_REG_WHOAMI 0x75

static const unsigned short normal_i2c[] = {
    MPU6050_I2C_ADDRESS,
    I2C_CLIENT_END
};
//TODO Improve this structure
struct mpu6050_device {
    struct i2c_client *client;
    struct mutex lock;
};

static int mpu6050_i2c_detect(struct i2c_client *client, 
        struct i2c_board_info *info){

    //struct i2c_adapter *adapter = client->adapter;

    if(client->addr != MPU6050_I2C_ADDRESS)
        return -ENODEV;

    dev_info(&client->dev, "Detected MPU6050\n");

    return 0;
}

static int mpu6050_i2c_probe(struct i2c_client *client, 
        const struct i2c_device_id *id){

    struct i2c_adapter *adapter = client->adapter;
    int ret;
    int error;

    dev_info(&client->dev, "Probe MPU6050\n");

    if(!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA) && 
            !i2c_check_functionality(adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
        return -EIO;

    //TODO Reset device here

    ret = i2c_smbus_read_byte_data(client, MPU6050_REG_WHOAMI);
    if(ret < 0){
        dev_err(&client->dev, "Failed to detect device\n");
        error = -ENXIO;
        goto err_free_res;
    }

    if(ret != MPU6050_I2C_ADDRESS){
        dev_err(&client->dev, "Failed to identify MPU6050\n");
        error = -ENXIO;
        goto err_free_res;
    }

err_free_res:

    return 0;
}


static int mpu6050_i2c_remove(struct i2c_client *client){
    dev_info(&client->dev, "Remove MPU6050\n");
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
