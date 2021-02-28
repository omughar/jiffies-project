#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gcd.h>

#include <linux/hash.h> // reference to GOLDEN_RATIO_PRIME


#include <asm/param.h>

//#include <linux/jiffies.h>


static int simple_init(void) {
	printk(KERN_INFO "Loading Kernel Module∖n");

	printk(KERN_INFO "%llu∖n", GOLDEN_RATIO_PRIME);

	return 0;
}


static void simple_exit(void) {
	printk(KERN_INFO "Removing Kernel Module∖n");


	unsigned long a = gcd(3300, 24);

	printk(KERN_INFO "Greatest Common Denominator between 3,300 and 24 is: %lu\n", a);

}



module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("OM");