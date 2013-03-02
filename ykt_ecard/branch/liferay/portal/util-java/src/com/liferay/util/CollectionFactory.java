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

package com.liferay.util;

import com.liferay.portal.kernel.util.GetterUtil;

import edu.emory.mathcs.backport.java.util.concurrent.ConcurrentHashMap;
import edu.emory.mathcs.backport.java.util.concurrent.CopyOnWriteArrayList;

import gnu.trove.THashMap;
import gnu.trove.THashSet;
import gnu.trove.TLinkedList;

import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * <a href="CollectionFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CollectionFactory {

	static boolean useTrove = GetterUtil.getBoolean(
		SystemProperties.get("trove"), true);

	static {
		if (useTrove) {
			try {
				Class.forName("gnu.trove.THashMap");
			}
			catch (Exception e) {
				useTrove = false;
			}
		}
	}

	public static Map getHashMap() {
		if (useTrove) {
			return new THashMap();
		}
		else {
			return new HashMap();
		}
	}

	public static Map getHashMap(int capacity) {
		if (useTrove) {
			return new THashMap(capacity);
		}
		else {
			return new HashMap(capacity);
		}
	}

	public static Set getHashSet() {
		if (useTrove) {
			return new THashSet();
		}
		else {
			return new HashSet();
		}
	}

	public static Set getHashSet(int capacity) {
		if (useTrove) {
			return new THashSet(capacity);
		}
		else {
			return new HashSet(capacity);
		}
	}

	public static List getLinkedList() {
		if (useTrove) {
			return new TLinkedList();
		}
		else {
			return new LinkedList();
		}
	}

	public static List getSyncArrayList() {
		return new CopyOnWriteArrayList();
	}

	public static List getSyncArrayList(int capacity) {
		return new CopyOnWriteArrayList();
	}

	public static List getSyncArrayList(List list) {
		return new CopyOnWriteArrayList(list);
	}

	public static Map getSyncHashMap() {
		return new ConcurrentHashMap();
	}

	public static Map getSyncHashMap(int capacity) {
		return new ConcurrentHashMap(capacity);
	}

	public static Map getSyncHashMap(Map map) {
		return new ConcurrentHashMap(map);
	}

	public static Set getSyncHashSet() {
		return new ConcurrentHashSet();
	}

	public static Set getSyncHashSet(int capacity) {
		return new ConcurrentHashSet(capacity);
	}

	public static Set getSyncHashSet(Set set) {
		return new ConcurrentHashSet(set);
	}

}