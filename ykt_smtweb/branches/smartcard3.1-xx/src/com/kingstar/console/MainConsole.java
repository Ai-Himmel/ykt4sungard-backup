package com.kingstar.console;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import com.kingstar.basetask.ThreadStateConstants;
import com.kingstar.basetask.bean.Task;
import com.kingstar.basetask.bean.ThreadTask;
import com.kingstar.console.sort.SortVector;
import com.kingstar.console.sort.TaskPriorityCompare;
import com.kingstar.files.DOMParse;
import com.kingstar.format.FormatterOutPut;
import com.kingstar.log.Debug;
import com.kingstar.thread.KillableThread;
import com.kingstar.version.Version;

public class MainConsole {
	//	采用优先级排序
	public static TaskPriorityCompare tc = new TaskPriorityCompare();

	public static volatile SortVector tasklist = new SortVector(tc);

	public static volatile SortVector threadslist = null;

	public static void ini() throws Exception {

		Debug.debug(Version.getVersion()); 

		 loadTasks();

		 loadThreads();

		runThreads();
	}

	private static void runThreads() throws InstantiationException,
			IllegalAccessException, ClassNotFoundException {
		// 起到全部的线程，主线程，守侯线程，写TASK任务线程，清除线程。

		Iterator iterator = threadslist.iterator();
		while (iterator.hasNext()) {
			ThreadTask thread = (ThreadTask) iterator.next();
			System.out.println("run threads: " + thread.getCla());

			//根据线程数，起对应的线程
			for (int i = 0; i < thread.getThreadcount(); i++) {
				KillableThread runnable = (KillableThread) Class.forName(
						thread.getCla()).newInstance();

				//设置线程属性
				runnable.setName(thread.getName());
				runnable.setDaemon(thread.isIsdaemon());
				runnable.setPriority(thread.getPriority());

				runnable.start();

				//set thread status "RUN"
				thread.setStatus(ThreadStateConstants.RUN);

				System.out.println("crrentthread name:"
						+ Thread.currentThread().getName());

			}

		}
	}

	private static void loadThreads() throws Exception {
		// initial add threadslist.xml to global static threadslist
		DOMParse d2 = new DOMParse("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\ThreadsList.xml");
		threadslist = d2.addThreadVector();
	}

	public static void loadTasks() throws Exception, ParseException {
		// initial add tasklist.xml to global static tasklist

		DOMParse d = new DOMParse("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\TaskList.xml");

		//使任务信息加载到record.db 
		d.addTaskVector();

		//初始化tasklist
		tasklist = new SortVector(tc);
		List list = FormatterOutPut.readTaskRecord();
		Iterator it = list.iterator();
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
		while (it.hasNext()) {
			Task t = (Task) it.next();
			//看任务时间是不是大于等于现在时间

			Date d1 = format.parse(t.getBelongdate());
			Date d2 = new Date();
			d2.setHours(-24);
			if (d1.compareTo(d2) >= 0) {
				tasklist.add(t);

			}

		}
		   
		Debug.debug("finished loaded tasks ");
		
	}

	public static void main(String[] args) throws ClassNotFoundException,
			Exception, InstantiationException {
		ini();
		printtasklist();
	}
	public static void printtasklist() {

		DOMParse.printTasklist(tasklist);
	}

}
