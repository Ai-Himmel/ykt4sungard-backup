package org.king.task;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-27
 */
public class ReconciliationTask implements Job {
    public void execute(JobExecutionContext jobExecutionContext) throws JobExecutionException {
        TaskUtil.jjlinkTask();
    }
}
