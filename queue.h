struct qnode {			//a node in the run/ready queue
    Task data;			//process
    struct qnode *nextPtr;
};
typedef struct qnode Qnode;
typedef Qnode *QnodePtr;

void enqueue(QnodePtr * headPtr, QnodePtr * tailPtr, Task task, int sort_by);
Task dequeue(QnodePtr * headPtr, QnodePtr * tailPtr);
int isEmpty(QnodePtr headPtr);

#define FIFO 0
#define SJF 1
#define RR 2
