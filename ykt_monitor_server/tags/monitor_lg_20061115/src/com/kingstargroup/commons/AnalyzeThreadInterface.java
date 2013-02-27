package com.kingstargroup.commons;

public interface AnalyzeThreadInterface {
	/*
	 * any thread's init method to initial all the param
	 * include cycle|limit|
	 */
	abstract void initParam();
	/*
	 * the main function for every thread to realize the analysis work
	 */
	abstract void anaylize();
	/*
	 * terminate this thread
	 */
	abstract void terminate();
	/*
	 * return the state of this thread:  true-->terminate,false-->alive
	 */
	abstract boolean  isTerminate();
	/*
	 * to run anaylize unstoply until this thread is stop request~
	 */
	abstract void run();
	/*
	 * to send mail
	 */
	abstract void sendMail();
	/*
	 * to send SMG
	 */
	abstract void sendSMG();

}
