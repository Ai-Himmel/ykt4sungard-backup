package com.kingstar.log;

import java.util.logging.Level;

import com.kingstar.files.Parameters;

//ALL  Integer.MAX_VALUE。 
//SEVERE（最高值） 1000
//WARNING        900
//INFO           800
//CONFIG        700
//FINE          600
//FINER         500
//FINEST（最低值）400
public class LogFactory {

	private static KSLogger instance = null;

	public static synchronized KSLogger getInstance() throws Exception {

		if (instance == null) {

			// 取出相关log参数
			Parameters p = new Parameters();
			p.load("console.ini");

			instance = new KSLogger(p.getProperty("LOGFILENAME"));

			// instance.addFileHandler(fsize, fcount, isappend, formatter)
			instance.addFileHandler(p.getPropertyI("LOGSIZE"), p
					.getPropertyI("FILECOUNT"), p.getPropertyBool("ISAPPEND"),
					p.getProperty("LOGFORMAT"));

			//set log filter level
			instance.setLevel(getLevel(p.getPropertyI("FILTERLEVEL")));
			// instance.setFilter(0);
		}
		return instance;

	}


	public static Level getLevel(int level) {
		Level l = null;
		switch (level) {

		case Integer.MAX_VALUE:
			l = Level.ALL;
		case 1000:
			l = Level.SEVERE;
		case 900:
			l = Level.WARNING;
		case 800:
			l = Level.INFO;
		case 700:
			l = Level.CONFIG;
		case 600:
			l = Level.FINE;
		case 500:
			l = Level.FINER;
		case 400:
			l = Level.FINEST;

		}
		return l;

	}

	public static void main(String args[]) throws Exception {

		KSLogger log = LogFactory.getInstance();

		log.Log(Level.WARNING, "test");
		log.Log(Level.WARNING, "THIS IS TEST LOG");

	}
}
