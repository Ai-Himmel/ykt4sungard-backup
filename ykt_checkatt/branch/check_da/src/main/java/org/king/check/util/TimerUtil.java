package org.king.check.util;

import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class TimerUtil {
	private static final Log log = LogFactory.getLog(TimerUtil.class); 
	/**
     * 
     */
    static long FLAG_STOP = -1;
    static long FLAG_RUNNING = 0;
    static long FLAG_FINISH = 1;
    
    
    /**
     * 是否已经创建计时器
     */
    static boolean isCreated = false;
    static Timer _timer = null;

    /**
     * 得到当前运行的线程
     * @return Timer
     */
    public static Timer getInstance()
    {
        if (!isCreated)
        {
            _timer = new Timer();
            isCreated = true;
        }
        return _timer;
    }

    /**
     * 配置任务到计时器
     * @param hour
     * 第一次执行任务的时间（小时）
     * @param min
     * 第一次执行任务的时间（分钟）
     * @param mill
     * 第一次执行任务的时间（毫秒）
     * @param task
     * 从TaskFactory得到的任务
     * @param period
     * 执行任务的周期（按分钟计算）
     */
    public static void shedule(int hour, int min, int mill, TimerTask task, long period)
    {
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.HOUR_OF_DAY, hour);
        calendar.set(Calendar.MINUTE, min);
        calendar.set(Calendar.MILLISECOND, mill);
        getInstance().schedule(task, calendar.getTime(), period);
    }

    /**
     * 运行管理器
     */
    public static void run()
    {
        Taskers tasks = new Taskers();
        shedule(Taskers.HOUR, Taskers.MIN, Taskers.MILL, tasks, Taskers.PEIROD);
    }
    public static void main(String[] args)
    {
    	log.debug("now is " + Calendar.getInstance().getTime());

    	log.debug("begin run...");
    	TimerUtil.run();
    	log.debug("end run...");
    }
}
