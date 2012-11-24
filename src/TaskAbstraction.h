#ifndef TASKABSTRACTION_H_
#define TASKABSTRACTION_H_

typedef void (*initcall_t)(void);
typedef struct {
    initcall_t fn_init;
    initcall_t fn_start;
} inittask_t;


// Defined in the linker script
extern inittask_t __task_initcall_start__[], __task_initcall_end__[];


#define __define_task_initcall(fnInit, fnStart) \
    static inittask_t __initcall_##fnInit __attribute__((__used__)) \
    __attribute__((__section__(".initcalltask.init"))) = { .fn_init = fnInit, .fn_start = fnStart };

#define TASK_CALLBACK(fnInit, fnStart) __define_task_initcall(fnInit, fnStart)

#define taskInitializeAll() { for (inittask_t *fn = __task_initcall_start__; fn < __task_initcall_end__; fn++) if (fn->fn_init) (fn->fn_init)(); }

#define taskStartAll() { for (inittask_t *fn = __task_initcall_start__; fn < __task_initcall_end__; fn++) if (fn->fn_start) (fn->fn_start)(); }


#endif