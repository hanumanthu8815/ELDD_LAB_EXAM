#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/ioctl.h>
#include<linux/timer.h>
#include<linux/jiffies.h>
#include<linux/gpio.h>
#include "header.h"

#define NAME question_2
dev_t dev;
static struct cdev my_cdev;

static int wait_time=3000;
struct timer_list led_timer;
void timer_callback_led_toggle(struct timer_list *timer);
static int gpioLed=5;
static bool globalvar=0;

//protocol
int NAME_open(struct inode *inode,struct file *filp);
long NAME_ioctl(struct file *filp,unsigned int cmd,unsigned long argp);
int NAME_release(struct inode *inode,struct file *filp);


struct file_operations fops=
{
    .owner      =        THIS_MODULE,
    .open       =        NAME_open,
    .unlocked_ioctl=     NAME_ioctl,
    .release    =        NAME_release,
};

static int __init prog_init(void)
{
    int result;
    dev=MKDEV(256,0);
    if((result=register_chrdev_region(dev,1,"question_2"))<0)
    {
        printk("cannot allocated device number..!\n");
        return -1;
    }
    cdev_init(&my_cdev,&fops);
    if((result=cdev_add(&my_cdev,dev,1))<0)
    {
        printk("\n cannot add major number and cdev structure..!\n");
        return -1;
    }
    if(!gpio_is_valid(gpioLed))
    {
        printk("\n INVALID PIN..!\n");
        return -ENODEV;
    }
    gpio_request(gpioLed,"GPIO_5");
    gpio_direction_output(gpioLed,0);
    gpio_export(gpioLed,false);

    timer_setup(&led_timer,timer_callback_led_toggle,0);    //timer init

    int is_active=mod_timer(&led_timer,jiffies + msecs_to_jiffies(wait_time));
    if(is_active)
    {
        printk("\n timer failed ");
        return -1;
    }
    printk("DRIVER LOADED");
    return 0;
}
static void __exit prog_exit(void)
{
    del_timer(&led_timer);
    gpio_unexport(gpioLed);
    unregister_chrdev_region(dev,1);
    cdev_del(&my_cdev);
    printk("\n DRIVER UNLOADED..!\n");
}
module_init(prog_init);
module_exit(prog_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SURYA");

int NAME_open(struct inode *inode,struct file *filp)
{
    printk("\n OPEN SYSTEM CALL...\n");
    return 0;
}
int NAME_release(struct inode *inode,struct file *filp)
{
    printk("\n CLOSE SYSTEM CALL...\n");
    return 0;
}
long NAME_ioctl(struct file *filp,unsigned int cmd,unsigned long argp)
{
    long result;
    switch(cmd)
    {
        case set_periodicity:
            result=copy_from_user(&wait_time,(int *)argp,sizeof(wait_time));
            if(result==0)
            {
                return result;
            }
            else
            {
                printk("\n error in set periodicity..!\n");
            }
            break;
        case get_periodicity:
            result=copy_to_user((int *)argp,(int *)&wait_time,sizeof(wait_time));
            if(result>0)
            {
                printk("\n error in get peroidicity..!\n");
            }
            break; 
    }
    return result;
}
void timer_callback_led_toggle(struct timer_list *timer)
{
    globalvar=!globalvar;
    gpio_set_value(gpioLed,globalvar);
    int led_value=gpio_get_value(gpioLed);
    unsigned long jiffies_for_msecs=msecs_to_jiffies(wait_time);
    int is_active=mod_timer(&led_timer,jiffies+jiffies_for_msecs);
    if(is_active)
    {
        printk("\n error in changing value of timer..!\n");
        return ;
    }
}

