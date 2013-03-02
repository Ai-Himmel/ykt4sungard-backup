package com.kingstar.console;
//package com.ks.console;
//
//import com.ks.thread.TaskThread;
//
//public class ThreadEngine {
//
//	// total thread counts
//	private static int threadcount = 0;
//
//	// runing thread counts
//	private static int runcount = 0;
//
//	public static int getThreadcount() {
//		return threadcount;
//	}
//
//	public static void setThreadcount(int threadcount) {
//		ThreadEngine.threadcount = threadcount;
//	}
//
//	public static int getRuncount() {
//		return runcount;
//	}
//
//	public static void addRuncount() {
//		
//		if(runcount>=threadcount)
//			return;
//		else {
//			ThreadEngine.runcount=++runcount;
//		}
//		
//	}
//	
//   public static void deleteRuncount() {
//		
//		if(runcount <=0)
//			return;
//		else {
//			ThreadEngine.runcount=--runcount;
//		}
//		
//	}
//	
//   public static void runThreads(){
//   for (int i = 0; i < threadcount; i++) {
//
//		TaskThread tt = new TaskThread();
//		
//		System.out.println("Starting taskthreads :" + i);
//		tt.run();
//		
//		
//
//	}
//   }
//   public static void main(String args){
//	   
//	   
//	   
//	   
//	   
//   }
//}
