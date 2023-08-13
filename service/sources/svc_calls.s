.syntax unified
.cpu cortex-m3
.thumb

.global OS_SVC_startScheduler
.global OS_SVC_createTask

.global OS_SVC_createMutex
.global OS_SVC_lockMutex
.global OS_SVC_releaseMutex

.global OS_SVC_createSemaphore
.global OS_SVC_takeSemaphore
.global OS_SVC_giveSemaphore

.global OS_SVC_createMailbox
.global OS_SVC_writeMailbox
.global OS_SVC_readMailbox

.global OS_SVC_delayTask
.global OS_SVC_destroyTask

.global OS_SVC_setTaskPriority

.text

.type OS_SVC_startScheduler, %function
OS_SVC_startScheduler:
    svc 0
    bx lr

.type OS_SVC_createTask, %function
OS_SVC_createTask:
    svc 1
    bx lr

.type OS_SVC_createMutex, %function
OS_SVC_createMutex:
    svc 2
    bx lr

.type OS_SVC_lockMutex, %function
OS_SVC_lockMutex:
    svc 3
    bx lr

.type OS_SVC_releaseMutex, %function
OS_SVC_releaseMutex:
    svc 4
    bx lr

.type OS_SVC_createSemaphore, %function
OS_SVC_createSemaphore:
    svc 5
    bx lr

.type OS_SVC_takeSemaphore, %function
OS_SVC_takeSemaphore:
    svc 6
    bx lr

.type OS_SVC_giveSemaphore, %function
OS_SVC_giveSemaphore:
    svc 7
    bx lr

.type OS_SVC_createMailbox, %function
OS_SVC_createMailbox:
    svc 8
    bx lr

.type OS_SVC_writeMailbox, %function
OS_SVC_writeMailbox:
    svc 9
    bx lr

.type OS_SVC_readMailbox, %function
OS_SVC_readMailbox:
    svc 10
    bx lr

.type OS_SVC_delayTask, %function
OS_SVC_delayTask:
    svc 11
    bx lr

.type OS_SVC_destroyTask, %function
OS_SVC_destroyTask:
    svc 12
    bx lr

.type OS_SVC_setTaskPriority, %function
OS_SVC_setTaskPriority:
    svc 13
    bx lr
