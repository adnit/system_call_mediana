#include <linux/sort.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

asmlinkage long sys_mediana(size_t size, int __user *array, int __user *result)
{
    int median;
    if (arr == NULL || n <= 0)
        return -EINVAL;

    if (!access_ok(VERIFY_READ, arr, n * sizeof(int)))
        return -EFAULT;
    
    sort(arr, arr + n, cmp_int, NULL);

    if (n % 2 == 0)
        median = (arr[n / 2] + arr[n / 2 - 1]) / 2;
    else
        median = arr[n / 2];

    return median;
}

