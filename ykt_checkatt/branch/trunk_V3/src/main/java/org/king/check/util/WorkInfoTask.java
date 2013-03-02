package org.king.check.util;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

public class WorkInfoTask implements Job {
    public void execute(JobExecutionContext jobContext) throws JobExecutionException {
    	CreateWorkInfoThread.startCreateWorkInfo();
    }
}
