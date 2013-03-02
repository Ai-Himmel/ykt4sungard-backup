package org.king.check.util;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;


/**
 * Created by IntelliJ IDEA.
 * User: Haiyu.Peng
 * Date: 2010-5-9
 * Time: 19:43:06
 * To change this template use File | Settings | File Templates.
 */

public class TaskProxy implements Job {
    public void execute(JobExecutionContext jobExecutionContext) throws JobExecutionException {
        new Taskers().runSumKQ();
    }
}

