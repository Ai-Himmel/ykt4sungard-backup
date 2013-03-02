package com.kingstar.log;

import java.util.logging.Filter;
import java.util.logging.LogRecord;

//ALL  Integer.MAX_VALUE。 
// SEVERE（最高值） 1000
// WARNING        900
//INFO           800
//CONFIG        700
//FINE          600
//FINER         500
//FINEST（最低值）400

class LogFilter implements Filter {
	int v = 0;

	public LogFilter(int v) {
		super();
		this.v = v;
	}

	public LogFilter() {
		super();
	}

	public boolean isLoggable(LogRecord record) {

		if (record.getLevel().intValue() > v) {
			return true;
		} else
			return false;

	}

}
