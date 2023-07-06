#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

int main(int argc, const char * argv[]) {
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                        (host_info64_t)&vm_stats, &count))
    {
        long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;

        long long used_memory = ((int64_t)vm_stats.active_count +
                                 (int64_t)vm_stats.inactive_count +
                                 (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
        printf("free memory: %lld\nused memory: %lld\n", free_memory, used_memory);
    }

    return 0;
}


// total virtual currently used
// xsw_usage vmusage = {0};
// size_t size = sizeof(vmusage);
// if( sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0)!=0 )
// {
//    perror( "unable to get swap usage by calling sysctlbyname(\"vm.swapusage\",...)" );
// }


// VM currently used 

// #include<mach/mach.h>

// struct task_basic_info t_info;
// mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

// if (KERN_SUCCESS != task_info(mach_task_self(),
//                               TASK_BASIC_INFO, (task_info_t)&t_info,
//                               &t_info_count))
// {
//     return -1;
// }
// // resident size is in t_info.resident_size;
// // virtual size is in t_info.virtual_size;