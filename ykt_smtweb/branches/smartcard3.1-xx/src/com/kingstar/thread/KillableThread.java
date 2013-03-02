package com.kingstar.thread;

//���߳���Ϣ�����ӡ�ɾ���������߳���
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