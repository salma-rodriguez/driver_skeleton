#include<linux/module.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
// #include<linux/kdev_t.h>
// #include<linux/major.h>
#include<linux/cdev.h>

#define DEBUG 1
#define COUNT 1
#define MK_PREFIX "mkdev: "
#define MK_DEV_NAME "mkdev"

#if DEBUG
#define DPRINTK(s, arg...) printk(MK_PREFIX s "\n", ##arg)
#else
#define DPRINTK(S, arg...)
#endif

static dev_t dev_id;
// static struct cdev *mkdev;
static int major = 0; /* dynamic major number */

static int mkdev_open(struct inode *inode, struct file *file) {
	/* write code here */
	return 0;
}

static ssize_t mkdev_read(struct file *filp, char __user *buf, size_t siz, loff_t *offset) {
	/* write code here */
	return 0;
}

static ssize_t mkdev_write(struct file *filp, const char __user *buf, size_t siz, loff_t *offset) {
	/* write code here */
	return 0;
}

static int mkdev_release(struct inode *inode, struct file *file) {
	return 0;
}

struct mkdev {
	unsigned long size;
	// struct semaphore sem;
	struct cdev cdev;
};

/* file_operations */
static const struct file_operations mkdev_ops = {
	.owner = THIS_MODULE,
	.read =	mkdev_read,
	.write = mkdev_write,
	.open = mkdev_open,
	.release = mkdev_release,
};

static int mkdev_setup_cdev(struct mkdev *dev, int index) {
	int ret_val;
	if (major) {
		dev_id = MKDEV(major, major + index);
		// ret_val = register_chrdev_region(dev_id, COUNT, MK_DEV_NAME);
	} else /*allocate dynamically */  {
		ret_val = alloc_chrdev_region(&dev_id, 0, COUNT, MK_DEV_NAME);
		major = MAJOR(dev_id);
		if (ret_val)
			goto inval;

	}
	cdev_init(&dev->cdev, &mkdev_ops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &mkdev_ops;
	cdev_add(&dev->cdev, dev_id, COUNT);
	return 0;
inval:
	DPRINTK("error registering device");
	return -EINVAL;
}

static int mkdev_destroy_cdev(struct mkdev *dev) {
	cdev_del(&dev->cdev);
	// unresister_chrdev_region(dewv_id, COUNT);
	// release_cdev(&dev_id);
}

static int __init mkdev_init(void) {
	DPRINTK("starting module...");
	return 0;
}

static void __exit mkdev_cleanup(void) {
	DPRINTK("exiting module...");
}

module_init(mkdev_init);
module_exit(mkdev_cleanup);

MODULE_DESCRIPTION("char device");
MODULE_AUTHOR("Salma Rodriguez <srodr063@fiu.edu>");
MODULE_LICENSE("GPL");
