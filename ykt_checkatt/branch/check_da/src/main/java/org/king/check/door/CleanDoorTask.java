package org.king.check.door;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-31
 */
public class CleanDoorTask implements Job {
    public void execute(JobExecutionContext jobContext) throws JobExecutionException {
        PersonsTaskBiz.cleanDoorData();
    }
}
