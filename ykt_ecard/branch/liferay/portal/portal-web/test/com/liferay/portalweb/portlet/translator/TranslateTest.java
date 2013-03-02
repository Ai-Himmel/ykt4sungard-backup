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

package com.liferay.portalweb.portlet.translator;

import com.liferay.portalweb.portal.BaseTestCase;

/**
 * <a href="TranslateTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TranslateTest extends BaseTestCase {
	public void testTranslate() throws Exception {
		selenium.select("_26_id", "label=English to Chinese (China)");
		selenium.type("_26_text",
			"My name is Liferay Translator, fluent in over 6 million forms of communication.");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"\u6211\u7684\u540d\u5b57\u662fLiferay \u8bd1\u8005, \u6d41\u5229\u5b8c\u5168\u6210\u529f6 \u901a\u4fe1\u7684\u767e\u4e07\u4e2a\u5f62\u5f0f\u3002 "));
		selenium.select("_26_id", "label=English to Chinese (Taiwan)");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"\u6211\u7684\u540d\u5b57\u662fLiferay \u8b6f\u8005, \u6d41\u5229\u5b8c\u5168\u6210\u529f6 \u901a\u4fe1\u7684\u767e\u842c\u500b\u5f62\u5f0f\u3002 "));
		selenium.select("_26_id", "label=English to Dutch");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Mijn naam is Vertaler Liferay, vloeiend in meer dan 6 miljoen vormen van mededeling. "));
		selenium.select("_26_id", "label=English to French");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Mon nom est traducteur de Liferay, fluent dans plus de 6 millions de formes de communication. "));
		selenium.select("_26_id", "label=English to German");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Mein Name ist der Liferay \u00dcbersetzer, der innen \u00fcber 6 Million Formen Kommunikation flie\u00dfend ist. "));
		selenium.select("_26_id", "label=English to Italian");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Il mio nome \u00e8 traduttore di Liferay, fluente dentro oltre 6 milione forme della comunicazione. "));
		selenium.select("_26_id", "label=English to Japanese");
		selenium.type("_26_text",
			"My name is JR Skywalker, fluent in over 6 million forms of communication.");
		verifyTrue(selenium.isTextPresent(
				"\u79c1\u306e\u540d\u524d\u306f\u30b3\u30df\u30e5\u30cb\u30b1\u30fc\u30b7\u30e7\u30f3\u306e6,000,000 \u306e\u5f62\u614b\u306b\u6d41\u66a2\u306aJR Skywalker \u3067\u3042\u308b\u3002 "));
		selenium.select("_26_id", "label=English to Korean");
		selenium.type("_26_text",
			"My name is Liferay Translator, fluent in over 6 million forms of communication.");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"\ub098\uc758 \uc774\ub984\uc740 \ucee4\ubba4\ub2c8\ucf00\uc774\uc158\uc758 6\ubc31\ub9cc\uac1c\uc758 \ubaa8\uc591\uc5d0 \uc548\uc73c\ub85c \uc720\ucc3d\ud55cLiferay\ud1b5\uc5ed \uc774\ub2e4. "));
		selenium.select("_26_id", "label=English to Portuguese");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Meu nome \u00e9 tradutor de Liferay, fluent dentro sobre 6 milh\u00e3o formul\u00e1rios de uma comunica\u00e7\u00e3o. "));
		selenium.select("_26_id", "label=English to Spanish");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Mi nombre es traductor de Liferay, fluido adentro sobre 6 millones de formas de comunicaci\u00f3n. "));
		selenium.select("_26_id", "label=Chinese (China) to English");
		selenium.type("_26_text",
			"\u6211\u7684\u540d\u5b57\u662fMike Vader \u8bd1\u8005, \u6d41\u5229\u5b8c\u5168\u6210\u529f6 \u901a\u4fe1\u7684\u767e\u4e07\u4e2a\u5f62\u5f0f\u3002 ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is Mike the Vader translator, fluent completely successful 6 correspondences million forms. "));
		selenium.select("_26_id", "label=Chinese (Taiwan) to English");
		selenium.type("_26_text",
			"\u6211\u7684\u540d\u5b57\u662fLiferay \u8b6f\u8005, \u6d41\u5229\u5b8c\u5168\u6210\u529f6 \u901a\u4fe1\u7684\u767e\u842c\u500b\u5f62\u5f0f\u3002 ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is the Liferay translator, fluent completely successful 6 correspondences million forms. "));
		selenium.select("_26_id", "label=Dutch to English");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		selenium.type("_26_text",
			"Mijn naam is Vertaler Liferay, vloeiend in meer dan 6 miljoen vormen van mededeling. ");
		verifyTrue(selenium.isTextPresent(
				"My name is translator Liferay, fluently in more than 6 millions forms of communication. "));
		selenium.select("_26_id", "label=French to English");
		selenium.type("_26_text",
			"Mon nom est traducteur de Liferay, fluent dans plus de 6 millions de formes de communication. ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is a translator of Liferay, flowing in more than 6 million forms of communication. "));
		selenium.select("_26_id", "label=French to German");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Mein Name ist \u00dcbersetzer von Liferay, flie\u00dfender in mehr als 6 Millionen Kommunikationsformen. "));
		selenium.select("_26_id", "label=German to English");
		selenium.type("_26_text",
			"Mein Name ist \u00dcbersetzer von Liferay, flie\u00dfender in mehr als 6 Millionen Kommunikationsformen. ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is a translator more flowing from Liferay, into more than 6 million communication forms. "));
		selenium.select("_26_id", "label=German to French");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"Mon nom est un traducteur coulant des Liferay, sous plus de 6 millions de formes de communication. "));
		selenium.select("_26_id", "label=Italian to English");
		selenium.type("_26_text",
			"Il mio nome \u00e8 traduttore di Liferay, fluente dentro oltre 6 milione forme della comunicazione. ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is translator of Liferay, flowing within beyond 6 million shapes the communication. "));
		selenium.select("_26_id", "label=Japanese to English");
		selenium.type("_26_text",
			"\u79c1\u306e\u540d\u524d\u306f\u30b3\u30df\u30e5\u30cb\u30b1\u30fc\u30b7\u30e7\u30f3\u306e6,000,000 \u306e\u5f62\u614b\u306b\u6d41\u66a2\u306aLiferay \u306e\u8a33\u8005\u3067\u3042\u308b\u3002 ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is the translator of fluent Liferay in form of 6,000,000 of communication. "));
		selenium.select("_26_id", "label=Korean to English");
		selenium.type("_26_text",
			"\ub098\uc758 \uc774\ub984\uc740 \ucee4\ubba4\ub2c8\ucf00\uc774\uc158\uc758 6\ubc31\ub9cc\uac1c\uc758 \ubaa8\uc591\uc5d0 \uc548\uc73c\ub85c \uc720\ucc3d\ud55cLiferay\ud1b5\uc5ed \uc774\ub2e4. ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is the Liferay interpretation which in 6000000 shapes of communication is fluent in inside. "));
		selenium.select("_26_id", "label=Portuguese to English");
		selenium.type("_26_text",
			"Meu nome \u00e9 tradutor de Liferay, fluent dentro sobre 6 milh\u00e3o formul\u00e1rios de uma comunica\u00e7\u00e3o. ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is translating of Liferay, fluent inside on 6 million forms of a communication."));
		selenium.select("_26_id", "label=Spanish to English");
		selenium.type("_26_text",
			"Mi nombre es traductor de Liferay, fluido adentro sobre 6 millones de formas de comunicaci\u00f3n. ");
		selenium.click("//input[@value='Translate']");
		selenium.waitForPageToLoad("30000");
		verifyTrue(selenium.isTextPresent(
				"My name is translator of Liferay, fluid inside on 6 million communication forms."));
	}
}