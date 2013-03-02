package org.king.utils;

import org.king.check.door.PersonsTask;
import org.quartz.CronTrigger;
import org.quartz.JobDetail;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.SimpleTrigger;
import org.quartz.Trigger;
import org.quartz.impl.StdSchedulerFactory;

import java.util.Date;
import java.util.HashMap;


public class QuartzScheduler {
    private static Scheduler scheduler;

    /**
     * quartz �������࣬����listener���ɡ�
     */
    public static void start() {
        try {
            scheduler = new StdSchedulerFactory().getScheduler();
            scheduler.start();
            Runtime.getRuntime().addShutdownHook(new Thread(new Shutdown(scheduler)));

        }
        catch (Exception e) {
            e.printStackTrace();
        }

    }

    /**
     * ���һ��ִֻ��һ�εĶ�ʱִ�е�quartz job
     *
     * @param jobName     jobΨһID
     * @param groupName   group������
     * @param contextData ��Ӧjob��Ҫ�Ĳ���
     * @param jobClass    ��Ӧjob��Ҫִ�е��࣬����ʵ��Job�ӿ�
     * @param time        ��ʼִ��job ��ʱ�� ,ִ����ɺ�Ͳ���ִ��
     */
    public static void scheduleJob(String jobName, String groupName, HashMap contextData, Class jobClass, Date time) {
        try {
            JobDetail job = new JobDetail(jobName, groupName, jobClass);
            job.getJobDataMap().put("contextData", contextData);

            Trigger trigger = new SimpleTrigger(jobName, groupName, time);
            scheduler.scheduleJob(job, trigger);
        }
        catch (SchedulerException e) {
            e.printStackTrace();
        }

    }

    /**
     * ���һ����ʱִ�е�quartz job
     *
     * @param jobId          jobΨһID
     * @param triggerId      triggerΨһID
     * @param groupName      group������
     * @param contextData    ��Ӧjob��Ҫ�Ĳ���
     * @param jobClass       ��Ӧjob��Ҫִ�е��࣬����ʵ��Job�ӿ�
     * @param startTime      ��ʼִ��job ��ʱ��
     * @param endTime        job   ʧЧʱ�䣬Ϊnull������ʵЧ
     * @param repeatCount    job�ظ���ʽ ,��SimpleTrigger�����ж���.REPEAT_INDEFINITEL��-1Ϊ����ִ��
     * @param repeatInterval job��ʱ����
     */
    public static void scheduleJob(String jobId, String triggerId, String groupName,
                                   HashMap contextData, Class jobClass, Date startTime, Date endTime, int repeatCount, long repeatInterval) {
        try {
            JobDetail job = new JobDetail(jobId, groupName, jobClass);
            job.getJobDataMap().put("contextData", contextData);

            Trigger trigger = new SimpleTrigger(triggerId, groupName, startTime, endTime, repeatCount, repeatInterval);
            scheduler.scheduleJob(job, trigger);
        }
        catch (SchedulerException e) {
            e.printStackTrace();
        }
    }

    /**
     * ���һ����ʱִ�е�quartz job
     *
     * @param jobId          jobΨһID
     * @param triggerId      triggerΨһID
     * @param groupName      group������
     * @param contextData    ��Ӧjob��Ҫ�Ĳ���
     * @param jobClass       ��Ӧjob��Ҫִ�е��࣬����ʵ��Job�ӿ�
     * @param cronExpression ����linux ��crontab �еĶ��巽ʽ
     */
    public static void scheduleJob(String jobId, String triggerId, String groupName,
                                   HashMap contextData, Class jobClass, String cronExpression) {
        try {
            JobDetail job = new JobDetail(jobId, groupName, jobClass);
            job.getJobDataMap().put("contextData", contextData);

            Trigger trigger = new CronTrigger(triggerId, groupName, jobId, groupName, cronExpression);
            scheduler.scheduleJob(job, trigger);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * ���һ��ÿ�춨ʱִ�е�quartz job
     *
     * @param jobId       jobΨһID
     * @param triggerId   triggerΨһID
     * @param groupName   group������
     * @param contextData ��Ӧjob��Ҫ�Ĳ���
     * @param jobClass    ��Ӧjob��Ҫִ�е��࣬����ʵ��Job�ӿ�
     * @param hour        24Сʱ��ʽ
     * @param minute      ����
     * @param second      ��
     */
    public static void scheduleJobEveryDay(String jobId, String triggerId, String groupName,
                                           HashMap contextData, Class jobClass, int hour, int minute, int second) {
        String cronExpression = second + " " + minute + " " + hour + " * * ?";
        scheduleJob(jobId, triggerId, groupName, contextData, jobClass, cronExpression);
    }

    //dayOfWeek: 1-7  1:Sunday

    /**
     * ���һ��ÿ�ܶ�ʱִ�е�quartz job
     *
     * @param jobId       jobΨһID
     * @param triggerId   triggerΨһID
     * @param groupName   group������
     * @param contextData ��Ӧjob��Ҫ�Ĳ���
     * @param jobClass    ��Ӧjob��Ҫִ�е��࣬����ʵ��Job�ӿ�
     * @param dayOfWeek   ÿ�ܼ�,1-7  1:Sunday
     * @param hour        24Сʱ��ʽ
     * @param minute      ����
     * @param second      ��
     */
    public static void scheduleJobEveryWeek(String jobId, String triggerId, String groupName,
                                            HashMap contextData, Class jobClass, int dayOfWeek, int hour, int minute, int second) {
        String cronExpression = second + " " + minute + " " + hour + " ? * " + dayOfWeek;
        scheduleJob(jobId, triggerId, groupName, contextData, jobClass, cronExpression);
    }

    /**
     * ɾ��һ��quartz job
     *
     * @param jobName   job����
     * @param groupName group����
     * @return ɾ���ɹ�����true
     */
    public static boolean scheduleJobDelete(String jobName, String groupName) {
        boolean returnValue = false;
        try {
            returnValue = scheduler.deleteJob(jobName, groupName);
        }
        catch (org.quartz.SchedulerException e) {

            e.printStackTrace();
        }
        return returnValue;
    }

    public static void main(String[] args) {
        try {
            scheduler = new StdSchedulerFactory().getScheduler();
            scheduler.start();
        } catch (SchedulerException e) {
            e.printStackTrace();  //To change body of catch statement use File | Settings | File Templates.
        }
        scheduleJobDelete("testJobID","testGroupName");
        //add a job
        HashMap contextData = new HashMap();
        // QuartzScheduler.scheduleJobEveryWeek("forDoorPerson", "forDoorPerson",
        //         "DoorPersonListEveryWeek", contextData, new PersonsTask().getClass(), 1, 0, 0, 0);

        QuartzScheduler.scheduleJob("testJobID", "testTriggerID", "testGroupName",
                contextData, new PersonsTask().getClass(), new Date(),
                null, SimpleTrigger.REPEAT_INDEFINITELY, 5L * 1000L);
        try {
            JobDetail job = scheduler.getJobDetail("testJobID","testGroupName");
            System.out.println(job.getName());
        } catch (SchedulerException e) {
            e.printStackTrace(); 
        }

    }

}
