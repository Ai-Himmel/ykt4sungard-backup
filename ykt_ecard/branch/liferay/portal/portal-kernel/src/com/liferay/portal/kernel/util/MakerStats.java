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

package com.liferay.portal.kernel.util;

import java.io.PrintStream;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * <a href="MakerStats.java.html"><b><i>View Source</i></b></a>
 *
 * @author Harry Mark
 *
 */
public class MakerStats {

	public MakerStats(String name) {
		_name = name;
	}

	public void add(String caller, int initSize, int finalSize) {
		SizeSample stat = null;

		synchronized (_map) {
			stat = (SizeSample)_map.get(caller);

			if (stat == null) {
				stat = new SizeSample(caller, initSize);

				_map.put(caller, stat);
			}

			_count++;
		}

		synchronized (stat) {
			stat.add(finalSize);
		}
	}

	public void display(PrintStream printer) {
		printer.println("caller,min,max,range,samples,average,initial");

		List list = new ArrayList(_map.size());

		list.addAll(_map.values());

		Collections.sort(list);

		int maxSize = 0;
		int sampleSize = 0;
		int totalSize = 0;

		for (int i = 0; i<list.size(); i++) {
			SizeSample stat = (SizeSample)list.get(i);

			printer.print(stat.getCaller());
			printer.print(",");
			printer.print(stat.getMinSize());
			printer.print(",");
			printer.print(stat.getMaxSize());
			printer.print(",");
			printer.print(stat.getMaxSize() - stat.getMinSize());
			printer.print(",");
			printer.print(stat.getSamplesSize());
			printer.print(",");
			printer.print(stat.getTotalSize() / stat.getSamplesSize());
			printer.print(",");
			printer.println(stat.getInitSize());

			sampleSize += stat.getSamplesSize();
			totalSize += stat.getTotalSize();

			if (stat.getMaxSize() > maxSize) {
				maxSize = stat.getMaxSize();
			}
		}

		int avg = 0;

		if (sampleSize > 0) {
			avg = totalSize / sampleSize;
		}

		printer.print("SAMPLES=");
		printer.print(sampleSize);
		printer.print(", AVERAGE=");
		printer.print(avg);
		printer.print(", MAX=");
		printer.println(maxSize);
	}

	private String _name;
	private Map _map = new HashMap();
	private int _count;

	private class SizeSample implements Comparable {

		public SizeSample(String caller, int initSize) {
			_caller = caller;
			_initSize = initSize;
			_minSize = Integer.MAX_VALUE;
			_maxSize = Integer.MIN_VALUE;
		}

		public void add(int finalSize) {
			if (finalSize < _minSize) {
				_minSize = finalSize;
			}

			if (finalSize > _maxSize) {
				_maxSize = finalSize;
			}

			_samplesSize++;
			_totalSize += finalSize;
		}

		public String getCaller() {
			return _caller;
		}

		public int getInitSize() {
			return _initSize;
		}

		public int getMaxSize() {
			return _maxSize;
		}

		public int getMinSize() {
			return _minSize;
		}

		public int getSamplesSize() {
			return _samplesSize;
		}

		public int getTotalSize() {
			return _totalSize;
		}

		public int compareTo(Object obj) {
			SizeSample other = (SizeSample)obj;

			int thisAvg = 0;

			if (_samplesSize > 0) {
				thisAvg = _totalSize / _samplesSize;
			}

			int otherAvg = 0;

			if (other.getSamplesSize() > 0) {
				otherAvg = other.getTotalSize() / other.getSamplesSize();
			}

			return otherAvg - thisAvg;
		}

		private String _caller;
		private int _initSize;
		private int _maxSize;
		private int _minSize;
		private int _samplesSize;
		private int _totalSize;

	}

}