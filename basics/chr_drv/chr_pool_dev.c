#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_AUTHOR("Oleksandr Kravchuk");
MODULE_LICENSE("WTFPL");
MODULE_DESCRIPTION("Character device driver");

// function prototypes
static int chrdev_release(struct inode *inode, struct file *filp);
static int chrdev_open(struct inode *inode, struct file *filp);
static ssize_t chrdev_read(struct file *filp, char __user *buf, size_t len, loff_t *offset);
static ssize_t chrdev_write(struct file *filp, const char __user *buf, size_t len, loff_t *offset);
static int chrdev_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);

#define DRV_NAME "chr_pool_dev"
#define DEV_NAME "chrpooldev"
#define MY_MACIG 'G'
#define READ_IOCTL _IOR(MY_MACIG, 0, int)
#define WRITE_IOCTL _IOW(MY_MACIG, 1, int)

static int major = 0;
static char msg[1024];

module_param(major, int, 0);
MODULE_PARM_DESC(major, "major number of chr_pool_dev, default is auto");

static struct file_operations fops = {
	.open		=	chrdev_open,
	.release	=	chrdev_release,
	.read		=	chrdev_read,
	.write		=	chrdev_write,
	.unlocked_ioctl	=	chrdev_ioctl,
	.owner		=	THIS_MODULE,
};

static int __init chrdev_init(void)
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

static void __exit chrdev_exit(void)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);
        
	unregister_chrdev_region(MKDEV(major, 0), 1);
}

static int chrdev_open(struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return 0;
}

static int chrdev_release(struct inode *inode, struct file *filp)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return 0;
}

static ssize_t chrdev_read(struct file *filp, char __user *buf, size_t len, loff_t *offset)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return simple_read_from_buffer(buf, len, offset, msg, sizeof(msg));
}

static ssize_t chrdev_write(struct file *filp, const char __user *buf, size_t len, loff_t *offset)
{
        printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return simple_write_to_buffer(msg, sizeof(msg), offset, buf, len);
}

static int chrdev_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	int len = sizeof(msg);

	switch(cmd) {
		case READ_IOCTL:
			copy_to_user((char *)arg, msg, len);
			break;
		case WRITE_IOCTL:
			copy_from_user(msg, (char *)arg, len);
			break;
		default:
			return -ENOTTY;
	}

	return len;
}

module_init(chrdev_init);
module_exit(chrdev_exit);

