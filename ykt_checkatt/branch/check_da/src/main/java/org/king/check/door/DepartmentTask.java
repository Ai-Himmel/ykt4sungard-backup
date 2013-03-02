package org.king.check.door;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-19
 */
public class DepartmentTask implements Job {
    public void execute(JobExecutionContext jobContext) throws JobExecutionException {
		PersonsTaskBiz.refreshDepartment();
	}
}
