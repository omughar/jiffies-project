#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>


#define BUFFER_SIZE 128
#define MY_PROC_NAME "jiffies"


ssize_t jiffies_proc_read(struct file *file, char *buf, size_t count, loff_t *pos);


static struct file_operations proc_ops = {
        .owner = THIS_MODULE,
        .read = jiffies_proc_read,
};


static int simple_init(void) {
	printk(KERN_INFO "Loading Kernel Module∖n");

	proc_create(MY_PROC_NAME, 0, NULL, &proc_ops);
	printk(KERN_INFO "/proc/%s is created\n", MY_PROC_NAME);

	return 0;
}


static void simple_exit(void) {
	printk(KERN_INFO "Removing Kernel Module∖n");

	remove_proc_entry(MY_PROC_NAME, NULL);
	printk( KERN_INFO "the Jiffies is: %lu\n", jiffies);

	printk( KERN_INFO "/proc/%s is removed\n", MY_PROC_NAME);

}




ssize_t jiffies_proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {

        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf(buffer, "Jiffies is: %lu\n", jiffies);
        printk( KERN_INFO "Jiffies is: %lu\n",jiffies);

        copy_to_user(usr_buf, buffer, rv);

        return rv;
}



module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Jiffies Module");
MODULE_AUTHOR("OM");