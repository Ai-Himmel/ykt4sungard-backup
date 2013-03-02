package com.kingstar.log;

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;
import java.util.logging.XMLFormatter;


//可通过调用某个 getLogger 工厂方法来获得 Logger 对象。这些方法要么创建一个新 Logger，要么返回一个合适的现有 Logger。 
//日志消息被转发到已注册的 Handler 对象，该对象可以将消息转发到各种目的地，包括控制台、文件、OS 日志等等。 
//每个 Logger 都有一个与其相关的 "Level"。这反映了此 logger 所关心的最低 Level。
//如果将 Logger 的级别设置为 null，那么它的有效级别继承自父亲，这可以通过其父亲一直沿树向上递归得到。 
//可以根据日志配置文件
public class KSLogger {

	String n = "";
	Logger s = null;
	Level l = null;

	public KSLogger(String n) {
		super();
		this.n = n;
		 s = Logger.getLogger(n);
	}

	// fsize - 写入到任何一个文件的最大字节数。
	// count - 要使用的文件数。
	// append - 指定 append 模式。
	// fformatter-(xml , txt)
	public void addFileHandler(int fsize, int fcount, boolean isappend,
			String formatter) {

		FileHandler myFileHandler=null;
		try {

			// pattern - 为输出文件命名的模式。
			// fsize - 写入到任何一个文件的最大字节数。
			// count - 要使用的文件数。
			// append - 指定 append 模式。
			// ftype-xml or txt
			 myFileHandler = new FileHandler(this.n, fsize, fcount,isappend);

			// SimpleFormatter, XMLFormatter
			// 因为设置了Formatter为SimpleFormatter,所以文件的内容会变成简单格式而不是XML格式
			if (formatter.equalsIgnoreCase("xml")) {
				myFileHandler.setFormatter(new XMLFormatter());
			} else
				myFileHandler.setFormatter(new SimpleFormatter());
			
			/*
			 * 因为在c:\program files\java\jdk1.5.0\jre\lib\logging.properties
			 * 默认设置了ConsoleHandler,所以不添加Handler都会在控制台看到日志
			 * 现在添加了myFileHandler,就会在文件中看到日志(默认为XML格式)
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

	//设置过滤级别
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
//			// pattern - 为输出文件命名的模式。
//			// limit - 写入到任何一个文件的最大字节数。
//			// count - 要使用的文件数。
//			// append - 指定 append 模式。
//			FileHandler myFileHandler = new FileHandler("application.log",
//					1024000, 3, true);
//
//			// SimpleFormatter, XMLFormatter
//			// 因为设置了Formatter为SimpleFormatter,所以文件的内容会变成简单格式而不是XML格式
//			myFileHandler.setFormatter(new SimpleFormatter());
//
//			s.addHandler(myFileHandler);
//
//			/*
//			 * 因为在c:\program files\java\jdk1.5.0\jre\lib\logging.properties
//			 * 默认设置了ConsoleHandler,所以不添加Handler都会在控制台看到日志
//			 * 现在添加了myFileHandler,就会在文件中看到日志(默认为XML格式)
//			 */
//
//		} catch (IOException e) {
//		}
//		;
//
//		s.log(Level.WARNING, "this is a s.warning");
//
//		// 因为myFilter会过滤掉上面这条日志,所以它不会被记录(也就是不显示出来)
//		//
//		// Logger sb = Logger.getLogger("s.b");
//		//
//		// sb.log(Level.INFO, "this is a sb.info");
//		//
//		// // 因为s设置了Level为WARNING,所以sb从它的父Logger s继承了该属性
//		//
//		// // 所以sb的Level为WARNING,所以INFO记录不会被发布
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
