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

/**
 * <a href="MulticastClientTool.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * A client that listens for multicast messages at a designated port. You may
 * use this to for potential multicast issues when tuning distributed caches.
 * </p>
 *
 * @author Michael C. Han
 *
 */
public class MulticastClientTool {

	public static void main(String[] args) {
        try {
            int port = GetterUtil.getInteger(args[1]);

			DatagramHandler handler = new DatagramHandler() {

				public void process(DatagramPacket packet) {
					String s = new String(
						packet.getData(), 0, packet.getLength());

					System.out.println(s);
				}

				public void errorReceived(Throwable t) {
					t.printStackTrace();
				}

			};

            MulticastTransport transport = new MulticastTransport(
				handler, args[0], port);

			transport.connect();

			synchronized (transport) {
                transport.wait();
            }
        }
        catch (Exception e) {
            e.printStackTrace();

			System.err.println(
				"Usage: java MulticastClientTool multicastAddress port");

			System.exit(1);
        }
    }

}