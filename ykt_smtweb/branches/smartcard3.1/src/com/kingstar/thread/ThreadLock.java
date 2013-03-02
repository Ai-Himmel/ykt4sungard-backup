package com.kingstar.thread;

/**
 * This class is used to implement two method that will replace the 
 * resume() and suspend() methods in thread (which have been deprecated).
 */
public class ThreadLock
{
    /**
     * This method will do a wait() on this object. The object will
     * remain in this state until another thread will releases it.
     */
	
	public static boolean runable=true;
    public static void threadSuspend(Object obj)
    {
        synchronized( obj )
        {
            try
            {            
                obj.wait();
            }
            catch(InterruptedException ie){}
        }
    }     
    
    
    public static void threadResume( Object obj)
    {
        synchronized( obj )
        {
            obj.notifyAll();
        }
    }        
     
    public synchronized  void threadSuspend()
    {
        try
        {
            wait();
        }
        catch(InterruptedException ie){}
    }

    public synchronized void threadResume()
    {
        notifyAll();
    }
}