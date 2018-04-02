#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

MODULE_AUTHOR("Oleksandr Kravchuk");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("Very simple example of PS/2 mouse IRQ handling");

#define DRV_NAME "irq_handling"
#define PS2_MOUSE_IRQ 12

struct my_fake_dev {
	unsigned long long counter;
};

struct my_fake_dev fake_dev = {0};


static irqreturn_t irq_handler(int irq, void *dev_id)
{
	struct my_fake_dev *fake_dev = dev_id;

	printk(KERN_DEBUG DRV_NAME ": mouse moves %llu\n", ++fake_dev->counter);

	return IRQ_HANDLED;
}

static int __init irq_init(void)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	if (request_irq(PS2_MOUSE_IRQ, &irq_handler, IRQF_SHARED, "my_mouse", &fake_dev)) {
		printk(KERN_ERR DRV_NAME ": cannot register IRQ %d\n", PS2_MOUSE_IRQ);
		return -EBUSY;
	}

	printk(KERN_DEBUG DRV_NAME ": request on IRQ %d succeeded\n", PS2_MOUSE_IRQ);

	return 0;
}

void __exit irq_exit(void)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	free_irq(PS2_MOUSE_IRQ, &fake_dev);

	printk(KERN_DEBUG DRV_NAME ": freeing IRQ %d\n", PS2_MOUSE_IRQ);
}

module_init(irq_init);
module_exit(irq_exit);

