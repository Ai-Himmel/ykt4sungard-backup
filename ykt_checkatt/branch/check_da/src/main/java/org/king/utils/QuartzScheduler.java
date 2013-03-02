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
     * quartz 的启动类，放入listener即可。
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
     * 添加一个只执行一次的定时执行的quartz job
     *
     * @param jobName     job唯一ID
     * @param groupName   group的名称
     * @param contextData 对应job需要的参数
     * @param jobClass    对应job需要执行的类，必须实现Job接口
     * @param time        开始执行job 的时间 ,执行完成后就不再执行
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
     * 添加一个定时执行的quartz job
     *
     * @param jobId          job唯一ID
     * @param triggerId      trigger唯一ID
     * @param groupName      group的名称
     * @param contextData    对应job需要的参数
     * @param jobClass       对应job需要执行的类，必须实现Job接口
     * @param startTime      开始执行job 的时间
     * @param endTime        job   失效时间，为null则永不实效
     * @param repeatCount    job重复方式 ,在SimpleTrigger类中有定义.REPEAT_INDEFINITEL或-1为永久执行
     * @param repeatInterval job的时间间隔
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
     * 添加一个定时执行的quartz job
     *
     * @param jobId          job唯一ID
     * @param triggerId      trigger唯一ID
     * @param groupName      group的名称
     * @param contextData    对应job需要的参数
     * @param jobClass       对应job需要执行的类，必须实现Job接口
     * @param cronExpression 类似linux 的crontab 中的定义方式
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
     * 添加一个每天定时执行的quartz job
     *
     * @param jobId       job唯一ID
     * @param triggerId   trigger唯一ID
     * @param groupName   group的名称
     * @param contextData 对应job需要的参数
     * @param jobClass    对应job需要执行的类，必须实现Job接口
     * @param hour        24小时格式
     * @param minute      分钟
     * @param second      秒
     */
    public static void scheduleJobEveryDay(String jobId, String triggerId, String groupName,
                                           HashMap contextData, Class jobClass, int hour, int minute, int second) {
        String cronExpression = second + " " + minute + " " + hour + " * * ?";
        scheduleJob(jobId, triggerId, groupName, contextData, jobClass, cronExpression);
    }

    //dayOfWeek: 1-7  1:Sunday

    /**
     * 添加一个每周定时执行的quartz job
     *
     * @param jobId       job唯一ID
     * @param triggerId   trigger唯一ID
     * @param groupName   group的名称
     * @param contextData 对应job需要的参数
     * @param jobClass    对应job需要执行的类，必须实现Job接口
     * @param dayOfWeek   每周几,1-7  1:Sunday
     * @param hour        24小时格式
     * @param minute      分钟
     * @param second      秒
     */
    public static void scheduleJobEveryWeek(String jobId, String triggerId, String groupName,
                                            HashMap contextData, Class jobClass, int dayOfWeek, int hour, int minute, int second) {
        String cronExpression = second + " " + minute + " " + hour + " ? * " + dayOfWeek;
        scheduleJob(jobId, triggerId, groupName, contextData, jobClass, cronExpression);
    }

    /**
     * 删除一个quartz job
     *
     * @param jobName   job名称
     * @param groupName group名称
     * @return 删除成功返回true
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
