#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/vmmeter.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <util.h>

struct uvmexp uvm;
int64_t phy_mem;
int64_t used_mem;
int64_t free_mem;
int64_t swap;
int64_t used_swap;
int64_t free_swap;

void output(char mode, int64_t size)
{
    char *human_size;
    switch (mode)
    {
    case 'm':
        printf("%18lld", size / (1024 * 1024));
        break;
    default:
        human_size = malloc(FMT_SCALED_STRSIZE);
        fmt_scaled(size, human_size);
        printf("%18s", human_size);
        free(human_size);
        break;
    }
}

void usage(void)
{
    fprintf(stderr, "usage: free [-m]\n");
    exit(1);
}

int main(int argc, char **argv)
{
    int mib[2];
    size_t len;
    char mode = 'h';

    if (pledge("stdio ps vminfo", NULL) == -1)
    {
        err(1, "pledge");
    }

    if (argc > 2)
    {
        usage();
    }
    else if (argc == 2)
    {
        if (!strcmp(argv[1], "-m"))
        {
            mode = 'm';
        }
        else
        {
            usage();
        }
    }

    mib[0] = CTL_HW;
    mib[1] = HW_PHYSMEM64;
    len = sizeof(phy_mem);
    if (sysctl(mib, 2, &phy_mem, &len, NULL, 0) == -1)
    {
        err(1, "sysctl");
    }

    mib[0] = CTL_VM;
    mib[1] = VM_UVMEXP;
    len = sizeof(uvm);

    if (pledge("stdio vminfo", NULL) == -1)
    {
        err(1, "pledge");
    }

    if (sysctl(mib, 2, &uvm, &len, NULL, 0) == -1)
    {
        err(1, "sysctl");
    }

    if (pledge("stdio", NULL) == -1)
    {
        err(1, "pledge");
    }

    free_mem = (int64_t)uvm.pagesize * uvm.free;
    used_mem = phy_mem - free_mem;

    swap = (int64_t)uvm.pagesize * uvm.swpages;
    used_swap = (int64_t)uvm.pagesize * uvm.swpginuse;
    free_swap = swap - used_swap;

    printf("        %18s%18s%18s\n", "total", "used", "free");

    printf("Mem:    ");
    output(mode, phy_mem);
    output(mode, used_mem);
    output(mode, free_mem);
    printf("\n");
    
    printf("Swap:   ");
    output(mode, swap);
    output(mode, used_swap);
    output(mode, free_swap);
    printf("\n");

    return 0;
}

