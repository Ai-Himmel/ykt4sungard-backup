package org.king.check.door;

import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * ��ʱͳ�Ʊ���
 * @author Yiming.You
 *
 */
public class ReportTask implements Job {
    public void execute(JobExecutionContext jobContext) throws JobExecutionException {
		PersonsTaskBiz.checkReport();
	}
}
