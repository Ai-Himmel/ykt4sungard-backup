package org.king.monitor.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.king.support.util.GetPropertiesUtil;
import org.king.support.util.SimpleEncoding;

import com.trilead.ssh2.Connection;
import com.trilead.ssh2.Session;
import com.trilead.ssh2.StreamGobbler;

public class MonitorUtils {
	
	public static String commandExec(String hostAddress,String commandLine,String commandArgs) throws IOException{
		if(getServerOS().indexOf("Windows")!=-1){
			return wincommandExec(hostAddress, commandLine, commandArgs);
		}else{
			return unixcommandExec(hostAddress, commandLine, commandArgs);
		}		
	}
	
	public static String unixcommandExec(String hostAddress,String commandLine,String commandArgs) throws IOException{
		Runtime runtime = Runtime.getRuntime();
		Process process = null;
		String line = null;
		String message ="";
		
		String execCommand = commandLine;
		
		InputStream is = null;
		InputStreamReader isr = null;
		BufferedReader br = null;
		if(commandLine.indexOf("$HOSTADDRESS$")!=-1){
			execCommand = commandLine.replace("$HOSTADDRESS$", hostAddress);
		}
		if(commandArgs!=null){
			String cmdargs[] = commandArgs.split("!");
			for(int i=0;i<cmdargs.length;i++){
				if(commandLine.indexOf("$ARG"+(i+1)+"$")!=-1){
					execCommand = execCommand.replace("$ARG"+(i+1)+"$", cmdargs[i]);
				}
			}
		}
		try {
			System.out.println(execCommand);
			process = runtime.exec(execCommand);
			is = process.getInputStream();
			isr = new InputStreamReader(is);
			br = new BufferedReader(isr);
			//不止取第一行返回信息
			while ((line = br.readLine()) != null) {
					message += line +" ";
			}
			br.close();
			isr.close();
			is.close();
		} catch (IOException e) {
			e.printStackTrace();
			throw new IOException("command:"+execCommand+" call failure!");
		}
		
		return message;
	}
	
	public static String wincommandExec(String hostAddress,String commandLine,String commandArgs) throws IOException{
		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		String server =config.getString("nagios.server.ip");
		String username =config.getString("nagios.server.username");
		String password = config.getString("nagios.server.password");
		try {
			password =new String(SimpleEncoding.decode(SimpleEncoding.hex2byte(password),"kingstar".getBytes()));
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		String message ="";
		try
		{
			/* Create a connection instance */

			Connection conn = new Connection(server);

			/* Now connect */

			conn.connect();

			/* Authenticate.
			 * If you get an IOException saying something like
			 * "Authentication method password not supported by the server at this stage."
			 * then please check the FAQ.
			 */

			boolean isAuthenticated = conn.authenticateWithPassword(username, password);

			if (isAuthenticated == false)
				throw new IOException("Authentication failed.");

			/* Create a session */

			Session sess = conn.openSession();
			String execCommand = commandLine;
			String line = null;
			
			if(commandLine.indexOf("$HOSTADDRESS$")!=-1){
				execCommand = commandLine.replace("$HOSTADDRESS$", hostAddress);
			}
			String cmdargs[] = commandArgs.split("!");
			for(int i=0;i<cmdargs.length;i++){
				if(commandLine.indexOf("$ARG"+(i+1)+"$")!=-1){
					execCommand = execCommand.replace("$ARG"+(i+1)+"$", cmdargs[i]);
				}
			}

			sess.execCommand(execCommand);

			/* 
			 * This basic example does not handle stderr, which is sometimes dangerous
			 * (please read the FAQ).
			 */

			InputStream stdout = new StreamGobbler(sess.getStdout());

			BufferedReader br = new BufferedReader(new InputStreamReader(stdout));

			
			//不止取第一行返回信息
			while ((line = br.readLine()) != null) {
					message += line +" ";
			}

			/* Show exit status, if available (otherwise "null") */

			System.out.println("ExitCode: " + sess.getExitStatus());

			/* Close this session */

			sess.close();

			/* Close the connection */

			conn.close();

		}
		catch (IOException e)
		{
			e.printStackTrace(System.err);
		}
		return message;
	}

	public static String getServerOS(){
		return System.getProperties().getProperty("os.name");
	}
	
	public static String pingCheck(String ipAddr) {
		String message = "up";
		Runtime runtime = Runtime.getRuntime();
		Process process = null;
		String line = null;
		InputStream is = null;
		InputStreamReader isr = null;
		BufferedReader br = null;
		String ip = ipAddr;
		try {
			// 根据CMD去PING IP
			if(getServerOS().indexOf("Windows")!=-1){
				process = runtime.exec("ping  " + ip + " -w 1 -n 1");
			}else{				
				process = runtime.exec("ping  " + ip + " -w 1 -c 1");
			}	
			is = process.getInputStream();
			isr = new InputStreamReader(is);
			br = new BufferedReader(isr);
			while ((line = br.readLine()) != null) {
				if ("Request timed out.".equals(line)
						|| (line.length() > 3 && (line.trim()
								.indexOf("Ping request could not")) >= 0)
						|| (line.trim().indexOf("connect: Invalid argument")>=0) || (line.trim().indexOf("0 received")>=0)) {
					message = "down";
				}
			}
			br.close();
			isr.close();
			is.close();
		} catch (IOException e) {
			message = "down";
			e.printStackTrace();
		}
		return message;
	}

}
