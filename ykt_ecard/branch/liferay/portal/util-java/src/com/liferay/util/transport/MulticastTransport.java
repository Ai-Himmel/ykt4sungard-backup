/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.util.transport;

import java.io.IOException;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MulticastTransport.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * The MulticastTransport will send strings across a specified multicast
 * address. It will also listen for messages and hand them to the appropriate
 * DatagramHandler.
 * </p>
 *
 * @author Michael C. Han
 *
 */
public class MulticastTransport extends Thread implements Transport {

	public MulticastTransport(DatagramHandler handler, String host, int port) {
        super("MulticastListener-" + host + port);

		setDaemon(true);
        _handler = handler;
        _host = host;
        _port = port;
    }

    public synchronized void connect() throws IOException {
        if (_socket == null) {
            _socket = new MulticastSocket(_port);
        }
        else if (_socket.isConnected() && _socket.isBound()) {
            return;
        }

		_address = InetAddress.getByName(_host);

		_socket.joinGroup(_address);

		_connected = true;

		start();
    }

    public synchronized void disconnect() {

		// Interrupt all processing

		if (_address != null) {
            try {
                _socket.leaveGroup(_address);
                _address = null;
            }
            catch (IOException e) {
                _log.error("Unable to leave group", e);
            }
        }

		_connected = false;

		interrupt();

		_socket.close();
    }

    public synchronized void sendMessage(String msg) throws IOException {
        _outboundPacket.setData(msg.getBytes());
        _outboundPacket.setAddress(_address);
        _outboundPacket.setPort(_port);

		_socket.send(_outboundPacket);
    }

    public boolean isConnected() {
        return _connected;
    }

    public void run() {
        try {
            while (_connected) {
                _socket.receive(_inboundPacket);
                _handler.process(_inboundPacket);
            }
        }
        catch (IOException e) {
            _log.error("Unable to process ", e);

			_socket.disconnect();

			_connected = false;

			_handler.errorReceived(e);
        }
    }

    private static final Log _log = LogFactory.getLog(MulticastTransport.class);

	private final byte[] _inboundBuffer = new byte[4096];

	private final DatagramPacket _inboundPacket =
        new DatagramPacket(_inboundBuffer, _inboundBuffer.length);

	private final byte[] _outboundBuffer = new byte[4096];

	private final DatagramPacket _outboundPacket =
        new DatagramPacket(_outboundBuffer, _outboundBuffer.length);

    private final String _host;
    private final DatagramHandler _handler;
    private final int _port;
    private boolean _connected;
    private MulticastSocket _socket;
    private InetAddress _address;

}