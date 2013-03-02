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

package com.liferay.portal.kernel.portlet;

import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="LiferayWindowState.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LiferayWindowState extends WindowState {

	public final static WindowState EXCLUSIVE = new WindowState("exclusive");

	public final static WindowState POP_UP = new WindowState("pop_up");

	public static boolean isExclusive(HttpServletRequest req) {
		String state = req.getParameter("p_p_state");

		if ((state != null) && (state.equals(EXCLUSIVE.toString()))) {
			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isMaximized(HttpServletRequest req) {
		String state = req.getParameter("p_p_state");

		if ((state != null) &&
			(state.equals(WindowState.MAXIMIZED.toString()))) {

			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isPopUp(HttpServletRequest req) {
		String state = req.getParameter("p_p_state");

		if ((state != null) && (state.equals(POP_UP.toString()))) {
			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isWindowStatePreserved(
		WindowState oldWindowState, WindowState newWindowState) {

		// Changes to EXCLUSIVE are always preserved

		if ((newWindowState != null) &&
			(newWindowState.equals(LiferayWindowState.EXCLUSIVE))) {

			return true;
		}

		// Some window states are automatically preserved

		if ((oldWindowState != null) &&
			(oldWindowState.equals(LiferayWindowState.POP_UP))) {

			return false;
		}
		else {
			return true;
		}
	}

	public LiferayWindowState(String name) {
		super(name);
	}

}