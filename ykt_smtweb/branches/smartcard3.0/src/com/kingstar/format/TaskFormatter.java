package com.kingstar.format;


import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.StringTokenizer;

import com.kingstar.basetask.TaskStateConstants;
import com.kingstar.basetask.bean.Task;

public class TaskFormatter implements TaskStateConstants ,Formatter{
	String separator = "|";
	Task task=null;
	boolean needtime=true;
	public boolean isNeedtime() {
		return needtime;
	}

	public void setNeedtime(boolean needtime) {
		this.needtime = needtime;
	}

	public void setSeparator(String i) {

		separator = i;
	}

	public String getTaskStatus(int i) {
		String s = "";

		if (START == i) {
			s = "��ʼ";
		}
		if (RUN == i) {
			s = "����";

		}
		if (CLOSED == i) {
			s = "�ر�";

		}
		if (ERROR == i) {
			s = "����";

		}

		else {
			s = "δ֪״̬";
		}
		return s;

	}

	public void setTask(Task t) {
		task = t;
	}

	
	public String getFormatData(){
		StringBuffer sb=new StringBuffer();
		 if(true==needtime){
		 Date d=new Date();
		Format format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		 sb.append(format.format(d)).append(separator);
		}
		sb.append(task.getId()).append(separator);
		sb.append(task.getName()).append(separator);
		sb.append(task.getCla()).append(separator);
		sb.append(task.getTasktype()).append(separator);
		sb.append(task.getPriority()).append(separator);
		sb.append(task.getRuntimetype()).append(separator);
		sb.append(task.getRuntimedata()).append(separator);
		sb.append(task.getDescription()).append(separator);
		sb.append(task.getBelongdate()).append(separator);
		sb.append(task.getBelongtype()).append(separator);
		sb.append(task.getStatus());
		return sb.toString();
			
	}
 
 
	public static void main(String[] args){
		
	
	}
}