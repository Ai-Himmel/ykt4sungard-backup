package org.king.check.door;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-8
 */
public class SyncDataTask implements Job {
    public void execute(JobExecutionContext jobContext) throws JobExecutionException {
        PersonsTaskBiz.syncData();
    }
}
