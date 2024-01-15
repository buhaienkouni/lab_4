// SPDX-License-Identifier: GPL-2-Clause
#include <hello1.h>

MODULE_AUTHOR("IO-16 Oleh Buhaienko");
MODULE_DESCRIPTION("Laboratorna robota 3");
MODULE_LICENSE("GPL");

static uint total = 1; 

module_param(total, uint, 0);
MODULE_PARM_DESC(total, "Execution count for lab work 4\n"); 

static int __init initialize_hello_module(void) 
{
    pr_info("hello2 module initializing\n"); 
    print_hello(total); 
    return 0;
}

static void __exit finalize_hello_module(void) 
{
    pr_info("hello2 module finalizing\n");
}

module_init(initialize_hello_module);
module_exit(finalize_hello_module);

