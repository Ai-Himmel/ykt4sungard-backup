/*
 * $Header: /home/jerenkrantz/tmp/commons/commons-convert/cvs/home/cvs/jakarta-commons//httpclient/src/java/org/apache/commons/httpclient/auth/MalformedChallengeException.java,v 1.6 2004/05/13 04:02:00 mbecke Exp $
 * $Revision: 155418 $
 * $Date: 2005-02-26 08:01:52 -0500 (Sat, 26 Feb 2005) $
 *
 * ====================================================================
 *
 *  Copyright 2002-2004 The Apache Software Foundation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 */

package org.apache.commons.httpclient.auth;

import org.apache.commons.httpclient.ProtocolException;

/**
 * Signals that authentication challenge is in some way invalid or 
 * illegal in the given context
 *
 * @author <a href="mailto:oleg@ural.ru">Oleg Kalnichevski</a>
 * 
 * @since 2.0
 */
public class MalformedChallengeException extends ProtocolException {

    /**
     * Creates a new MalformedChallengeException with a <tt>null</tt> detail message. 
     */
    public MalformedChallengeException() {
        super();
    }

    /**
     * Creates a new MalformedChallengeException with the specified message.
     * 
     * @param message the exception detail message
     */
    public MalformedChallengeException(String message) {
        super(message);
    }

    /**
     * Creates a new MalformedChallengeException with the specified detail message and cause.
     * 
     * @param message the exception detail message
     * @param cause the <tt>Throwable</tt> that caused this exception, or <tt>null</tt>
     * if the cause is unavailable, unknown, or not a <tt>Throwable</tt>
     * 
     * @since 3.0
     */
    public MalformedChallengeException(String message, Throwable cause) {
        super(message, cause);
    }
}
