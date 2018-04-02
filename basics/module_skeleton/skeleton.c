#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Oleksandr Kravchuk");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("Linux kernel module skeleton");

#define DRV_NAME "skeleton"


static int __init skeleton_init(void)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	return 0;
}

static void __exit skeleton_exit(void)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);
}

module_init(skeleton_init);
module_exit(skeleton_exit);

