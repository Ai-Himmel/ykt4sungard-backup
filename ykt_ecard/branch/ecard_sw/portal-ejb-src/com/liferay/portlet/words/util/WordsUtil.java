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

package com.liferay.portlet.words.util;

import com.liferay.portal.util.ContentUtil;
import com.liferay.portlet.words.ScramblerException;
import com.liferay.util.CollectionFactory;
import com.liferay.util.StringUtil;
import com.liferay.util.jazzy.BasicSpellCheckListener;

import com.swabunga.spell.engine.SpellDictionaryHashMap;
import com.swabunga.spell.event.DefaultWordFinder;
import com.swabunga.spell.event.SpellChecker;
import com.swabunga.spell.event.StringWordTokenizer;

import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

/**
 * <a href="WordsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class WordsUtil {

	public static List checkSpelling(String text) {
		return _instance._checkSpelling(text);
	}

	public static Set getDictionary() {
		return _instance._getDictionary();
	}

	public static boolean isDictionaryWord(String word) {
		return _instance._isDictionaryWord(word);
	}

	public static String[] scramble(String word) throws ScramblerException {
		Scrambler scrambler = new Scrambler(word);

		return scrambler.scramble();
	}

	public static String[] unscramble(String word) throws ScramblerException {
		return _instance._unscramble(word);
	}

	private WordsUtil() {
		_dictionary = CollectionFactory.getHashSet(150000);

		String[] dictionaryWords = StringUtil.split(
			ContentUtil.get("content/en_US/words.txt"), "\n");		
		for (int i = 0; i < dictionaryWords.length; i++) {
			_dictionary.add(dictionaryWords[i]);
		}
		try {
			_spellDictionary = new SpellDictionaryHashMap();
			String[] dics = new String[] {
				"center.dic", "centre.dic", "color.dic", "colour.dic",
				"eng_com.dic", "english.0", "english.1", "ise.dic", "ize.dic",
				"labeled.dic", "labelled.dic", "yse.dic", "yze.dic"
			};			
			for (int i = 0; i < dics.length; i++) {				
				_spellDictionary.addDictionary(new StringReader(
					ContentUtil.get("content/en_US/dic/" + dics[i])));
			}			
		}
		
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	private List _checkSpelling(String text) {
		SpellChecker checker = new SpellChecker(_spellDictionary);

		BasicSpellCheckListener listener = new BasicSpellCheckListener(text);

		checker.addSpellCheckListener(listener);

		checker.checkSpelling(
			new StringWordTokenizer(new DefaultWordFinder(text)));

		return listener.getInvalidWords();
	}

	private Set _getDictionary() {
		return _dictionary;
	}

	private boolean _isDictionaryWord(String word) {
		return _dictionary.contains(word);
	}

	private String[] _unscramble(String word) throws ScramblerException {
		List validWords = new ArrayList();

		String[] words = scramble(word);

		for (int i = 0; i < words.length; i++) {
			if (_dictionary.contains(words[i])) {
				validWords.add(words[i]);
			}
		}

		return (String[])validWords.toArray(new String[0]);
	}

	private static WordsUtil _instance = new WordsUtil();

	private Set _dictionary;
	private SpellDictionaryHashMap _spellDictionary;

}