package com.kingstar.thread;

public class RerunnableThread extends KillableThread {

	private volatile Runnable task = null;
	private volatile boolean running = false;
	private ThreadLock lock = new ThreadLock();

	public RerunnableThread(Runnable task) {
		super();
		this.task = task;
		setDaemon(true);
	}

	public void run() {
		running = true;
		while (!Thread.currentThread().isInterrupted()) {
			if (task == null) {
				return;
			}

			try {
				task.run();
			} catch (Throwable t) {
			}

			synchronized (lock) {
				if (running) {
					running = false;
					lock.threadSuspend();
				}
				running = true;
			}
		}

	}

	public void start() throws IllegalThreadStateException {
		if (isAlive())
			synchronized (lock) {
				running = false;
				lock.threadResume();
			}
		else {
			super.start();
		}
	}

	public boolean isRunning() {
		return running;
	}

	public void kill() {
		super.kill();

		synchronized (lock) {
			task = null;
			running = false;
			lock.threadResume();
		}

		try {
			join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		RerunnableThread rt = new RerunnableThread(new Runnable() {
			public void run() {
				System.out.println("thread alive");
			}
		}

		);

		for (int i = 0; i < 10; i++) {
			System.out.println(i);
			// System.out.println("22222222");        

			rt.start();
		}
		rt.kill();
		for (int i = 0; i < 2; i++) {
			System.out.println("11111111");
			System.out.println("22222222");
			//rt.start();
		}

	}

}