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

package com.liferay.portal.tools;

import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.translator.model.Translation;
import com.liferay.portlet.translator.util.TranslationWebCacheItem;
import com.liferay.util.FileUtil;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.StringReader;

import java.util.Properties;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="LangBuilder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LangBuilder {

	public static void main(String[] args) {
		if (args.length == 2) {
			new LangBuilder(args[0], args[1]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public LangBuilder(String langDir, String langFile) {
		try {
			_langDir = langDir;
			_langFile = langFile;

			String content = _orderProps(
				new File(_langDir + "/" + _langFile + ".properties"));

			_createProps(content, "ar"); // Arabic
			_createProps(content, "ca"); // Catalan
			_createProps(content, "zh_CN"); // Chinese (China)
			_createProps(content, "zh_TW"); // Chinese (Taiwan)
			_createProps(content, "cs"); // Czech
			_createProps(content, "nl"); // Dutch
			_createProps(content, "fi"); // Finnish
			_createProps(content, "fr"); // French
			_createProps(content, "de"); // German
			_createProps(content, "el"); // Greek
			_createProps(content, "hu"); // Hungarian
			_createProps(content, "it"); // Italian
			_createProps(content, "ja"); // Japanese
			_createProps(content, "ko"); // Korean
			_createProps(content, "fa"); // Persian
			_createProps(content, "pt"); // Portuguese
			_createProps(content, "ru"); // Russian
			_createProps(content, "es"); // Spanish
			_createProps(content, "sv"); // Swedish
			_createProps(content, "tr"); // Turkish
			_createProps(content, "vi"); // Vietnamese
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void _createProps(String content, String languageId)
		throws IOException {

		File propsFile = new File(
			_langDir + "/" + _langFile + "_" + languageId + ".properties");

		Properties props = new Properties();

		if (propsFile.exists()) {
			props.load(new FileInputStream(propsFile));
		}

		File nativePropsFile = new File(
			_langDir + "/" + _langFile + "_" + languageId +
				".properties.native");

		Properties nativeProps = new Properties();

		if (nativePropsFile.exists()) {
			nativeProps.load(new FileInputStream(nativePropsFile));
		}

		String translationId = "en_" + languageId;

		if (translationId.equals("en_zh_CN")) {
			translationId = "en_zh";
		}
		else if (translationId.equals("en_zh_TW")) {
			translationId = "en_zt";
		}

		BufferedReader br = new BufferedReader(new StringReader(content));
		BufferedWriter bw = new BufferedWriter(new FileWriter(nativePropsFile));

		String line = null;

		while ((line = br.readLine()) != null) {
			line = line.trim();

			int pos = line.indexOf("=");

			if (pos != -1) {
				String key = line.substring(0, pos);
				String value = line.substring(pos + 1, line.length());

				String translatedText = props.getProperty(key);

				if ((translatedText != null) &&
					((translatedText.indexOf("Babel Fish") != -1) ||
					 (translatedText.indexOf("Yahoo! - 999") != -1))) {

					translatedText = "";
				}

				if ((translatedText == null) || translatedText.equals("")) {
					if (line.indexOf("{") != -1 || line.indexOf("<") != -1) {
						translatedText = value;
					}
					else if (key.equals("lang.dir")) {
						translatedText = "ltr";
					}
					else if (key.equals("lang.line.begin")) {
						translatedText = "left";
					}
					else if (key.equals("lang.line.end")) {
						translatedText = "right";
					}
					else {
						translatedText = _translate(translationId, value, 0);
					}
				}

				if (Validator.isNotNull(translatedText)) {
					if (translatedText.indexOf("&#39;") != -1) {
						translatedText =
							StringUtil.replace(translatedText, "&#39;", "\'");
					}

					bw.write(key + "=" + translatedText);

					bw.newLine();
					bw.flush();
				}
				else if (nativeProps.containsKey(key)) {
					bw.write(key + "=");

					bw.newLine();
					bw.flush();
				}
			}
			else {
				bw.write(line);

				bw.newLine();
				bw.flush();
			}
		}

		br.close();
		bw.close();
	}

	private String _orderProps(File propsFile) throws IOException {
		String content = FileUtil.read(propsFile);

		BufferedReader br = new BufferedReader(new StringReader(content));
		BufferedWriter bw = new BufferedWriter(new FileWriter(propsFile));

		Set messages = new TreeSet();

		boolean begin = false;

		String line = null;

		while ((line = br.readLine()) != null) {
			int pos = line.indexOf("=");

			if (pos != -1) {
				String key = line.substring(0, pos);
				String value = line.substring(pos + 1, line.length());

				messages.add(key + "=" + value);
			}
			else {
				if (begin == true && line.equals("")) {
					_sortAndWrite(bw, messages);
				}

				if (line.equals("")) {
					begin = !begin;
				}

				bw.write(line);
				bw.newLine();
			}

			bw.flush();
		}

		if (messages.size() > 0) {
			_sortAndWrite(bw, messages);
		}

		br.close();
		bw.close();

		return FileUtil.read(propsFile);
	}

	private void _sortAndWrite(BufferedWriter bw, Set messages)
		throws IOException {

		String[] messagesArray = (String[])messages.toArray(new String[0]);

		for (int i = 0; i < messagesArray.length; i++) {
			bw.write(messagesArray[i]);
			bw.newLine();
		}

		messages.clear();
	}

	private String _translate(
		String translationId, String fromText, int limit) {

		if (translationId.equals("en_ar") ||
			translationId.equals("en_ca") ||
			translationId.equals("en_cs") ||
			translationId.equals("en_fi") ||
			translationId.equals("en_hu") ||
			translationId.equals("en_fa") ||
			translationId.equals("en_ru") ||
			translationId.equals("en_sv") ||
			translationId.equals("en_tr") ||
			translationId.equals("en_vi")) {

			// Automatic translator does not support Arabic, Catalan, Czech,
			// Finnish, Hungarian, Persian, Russian, Swedish, Turkish,
			// or Vietnamese

			return null;
		}

		// Limit the number of retries to 3

		if (limit == 3) {
			return null;
		}

		String toText = null;

		try {
			System.out.println("Translating " + translationId + " " + fromText);

			WebCacheItem wci = new TranslationWebCacheItem(
				translationId, fromText);

			Translation translation = (Translation)wci.convert("");

			toText = translation.getToText();

			if ((toText != null) &&
				(toText.indexOf("Babel Fish") != -1)) {

				toText = null;
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Keep trying

		if (toText == null) {
			return _translate(translationId, fromText, ++limit);
		}

		return toText;
	}

	private String _langDir;
	private String _langFile;

}