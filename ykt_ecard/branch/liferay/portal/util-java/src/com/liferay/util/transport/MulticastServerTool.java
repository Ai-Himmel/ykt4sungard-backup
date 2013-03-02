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

import com.liferay.portal.kernel.util.GetterUtil;

import java.net.DatagramPacket;
import java.net.InetAddress;

/**
 * <a href="MulticastServerTool.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * A server that will send out heart beat messages until you kill it. This
 * enables you to try and debug multicast issues.
 * </p>
 *
 * @author Michael C. Han
 *
 */
public class MulticastServerTool {

	public static void main(String[] args) {
        try {
            int port = GetterUtil.getInteger(args[1]);
            long interval = GetterUtil.getLong(args[2]);

			DatagramHandler handler = new DatagramHandler() {

				public void process(DatagramPacket packet) {
					String s =
						new String(packet.getData(), 0, packet.getLength());
					System.out.println(s);
				}

				public void errorReceived(Throwable t) {
					t.printStackTrace();
				}

			};

			MulticastTransport transport = new MulticastTransport(
                handler, args[0], port);

			transport.connect();

			String msg =
				InetAddress.getLocalHost().getHostName() + ":" + port +
					" heartbeat " ;

			int i = 0;

			while (true) {
                transport.sendMessage(msg + i);

				i++;

				Thread.sleep(interval);
            }
        }
        catch (Exception e) {
            e.printStackTrace();

			System.err.println(
				"Usage: java MulticastServerTool multicastAddress port " +
					"interval");

			System.exit(1);
        }
    }

}