//version 1.2
package com.kingstar.files;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import com.kingstar.basetask.TaskStateConstants;
import com.kingstar.basetask.ThreadStateConstants;
import com.kingstar.basetask.bean.DataSource;
import com.kingstar.basetask.bean.DateWrapper;
import com.kingstar.basetask.bean.Task;
import com.kingstar.basetask.bean.TaskConstants;
import com.kingstar.basetask.bean.ThreadTask;
import com.kingstar.console.ChronologicalKey;
import com.kingstar.console.sort.Compare;
import com.kingstar.console.sort.SortVector;
import com.kingstar.format.FormatterOutPut;

public class DOMParse {

	Element root = null;

	NodeList list = null;

	Element element = null;

	public DOMParse(String fname) throws Exception {

		DocumentBuilderFactory dbfactory = DocumentBuilderFactory.newInstance();

		// 指定DocumentBuilder
		DocumentBuilder builder = dbfactory.newDocumentBuilder();
		Document doc = builder.parse(new File(fname));
		root = doc.getDocumentElement();

	}

	//add temp task to RECORD.dat

	public static void addTempTask(Task temp){ 
		Format format2 = new SimpleDateFormat("yyyy-MM-dd");
		Date d = new Date();
		String nowdate = format2.format(d);
		
		Task t=new Task();
		
		t.setId(new Long(ChronologicalKey.next()));
		t.setName(temp.getName());
		t.setCla(temp.getCla());
		t.setPriority(temp.getPriority());
		t.setTasktype(temp.getTasktype());
		t.setRuntimetype(temp.getRuntimetype());
		t.setRuntimedata(temp.getRuntimedata());
		t.setDescription(temp.getDescription());
		t.setBelongdate(nowdate);
		t.setBelongtype(TaskConstants.tempadd);
		t.setStatus(TaskStateConstants.START);
		FormatterOutPut.writeTaskLog(t);

		try {
		 FormatterOutPut.writeTaskRecord(t);
		} catch (Exception e) {

			e.printStackTrace();
		}
			
	}
	//*************************************************
	//delete expire tasks
	public synchronized static ArrayList getNotExpireTasks(){
		ArrayList ary=new ArrayList();
		try {
			 ary = FormatterOutPut.readTaskRecord();
			   
			for (int i = 0; i < ary.size(); i++) {
				Task temp = (Task)ary.get(i);
				SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
				Date d1 = format.parse(temp.getBelongdate());
				Date d2 = new Date();
				d2.setHours(-24);
				//比昨天前的任务全删除
				if(d1.compareTo(d2)< 0){
				 ary.remove(i);			
				}
			}
	 
		} catch (Exception e) {
			 
			e.printStackTrace();
		}
		return ary;
		
	}
	//delete expire history tasks
	public synchronized static ArrayList getNotExpireHistoryTasks(){
		ArrayList ary=new ArrayList();
		try {
			 ary = FormatterOutPut.readTaskHistoryFromfile();
			   
			for (int i = 0; i < ary.size(); i++) {
				Task temp = (Task)ary.get(i);
				SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
				Date d1 = format.parse(temp.getBelongdate());
				Date d2 = new Date();
				d2.setHours(-24);
				//比昨天前的任务全删除
				if(d1.compareTo(d2)< 0){
				 ary.remove(i);			
				}
			}
		} catch (Exception e) {
			 
			e.printStackTrace();
		}
		return ary;
		
	}
	//execute delete expired tasks
	public synchronized static void ExecExpireTasks() throws Exception {
		Parameters parameters = new Parameters();
		ArrayList ary = new ArrayList();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		String filename = parameters.getProperty("RECORDDB");

		File file = new File(filename);
		if (!file.exists()) {    
          return ;
		}else{
			ary = getNotExpireTasks();
			FileOutputStream ostream = new FileOutputStream(filename);
			ObjectOutputStream out = new ObjectOutputStream(ostream);
			out.writeObject(ary);
			out.flush();
			out.close();
			ostream.close();
			ary=null;
			file = null;
		}
		
		
	}
	//execute delete expired history tasks
	public synchronized static void ExecExpireHistoryTasks() throws Exception {
		Parameters parameters = new Parameters();
		ArrayList ary = new ArrayList();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		String filename = parameters.getProperty("HISTORYDB");

		File file = new File(filename);
		if (!file.exists()) {    
          return ;
		}else{
			ary = getNotExpireHistoryTasks();
			FileOutputStream ostream = new FileOutputStream(filename);
			ObjectOutputStream out = new ObjectOutputStream(ostream);
			out.writeObject(ary);
			out.flush();
			out.close();
			ostream.close();
			ary=null;
			file = null;
		}
		
		

	}
	public synchronized static void  deleteTaskLog(){
	Parameters parameters = new Parameters();
	try {
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
	  String TASKLOG = parameters.getProperty("TASKLOG");
	  String TASKHISTORYLOG=parameters.getProperty("TASKHISTORYLOG");
	  
	  File f1 = new File(TASKLOG);
	  File f2 = new File(TASKHISTORYLOG);
	  if(f1.exists()&&f2.exists()){
		  f1.delete();
		  f2.delete();
		  f1=null;
		  f2=null;	  
	  }
	}
	catch (IOException e) {
		 
		e.printStackTrace();
	}
}

	//*******************************************************************
	// 从Taskslist.xml 加到VECTOR对象中
	public void addTaskVector() throws Exception {
		
		//***********************************
		
		ExecExpireTasks();//delete expire task from record.dat
		ExecExpireHistoryTasks();//delete expire task from HISTORY.dat
		deleteTaskLog();//delete expire log.txt and historylog.txt
		
		//***************************************
		Format format2 = new SimpleDateFormat("yyyy-MM-dd");
		Date d = new Date();
		String nowdate = format2.format(d);

		Compare cp = new Task();
		SortVector v = new SortVector(cp);

		list = root.getElementsByTagName("task");
		Format format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

		for (int i = 0; i < list.getLength(); i++) {
			Task task = new Task();
			Element element = (Element) list.item(i);

			task.setId(new Long(getElementValue(element, "id")));
			
			task.setName(getElementValue(element, "name"));
			task.setCla(getElementValue(element, "class"));
			task.setPriority(new Integer(getElementValue(element, "priority")));
			task.setTasktype(getElementValue(element, "tasktype"));
			task.setRuntimetype(getElementValue(element, "runtimetype"));
			task.setRuntimedata(getElementValue(element, "runtimedata"));
			task.setDescription(getElementValue(element, "description"));
			task.setBelongdate(nowdate);
			task.setBelongtype(TaskConstants.define);
			task.setStatus(TaskStateConstants.START);

			if (!isReload(task.getName(), task.getBelongdate())) {
				if (task.getTasktype().equals(TaskConstants.time)) {

					// times task analyse
					if (task.getRuntimetype().equals(TaskConstants.times)) {

						ArrayList l = null;

						// 得到用","分开的
						l = DateWrapper.splitDate(task.getRuntimedata(), ",");

						for (int count = 0; count < l.size(); count++) {

							ArrayList l2 = null;
							// 得到用":"分开的

							l2 = DateWrapper.splitDate((String) l.get(count),
									":");

							// resulte format is 7:00,设置时间和分钟

							DateWrapper dw = new DateWrapper();

							dw.setHours(Integer.parseInt((String) l2.get(0)));
							dw.setMinutes(Integer.parseInt((String) l2.get(1)));
							dw.setSeconds(Integer.parseInt((String) l2.get(2)));

							Task temp = new Task();

							// Start clone operation
							temp.setId(new Long(ChronologicalKey.next()));
							
							temp.setName(task.getName());
							temp.setCla(task.getCla());
							temp.setPriority(task.getPriority());
							temp.setTasktype(task.getTasktype());
							temp.setRuntimetype(task.getRuntimetype());
							temp.setDescription(task.getDescription());
							temp.setStatus(task.getStatus());
							String s1 = format.format(dw.getDate());
							temp.setRuntimedata(s1.toString());
							temp.setBelongdate(task.getBelongdate());
							temp.setBelongtype(task.getBelongtype());
							// end clone operation

                            // v.add(temp);

							// write task info

							FormatterOutPut.writeTaskLog(temp);
							try {
							FormatterOutPut.writeTaskRecord(temp);
							} catch (Exception e) {

								e.printStackTrace();
							}

						}

					}
					// interval task analyse
					if (task.getRuntimetype().equals(TaskConstants.interval)) {

						ArrayList l = null;
						ArrayList l2 = null;
						DateWrapper begin = new DateWrapper();
						DateWrapper end = new DateWrapper();
						l = DateWrapper.splitDate(task.getRuntimedata(), ",");

						// 只取前面两个数据，第三个是interval

						// deal with begin date,get l(0)

						l2 = DateWrapper.splitDate((String) l.get(0), ":");
						begin.setHours(Integer.parseInt((String) l2.get(0)));
						begin.setMinutes(Integer.parseInt((String) l2.get(1)));
						begin.setSeconds(Integer.parseInt((String) l2.get(2)));
						// System.out.println("test..begin."+format.format(begin.getDate()));

						// deal with end date,get l(1)
						l2 = DateWrapper.splitDate((String) l.get(1), ":");
						end.setHours(Integer.parseInt((String) l2.get(0)));
						end.setMinutes(Integer.parseInt((String) l2.get(1)));
						end.setSeconds(Integer.parseInt((String) l2.get(2)));

						// System.out.println("test..end."+format.format(end.getDate()));

						List l3 = DateWrapper.generateInterval(begin.getDate(),
								end.getDate(), Integer.parseInt((String) l
										.get(2)));
						for (int j = 0; j < l3.size(); j++) {

							Date d2 = (Date) l3.get(j);

							// 现在时间大于产生的间隔时间时
							// if (new Date().compareTo(d2) >= 0) {
							Task temp = new Task();

							// Start clone operation
							// 
							temp.setId(new Long(ChronologicalKey.next()));
							
							temp.setName(task.getName());
							temp.setCla(task.getCla());
							temp.setPriority(task.getPriority());
							temp.setTasktype(task.getTasktype());
							temp.setRuntimetype(task.getRuntimetype());
							temp.setDescription(task.getDescription());
							temp.setStatus(task.getStatus());
							temp.setRuntimedata(format.format(d2));
							temp.setBelongdate(task.getBelongdate());
							temp.setBelongtype(task.getBelongtype());
							// end clone operation

                            //	 v.add(temp);

							// write task info

							FormatterOutPut.writeTaskLog(temp);

							try {
								FormatterOutPut.writeTaskRecord(temp);
							} catch (Exception e) {

								e.printStackTrace();
							}

						}

					}

				}
				// series task analyse
				if (task.getTasktype().equals(TaskConstants.series)) {
					Task temp = new Task();

					// Start clone operation
					// temp.setId(task.getId());

					temp.setId(new Long(ChronologicalKey.next()));
				
					temp.setName(task.getName());
					temp.setCla(task.getCla());
					temp.setPriority(task.getPriority());
					temp.setTasktype(task.getTasktype());
					temp.setRuntimetype(task.getRuntimetype());
					temp.setDescription(task.getDescription());
					temp.setStatus(task.getStatus());
					temp.setBelongdate(task.getBelongdate());
					temp.setBelongtype(task.getBelongtype());

					// end clone operation

                    //	 v.add(temp);

					// write task info

					   FormatterOutPut.writeTaskLog(temp);

					try {
						FormatterOutPut.writeTaskRecord(temp);
					} catch (Exception e) {

						e.printStackTrace();
					}
				}
			}

		}
		printTasklist(v);
		 

	}

	public static void printTasklist(SortVector v) {
		System.out.println("start print tasklist!!!");

		Iterator i = v.iterator();

		while (i.hasNext()) {

			Task t = null;
			t = (Task) i.next();
			t.debug();

		}
	}

	// 从Threadslist.xml 加到VECTOR对象中
	public SortVector addThreadVector() {

		Compare cp = new ThreadTask();
		SortVector v = new SortVector(cp);

		ThreadTask thread = new ThreadTask();
		list = root.getElementsByTagName("thread");

		for (int i = 0; i < list.getLength(); i++) {

			Element element = (Element) list.item(i);
			thread.setId(getElementValue(element, "id"));

			thread.setName(getElementValue(element, "name"));
			thread.setCla(getElementValue(element, "class"));

			thread.setDescription(getElementValue(element, "description"));
			thread.setPriority(Integer.parseInt(getElementValue(element,
					"priority")));

			thread.setIsdaemon(Boolean.getBoolean(getElementValue(element,
					"isdaemon")));

			thread.setThreadtype(getElementValue(element, "threadtype"));
			thread.setThreadcount(Integer.parseInt(getElementValue(element,
					"threadcount")));
			thread.setThreadGroup(getElementValue(element, "threadGroup"));

			thread.setStatus(ThreadStateConstants.START);

			// **************clone operation
			ThreadTask runthread = new ThreadTask();

			runthread.setId(thread.getId());
			runthread.setName(thread.getName());
			runthread.setCla(thread.getCla());
			runthread.setPriority(thread.getPriority());
			runthread.setDescription(thread.getDescription());
			runthread.setIsdaemon(thread.isIsdaemon());
			runthread.setThreadtype(thread.getThreadtype());
			runthread.setThreadGroup(thread.getThreadGroup());
			runthread.setThreadGroup(thread.getThreadGroup());

			runthread.setStatus(thread.getStatus());

			// ***************
			v.add(runthread);

		}
		printThreadslist(v);
		return v;

	}

	// 从datasource.xml 加到VECTOR对象中
	public SortVector addDataSourceVector() {
		//		
		Compare cp = new ThreadTask();
		SortVector v = new SortVector(cp);

		DataSource datasource = new DataSource();
		list = root.getElementsByTagName("datasource");

		for (int i = 0; i < list.getLength(); i++) {
			Element element = (Element) list.item(i);

			datasource.setId(Integer.parseInt(getElementValue(element, "id")));
			datasource.setDbtype(getElementValue(element, "type"));
			datasource.setUrl(getElementValue(element, "url"));
			datasource.setMaxconn(Integer.parseInt(getElementValue(element,
					"maxconn")));
			datasource
					.setDriver_class(getElementValue(element, "driver_class"));
			datasource.setUsername(getElementValue(element, "username"));
			datasource.setPassword(getElementValue(element, "password"));
			datasource.setComment(getElementValue(element, "comment"));
			// **************clone operation
			DataSource temp = new DataSource();

			temp.setId(datasource.getId());
			temp.setDbtype(datasource.getDbtype());
			temp.setUrl(datasource.getUrl());
			temp.setMaxconn(datasource.getMaxconn());
			temp.setDriver_class(datasource.getDriver_class());
			temp.setUsername(datasource.getUsername());
			temp.setPassword(datasource.getPassword());
			temp.setComment(datasource.getComment());
			// ***************
			v.add(temp);
		}
		return v;

	}

	private void printThreadslist(SortVector v) {

		Iterator i = v.iterator();

		while (i.hasNext()) {

			ThreadTask t = null;
			t = (ThreadTask) i.next();
			t.debug();

		}
	}

	private String getElementAttribute(Element element, String attributevalue) {
		String id = element.getAttribute(attributevalue);
		return id;
	}

	private String getElementValue(Element element, String valuename) {
		NodeList titleList = element.getElementsByTagName(valuename);
		Element description = (Element) titleList.item(0);
		String t = (String) description.getFirstChild().getNodeValue();
		return t;
	}
 
	
	private static boolean isReload(String taskn, String taskd)
			throws Exception {
		boolean result = false;
		Parameters parameters = new Parameters();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		String filename = parameters.getProperty("RECORDDB");
		File f = new File(filename);

		if (!f.exists()) {
			result = false;

		} else {
			List loop = FormatterOutPut.readTaskRecord();
			Iterator it = loop.iterator();
			while (it.hasNext()) {

				Task t = (Task) it.next();
				// System.out.println(taskn + "| " + t.getName() + "|" + taskd
				// + "|" + t.getBelongdate());
				if ((taskn.equals(t.getName()))
						&& (taskd.equals(t.getBelongdate()))) {

					result = true;

					break;

				}

			}

		}
		return result;

	}

	public static void main(String[] args) throws Exception {

		DOMParse d1 = new DOMParse("TaskList.xml");
		//d1.addTaskVector();
        d1.deleteTaskLog();
		

		// DOMParse d2 = new DOMParse("Threadslist.xml");
		// d2.addThreadVector();

		// Format format2 = new SimpleDateFormat("yyyy-MM-dd");
		// Date d = new Date();
		// String nowdate = format2.format(d);
		//
		// List loop = FormatterOutPut.readTaskRecord();
		// Iterator it = loop.iterator();
		// while(it.hasNext()){
		//			
		// Task t=(Task) it.next();
		// //if(!task.getName().equals(t.getName())&&(!task.getBelongdate().equals(nowdate))){
		// System.out.println(t.getName()+nowdate);
		//				
		// }

	}

}
