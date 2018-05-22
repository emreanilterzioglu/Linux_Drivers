#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/i2c.h>
#include <linux/utsname.h>

#include <linux/time.h>

struct timeval tstart;
struct timeval tend;
struct timeval now;
unsigned int temp, second, minute, hour;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NONAME");
MODULE_DESCRIPTION("Basic hello module");
static char *param = "world";
module_param(param, charp, 0);
/* Add your code here */
static int __init hello_init(void)
{
do_gettimeofday(&tstart);


    pr_alert("Good morrow to this fair assembly.\n%s\n",param);
    printk("Kernel version %s\nKernel release %s\n", utsname()->version, utsname()->release);

    return 0;
}

static void __exit hello_exit(void)
{

    pr_alert("Alas, poor world, what treasure hast thou lost!\n");


do_gettimeofday(&tend);

printk("time taken: %ld millisec\n",
 1000 * (tend.tv_sec - tstart.tv_sec) +
 (tend.tv_usec - tstart.tv_usec) / 1000);

do_gettimeofday(&now);
temp = now.tv_sec;
second = temp%60;
temp /= 60;
minute = temp%60;
temp /= 60;
hour = temp%24;
printk("%02d:%02d:%02d:%06d\n", hour, minute, second, now.tv_usec);


}

module_init(hello_init);
module_exit(hello_exit);



