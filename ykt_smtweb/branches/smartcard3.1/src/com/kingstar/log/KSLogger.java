package com.kingstar.log;

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.util.logging.XMLFormatter;


//��ͨ������ĳ�� getLogger ������������� Logger ������Щ����Ҫô����һ���� Logger��Ҫô����һ�����ʵ����� Logger�� 
//��־��Ϣ��ת������ע��� Handler ���󣬸ö�����Խ���Ϣת��������Ŀ�ĵأ���������̨���ļ���OS ��־�ȵȡ� 
//ÿ�� Logger ����һ��������ص� "Level"���ⷴӳ�˴� logger �����ĵ���� Level��
//����� Logger �ļ�������Ϊ null����ô������Ч����̳��Ը��ף������ͨ���丸��һֱ�������ϵݹ�õ��� 
//���Ը�����־�����ļ�
public class KSLogger {

	String n = "";
	Logger s = null;
	Level l = null;

	public KSLogger(String n) {
		super();
		this.n = n;
		 s = Logger.getLogger(n);
	}

	// fsize - д�뵽�κ�һ���ļ�������ֽ�����
	// count - Ҫʹ�õ��ļ�����
	// append - ָ�� append ģʽ��
	// fformatter-(xml , txt)
	public void addFileHandler(int fsize, int fcount, boolean isappend,
			String formatter) {

		FileHandler myFileHandler=null;
		try {

			// pattern - Ϊ����ļ�������ģʽ��
			// fsize - д�뵽�κ�һ���ļ�������ֽ�����
			// count - Ҫʹ�õ��ļ�����
			// append - ָ�� append ģʽ��
			// ftype-xml or txt
			 myFileHandler = new FileHandler(this.n, fsize, fcount,isappend);

			// SimpleFormatter, XMLFormatter
			// ��Ϊ������FormatterΪSimpleFormatter,�����ļ������ݻ��ɼ򵥸�ʽ������XML��ʽ
			if (formatter.equalsIgnoreCase("xml")) {
				myFileHandler.setFormatter(new XMLFormatter());
			} else
				myFileHandler.setFormatter(new SimpleFormatter());
			
			/*
			 * ��Ϊ��c:\program files\java\jdk1.5.0\jre\lib\logging.properties
			 * Ĭ��������ConsoleHandler,���Բ����Handler�����ڿ���̨������־
			 * ���������myFileHandler,�ͻ����ļ��п�����־(Ĭ��ΪXML��ʽ)
			 */

		} catch (IOException e) {
		}
		s.addHandler(myFileHandler);

//
		//setFilter();
	}

	public void Log(Level l,String m) {
		s = Logger.getLogger(this.n);
  		s.log(l, m);
		
	}

	public void setFilter(int i) {
		s.setFilter(new LogFilter(i));
	}

	//���ù��˼���
	public void setLevel(Level level) {
		s.setLevel(Level.ALL);
		//s.setLevel(level);
	}


	public static void main(String[] args) {

//		Logger s = Logger.getLogger("consoleLog");
//
//		s.log(Level.INFO, "this is a info");
//
//		s.setLevel(Level.WARNING);
//
//		s.setFilter(new LogFilter());
//
//		try {
//
//			// pattern - Ϊ����ļ�������ģʽ��
//			// limit - д�뵽�κ�һ���ļ�������ֽ�����
//			// count - Ҫʹ�õ��ļ�����
//			// append - ָ�� append ģʽ��
//			FileHandler myFileHandler = new FileHandler("application.log",
//					1024000, 3, true);
//
//			// SimpleFormatter, XMLFormatter
//			// ��Ϊ������FormatterΪSimpleFormatter,�����ļ������ݻ��ɼ򵥸�ʽ������XML��ʽ
//			myFileHandler.setFormatter(new SimpleFormatter());
//
//			s.addHandler(myFileHandler);
//
//			/*
//			 * ��Ϊ��c:\program files\java\jdk1.5.0\jre\lib\logging.properties
//			 * Ĭ��������ConsoleHandler,���Բ����Handler�����ڿ���̨������־
//			 * ���������myFileHandler,�ͻ����ļ��п�����־(Ĭ��ΪXML��ʽ)
//			 */
//
//		} catch (IOException e) {
//		}
//		;
//
//		s.log(Level.WARNING, "this is a s.warning");
//
//		// ��ΪmyFilter����˵�����������־,���������ᱻ��¼(Ҳ���ǲ���ʾ����)
//		//
//		// Logger sb = Logger.getLogger("s.b");
//		//
//		// sb.log(Level.INFO, "this is a sb.info");
//		//
//		// // ��Ϊs������LevelΪWARNING,����sb�����ĸ�Logger s�̳��˸�����
//		//
//		// // ����sb��LevelΪWARNING,����INFO��¼���ᱻ����
//		//
//		// sb.log(Level.WARNING, "this is a sb.warning");
		
//		KSLogger s=new KSLogger("sfd");
//		s.addFileHandler(1111111, 2, true, "txt");
//		
//		s.Log(Level.WARNING, "initical");
//		
//		s.Log(Level.CONFIG, "initical");
//		s.Log(Level.WARNING, "initical");
	}

}
