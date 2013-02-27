/**
 * 
 */
package com.kingstargroup.action.bgAnalysis;

import java.util.Calendar;

/**
 * @author Administrator
 *
 */
public class AbDeviceHistoryAnalysisAction extends Thread implements Runnable {

	/**
	 * 
	 */
	public AbDeviceHistoryAnalysisAction() {
		super();
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		// TODO Auto-generated method stub
		while (true) {			
			long now = Calendar.getInstance().getTimeInMillis();
			//todo analysis here
			
			//sleep thread follows the setting
			try {
				sleep(50000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}
