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

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;

import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="Autocomplete.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Autocomplete {

	public static JSONArray arrayToJson(String[] array, int max) {
		return arrayToJson(_singleToPairArray(array), max);
	}

	public static JSONArray arrayToJson(String[][] array, int max) {
		if (max <= 0) {
			max = array.length;
		}

		JSONArray jsonArray = new JSONArray();

		for (int i = 0; (i < array.length) && (i < max); i++) {
			String text = array[i][0];
			String value = array[i][1];

			JSONObject jsonObj = new JSONObject();

			jsonObj.put("text", text);
			jsonObj.put("value", value);

			jsonArray.put(jsonObj);
		}

		return jsonArray;
	}

	public static String arrayToXml(String[] array, int max) {
		return arrayToXml(_singleToPairArray(array), max);
	}

	public static String arrayToXml(String[][] array, int max) {
		if (max <= 0) {
			max = array.length;
		}

		StringMaker sm = new StringMaker();

		sm.append("<?xml version=\"1.0\"?>");

		sm.append("<ajaxresponse>");

		for (int i = 0; (i < array.length) && (i < max); i++) {
			String text = array[i][0];
			String value = array[i][1];

			sm.append("<item>");
			sm.append("<text><![CDATA[");
			sm.append(text);
			sm.append("]]></text>");
			sm.append("<value><![CDATA[");
			sm.append(value);
			sm.append("]]></value>");
			sm.append("</item>");
		}

		sm.append("</ajaxresponse>");

		return sm.toString();
	}

	public static String[][] listToArray(
		List list, String textParam, String valueParam) {

		String[][] array = new String[list.size()][2];

		for (int i = 0; i < list.size(); i++) {
			Object bean = list.get(i);

			Object text = BeanUtil.getObject(bean, textParam);

			if (text == null) {
				text = StringPool.BLANK;
			}

			Object value = BeanUtil.getObject(bean, valueParam);

			if (value == null) {
				value = StringPool.BLANK;
			}

			array[i][0] = text.toString();
			array[i][1] = value.toString();
		}

		return array;
	}

	public static JSONArray listToJson(
		List list, String textParam, String valueParam) {

		return arrayToJson(listToArray(list, textParam, valueParam), -1);
	}

	public static String listToXml(
		List list, String textParam, String valueParam) {

		return arrayToXml(listToArray(list, textParam, valueParam), -1);
	}

	private static String[][] _singleToPairArray(String[] array) {
		String[][] pairArray = new String[array.length][2];

		for (int i = 0; i < array.length; i++) {
			pairArray[i][0] = Html.escape(array[i]);
			pairArray[i][1] = array[i];
		}

		return pairArray;
	}

}