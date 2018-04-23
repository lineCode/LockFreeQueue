# LockFreeQueue
Sample of a Boost LockFree Queue

Lockfree queues require that the queued type (T) meets the following 
requirements:

* T must have a copy constructor
* T must have a trivial assignment operator
* T must have a trivial destructor


shared_ptr has neither a trivial assignment operator or destructor and
cannot be used in the lockfree containers.
