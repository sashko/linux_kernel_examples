#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("Oleksandr Kravchuk");
MODULE_LICENSE("WTFPL");
MODULE_DESCRIPTION("/dev/null device analog");

// function prototypes
static int devnull_release(struct inode *inode, struct file *filp);
static int devnull_open(struct inode *inode, struct file *filp);
static ssize_t devnull_read(struct file *filp, char __user *buf, size_t len, loff_t *offset);
static ssize_t devnull_write(struct file *filp, const char __user *buf, size_t len, loff_t *offset);

#define DRV_NAME "dev_null"
#define DEV_NAME "devnull"

static int major = 0;

module_param(major, int, 0);
MODULE_PARM_DESC(major, "major number of devnull, default is auto");

static struct file_operations fops = {
	.open		=	devnull_open,
	.release	=	devnull_release,
	.read		=	devnull_read,
	.write		=	devnull_write,
	.owner		=	THIS_MODULE,
};

static int __init devnull_init(void)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);
        
        if (major == 0) {
		dev_t dev;
		if (alloc_chrdev_region(&dev, 0, 1, DEV_NAME) != 0) {
			goto err_alloc;
		}
		major = MAJOR(dev);
        } else {
		if (register_chrdev(major, DEV_NAME, &fops) != 0) {
			goto err_reg;
		}
        }

        printk(KERN_DEBUG DRV_NAME ": assigned major: %d\n", major);

        return 0;

err_alloc:
	printk(KERN_WARNING DRV_NAME ": char device allocation failed\n");
	return -EFAULT;
err_reg:
	printk(KERN_WARNING DRV_NAME ": char device registration failed\n");
	return -EFAULT;
}

static void __exit devnull_exit(void)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);
        
	unregister_chrdev_region(MKDEV(major, 0), 1);
}

static int devnull_open(struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return 0;
}

static int devnull_release(struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return 0;
}

static ssize_t devnull_read(struct file *filp, char __user *buf, size_t len, loff_t *offset)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return 0;
}

static ssize_t devnull_write(struct file *filp, const char __user *buf, size_t len, loff_t *offset)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return len;
}

module_init(devnull_init);
module_exit(devnull_exit);

