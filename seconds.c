#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gcd.h>
#include <linux/hash.h>
#include <asm/param.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
//#include <asm/uaccess.h>
#include <linux/uaccess.h>


#define BUFFER_SIZE 128
#define MY_PROC_NAME "seconds"

static long in = 0;

ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);


static struct file_operations proc_ops = {
        .owner = THIS_MODULE,
        .read = proc_read,
};


static int simple_init(void) {
	printk(KERN_INFO "Loading Kernel Module∖n");

	proc_create(MY_PROC_NAME, 0, NULL, &proc_ops);
	printk(KERN_INFO "/proc/%s is created\n", MY_PROC_NAME);
	in = (long)jiffies;
	return 0;
}


static void simple_exit(void) {
	printk(KERN_INFO "Removing Kernel Module∖n");

	remove_proc_entry(MY_PROC_NAME, NULL);
	printk( KERN_INFO "In proc_exit(), the Jiffies is: %lu\n", jiffies);

	printk( KERN_INFO "/proc/%s removed\n", MY_PROC_NAME);

}




ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;
        rv = sprintf(buffer, "In proc_read(), the Jiffies is: %lu\n", (jiffies-in)/HZ);

        printk( KERN_INFO "In proc_read(), the Jiffies is: %lu\n", (jiffies-in)/HZ);

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}



module_init(simple_init);
module_exit(simple_exit);


MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("OM");