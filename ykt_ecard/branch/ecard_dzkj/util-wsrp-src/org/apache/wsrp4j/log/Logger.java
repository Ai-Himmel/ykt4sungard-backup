/*
 * Copyright 2000-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 

 */

package org.apache.wsrp4j.log;

/**
 <CODE>Logger</CODE> defines the methods which are used to create logging messages.
 <P>
 Logging levels are: <BR>
 <DL>
 <DT><CODE>ERROR</CODE>
 <DD>A serious failure in the execution of the application
 <DT><CODE>WARN</CODE>
 <DD>An abnormal condition has been detected. The user may have to take action, but the
 running code is able to handle this condition without ultimately failing.
 <DT><CODE>INFO</CODE>
 <DD>A condition that is worth noting but that does not require the user to perform
 an action.
 <DT><CODE>TRACE_LOW</CODE>
 <DD>A low-detail trace message.
 <DT><CODE>TRACE_MEDIUM</CODE>
 <DD>A medium-detail trace message.
 <DT><CODE>TRACE_HIGH</CODE>
 <DD>A high-detail trace message.
 </DL>
 <BR>
 
 Plain-text messages can be logged through the <CODE>text(...)</CODE> methods. These
 messages are generally hard-coded into the application.<BR>
 These methods should only be used for logging trace data.
 <P>
 In addition, the following specialized methods are available to log trace information.
 Each of these trace methods is a convenience to the application programmer:
 <DL>
 <DT><CODE>entry</CODE>
 <DD>Logs entry into a method.
 <DT><CODE>exit</CODE>
 <DD>Logs exit from a method.
 <DT><CODE>stackTrace</CODE>
 <DD>Logs the call stack.
 </DL>
 <P>
 For performance reasons the method <CODE>isLogging(int logLevel)</CODE> should be used
 to check if a given logging level is written at all to the output. The method should
 be used for the log message level entries, but is absolutely required to be called for
 trace messages to avoid unnecessary round-trips and object creation.<BR>
 <P>
 */

public interface Logger {
	/**
	 Defines an error message.<BR>
	 Use this type to inform the user of a serious failure in the execution of the application.
	 */
	public static final int ERROR = 10;

	/**
	 Defines a warning message.<BR>
	 Use this type to inform a user that an abnormal condition has been detected. The user
	 may have to take action, but the running code is able to handle this condition without
	 ultimately failing.<BR>
	 A warning message is less severe than an error message.
	 */
	public static final int WARN = 20;

	/**
	 Defines an informational message.<BR>
	 Use this type to indicate conditions that are worth noting but that do not require a
	 user to take any precautions or perform an action. Do not use this log level for
	 repeating events.<BR>
	 An informational message is less severe than a warning message.
	 */
	public static final int INFO = 30;

	/**
	 Defines a low-detail trace message.
	 */
	public static final int TRACE_LOW = 40;

	/**
	 Defines a medium-detail trace message.
	 */
	public static final int TRACE_MEDIUM = 50;

	/**
	 Defines a high-detail trace message.
	 */
	public static final int TRACE_HIGH = 60;

	/**
	 Determines if this logger is logging data for a given log level or not.
	 *
	 @param logLevel      The log level to be checked.
	 @return <code>true</code> when the object is logging the log level;
	 <code>false</code> otherwise.
	 */
	public boolean isLogging(int logLevel);

	/**
	 Logs a text message with no parameters.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param text          The message text.
	 */
	public void text(int logLevel, String loggingMethod, String text);

	/**
	 Logs a text message with one parameter.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param text          The message text.
	 @param parm1         An element to be displayed with the message.
	 */
	public void text(int logLevel, String loggingMethod, String text,
			Object parm1);

	/**
	 Logs a text message with an array of parameters.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param text          The message text.
	 @param parms         An array of elements to be displayed with the message.
	 */
	public void text(int logLevel, String loggingMethod, String text,
			Object[] parms);

	/**
	 Logs a text message with no parameters.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param t             The throwable that is cause for this log entry.
	 @param text          The message text.
	 */
	public void text(int logLevel, String loggingMethod, Throwable t,
			String text);

	/**
	 Logs a text message with an array of parameters.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param t             The throwable that is cause for this log entry.
	 @param text          The message text.
	 @param parms         An array of elements to be displayed with the message.
	 */
	public void text(int logLevel, String loggingMethod, Throwable t,
			String text, Object[] parms);

	/**
	 Logs entry into a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 */
	public void entry(int logLevel, String loggingMethod);

	/**
	 Logs entry into a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param parm1         An element to be displayed as trace data.
	 */
	public void entry(int logLevel, String loggingMethod, Object parm1);

	/**
	 Logs entry into a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param parms         An array of parameters passed to the method.
	 */
	public void entry(int logLevel, String loggingMethod, Object[] parms);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 */
	public void exit(int logLevel, String loggingMethod);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, byte retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, short retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, int retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, long retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, float retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, double retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, char retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, boolean retValue);

	/**
	 Logs exit from a method.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param retValue      The returned value.
	 */
	public void exit(int logLevel, String loggingMethod, Object retValue);

	/**
	 Logs the call stack.
	 *
	 @param logLevel      The level of the log entry.
	 @param loggingMethod The name of the logging method.
	 @param text          The message text.
	 */
	public void stackTrace(int logLevel, String loggingMethod, String text);
}