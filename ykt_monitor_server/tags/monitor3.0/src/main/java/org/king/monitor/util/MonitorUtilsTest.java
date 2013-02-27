package org.king.monitor.util;

import java.io.IOException;

import junit.framework.TestCase;

public class MonitorUtilsTest extends TestCase {

	public void testCommandExec() {
		try {
			MonitorUtils.commandExec("10.49.188.250", "check_ping -H $HOSTADDRESS$ -w $ARG1$ -c $ARG2$ -p 5", "123!123");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
