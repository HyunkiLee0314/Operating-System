#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

struct birthday 
{	
	
	
	
	
	
};

/**
 * The following defines and initializes a list_head object named birthday_list
 */
static LIST_HEAD(birthday_list);

int simple_init(void)
{
	

       printk(KERN_INFO "Loading Module\n");

       
       
       
       
       return 0;
}

void simple_exit(void) {
	
	
	printk(KERN_INFO "Removing Module\n");

	
	
	

}

module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Kernel Data Structures");
MODULE_AUTHOR("SGG");
