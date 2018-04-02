#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

MODULE_AUTHOR("Oleksandr Kravchuk");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("Very simple example of IRQ handling");

#define DRV_NAME "irq_handling"

static int irq;
static char *interface;

module_param(interface, charp, 0644);
MODULE_PARM_DESC(interface, "A network interface");
module_param(irq, int, 0644);
MODULE_PARM_DESC(irq, "The IRQ of the network interface");


static irqreturn_t my_interrupt(int irq, void *dev_id)
{
	printk(KERN_DEBUG DRV_NAME ": Interupt!\n");

	return IRQ_HANDLED;
}

static int __init irq_init(void)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	if (request_irq(irq, &my_interrupt, IRQF_SHARED, interface, &irq)) {
		printk(KERN_ERR DRV_NAME ": cannot register IRQ %d\n", irq);
		return -EBUSY;
	}

	printk(KERN_DEBUG DRV_NAME ": request on IRQ %d succeeded\n", irq);

	return 0;
}

void __exit irq_exit(void)
{
	printk(KERN_DEBUG DRV_NAME ": %s()\n", __FUNCTION__);

	free_irq(irq, &irq);

	printk(KERN_DEBUG DRV_NAME ": freeing IRQ %d\n", irq);
}

module_init(irq_init);
module_exit(irq_exit);

