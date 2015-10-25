#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TerryAlu");

static char *command = "NULL";
static int pid = -1;

static int succ = 1;

/* Parameters list */
module_param(command, charp, 0644);
MODULE_PARM_DESC(command, "showall or parentchild");
module_param(pid, int, 0644);
MODULE_PARM_DESC(pid, "target pid");

static int proc_show(struct seq_file *m, void *v)
{
	if(!strcmp(command, "showall"))
	{
		struct task_struct *task;

		for_each_process(task)
			seq_printf(m, "%s [%d]\n", task->comm, task->pid);
	}
	else
	{
		struct task_struct* target_task;
		struct list_head* lptr;
		struct task_struct* temp;

		/* find task by pid */
		target_task = pid_task(find_vpid(pid), PIDTYPE_PID);
		seq_printf(m, "Current: %s <%d>\n", target_task->comm, target_task->pid);
		seq_printf(m, "Parents: %s <%d>\n", target_task->parent->comm, target_task->parent->pid);
		
		seq_printf(m, "Children: ");
		/* lptr point list_head struct address, second parameter get the start address of next entry */
		list_for_each(lptr, &target_task->children)
		{
			/* calculate the offset and get the start address of the entry => return the entry ptr */
			temp = list_entry(lptr, struct task_struct, sibling);
			seq_printf(m, "%s <%d> ", temp->comm, temp->pid);
		}
		seq_printf(m, "\n");
	}

	return 0;
}

static int proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_show, NULL);
}

static const struct file_operations proc_fops = {
	.open  = proc_open,
	.read  = seq_read,
	.llseek  = seq_lseek,
	.release = single_release,
};

static int __init lspr_init(void)
{
	if(!strcmp(command, "showall") || !strcmp(command, "parentchild"))
	{
		if(!strcmp(command, "parentchild") && pid<0)
		{
			succ = 0;
			printk(KERN_ALERT "Wrong pid, please re-install.\n");
			return 0;
		}

		proc_create("lsproc", 0, NULL, &proc_fops);
		printk(KERN_INFO "Create file \"lsproc\"");
		return 0;
	}
	else
	{
		succ = 0;
		printk(KERN_ALERT "Wrong command, please re-install.\n");
		return 0;
	}
}

static void __exit lspr_exit(void)
{
	if(succ)
		remove_proc_entry("lsproc", NULL);
}

module_init(lspr_init);
module_exit(lspr_exit);
