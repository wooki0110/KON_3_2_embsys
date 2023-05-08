#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple gpio driver for dot matrix");

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class* my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_dot_matrix"
#define DRIVER_CLASS "MyModuleClass_dot"

/* brief write data to buffer */

static ssize_t driver_write(struct file* File, const char* user_buffer, size_t count, loff_t* offs) {
	int to_copy, not_copied, delta;
	unsigned int value = 0;

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data to user */
	not_copied = copy_from_user(&value, user_buffer, to_copy);

	/* Row */
	if (value & (1 << 0)) {
		gpio_set_value(2, 1);
	}
	else {
		gpio_set_value(2, 0);
	}

	if (value & (1 << 1)) {
		gpio_set_value(3, 1);
	}
	else {
		gpio_set_value(3, 0);
	}

	if (value & (1 << 2)) {
		gpio_set_value(4, 1);
	}
	else {
		gpio_set_value(4, 0);
	}

	if (value & (1 << 3)) {
		gpio_set_value(27, 1);
	}
	else {
		gpio_set_value(27, 0);
	}

	if (value & (1 << 4)) {
		gpio_set_value(22, 1);
	}
	else {
		gpio_set_value(22, 0);
	}

	if (value & (1 << 5)) {
		gpio_set_value(10, 1);
	}
	else {
		gpio_set_value(10, 0);
	}

	if (value & (1 << 6)) {
		gpio_set_value(9, 1);
	}
	else {
		gpio_set_value(9, 0);
	}

	if (value & (1 << 7)) {
		gpio_set_value(11, 1);
	}
	else {
		gpio_set_value(11, 0);
	}
	/* Column */
	if (value & (1 << 15)) {
		gpio_set_value(14, 0);
	}
	else {
		gpio_set_value(14, 1);
	}

	if (value & (1 << 14)) {
		gpio_set_value(15, 0);
	}
	else {
		gpio_set_value(15, 1);
	}

	if (value & (1 << 13)) {
		gpio_set_value(23, 0);
	}
	else {
		gpio_set_value(23, 1);
	}

	if (value & (1 << 12)) {
		gpio_set_value(24, 0);
	}
	else {
		gpio_set_value(24, 1);
	}

	if (value & (1 << 11)) {
		gpio_set_value(25, 0);
	}
	else {
		gpio_set_value(25, 1);
	}

	if (value & (1 << 10)) {
		gpio_set_value(8, 0);
	}
	else {
		gpio_set_value(8, 1);
	}
	if (value & (1 << 9)) {
		gpio_set_value(7, 0);
	}
	else {
		gpio_set_value(7, 1);
	}
	if (value & (1 << 8)) {
		gpio_set_value(18, 0);
	}
	else {
		gpio_set_value(18, 1);
	}

	/* Calculate data */
	delta = to_copy - not_copied;
	return delta;
}

/* This function is called, when the device file is opened */
static int driver_open(struct inode* device_file, struct file* instance) {
	printk("dot matrix - open was called\n");
	return 0;
}

/* This function is called, when the device file is closed */
static int driver_close(struct inode* device_file, struct file* instance) {
	printk("dot matrix - close was called\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	//.read = driver_read,
	.write = driver_write
};

/* brief This function is called, when the module is loaded into the kernel */
static int __init ModuleInit(void) {
	printk("Hello, Kernel!\n");

	/* Allocate a device nr */
	if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated\n");
		return -1;
	}
	printk("read_write - Device Nr.Major : %d, Minor : %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

	/* create device class */
	if ((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not be created!\n");
		goto ClassError;
	}

	/* creat device file */
	if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file\n");
		goto FileError;
	}

	/* Initialize device file */
	cdev_init(&my_device, &fops);

	/* Registering device to kernel */
	if (cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}

	/* Set D1~8 segments GPIO */
	/* GPIO 2 init */
	if (gpio_request(2, "rpi-gpio-2")) {
		printk("Can not allocate GPIO 2\n");
		goto AddError;
	}

	/* Set GPIO 2 direction */
	if (gpio_direction_output(2, 0)) {
		printk("Can not set GPIO 2 to output!\n");
		goto Gpio2Error;
	}

	/* GPIO 3 init */
	if (gpio_request(3, "rpi-gpio-3")) {
		printk("Can not allocate GPIO 3\n");
		goto AddError;
	}

	/* Set GPIO 3 direction */
	if (gpio_direction_output(3, 0)) {
		printk("Can not set GPIO 3 to output!\n");
		goto Gpio3Error;
	}

	/* GPIO 4 init */
	if (gpio_request(4, "rpi-gpio-4")) {
		printk("Can not allocate GPIO 4\n");
		goto AddError;
	}

	/* Set GPIO 4 direction */
	if (gpio_direction_output(4, 0)) {
		printk("Can not set GPIO 4 to output!\n");
		goto Gpio4Error;
	}

	/* GPIO 27 init */
	if (gpio_request(27, "rpi-gpio-27")) {
		printk("Can not allocate GPIO 27\n");
		goto AddError;
	}

	/* Set GPIO 27 direction */
	if (gpio_direction_output(27, 0)) {
		printk("Can not set GPIO 27 to output!\n");
		goto Gpio27Error;
	}

	/* GPIO 22 init */
	if (gpio_request(22, "rpi-gpio-22")) {
		printk("Can not allocate GPIO 22\n");
		goto AddError;
	}

	/* Set GPIO 22 direction */
	if (gpio_direction_output(22, 0)) {
		printk("Can not set GPIO 22 to output!\n");
		goto Gpio22Error;
	}

	/* GPIO 10 init */
	if (gpio_request(10, "rpi-gpio-10")) {
		printk("Can not allocate GPIO 10\n");
		goto AddError;
	}

	/* Set GPIO 10 direction */
	if (gpio_direction_output(10, 0)) {
		printk("Can not set GPIO 10 to output!\n");
		goto Gpio10Error;
	}

	/* GPIO 9 init */
	if (gpio_request(9, "rpi-gpio-9")) {
		printk("Can not allocate GPIO 9\n");
		goto AddError;
	}

	/* Set GPIO 9 direction */
	if (gpio_direction_output(9, 0)) {
		printk("Can not set GPIO 9 to output!\n");
		goto Gpio9Error;
	}

	/* GPIO 11 init */
	if (gpio_request(11, "rpi-gpio-11")) {
		printk("Can not allocate GPIO 11\n");
		goto AddError;
	}

	/* Set GPIO 11 direction */
	if (gpio_direction_output(11, 0)) {
		printk("Can not set GPIO 11 to output!\n");
		goto Gpio11Error;
	}

	/* Set Column 0~7 segments GPIO*/
	/* GPIO 14 init */
	if (gpio_request(14, "rpi-gpio-14")) {
		printk("Can not allocate GPIO 14\n");
		goto AddError;
	}

	/* Set GPIO 14 direction */
	if (gpio_direction_output(14, 0)) {
		printk("Can not set GPIO 14 to output!\n");
		goto Gpio14Error;
	}

	/* GPIO 15 init */
	if (gpio_request(15, "rpi-gpio-15")) {
		printk("Can not allocate GPIO 15\n");
		goto AddError;
	}

	/* Set GPIO 15 direction */
	if (gpio_direction_output(15, 0)) {
		printk("Can not set GPIO 15 to output!\n");
		goto Gpio15Error;
	}

	/* GPIO 18 init */
	if (gpio_request(18, "rpi-gpio-18")) {
		printk("Can not allocate GPIO 18\n");
		goto AddError;
	}

	/* Set GPIO 18 direction */
	if (gpio_direction_output(18, 0)) {
		printk("Can not set GPIO 18 to output!\n");
		goto Gpio18Error;
	}

	/* GPIO 23 init */
	if (gpio_request(23, "rpi-gpio-23")) {
		printk("Can not allocate GPIO 23\n");
		goto AddError;
	}

	/* Set GPIO 23 direction */
	if (gpio_direction_output(23, 0)) {
		printk("Can not set GPIO 23 to output!\n");
		goto Gpio23Error;
	}

	/* GPIO 24 init */
	if (gpio_request(24, "rpi-gpio-24")) {
		printk("Can not allocate GPIO 24\n");
		goto AddError;
	}

	/* Set GPIO 24 direction */
	if (gpio_direction_output(24, 0)) {
		printk("Can not set GPIO 24 to output!\n");
		goto Gpio24Error;
	}

	/* GPIO 25 init */
	if (gpio_request(25, "rpi-gpio-25")) {
		printk("Can not allocate GPIO 25\n");
		goto AddError;
	}

	/* Set GPIO 25 direction */
	if (gpio_direction_output(25, 0)) {
		printk("Can not set GPIO 25 to output!\n");
		goto Gpio25Error;
	}

	/* GPIO 8 init */
	if (gpio_request(8, "rpi-gpio-8")) {
		printk("Can not allocate GPIO 8\n");
		goto AddError;
	}

	/* Set GPIO 8 direction */
	if (gpio_direction_output(8, 0)) {
		printk("Can not set GPIO 8 to output!\n");
		goto Gpio8Error;
	}

	/* GPIO 7 init */
	if (gpio_request(7, "rpi-gpio-7")) {
		printk("Can not allocate GPIO 7\n");
		goto AddError;
	}

	/* Set GPIO 7 direction */
	if (gpio_direction_output(7, 0)) {
		printk("Can not set GPIO 7 to output!\n");
		goto Gpio7Error;
	}

	return 0;

Gpio2Error:
	gpio_free(2);
Gpio3Error:
	gpio_free(3);
Gpio4Error:
	gpio_free(4);
Gpio27Error:
	gpio_free(27);
Gpio22Error:
	gpio_free(22);
Gpio10Error:
	gpio_free(10);
Gpio9Error:
	gpio_free(9);
Gpio11Error:
	gpio_free(11);
Gpio14Error:
	gpio_free(14);
Gpio15Error:
	gpio_free(15);
Gpio18Error:
	gpio_free(18);
Gpio23Error:
	gpio_free(23);
Gpio24Error:
	gpio_free(24);
Gpio25Error:
	gpio_free(25);
Gpio8Error:
	gpio_free(8);
Gpio7Error:
	gpio_free(7);
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

/**
* @brief This function is called, when the module is removed from the kernel
*/
static void __exit ModuleExit(void) {
	gpio_set_value(2, 0);
	gpio_set_value(3, 0);
	gpio_set_value(4, 0);
	gpio_set_value(27, 0);
	gpio_set_value(22, 0);
	gpio_set_value(10, 0);
	gpio_set_value(9, 0);
	gpio_set_value(11, 0);

	gpio_set_value(14, 0);
	gpio_set_value(15, 0);
	gpio_set_value(18, 0);
	gpio_set_value(23, 0);
	gpio_set_value(24, 0);
	gpio_set_value(25, 0);
	gpio_set_value(8, 0);
	gpio_set_value(7, 0);
	
	gpio_free(2);
	gpio_free(3);
	gpio_free(4);
	gpio_free(27);
	gpio_free(22);
	gpio_free(10);
	gpio_free(9);
	gpio_free(11);

	gpio_free(14);
	gpio_free(15);
	gpio_free(18);
	gpio_free(23);
	gpio_free(24);
	gpio_free(25);
	gpio_free(8);
	gpio_free(7);

	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
