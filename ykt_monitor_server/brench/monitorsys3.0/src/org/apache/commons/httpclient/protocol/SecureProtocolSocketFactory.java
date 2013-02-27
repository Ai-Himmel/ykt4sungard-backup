/*
 * $Header: /home/jerenkrantz/tmp/commons/commons-convert/cvs/home/cvs/jakarta-commons//httpclient/src/java/org/apache/commons/httpclient/protocol/SecureProtocolSocketFactory.java,v 1.6 2004/04/18 23:51:38 jsdever Exp $
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

package org.apache.commons.httpclient.protocol;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

/**
 * A ProtocolSocketFactory that is secure.
 * 
 * @see org.apache.commons.httpclient.protocol.ProtocolSocketFactory
 * 
 * @author Michael Becke
 * @author <a href="mailto:mbowler@GargoyleSoftware.com">Mike Bowler</a>
 * @since 2.0
 */
public interface SecureProtocolSocketFactory extends ProtocolSocketFactory {

    /**
     * Returns a socket connected to the given host that is layered over an
     * existing socket.  Used primarily for creating secure sockets through
     * proxies.
     * 
     * @param socket the existing socket 
     * @param host the host name/IP
     * @param port the port on the host
     * @param autoClose a flag for closing the underling socket when the created
     * socket is closed
     * 
     * @return Socket a new socket
     * 
     * @throws IOException if an I/O error occurs while creating the socket
     * @throws UnknownHostException if the IP address of the host cannot be
     * determined
     */
    Socket createSocket(
        Socket socket, 
        String host, 
        int port, 
        boolean autoClose
    ) throws IOException, UnknownHostException;              

}
