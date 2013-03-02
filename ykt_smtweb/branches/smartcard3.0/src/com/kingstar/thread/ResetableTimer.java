
package com.kingstar.thread;

import java.util.Timer;
import java.util.TimerTask;

public class ResetableTimer
{
    private static Timer timer = new Timer();
    
    private   volatile Runnable     task       = null;
    private   volatile long         sleepTime  = 0;
    private   volatile boolean      running    = false;
    private   volatile int          priority   = Thread.NORM_PRIORITY;
    private   volatile RTTimerTask  timerTask   = null;
       
    public boolean isRunning()
    {
        return running;
    }
                                            
    private ResetableTimer( Runnable task, long sleepTime )
    {
     //   KillablesList.add(this);   
        this.task         = task;
        this.sleepTime    = sleepTime;
    }
    
    public ResetableTimer( Runnable task, long sleepTime, boolean seconds )
    {
        this(task, (seconds) ? sleepTime * 1000 : sleepTime);
    }
    
    public ResetableTimer( Runnable task, long sleepTime, boolean seconds, int priority )
    {
        this(task, sleepTime, seconds);
        this.priority = priority;
    }
    
    public synchronized void start()
    {       
        try
        {   
            if (!running)
            {
                running = true;
                timerTask = new RTTimerTask(task,priority);
                timer.scheduleAtFixedRate(timerTask, sleepTime, sleepTime);
            }
        }
        catch (Throwable e)
        {
            e.printStackTrace();   
        }
    }
    
    public synchronized void stop()
    {
        running = false;
        if (timerTask != null)
        {
            timerTask.kill();
            timerTask = null;
        }
    }
 
    public void reset()
    {        
        stop();
        start();
    }
    
    private void reset( long sleepTime )
    {
        
        this.sleepTime = sleepTime;
        reset();
    }    

    public synchronized void reset( long sleepTime, boolean seconds )
    {
        reset( (seconds) ? sleepTime * 1000 : sleepTime);
    }  
      
    public void kill()
    {
        stop();
    }    
    
    private static class RTTimerTask extends TimerTask
    {
        Runnable task = null;
        int priority  = Thread.NORM_PRIORITY;
        
        public RTTimerTask(Runnable task, int priority)
        {
            this.task = task;
            this.priority = priority;
        }
        
        public synchronized void run()
        {
            Thread thread = null; //#2
            thread = new Thread(task);
            thread.setDaemon(true);
            thread.setPriority(priority);
            thread.start();
         }
        
        public synchronized void kill()
        {
            cancel();
        }
    }
}