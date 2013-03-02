package com.kingstar.thread;

//对线程信息的增加、删除、设置线程名
public class KillableThread extends Thread implements Killable
{
    
    public KillableThread(Runnable runnable)
    {
        super(runnable);
        KillablesList.add(this);   
    }
    
    public KillableThread()
    {
        super();
        KillablesList.add(this);   
    }
   
   
    public void kill()
    {
       // this.interrupt();  
      //change getid
        KillablesList.kill(this.getName());  
    }
    
   
}