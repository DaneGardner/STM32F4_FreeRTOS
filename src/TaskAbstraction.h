#ifndef TASKABSTRACTION_H_
#define TASKABSTRACTION_H_

#define TASKCB_MAXPRIORITY 256
#define TASKCB_MINPRIORITY 0
#define TASKCB_INITTASKS ((TASKCB_MAXPRIORITY - TASKCB_MINPRIORITY) / 4)
#define TASKCB_STARTTASKS ((TASKCB_MAXPRIORITY - TASKCB_MINPRIORITY) / 2)

typedef void (*functionCB_t)(void);

typedef struct {
    functionCB_t function;
    uint32_t priority;
} taskCB_t;

// Defined in the linker script
extern taskCB_t __taskCB_start__[], __taskCB_end__[];

#define __define_taskCB(pri,func) \
    static taskCB_t __taskCB_##func \
        __attribute__((__used__)) \
        __attribute__((__section__(".taskCB.init"))) = { .function = func, .priority = pri };

#define TASKCB(pri,func) __define_taskCB(pri,func)

static uint32_t cbcmp(const taskCB_t *left, const taskCB_t *right)
{
    if(left->priority > right->priority) {
        return 1;
    } else if(left->priority < right->priority) {
        return -1;
    }
    return 0;
}

static inline void taskCallbackAll(uint32_t min = TASKCB_MINPRIORITY, uint32_t max = TASKCB_MAXPRIORITY);

static inline void taskCallbackAll(uint32_t min, uint32_t max)
{
    if(!(__taskCB_end__ - __taskCB_start__)) {
        return;
    }

    // Create the local buffer that we can sort
    taskCB_t *taskCBs[__taskCB_end__ - __taskCB_start__];

    // Populate the buffer
    uint32_t index = 0;
    for(taskCB_t *func = __taskCB_start__; func < __taskCB_end__; ++func) {
        taskCBs[index++] = func;
    }

    // Sort the task callbacks by priority
    //TODO: This adds 1.5k to the binary!  There might be a better way to do this.
    qsort(taskCBs, sizeof(taskCBs), sizeof(taskCB_t *), (int(*)(const void*, const void*))cbcmp);

    // Execute the buffer functions in order
    for(index = 0; index < sizeof(taskCBs); ++index) {
        taskCB_t *taskCB = taskCBs[index]
        if(taskCB && taskCB->priority => min && taskCB->priority <= max) {
            functionCB_t function = taskCB->function;
            if(function) {
                (function)();
            }
        }
    }
}

#endif