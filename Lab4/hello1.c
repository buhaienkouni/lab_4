// SPDX-License-Identifier: GPL-2-Clause
#include <hello1.h>

MODULE_AUTHOR("IO-16 Oleh Buhaienko");
MODULE_DESCRIPTION("Laboratorna robota 3");
MODULE_LICENSE("GPL");

struct timing_data {
    struct list_head list_node;
    ktime_t begin_time;
    ktime_t finish_time;
};

static struct list_head head_node = LIST_HEAD_INIT(head_node);

int print_hello(uint total) 
{
    struct timing_data *item, *temp_item; 
    uint index; 

    // Validating 'total' parameter
    if (total == 0) {
        pr_err("Invalid 'total': must be greater than 0\n");
        return -EINVAL;
    } else if (total < 5) {
        pr_info("'total' is less than 5\n");
    } else if (total <= 10) {
        pr_warn("'total' is between 5 and 10\n");
    } else { 
        pr_err("'total' exceeds 10\n");
        return -EINVAL;
    }

    for (index = 0; index < total; index++) {
        item = kmalloc(sizeof(struct timing_data), GFP_KERNEL);
        if (!item) { // Checking if kmalloc returned NULL
            goto handle_error;
        }
        item->begin_time = ktime_get();
        pr_info("Processing entry number: %u\n", index);
        item->finish_time = ktime_get();
        list_add_tail(&item->list_node, &head_node);
    }
    return 0;

handle_error: 
    pr_err("Memory allocation failed\n");
    list_for_each_entry_safe(item, temp_item, &head_node, list_node) {
        list_del(&item->list_node);
        kfree(item);
    }
    return -ENOMEM;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void) 
{
    pr_info("hello1 module initializing\n");
    return 0;
}

static void __exit hello1_exit(void) 
{
    struct timing_data *item, *temp_item; 

    list_for_each_entry_safe(item, temp_item, &head_node, list_node) {
        pr_info("Execution duration: %lld ns\n", ktime_to_ns(item->finish_time - item->begin_time));
        list_del(&item->list_node);
        kfree(item);
    }
    BUG_ON(!list_empty(&head_node));
    pr_info("hello1 module removed\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

