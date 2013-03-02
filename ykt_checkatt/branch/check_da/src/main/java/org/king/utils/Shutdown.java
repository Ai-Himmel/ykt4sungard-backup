package org.king.utils;

import org.quartz.Scheduler;
import org.quartz.SchedulerException;

public class Shutdown implements Runnable
{
    private Scheduler s;

    public Shutdown(Scheduler s)
    {
        this.s = s;
    }

    //~ Methods ////////////////////////////////////////////////////////////////

    public void run()
    {
        try
        {
            s.shutdown();
        }
        catch (SchedulerException e)
        {
            e.printStackTrace();
        }
    }
}


