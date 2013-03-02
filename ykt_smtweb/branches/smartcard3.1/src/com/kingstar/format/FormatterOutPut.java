package com.kingstar.format;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import com.kingstar.basetask.bean.Task;
import com.kingstar.db.Pool;
import com.kingstar.files.Parameters;

public class FormatterOutPut {

	private static Parameters parameters;

	
	//write task log file
	public synchronized static void writeTaskLog(Task t) {
		parameters = new Parameters();
		try {
			parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		FileWriter f;
		TaskFormatter formatter = new TaskFormatter();
		BufferedWriter bw = null;

		File file1 = new File(parameters.getProperty("TASKLOG"));
		if (!file1.exists()) {
			try {
				f = new FileWriter(parameters.getProperty("TASKLOG"));
				bw = new BufferedWriter(f);
				formatter.setTask(t);
				bw.write(formatter.getFormatData());
				bw.newLine();
				// f1.write("\r\n");
				bw.flush();
				bw.close();
				f.close();
				file1=null;
			} catch (IOException e) {
				e.printStackTrace();
			}

		} else if (file1.exists() && file1.canWrite()) {

			try {
				f = new FileWriter(parameters.getProperty("TASKLOG"), true);
				bw = new BufferedWriter(f);
				formatter.setTask(t);
				bw.write(formatter.getFormatData());
				bw.newLine();
				// f1.write("\r\n");
				bw.flush();
				bw.close();
				f.close();
				file1=null;
			} catch (IOException e) {
				e.printStackTrace();
			}

		}
	}

	// write taskhistory in log
	public synchronized static void writeTaskHistory(Task t){
		parameters = new Parameters();
		try {
			parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		
		String taskHistorytype=parameters.getProperty("TASKHISTORYTYPE");
		if(taskHistorytype.equalsIgnoreCase("FILE")){
			writeTaskHistoryLog(t);
		}
		else if(taskHistorytype.equalsIgnoreCase("DB")){
			
			try {
				insertTaskHistory(t);
			} catch (Exception e) {
				 
				e.printStackTrace();
			}
			
		}
		
	}
//	 write taskhistory in db
	public synchronized static void insertTaskHistory(Task t) throws Exception{
		parameters = new Parameters();
		try {
			parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		int db=parameters.getPropertyI("DEFAULTDB");
		Pool p=new Pool();
		p.getPool(db);
		
		StringBuffer sb=new StringBuffer();
		
		sb.append("insert into taskhistory  values (");
		sb.append("'").append(t.getId()).append("'").append(" ,");
		sb.append("'").append(t.getName()).append("'").append(" ,");
		sb.append("'").append(t.getCla()).append("'").append(" ,");
		sb.append("'").append(t.getPriority()).append("'").append(" ,");
		sb.append("'").append(t.getTasktype()).append("'").append(" ,");
		sb.append("'").append(t.getRuntimetype()).append("'").append(" ,");
		sb.append("'").append(t.getRuntimedata()).append("'").append(" ,");
		sb.append("'").append(t.getDescription()).append("'").append(" ,");
		sb.append("'").append(t.getStatus()).append("'").append(" ,");
		sb.append("'").append(t.getBelongdate()).append("'").append(" ,");
		sb.append("'").append(t.getBelongtype()).append("'");
		sb.append(")");
		 
		p.Update(sb.toString());
		
		p.close(db);
		
	}
	public synchronized static void writeTaskHistoryLog(Task t) {
		try {
			parameters = new Parameters();
			parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
			String TASKHISTORYFILE1 = parameters
					.getProperty("TASKHISTORYLOG");

			FileWriter f;

			TaskFormatter formatter = new TaskFormatter();

			BufferedWriter bw = null;

			File file2 = new File(TASKHISTORYFILE1);
			if (!file2.exists()) {
				f = new FileWriter(TASKHISTORYFILE1);
				bw = new BufferedWriter(f);
				formatter.setTask(t);
				bw.write(formatter.getFormatData());
				bw.newLine();
				// f1.write("\r\n");
				bw.flush();
				bw.close();
				f.close();
				file2=null;

			}
		//	if (file2.exists() && file2.canWrite()) {
			else{
				f = new FileWriter(TASKHISTORYFILE1, true);
				bw = new BufferedWriter(f);
				formatter.setTask(t);
				bw.write(formatter.getFormatData());
				bw.newLine();
				// f1.write("\r\n");
				bw.flush();
				bw.close();
				f.close();
				file2=null;
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	// ########################################################
	// write task objects operation
	public synchronized static void writeTaskRecord(Task t) throws Exception {
		parameters = new Parameters();
		ArrayList ary = new ArrayList();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		String filename = parameters.getProperty("RECORDDB");

		File file = new File(filename);
		if (!file.exists()) {

			FileOutputStream ostream = new FileOutputStream(filename);
			ObjectOutputStream out = new ObjectOutputStream(ostream);
			ary.add(t);
			out.writeObject(ary);
			out.flush();
			out.close();
			ostream.close();
			ary=null;
			file=null;

		}

		else{
			ary = readTaskRecord();

			FileOutputStream ostream2 = new FileOutputStream(filename);

			ObjectOutputStream out2 = new ObjectOutputStream(ostream2);

			ary.add(t);
			out2.writeObject(ary);
			out2.flush();

			out2.close();
			ostream2.close();
			ary=null;
			file = null;
		}
		
		

	}

	// get task objects operation
	public synchronized static ArrayList readTaskRecord() throws Exception {
		parameters = new Parameters();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		String filename = parameters.getProperty("RECORDDB");
		FileInputStream fis = new FileInputStream(filename);
		ObjectInputStream ois = new ObjectInputStream(fis);
		ArrayList e;

		e = (ArrayList) ois.readObject();

		ois.close();
		fis.close();
		return e;

	}

	// ###############################################################
	// history operation
	public synchronized static void StoreTaskHistorys(Task t) throws Exception {
		parameters = new Parameters();
		ArrayList ary = new ArrayList();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");

		String filename = parameters.getProperty("HISTORYDB");

		File file = new File(filename);
		if (!file.exists()) {

			FileOutputStream ostream = new FileOutputStream(filename);
			ObjectOutputStream out = new ObjectOutputStream(ostream);
			ary.add(t);
			out.writeObject(ary);
			out.flush();

			out.close();
			ostream.close();
			ary=null;
			file=null;

		}
	
		else{
			ary = readTaskHistoryFromfile();

			FileOutputStream ostream2 = new FileOutputStream(filename);

			ObjectOutputStream out2 = new ObjectOutputStream(ostream2);

			ary.add(t);
			out2.writeObject(ary);
			out2.flush();

			out2.close();
			ostream2.close();
			ary=null;
			file=null;
		}
		

	}

	public synchronized static ArrayList readTaskHistoryFromfile() throws Exception {
		parameters = new Parameters();
		parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		String filename = parameters.getProperty("HISTORYDB");
		FileInputStream fis = new FileInputStream(filename);
		ObjectInputStream ois = new ObjectInputStream(fis);
		ArrayList e;

		e = (ArrayList) ois.readObject();

		ois.close();
		fis.close();
		return e;

	}

	// compare task is runed
	public synchronized static boolean isruned(Task task) {
		parameters = new Parameters();
		try {
			parameters.load("D:\\tomcat5\\webapps\\smartcardweb\\WEB-INF\\classes\\console.ini");
		} catch (IOException e1) {

			e1.printStackTrace();
		}
		String filename = parameters.getProperty("HISTORYDB");
		boolean result = false;

		File file = new File(filename);
		if (!file.exists()) {
			result = false;
		} else {
			ArrayList t;
			try {
				t = readTaskHistoryFromfile();

				for (int i = 0; i < t.size(); i++) {
					Task temp = (Task) t.get(i);
					if (task.getId() == (temp.getId())) {
                  
						result = true;
						break;

					}
				}
			} catch (Exception e) {

				e.printStackTrace();
			}
		}
		file = null;
		return result;

	}

	// end history operation
	// ###############################################################

	public static void main(String[] args) throws Exception {

		// Task t = new Task();
		// Task t1 = new Task();
		// Task t2 = new Task();
		// t.setName("aaa");
		// t1.setName("bbb");
		// t2.setName("ccc");
		// 		
		// FormatterOutPut.writeTaskTOfile(t);
		// FormatterOutPut.writeTaskTOfile(t1);
		// FormatterOutPut.writeTaskTOfile(t2);

	//ArrayList a = FormatterOutPut.readTaskHistoryFromfile();
		ArrayList a = FormatterOutPut.readTaskRecord();
		for (int i = 0; i < a.size(); i++) {
			Task tt = (Task) a.get(i);

			tt.debug();

		}
	}

}
