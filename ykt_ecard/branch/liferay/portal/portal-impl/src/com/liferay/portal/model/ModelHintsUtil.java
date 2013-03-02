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

package com.liferay.portal.model;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.util.InitUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.ListUtil;

import java.io.StringReader;

import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ModelHintsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ModelHintsUtil {

	static {
		InitUtil.init();
	}

	public static Map getDefaultHints(String model) {
		return _instance._getDefaultHints(model);
	}

	public static Element getFieldsEl(String model, String field) {
		return _instance._getFieldsEl(model, field);
	}

	public static List getModels() {
		return _instance._getModels();
	}

	public static String getType(String model, String field) {
		return _instance._getType(model, field);
	}

	public static Map getHints(String model, String field) {
		return _instance._getHints(model, field);
	}

	public static String trimString(String model, String field, String value) {
		if (value == null) {
			return value;
		}

		Map hints = getHints(model, field);

		if (hints == null) {
			return value;
		}

		int maxLength = GetterUtil.getInteger(
			ModelHintsDefaults.TEXT_MAX_LENGTH);

		maxLength = GetterUtil.getInteger(
			(String)hints.get("max-length"), maxLength);

		if (value.length() > maxLength) {
			return value.substring(0, maxLength);
		}
		else {
			return value;
		}
	}

	private ModelHintsUtil() {
		_hintCollections = CollectionFactory.getHashMap();
		_defaultHints = CollectionFactory.getHashMap();
		_modelFields = CollectionFactory.getHashMap();
		_models = new TreeSet();

		try {
			ClassLoader classLoader = getClass().getClassLoader();

			String[] configs = StringUtil.split(
				PropsUtil.get(PropsUtil.MODEL_HINTS_CONFIGS));

			for (int i = 0; i < configs.length; i++) {
				_read(classLoader, configs[i]);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private Map _getDefaultHints(String model) {
		return (Map)_defaultHints.get(model);
	}

	private Element _getFieldsEl(String model, String field) {
		Map fields = (Map)_modelFields.get(model);

		if (fields == null) {
			return null;
		}
		else {
			return (Element)fields.get(field + _ELEMENTS_SUFFIX);
		}
	}

	private List _getModels() {
		return ListUtil.fromCollection(_models);
	}

	private String _getType(String model, String field) {
		Map fields = (Map)_modelFields.get(model);

		if (fields == null) {
			return null;
		}
		else {
			return (String)fields.get(field + _TYPE_SUFFIX);
		}
	}

	private Map _getHints(String model, String field) {
		Map fields = (Map)_modelFields.get(model);

		if (fields == null) {
			return null;
		}
		else {
			return (Map)fields.get(field + _HINTS_SUFFIX);
		}
	}

	private void _read(ClassLoader classLoader, String source)
		throws Exception {

		String xml = null;

		try {
			xml = StringUtil.read(classLoader, source);
		}
		catch (Exception e) {
			_log.warn("Cannot load " + source);
		}

		if (xml == null) {
			return;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Loading " + source);
		}

		SAXReader reader = new SAXReader();

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		Iterator itr1 = root.elements("hint-collection").iterator();

		while (itr1.hasNext()) {
			Element hintCollection = (Element)itr1.next();

			String name = hintCollection.attributeValue("name");

			Map hints = (Map)_hintCollections.get(name);

			if (hints == null) {
				hints = CollectionFactory.getHashMap();

				_hintCollections.put(name, hints);
			}

			Iterator itr2 = hintCollection.elements("hint").iterator();

			while (itr2.hasNext()) {
				Element hint = (Element)itr2.next();

				String hintName = hint.attributeValue("name");
				String hintValue = hint.getText();

				hints.put(hintName, hintValue);
			}
		}

		itr1 = root.elements("model").iterator();

		while (itr1.hasNext()) {
			Element model = (Element)itr1.next();

			String name = model.attributeValue("name");

			Map defaultHints = CollectionFactory.getHashMap();

			_defaultHints.put(name, defaultHints);

			Element defaultHintsEl = model.element("default-hints");

			if (defaultHintsEl != null) {
				Iterator itr2 = defaultHintsEl.elements("hint").iterator();

				while (itr2.hasNext()) {
					Element hint = (Element)itr2.next();

					String hintName = hint.attributeValue("name");
					String hintValue = hint.getText();

					defaultHints.put(hintName, hintValue);
				}
			}

			Map fields = (Map)_modelFields.get(name);

			if (fields == null) {
				fields = CollectionFactory.getHashMap();

				_modelFields.put(name, fields);
			}

			_models.add(name);

			Iterator itr2 = model.elements("field").iterator();

			while (itr2.hasNext()) {
				Element field = (Element)itr2.next();

				String fieldName = field.attributeValue("name");
				String fieldType = field.attributeValue("type");

				Map fieldHints = CollectionFactory.getHashMap();

				fieldHints.putAll(defaultHints);

				Iterator itr3 = field.elements("hint-collection").iterator();

				while (itr3.hasNext()) {
					Element hintCollection = (Element)itr3.next();

					Map hints = (Map)_hintCollections.get(
						hintCollection.attributeValue("name"));

					fieldHints.putAll(hints);
				}

				itr3 = field.elements("hint").iterator();

				while (itr3.hasNext()) {
					Element hint = (Element)itr3.next();

					String hintName = hint.attributeValue("name");
					String hintValue = hint.getText();

					fieldHints.put(hintName, hintValue);
				}

				fields.put(fieldName + _ELEMENTS_SUFFIX, field);
				fields.put(fieldName + _TYPE_SUFFIX, fieldType);
				fields.put(fieldName + _HINTS_SUFFIX, fieldHints);
			}
		}
	}

	private static final String _ELEMENTS_SUFFIX = "_ELEMENTS";

	private static final String _TYPE_SUFFIX = "_TYPE";

	private static final String _HINTS_SUFFIX = "_HINTS";

	private static Log _log = LogFactory.getLog(ModelHintsUtil.class);

	private static ModelHintsUtil _instance = new ModelHintsUtil();

	private Map _hintCollections;
	private Map _defaultHints;
	private Map _modelFields;
	private Set _models;

}