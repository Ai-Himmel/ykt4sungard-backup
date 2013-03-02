/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.servlet;

import java.io.IOException;
import java.util.Iterator;
import java.util.Locale;

import javax.imageio.ImageIO;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.liferay.portlet.words.util.WordsUtil;
import com.liferay.util.captcha.MultipleGimpyEngine;
import com.liferay.util.captcha.WordListDictionnary;
import com.octo.captcha.component.word.DefaultSizeSortedWordList;
import com.octo.captcha.component.word.wordgenerator.DictionaryWordGenerator;
import com.octo.captcha.image.ImageCaptcha;

/**
 * <a href="CaptchaServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class CaptchaServlet extends HttpServlet {

	public void init(ServletConfig sc) throws ServletException {
		synchronized (CaptchaServlet.class) {
			super.init(sc);

			try {				
//				DefaultSizeSortedWordList wordList = new DefaultSizeSortedWordList(Locale.getDefault());				
//				Iterator itr = WordsUtil.getDictionaryList().iterator();				
//				while (itr.hasNext()) {
//					wordList.addWord((String)itr.next());
//				}				
//				com.octo.captcha.component.word.wordgenerator.DictionaryWordGenerator wordGenerator = new DictionaryWordGenerator(
//					new WordListDictionnary(wordList));

				/*
				_engine = new MultipleGimpyEngine(
					wordGenerator, width, height, minFontSize, maxFontSize,
					minWordLength, maxWordLength, textColor);
				*/
				_engine = new MultipleGimpyEngine();
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

//		if (!PortalInstances.matches()) {
//			return;
//		}

		HttpSession ses = req.getSession();

		ImageCaptcha captcha = (ImageCaptcha)ses.getAttribute("CAPTCHA");

		if (captcha == null) {
			_engine = new MultipleGimpyEngine();
			captcha = _engine.getImageCaptchaFactory().getImageCaptcha();

			ses.setAttribute("CAPTCHA", captcha);
		}

		ServletOutputStream out = res.getOutputStream();

		ImageIO.write(
			captcha.getImageChallenge(), "jpeg", res.getOutputStream());

		out.flush();
	}

	private MultipleGimpyEngine _engine;

}