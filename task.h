struct task {			//process 
    int id;			//pid 
    int bt;			//burst time
    int at;			//arrival time
    int pr;			//priority
};
typedef struct task Task;
typedef Task *TaskPtr;
