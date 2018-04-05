#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Oleksandr Kravchuk");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("Linux kernel module skeleton");

#define DRV_NAME "skeleton"


static int __init skeleton_init(void)
{
	pr_debug("%s: %s\n", DRV_NAME, __func__);

	return 0;
}

static void __exit skeleton_exit(void)
{
	pr_debug("%s: %s\n", DRV_NAME, __func__);
}

module_init(skeleton_init);
module_exit(skeleton_exit);

