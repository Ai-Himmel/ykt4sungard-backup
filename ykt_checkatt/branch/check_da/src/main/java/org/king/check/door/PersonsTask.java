package org.king.check.door;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: 2010-4-15
 * Time: 0:21:23
 * To change this template use File | Settings | File Templates.
 */
public class PersonsTask implements Job {
    public void execute(JobExecutionContext jobContext) throws JobExecutionException {
		PersonsTaskBiz.execute();
	}
}
