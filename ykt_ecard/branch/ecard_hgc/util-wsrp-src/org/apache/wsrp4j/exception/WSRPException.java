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

package org.apache.wsrp4j.exception;

/**
 * Common Exception class within the WSRP environment 
 */
public class WSRPException extends Exception {

	/*
	 Holds the message identifier - enables a  more comfortable error handling
	 */
	private int errCode = 0;

	private Throwable nestedThrowable = null;

	// exception is in the common range
	private static final int COMMON_EXCEPTION = 1;

	// exception is in the consumer range
	private static final int CONSUMER_EXCEPTION = 2;

	// exception is in the producer range
	private static final int PRODUCER_EXCEPTION = 4;

	// exception is in the provider range
	private static final int PROVIDER_EXCEPTION = 8;

	// type (range) of the exception
	private int exceptionRange = 0;

	/*
	 Creates a new common exception
	 @deprecated
	 */
	public WSRPException() {
		this(0, null);
	}

	/**
	 Creates a new common excpetion. The message to be passed will be ignored
	 @param errorCode integer representing an error code
	 */
	public WSRPException(int errorCode) {
		this(errorCode, null);
	}

	/**
	 Creates a new common excpetion. The message to be passed will be ignored
	 @param errorCode integer representing an error code
	 @param t Throwable to be wrapped
	 */
	public WSRPException(int errorCode, Throwable t) {
		//String message = Messages.get(errorCode);
		super(Messages.get(errorCode));
		errCode = errorCode;
		nestedThrowable = t;
	}

	/**
	 Returns an error code
	 @return integer representing an error code
	 */
	public int getErrorCode() {
		return errCode;
	}

	/**
	 Returns a nested Throwable
	 @return Throwable if a nested Throwable exists or null
	 */
	public Throwable getNestedThrowable() {
		return nestedThrowable;
	}

	/**
	 * Returns  the exception as String
	 */
	public String toString() {
		StringBuffer s = new StringBuffer(this.getClass().getName());
		s.append(": ");
		s.append(getMessage());
		if (nestedThrowable != null) {
			s.append("\n\nNested Throwable is:\n");
			s.append(nestedThrowable.toString());
		}
		return s.toString();
	}

	/**
	 * Returns the Exception in the HTML string format. Nested
	 * exceptions are included in the report.
	 * 
	 * @returns exception message formatted as HTML string
	 */
	public String toHTMLString() {

		StringBuffer s = new StringBuffer();

		s.append("<H2>Exception occured!</H2><br>");
		s.append("<b>" + this.getClass().getName() + "</><br>");
		s.append("   Message = " + getMessage() + "<br>");
		s.append("   Type    = " + getExceptionRange() + "<br>");

		if (this.nestedThrowable != null) {

			Throwable t = nestedThrowable;
			s.append("<H3>Exception stack:</H3>");

			while (t != null) {
				s.append("<br><b>" + t.getClass().getName() + "</><br>");
				if (t instanceof WSRPException) {
					s.append("   Message = " + ((WSRPException) t).getMessage()
							+ "<br>");
					s.append("   Type    = "
							+ ((WSRPException) t).getExceptionRange() + "<br>");
					t = ((WSRPException) t).getNestedThrowable();
				}
				else {
					s.append("   Message = " + t.getMessage() + "<br>");
					t = null;
				}
			}
		}

		return s.toString();
	}

	/**
	 * Returns the range identifier of this exception. E.g.
	 * Common, Consumer, Producer or Provider range. 
	 * 
	 * @return the exception range id
	 */
	public int getExceptionRange() {

		return exceptionRange;
	}

	/**
	 * Assign the exception to the common range
	 */
	public void setCommonExceptionRange() {

		exceptionRange = COMMON_EXCEPTION;
	}

	/**
	 * Assign the exception to the consumer range
	 */
	public void setConsumerExceptionRange() {

		exceptionRange = CONSUMER_EXCEPTION;
	}

	/**
	 * Assign the exception to the producer range
	 */
	public void setProducerExceptionRange() {

		exceptionRange = PRODUCER_EXCEPTION;
	}

	/**
	 * Assign the exception to the provider range
	 */
	public void setProviderExceptionRange() {

		exceptionRange = PROVIDER_EXCEPTION;
	}
}