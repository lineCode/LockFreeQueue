# LockFreeQueue
Sample of a Boost LockFree Queue

Lockfree queues require that the queued type (T) meets the following 
requirements:

  o T must have a copy constructor
  o T must have a trivial assignment operator
  o T must have a trivial destructor


shared_ptr has neither a trivial assignment operator or destructor and
cannot be used in the lockfree containers.