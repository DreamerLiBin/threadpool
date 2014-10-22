threadpool
==========

A simple C++ threadpool

Quick Start:

	make
	./thpool

Basic usage:

	/* create a threadpool */
	LThreadPool lthpool(5);

	/*
	* create a job and initialize it
	* func is some function pointer
	* arg point to the argument list
	*/
	LBaseJob* job = new LBaseJob();
	job->routine = func;
	job->arg = argument;

	/* use threadpool to do the job */
	lthpool.run(job);

	/* destroy the threadpool and free resources */
	lthpool.destroy();
