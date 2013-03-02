package com.kingstar.task;


public class MainThreadConfig {
	private static MainThreadConfig intance = null;
	private static Object mutex = new Object();
	
	public static MainThreadConfig getIntance() {
		if (intance == null) {
			synchronized (mutex) {
				if (intance == null) {
					intance = new MainThreadConfig();
				}
			}
		}
		return intance;
	}

	public void ini() throws Exception {

		runThreads();
	}

	private void runThreads() throws InstantiationException,
			IllegalAccessException, ClassNotFoundException {
		// ��ȫ�����̣߳����̣߳��غ��̣߳�дTASK�����̣߳�����̡߳�
		TimeTaskForSerialCheckThread a = new TimeTaskForSerialCheckThread();
		a.start();
	}
	
	

}
