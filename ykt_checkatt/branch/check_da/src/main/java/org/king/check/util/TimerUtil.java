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
     * �Ƿ��Ѿ�������ʱ��
     */
    static boolean isCreated = false;
    static Timer _timer = null;

    /**
     * �õ���ǰ���е��߳�
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
     * �������񵽼�ʱ��
     * @param hour
     * ��һ��ִ�������ʱ�䣨Сʱ��
     * @param min
     * ��һ��ִ�������ʱ�䣨���ӣ�
     * @param mill
     * ��һ��ִ�������ʱ�䣨���룩
     * @param task
     * ��TaskFactory�õ�������
     * @param period
     * ִ����������ڣ������Ӽ��㣩
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
     * ���й�����
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
