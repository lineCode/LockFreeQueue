# LockFreeQueue

Sample of a Boost LockFree Queue

Lockfree queues require that the queued type (T) meets the following requirements:

* T must have a copy constructor
* T must have a trivial assignment operator
* T must have a trivial destructor

The **shared_ptr** has neither a trivial assignment operator or destructor and **cannot be used in the lockfree containers**.

Because more than one thread reads from the queue, the class **boost::lockfree::spsc_queue** must not be used. Thus, I use **boost::lockfree::queue** instead.

Thanks to **std::atomic**, access to the variables producer_count and consumer_count is also now thread safe.

The size of the queue is set to 128 – this is the parameter passed to the constructor. However, this is only the initial size. By default, **boost::lockfree::queue** is not implemented with a circular buffer. If more items are added to the queue than the capacity is set to, it is automatically increased. **boost::lockfree::queue dynamically** allocates additional memory if the initial size isn’t sufficient.

That means that **boost::lockfree::queue** isn’t necessarily lock free. The allocator used by **boost::lockfree::queue** by default is **boost::lockfree::allocator**, which is based on **std::allocator**. Thus, this allocator determines whether **boost::lockfree::queue** is lock free without constraints.
