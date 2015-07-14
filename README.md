# envelope

**Usable system classes**
- Thread		: a wrapper for pthread.
- Mutex 		: a wrapper for pthread_mutex.
- ScopedMutex	: Locks and unlocks mutex in a function scope.
- Timer 		: uses time.h and unistd.h for sleeping and timing.
- Stack 		: template class that implements a generic stack.
- HashMap		: template class that implements a generic hash-map.
- Queue			: template class that implements a generic queue.
 
**Note**
The project is for embedded systems, therefore no `new` or other dynamic allocations allowed on runtime. 


