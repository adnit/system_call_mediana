#include <linux/sort.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

asmlinkage long sys_mediana(int __user *array, size_t size, int __user *result)
{
    if (array == NULL || size == 0)
        return -EINVAL;

    // Allocate memory to store the array
    int *karray = kmalloc(size * sizeof(int), GFP_KERNEL);
    if (karray == NULL)
        return -ENOMEM;

    // Copy the array from user space to kernel space
    int ret = copy_from_user(karray, array, size * sizeof(int));
    if (ret != 0) {
        kfree(karray);
        return -EFAULT;
    }

    // Sort the array
    sort(karray, size, sizeof(int), cmp_int, NULL);

    // Calculate the median
    int median;
    if (size % 2 == 0)
        median = (karray[size / 2 - 1] + karray[size / 2]) / 2;
    else
        median = karray[size / 2];

    // Copy the result back to user space
    ret = copy_to_user(result, &median, sizeof(int));
    if (ret != 0) {
        kfree(karray);
        return -EFAULT;
    }

    // Free the memory and return success
    kfree(karray);
    return 0;
}
