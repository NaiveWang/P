#include "PVM.h"
void *mutexHandler()
{
  /*int c0,c1;
  for(;;)
  {
    //wait for the handler lock
    pthread_mutex_lock(&rtLock);
    //wait the mutex of queue
    pthread_mutex_lock(&qLock);
    //do the job
    printf("Handling!!!%d %d\n",queueH,queueT);
    while(queueH-queueT)
    {
      //some thing on queue handle one node of it
      //branch, get the resource or wait?
      switch(waitingQueue[queueT].opTyp)
      {
        case MTX_HDL_TYP_WAIT://wait procedure
          //look up the mutex lock
          if(waitingQueue[queueT].mTarget->lock)
          {
            //non-zero, wait
            //put the instance info into the tail
            if(waitingQueue[queueT].mTarget->waitList)
            {
              waitL *wlp = waitingQueue[queueT].mTarget->waitList;
              //there are some node here
              //find tail
              while(wlp->next) wlp = wlp->next;
              wlp->next = malloc(sizeof(waitL));
              wlp = wlp->next;
              wlp->next = NULL;
              wlp->pid = waitingQueue[queueT].pid;
            }
            else
            {
              //there are no node, just initlize it.
              waitingQueue[queueT].mTarget->waitList = malloc(sizeof(waitL));
              //assign the value
              waitingQueue[queueT].mTarget->waitList->next=NULL;
              waitingQueue[queueT].mTarget->waitList->pid = waitingQueue[queueT].pid;
            }
            //leave the status to wait(nop)
          }
          else
          {
            //zero, take the bun!
            //set the lock
            waitingQueue[queueT].mTarget->lock = waitingQueue[queueT].pid;
            //set the status to running
            waitingQueue[queueT].pid->status = PROCESSOR_STATUS_RUNNING;
            waitingQueue[queueT].pid->performance = INITIAL_PERFORMANCE_VAL;
          }
          break;
        case MTX_HDL_TYP_TEST:
          //test, always set running at least
          //set what ? flag!!!!!!
          //branch, if the mutex is vacant
          if(waitingQueue[queueT].mTarget->lock)
          {
            //locked, set flag to 0
            waitingQueue[queueT].pid->eflag = 0;
          }
          else
          {
            //bingo
            //set the lock
            waitingQueue[queueT].mTarget->lock = waitingQueue[queueT].pid;
            //set flag to -1
            waitingQueue[queueT].pid->eflag = -1;
          }
          //always set the status to runnning
          waitingQueue[queueT].pid->status = PROCESSOR_STATUS_RUNNING;
          waitingQueue[queueT].pid->performance = INITIAL_PERFORMANCE_VAL;
          break;
        case MTX_HDL_TYP_LEAVE:
          //set the lock to zero
          waitingQueue[queueT].mTarget->lock = NULL;
          //set the current instance to running status
          waitingQueue[queueT].pid->status = PROCESSOR_STATUS_RUNNING;
          waitingQueue[queueT].pid->performance = INITIAL_PERFORMANCE_VAL;
          //if there is any thing on waiting list, get it with lock
          if(waitingQueue[queueT].mTarget->waitList)
          {
            waitL *wlp;
            //something, give it to it
            wlp = waitingQueue[queueT].mTarget->waitList;
            waitingQueue[queueT].mTarget->lock = wlp->pid;
            wlp->pid->status = PROCESSOR_STATUS_RUNNING;
            waitingQueue[queueT].mTarget->waitList = waitingQueue[queueT].mTarget->waitList->next;
            free(wlp);
          }
          break;
        /*case TRIGGER:
        //handle with trigger
          //add the value into every next processor
          printf("OOO");
          for(c0=0;&listInstance[c0]!=waitingQueue[queueT].pid;c0++);
          //modify related instance trigger value
          for(c1=0;c1<triggerList[c0].number;c1++)
          {
            //increase the value of list
            listInstance[triggerList[c0].list[c1]].currentVal++;
          }
          //loop : scan the instances

          for(c0=0;c0<listInstanceSize;c0++)
          {
            //condition : suspended/match the value
            if(listInstance[c0].status == PROCESSOR_STATUS_SUSPENDED && listInstance[c0].triggerVal == listInstance[c0].currentVal)
            {
              //set it running,
              listInstance[c0].status = PROCESSOR_STATUS_RUNNING;
              //change the current val to 0
              listInstance[c0].currentVal = 0;
            }
          }
          break;
        default : ;//error halt;
      }
      //delete one of the node
      queueT++;
      queueT %= M_WAITING_LIST_SIZE;
    }
    //unlock mutex
    pthread_mutex_unlock(&qLock);
    //ground self
    pthread_mutex_lock(&rtLock);
    printf("handler ended\n");
  }*/
  //here is the new one
  for(;;)
  {
      //infinite loop
      //get the execution permission
      pthread_mutex_lock(&rtExecLock);
      //do the job
      //read arguments global arguments
      switch(mutexHandlerArg.opTyp)
      {
          case MTX_HDL_TYP_WAIT:
            //test the mutex status
            if(mutexHandlerArg.mTarget->lock==NULL)
            {
                //can take over
                //take over
                mutexHandlerArg.mTarget->lock=mutexHandlerArg.pid;
                //set status to running
                mutexHandlerArg.pid->status=PROCESSOR_STATUS_RUNNING;
                mutexHandlerArg.pid->performance=INITIAL_PERFORMANCE_VAL;
            }
            else
            {
                //need wait, put it on the waiting list
                //list is empty?
                if(mutexHandlerArg.mTarget->waitList==NULL)
                {
                    //empty, set the first element
                    mutexHandlerArg.mTarget->waitList = malloc(sizeof(waitL));
                    mutexHandlerArg.mTarget->waitList->next=NULL;
                    mutexHandlerArg.mTarget->waitList->pid=mutexHandlerArg.pid;
                }
                else
                {
                    //find the tail
                    waitL *p = mutexHandlerArg.mTarget->waitList;
                    while(p->next) p=p->next;
                    p->next = malloc(sizeof(waitL));
                    p->next->next=NULL;
                    p->next->pid=mutexHandlerArg.pid;
                }
            }
            break;
          case MTX_HDL_TYP_TEST:
            //test if it has been take over
            if(mutexHandlerArg.mTarget->lock==NULL)
            {
                //can take over
                //take over
                mutexHandlerArg.mTarget->lock=mutexHandlerArg.pid;
                //set flag to -1
                mutexHandlerArg.pid->eflag=-1;
            }
            else
            {
                //can not take over
                //set flag to 0
                mutexHandlerArg.pid->eflag=0;
            }
            //no matter what happened, set status to running
            mutexHandlerArg.pid->status=PROCESSOR_STATUS_RUNNING;
            mutexHandlerArg.pid->performance=INITIAL_PERFORMANCE_VAL;
            break;
          case MTX_HDL_TYP_LEAVE:
              //set the master instance's status to running
              mutexHandlerArg.pid->status=PROCESSOR_STATUS_RUNNING;
              mutexHandlerArg.pid->performance=INITIAL_PERFORMANCE_VAL;
              //look up the list(branch)
              if(mutexHandlerArg.mTarget->waitList==NULL)
              {
                  //waiting list empty
                  //just set lock to empty
                  mutexHandlerArg.mTarget->lock=NULL;
              }
              else
              {
                  waitL *p=mutexHandlerArg.mTarget->waitList;
                  //someone are waiting
                  //put the guy to lock
                  mutexHandlerArg.mTarget->lock=p->pid;
                  mutexHandlerArg.mTarget->waitList = p->next;
                  //set this guy running
                  p->pid->status=PROCESSOR_STATUS_RUNNING;
                  p->pid->performance=INITIAL_PERFORMANCE_VAL;
                  //release memory
                  free(p);
              }
              break;
          default:;//awake error handler
      }
      //release the mutex
      pthread_mutex_unlock(&rtLock);
  }
  //
}
void VMReadFile(char *file)
{
  int c0;
  //get file
  VMpe=parseFile(file);
  //checkStructure(VMpe);
  //initialize the code list
  c0=VMpe->processorTemplateNum;
  listCode = malloc(sizeof(void*) * c0);
  //getchar();
  while(c0--)
  {
    *(listCode+c0)=(VMpe->processorTemplates + c0)->code;
  }//getchar();
  //initialaze the mutex list
  c0=VMpe->mutexNum;
  listMutex=malloc(sizeof(mutex) * c0);
  while(c0--)
  {
    (listMutex + c0)->lock = NULL;
    (listMutex + c0)->size = *(VMpe->mutexSizeList + c0);
    (listMutex + c0)->content = malloc((listMutex + c0)->size);
    (listMutex + c0)->waitList = NULL;
  }

  //initialize the instance list
  //allocate the space
  listInstanceSize = VMpe->processorInstanceNUM;
  listInstance = malloc(sizeof(PBase) * listInstanceSize);
  printf("%d\n",listInstanceSize);//getchar();
  for(c0=0;c0<listInstanceSize;c0++)
  {
    //allocate data section.
    ///listInstance[c0].data = malloc(VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].dataSize);
    //assign value
    listInstance[c0].code = VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].code;
    listInstance[c0].pc = VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].code;//getchar();
    listInstance[c0].PID = &listInstance[c0];
    listInstance[c0].status = VMpe->processorInstances[c0].initStatus;
    listInstance[c0].eflag = 0;
    listInstance[c0].triggerVal=0;
    listInstance[c0].currentVal=0;
    listInstance[c0].performance=INITIAL_PERFORMANCE_VAL;
    //allocate data space!
    listInstance[c0].data=malloc(
      VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size+
      VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stackSize+
      VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].globalSize+
      256*sizeof(void*));
    {
      void* *ap = listInstance[c0].data;
      //PRINTADDR(listInstance[c0].data);
      //PRINTADDR(ap);
      //PRINTADDR(ap[0]);
      //data r
      ap[0] = listInstance[c0].data;
      //ap+=sizeof(void*);
      //PRINTADDR(ap[0]);
      //PRINTADDR(*(long*)listInstance[c0].data);
      //stack0 base pointer
      ap[1] = listInstance[c0].data + 256 * 8;
      //ap++;
      //stack0 pointer
      ap[2] = listInstance[c0].data + 256 * 8;
      //ap++;
      //stack base pointer
      ap[3] = listInstance[c0].data + 256 * 8 + VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size;
      //ap++;
      //stack pointer
      ap[4] = listInstance[c0].data + 256 * 8 + VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size;
      //ap++;
      //global base pointer
      ap[5] = listInstance[c0].data + 256 * 8 +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stack0Size +
        VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].stackSize;
      //ap++;
      //constant/string base pointer.
      //ap++;
    }
    {
      int c1;
      void* *dataBase = listInstance[c0].data;//global data base is at [5]
      //printf("\t%d\n",VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initNumGlobal);
      for(c1=0;c1<VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initNumGlobal;c1++)
      {
        //printf(")%d()%d(\n",VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].offset,VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].length);
        //printf("X%ldX\n",*(long*)VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].data);
        memmove(
          (char*)dataBase[5]+VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].offset,
          VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].data,
          VMpe->processorTemplates[VMpe->processorInstances[c0].processorReferenceNo].initDataGlobal[c1].length);
        //read global data
      }
      for(c1=0;c1<VMpe->processorInstances[c0].initNum;c1++)
      {
        memmove(
          (char*)dataBase[5]+VMpe->processorInstances[c0].initData[c1].offset,
          VMpe->processorInstances[c0].initData[c1].data,
          VMpe->processorInstances[c0].initData[c1].length);
        //read global data
      }
    }
  }
  //Connections
  for(c0=0;c0<VMpe->connectionMappingNum;c0++)
  {
    //find the address anyway
    void* addr;
    switch(VMpe->connectionMapping[c0].nodeDType)
    {
      case TYP_INST:
        addr = *(void**)(listInstance[VMpe->connectionMapping[c0].nodeDNo].data + 5 * sizeof(void*));
        break;
      case TYP_MUTEX:
        addr = (listMutex[VMpe->connectionMapping[c0].nodeDNo].content);
        break;
      default:
        printf("In connection %d : unknown reference type ID:%d\n",c0,VMpe->connectionMapping[c0].nodeDType);
        return;
    }//now we have got the address
    //put it on to the right instance
    *(void**)(listInstance[VMpe->connectionMapping[c0].nodeSNo].data + VMpe->connectionMapping[c0].nodeSPort * sizeof(void*))=addr;
  }
  //constraint
  //initialize the constrtaint
  //1.allocate a map
  triggerList = malloc(VMpe->processorInstanceNUM*sizeof(tgr));
  //set the block to zero
  //memset(constraintMap,0,VMpe->processorInstanceNUM * VMpe->processorInstanceNUM);
  //set the initlalized val to zero
  for(c0=0;c0<VMpe->processorInstanceNUM;c0++)
  {
    //set each trigger number to zero
    triggerList[c0].number=0;
    triggerList[c0].list = NULL;
  }
  for(c0=0;c0<VMpe->constraintNum;c0++)
  {
    static int c1;
    //put the number into
    triggerList[VMpe->constraintList[c0].nodeDNo].number = VMpe->constraintList[c0].nodeSNum;
    triggerList[VMpe->constraintList[c0].nodeDNo].list = malloc(sizeof(int) * VMpe->constraintList[c0].nodeSNum);
    for(c1=0;c1<VMpe->constraintList[c0].nodeSNum;c1++)
    {
      //heris the descent one
      triggerList[VMpe->constraintList[c0].nodeDNo].list[c1] = VMpe->constraintList[c0].nodeSNoList[c1];
      listInstance[VMpe->constraintList[c0].nodeSNoList[c1]].triggerVal++;
    }
  }
  //assign them to each instances
  for(c0=0;c0<VMpe->processorInstanceNUM;c0++)
  {
    //assign for each, just copy the address
    listInstance[c0].triggerNum = triggerList[c0].number;
    listInstance[c0].triggerList = triggerList[c0].list;
  }
}
void debugVM(PBase *p,int howManyStack0Elem)
{
  long* stack0p;
  printf("\nVM Debug Start\t");
  printf("ProcessorID:%lu/%d ",(unsigned long)p,p->performance);
  printf("Next Instruction P:%lx No:%hu\n",(long)p->pc,*(unsigned short*)p->pc);
  printf("Current Status:%x ",p->status);
  printf("Current Flag:%x ",(p->eflag>>8) & 0xFF);
  printf("datapointer : %lx \n",(long)(p->data));
  printf("Jumping val(maybe)%ld\n",*(long*)(p->pc+2));
  //printf("self0pointer:%lx \n",*(long*)(p->data));
  //PRINTADDR(*(long*)p->data);
  //printf("Stack0pointer : %lx \n",*(long*)(p->data + POINTER_STACK0));
  stack0p=(long*)*(long*)(p->data + POINTER_STACK0);
  printf("stack0TopValue :%lx:%lx:%ld/%lx/%ld\n",*(long*)(p->data+8),(long)stack0p,*(stack0p-1),*(stack0p-1),*(stack0p-1));
  printf("##%ld\t", *(long*)(p->data+40));
  /*while(howManyStack0Elem--)
  {
    printf("stack0:%lx\n",*stack0p);
    stack0p--;
  }*/
  printf("\nVM Debug End\n");
}
void *execDebug(void* no)
{
  int error=0;
  int ino = *(int*)no;
  while(!error)
  {//loop for each loadded processor
    //execute one thread
    printf("@%d\n",listInstance[ino].status);
    while(!listInstance[ino].status)//trap not invoked^^^^^^^^^^^
    {
      //printf("Trying one step...\n");
      debugVM(&listInstance[ino],4);
      executionOneStep(&listInstance[ino]);
      //printf("Ended.\n");
      //debugVM(&listInstance[ino],4);
      getchar();
      //scanf("\n");
    }
    ino+=NUM_E_THREAD;
    if(ino==listInstanceSize) ino = *(int*)no;
  }
}
void *execNormal(void *initPointer)
{
  /**
   * here is the execution function, it belongs to different thread
   * and the execution list cones to a circular link list
   */
  //values on the stack whlie running
  //int performance=INITIAL_PERFORMANCE_VAL;//how much step run on each instance
  int delay;//this attrbute means sleep how many ms for each circle scan
  IME *instanceMountingList;
  int a0,a1;
  int idleCounter;
  //initialize the list pointer
  instanceMountingList = (IME*)initPointer;
  /*for(;;)//update the structure of execution unit
  {//the execution step
    //check the info of performance
    //branch:idle or active
    if(performance)
    {
      printf("running id : %ld\n",*(long*)instanceMountingList->list->instance);
      //active section
      //execute current instance, switch
      //a0=performance;//resource counter
      /*while(a0)
      {
        //loop enabled block
        switch(instanceMountingList->list->instance->status)
        {
          case PROCESSOR_STATUS_RUNNING:
            //running
            //debugVM(instanceMountingList->list->instance,2);
            executionOneStep(instanceMountingList->list->instance);
            a0--;
            break;
          case PROCESSOR_STATUS_SYS:
            //system call
            APIHandler(instanceMountingList->list->instance);
            a0--;
            break;
          case PROCESSOR_STATUS_HALT:
            //halt the VM
            pthread_mutex_unlock(&haltLock);
            errno=0;
            //maybe here we need to modify some global variables.
            a0=-1;
            break;
          case PROCESSOR_STATUS_SUSPENDED:
            //instance was suspended
            //call the trigger handler
            pthread_mutex_lock(&qLock);
            //write the queue
            waitingQueue[queueH].pid = instanceMountingList->list->instance;
            waitingQueue[queueH].mTarget = NULL;
            waitingQueue[queueH].opTyp = TRIGGER;
            queueH++;
            queueH %= M_WAITING_LIST_SIZE;
            //awake the mutex handler
            pthread_mutex_unlock(&rtLock);
            pthread_mutex_unlock(&qLock);
            a0=-1;
            break;
          case PROCESSOR_STATUS_REBOOT:
            //instance is waiting for restart
            //do something????
            //change status to suspended
            instanceMountingList->list->instance->status=PROCESSOR_STATUS_SUSPENDED;
            break;
          case PROCESSOR_STATUS_MWAIT:
            //call the mutex handler
            //wait for the queue mutex
            pthread_mutex_lock(&qLock);
            //write the queue
            queueH++;
            queueH %= M_WAITING_LIST_SIZE;
            waitingQueue[queueH].pid = instanceMountingList->list->instance;
            waitingQueue[queueH].mTarget = (mutex*)instanceMountingList->list->instance->exAddr;
            waitingQueue[queueH].opTyp = MTX_HDL_TYP_WAIT;
            //awake the mutex handler
            pthread_mutex_unlock(&rtLock);
            pthread_mutex_unlock(&qLock);
            a0=-1;
            break;
          case PROCESSOR_STATUS_MTEST:
            //call the mutex handler
            pthread_mutex_lock(&qLock);
            //write the queue
            queueH++;
            queueH %= M_WAITING_LIST_SIZE;
            waitingQueue[queueH].pid = instanceMountingList->list->instance;
            waitingQueue[queueH].mTarget = (mutex*)instanceMountingList->list->instance->exAddr;
            waitingQueue[queueH].opTyp = MTX_HDL_TYP_TEST;
            //awake the mutex handler
            pthread_mutex_unlock(&rtLock);
            pthread_mutex_unlock(&qLock);
            a0=-1;
            break;
          case PROCESSOR_STATUS_MLEAVE:
            //call the mutex handler
            pthread_mutex_lock(&qLock);
            //write the queue
            queueH++;
            queueH %= M_WAITING_LIST_SIZE;
            waitingQueue[queueH].pid = instanceMountingList->list->instance;
            waitingQueue[queueH].mTarget = (mutex*)instanceMountingList->list->instance->exAddr;
            waitingQueue[queueH].opTyp = MTX_HDL_TYP_LEAVE;
            //awake the mutex handler
            pthread_mutex_unlock(&rtLock);
            pthread_mutex_unlock(&qLock);
            a0=-1;
            break;
          default:;//error/unknown status
        }
        if(a0 == -1) break;
      }*
      if(a0)
      {//runs properly
        //increase performance
        if(performance < MAX_PERFORMANCE_VAL)
          performance+=INITIAL_PERFORMANCE_VAL;
        a1=0;
      }
      else
      {
        //bump
        //set the performance to start
        performance = INITIAL_PERFORMANCE_VAL;
        a1++;
        if(a1==instanceMountingList->INumber)
        {
          //all processor are idle
          //set the performance to 0, goto the sleep section
          performance = 0;
          delay = INITIAL_DELAY_VAL;
        }
      }
      instanceMountingList->list = instanceMountingList->list->next;
      //TO DO : count the idle instance here
    }
    else
    {
      /*idle section*
      usleep(delay);printf("thread is slept\n");
      //loop : check the the list if exist one that is runnnig
      instanceMountingList->start = instanceMountingList->list;
      for(;;)
      {
        instanceMountingList->list = instanceMountingList->list->next;
        //check the instance status
        if(!instanceMountingList->list->instance->status)
        {
          //running instance detected
          performance = INITIAL_PERFORMANCE_VAL;
          break;
        }
        if(instanceMountingList->start - instanceMountingList->list)
          continue;//not to the end
        else
        {
          //the end, all instances are suspended
          //set the sleep time longer
          delay += INITIAL_DELAY_VAL;
          break;
        }
      }
    }
  }*/
  for(;;)
  {
    //running loop, check each of instance list
    if(delay)
    {
      //sleeping section
      //sleep
      usleep(delay);
      //check if exist any instance that at running state
      for(a0=0;a0<instanceMountingList->INumber;a0++)
      {
        if(instanceMountingList->list->instance->status==PROCESSOR_STATUS_RUNNING)
        {//detected
          //close the enable flag
          delay=0;
          //set performance to start value
          instanceMountingList->list->instance->performance = INITIAL_PERFORMANCE_VAL;
          //jump out
          break;
        }
        //check next
        instanceMountingList->list = instanceMountingList->list->next;
      }
      //deal with the situation : nobody was awake
      if(a0==instanceMountingList->INumber)
      {
        //increase the sleeping time
        if(delay<MAX_DELAY_VAL)//deal with : oops, sleeping to die
        {
          //increase it
          delay += INITIAL_DELAY_VAL;
        }
      }
    }
    else
    {
      //active section
      //execution section
      if(instanceMountingList->list->instance->performance)
      {
        //running section
        //set the counter to 0
        idleCounter=0;
        a0=instanceMountingList->list->instance->performance;
        //switch with status
        while(a0--)
        {//loop the n cycle
          //debugVM(instanceMountingList->list->instance,1);
          switch(instanceMountingList->list->instance->status)
          {
            case PROCESSOR_STATUS_RUNNING:
              //execution
              printf("$$$$$$$$$$$%d\n",instanceMountingList->list->instance->status);
              executionOneStep(instanceMountingList->list->instance);
              debugVM(instanceMountingList->list->instance,1);
              printf("???????????%d\n",instanceMountingList->list->instance->status);
              getchar();
              if(a0==0)
              {
                if(instanceMountingList->list->instance->performance<MAX_PERFORMANCE_VAL)
                  instanceMountingList->list->instance->performance+=INITIAL_PERFORMANCE_VAL;
                instanceMountingList->list = instanceMountingList->list->next;
              }
              break;
            case PROCESSOR_STATUS_SYS:
              //api calling
              APIHandler(instanceMountingList->list->instance);
              if(a0==0)
              {
                if(instanceMountingList->list->instance->performance<MAX_PERFORMANCE_VAL)
                  instanceMountingList->list->instance->performance+=INITIAL_PERFORMANCE_VAL;
                instanceMountingList->list = instanceMountingList->list->next;
              }
              break;
            default://meet up with the suspended section
              //set the counter to 0
              a0=0;
              //set the performance to 0
              instanceMountingList->list->instance->performance=0;
          }
        }
      }
      else
      {
        //suspended(board) section
        //increase the counter
        idleCounter++;
        //switch with status
        switch(instanceMountingList->list->instance->status)
        {
          case PROCESSOR_STATUS_HALT:
            pthread_mutex_unlock(&haltExecLock);
            errno=0;
            return NULL;
            break;
          case PROCESSOR_STATUS_SUSPENDED:
            //loop, search each "next instance"
            for(a0=0;a0<instanceMountingList->list->instance->triggerNum;a0++)
            {
              printf("awaking.............%ld\n",instanceMountingList->list->instance);
              if(listInstance[instanceMountingList->list->instance->triggerList[a0]].status == PROCESSOR_STATUS_SUSPENDED)
              {
                //suspended & was the chosen one
                //here is the mutex section
                //
                pthread_mutex_lock(&triggerLock);
                listInstance[instanceMountingList->list->instance->triggerList[a0]].status = PROCESSOR_STATUS_RUNNING;
                pthread_mutex_unlock(&triggerLock);
              }
            }
            break;
          //case PROCESSOR_STATUS_REBOOT:break;
          case PROCESSOR_STATUS_MWAIT:
            pthread_mutex_lock(&rtLock);
            //queueH++;
            //queueH %= M_WAITING_LIST_SIZE;
            mutexHandlerArg.pid = instanceMountingList->list->instance;
            mutexHandlerArg.mTarget = (mutex*)instanceMountingList->list->instance->exAddr;
            mutexHandlerArg.opTyp = MTX_HDL_TYP_WAIT;
            //awake the mutex handler
            pthread_mutex_unlock(&rtExecLock);
            //pthread_mutex_unlock(&qLock);
            break;
          case PROCESSOR_STATUS_MTEST:
            //
            pthread_mutex_lock(&rtLock);
            //queueH++;
            //queueH %= M_WAITING_LIST_SIZE;
            mutexHandlerArg.pid = instanceMountingList->list->instance;
            mutexHandlerArg.mTarget = (mutex*)instanceMountingList->list->instance->exAddr;
            mutexHandlerArg.opTyp = MTX_HDL_TYP_TEST;
            //awake the mutex handler
            pthread_mutex_unlock(&rtExecLock);
            //pthread_mutex_unlock(&qLock);
            break;
          case PROCESSOR_STATUS_MLEAVE:
            pthread_mutex_lock(&rtLock);
            //queueH++;
            //queueH %= M_WAITING_LIST_SIZE;
            mutexHandlerArg.pid = instanceMountingList->list->instance;
            mutexHandlerArg.mTarget = (mutex*)instanceMountingList->list->instance->exAddr;
            mutexHandlerArg.opTyp = MTX_HDL_TYP_LEAVE;
            //awake the mutex handler
            pthread_mutex_unlock(&rtExecLock);
            //pthread_mutex_unlock(&qLock);
            //a0=-1;
            break;
            default:;//error handler
        }
      }
      //move to next instance
      instanceMountingList->list = instanceMountingList->list->next;
      //check the counter if all of the instance are slept
      if(idleCounter==instanceMountingList->INumber)
      {
        //sleep ready!
        delay = INITIAL_DELAY_VAL;
      }
    }
  }
}
void dispatcher()
{
  int c0,c1;
  char *tagL;
  char tag0;
  ///put the instance into each thread link list
  //initialize the instance structure
  for(c0=0;c0<NUM_E_THREAD;c0++)
  {
    //initialize each of them
    executionGroup[c0].INumber=0;
    executionGroup[c0].start=NULL;
    executionGroup[c0].list=NULL;
  }
  //graph operation : modify put it into each mounting list
  //initialize the tag list
  tagL = malloc(listInstanceSize);
  for(c0=0;c0<listInstanceSize;c0++)
  {
    if(listInstance[c0].status == PROCESSOR_STATUS_RUNNING)
    {
      //the start point found
      //this section may cause error : all instances are sleeping
      //tag0=0;
      tagL[c0]=1;
    }
    else tagL[c0]=-1;
  }
  //set the instance dispatching pointer
  c0=0;
  //set the stop sign to 0
  tag0=-1;
  //loop : first round, initializer
  //for(c0=0)
  //loop : start
  while(tag0)
  {
    //assume stop at next round
    tag0=~tag0;
    //loop1:add the marked dot into group
    for(c1=0;c1<listInstanceSize;c1++)
    {
      //find it with value 1
      if(tagL[c1]==1)
      {
        //found one
        //add them to the group
        //here is the adding section(link list operation)
        if(executionGroup[c0].start)
        {
          IMLList *auxptr;
          //there has been at least one element in it
          auxptr = executionGroup[c0].list->next;
          executionGroup[c0].INumber++;
          executionGroup[c0].list->next = malloc(sizeof(IMLList));
          executionGroup[c0].list->next->next = auxptr;
          executionGroup[c0].list->next->instance = &listInstance[c1];
        }
        else
        {
          //this mounter is rookie
          executionGroup[c0].INumber++;
          executionGroup[c0].start = malloc(sizeof(IMLList));
          executionGroup[c0].list = executionGroup[c0].start;
          executionGroup[c0].start->instance = &listInstance[c1];
          executionGroup[c0].start->next = executionGroup[c0].start;
        }
        //move the execution group cursor
        c0++;
        c0%=NUM_E_THREAD;
      }
    }
    /**debug section start**
    //print the tag list
    for(c1=0;c1<listInstanceSize;c1++)
    {
      //print each tag of them
      printf("%d/",tagL[c1]);
    }
    //round mark
    printf("\n");
    /**debug section ended**/
    //loop2:find new element
    for(c1=0;c1<listInstanceSize;c1++)
    {
      //find elem with 1
      if(tagL[c1]==1)
      {
        //if there are something in the trigger list
        //printf("%d!%d!%d!%d\n",*tagL,tagL[1],tagL[2],tagL[3]);
        //set it self to 0
        tagL[c1]=0;
        if(triggerList[c1].number)
        {
          //loop, modify the trigger list
          int c2;
          for(c2=0;c2<triggerList[c1].number;c2++)
          {
            //printf("%dWTF\n",tagL[triggerList[c1].list[c2]]);
            //if the instance is new, set it to 1
            if(tagL[triggerList[c1].list[c2]]==-1)
            {
              //set it to 1
              tagL[triggerList[c1].list[c2]]=2;
              tag0=-1;
            }
          }
        }
      }
    }
    //loop 3 : set all the new fellow to the formal state
    for(c1=0;c1<listInstanceSize;c1++)
    {
      if(tagL[c1]==2) tagL[c1]--;
    }
  }
}
void VMStartUp()
{
  //loop :
  int a0;
  //check each thread dispatcher,
  //create the thread which has non-zero list
  for(a0=0;a0<NUM_E_THREAD;a0++)
  {
    //check each group
    if(executionGroup[a0].INumber)
    {
      //run the thread!
      printf("creating %d ...\n",a0);
      pthread_create(&executionThread[a0],NULL,execNormal,&executionGroup[a0]);
    }
  }
  //halt handller
  pthread_mutex_init(&haltExecLock,NULL);
  pthread_mutex_lock(&haltExecLock);
  pthread_mutex_init(&triggerLock,NULL);
  pthread_mutex_init(&rtLock,NULL);
  pthread_mutex_init(&rtExecLock,NULL);
  pthread_mutex_lock(&rtExecLock);
  pthread_create(&haltT,NULL,VMHalt,NULL);
  pthread_create(&mutexT,NULL,mutexHandler,NULL);
  pthread_join(haltT,NULL);
}
void *VMHalt()
{
  int a0;
  //kill all of the thread
  //kill handler
  pthread_mutex_lock(&haltExecLock);
  pthread_kill(mutexT,SIGUSR1);
  pthread_join(mutexT,NULL);
  //kill execution thread if it is in the running mode
  for(a0=0;a0<NUM_E_THREAD;a0++)
  {
    //check each group
    if(executionGroup[a0].INumber)
    {
      //run the thread!
      pthread_kill(executionThread[a0],SIGUSR1);
      pthread_join(executionThread[a0],NULL);
    }
  }
  pthread_exit(NULL);
}
void handlerSegFault(int a)
{
  //signal();
  printf("bad behavor while accessing memory.\n");
  //call the exit thread
  pthread_mutex_unlock(&haltExecLock);
  pthread_join(haltT,NULL);
  releaseMemory();
  exit(-1);
}
void releaseMemory()
{
  //assume that vmpe has already released
  //free code section
  int a0,a1;
  for(a0=0;a0<listCodeSize;a0++)
    free(listCode[a0]);
  free(listCode);
  for(a0=0;a0<listMutexSize;a0++)
  {
    //free data section
    free(listMutex[a0].content);
    //free the waiting list, if it exist
    while(listMutex[a0].waitList)
    {
      waitL* p = listMutex[a0].waitList;
      listMutex[a0].waitList = listMutex[a0].waitList->next;
      free(p);
    }
  }
  free(listMutex);
  //instance
  for(a0=0;a0<listInstanceSize;a0++)
  {
    //free data section
    free(listInstance[a0].data);
    //trigger list inner data
    if(triggerList[a0].number)
      free(triggerList[a0].list);
  }
  free(listInstance);
}
void debugPrintConstraint()
{
  //debug section
  int a0,a1;
  //print all of the instance firstly
  for(a0=0;a0<listInstanceSize;a0++)
  {
    //print each address of the instance
    printf("No.%d/%ld\n",a0,(long)&listInstance[a0]);
  }
  for(a0=0;a0 < listInstanceSize;a0++)
  {
    //print each instance
    printf("No.%d/%d:",a0,triggerList[a0].number);
    for(a1=0;a1<triggerList[a0].number;a1++)
    {
      printf("%d/",triggerList[a0].list[a1]);
    }
    printf("\n");
  }
}
void debugPrintMountingList()
{
  //print all of the mounting table
  int a0,a1;
  for(a0=0;a0<NUM_E_THREAD;a0++)
  {
    //each mounting group
    printf("Group %d/%d:",a0,executionGroup[a0].INumber);
    if(executionGroup[a0].INumber)
    {
      executionGroup[a0].list = executionGroup[a0].start;
      do
      {
        /* code */
        executionGroup[a0].list = executionGroup[a0].list->next;
        printf("%ld/",(long)executionGroup[a0].list->instance);
      }
      while(executionGroup[a0].list - executionGroup[a0].start);
    }
    //view all of the element
    printf("\n");
  }
}
void graphStartUp(int* argc,char **argv)
{
  //initialize section
  glutInit(argc,argv);
}
void graphShape(int w,int h)
{
  //
  glViewport(1,1,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1,graph_size,-1,graph_size);
  glMatrixMode(GL_MODELVIEW);
}
void graphDrawInstance(int id)
{
  //set the color
  static float dot_size;
  glColor3f(1.0f,
    1.0-((float)listInstance[id].performance/(float)MAX_PERFORMANCE_VAL),
    1.0-((float)listInstance[id].performance/(float)MAX_PERFORMANCE_VAL));
  //printf("$%f$\n",(listInstance[id].performance/(float)MAX_PERFORMANCE_VAL));
  dot_size = graph_size/40;
  glBegin(GL_QUADS);
  glVertex2f(gpp[id].x,gpp[id].y);
  glVertex2f(gpp[id].x+dot_size,gpp[id].y);
  glVertex2f(gpp[id].x+dot_size,gpp[id].y+dot_size);
  glVertex2f(gpp[id].x,gpp[id].y+dot_size);
  glEnd();
}
void graphDisp()
{
  static int a0;
  for(;;)
  {
    usleep(GRAPH_SLEEPING_TIME);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    for(a0=0;a0<listInstanceSize;a0++)
    {
      //draw each dot
      graphDrawInstance(a0);
      //printf("%d/%d\n",a0,listInstance[a0].performance);
    }
    glFlush();
  }
}
void *graphMonitor()
{
  //initializing section
  //glut main loop
  //reshape func
  //reshape
  //for(;;)
  //{
  int n,a0;
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(GRAPH_WINDOW_L,GRAPH_WINDOW_H);
  glutCreateWindow("PVM Monitor");
  //initialize the postion list
  //initialize data
  gpp = malloc(listInstanceSize * sizeof(gPos));
  for(n=2;(n*(n-1))<=listInstanceSize;n++);
  graph_size=n;
  for(a0=0;a0<listInstanceSize;a0++)
  {
    gpp[a0].x=a0%n;
    gpp[a0].y=a0/n;
  }
  //reshape
  glutReshapeFunc(graphShape);
  glutDisplayFunc(graphDisp);
  glutMainLoop();
  //}
}
