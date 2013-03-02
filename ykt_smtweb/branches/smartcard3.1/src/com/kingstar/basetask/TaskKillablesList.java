package com.kingstar.basetask;

import java.util.Iterator;

import com.kingstar.basetask.bean.Task;
import com.kingstar.console.MainConsole;
import com.kingstar.console.sort.SortVector;
import com.kingstar.console.sort.TaskPriorityCompare;

//task manager
public class TaskKillablesList
{
 
	public  static void close(Task t)
    {

       Iterator iter=MainConsole.tasklist.iterator();
        
        while (iter.hasNext())
        {
            Task task = (Task) iter.next();
           
            if (t.getId().equals(task.getId()))
            {             
            	//…Ë÷√◊¥Ã¨πÿ±’
            	   task.setStatus(TaskStateConstants.CLOSED);
            	    System.out.println("task id change"+task.getStatus());
                                            
            }
        }
    }
	public static void main(String[] args){
		TaskPriorityCompare tc = new TaskPriorityCompare();
		SortVector sv=new SortVector(tc);
		Task t=new Task();
		Task t1=new Task();
		t.setName("aaa");
		t1.setName("bbbb");
		sv.add(t);
		sv.add(t1);
		Iterator iter=sv.iterator();
		 while (iter.hasNext())
	        {
	            Task task = (Task) iter.next();
	           
	            if (task.getName().equals("aaa"))
	            {             
	            	//…Ë÷√◊¥Ã¨πÿ±’
	            	   task.setStatus(TaskStateConstants.CLOSED);
	            	                      
	            }
		
	}
		 Iterator iter2=sv.iterator();
		 while (iter2.hasNext())
	        {
	            Task task = (Task) iter2.next();

               System.out.println(task.getName()+task.getStatus());
		
	}
	}
   
}