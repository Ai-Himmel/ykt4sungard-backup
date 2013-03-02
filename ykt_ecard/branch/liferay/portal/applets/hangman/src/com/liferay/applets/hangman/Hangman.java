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

package com.liferay.applets.hangman;

import java.applet.Applet;
import java.applet.AudioClip;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/**
 * <a href="Hangman.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class Hangman extends Applet implements KeyListener {

	private static final int MEDIA_TRACKER_HANG = 0;

	private static final int MEDIA_TRACKER_DANCE = 1;

	private static final int TOTAL_IMAGES_HANG = 5;

	private static final int TOTAL_IMAGES_DANCE = 5;

	private static final int HANG_WIDTH = 42;

	private static final int HANG_HEIGHT = 64;

	private static final int DANCE_WIDTH = 100;

	private static final int DANCE_HEIGHT = 80;

	private static final int[] DANCE_STEP = new int[] {
		12, 28, 8, -6, -20, 12, -10, -6, -10, -20, 8, 8, 12, -8, -4
	};

	public void init() {
		_initValues();
		_buildWordList();
		_loadResources();

		addKeyListener(this);
		_newGame();
	}

	public void paint(Graphics g) {
		// gallows and noose
		g.setColor(new Color(128, 64, 0));
		g.fillRect(10, HANG_HEIGHT * 2 + 10, HANG_WIDTH + 3, 3);
		g.fillRect(HANG_WIDTH / 2 + 10, 10, 3, HANG_HEIGHT * 2);
		g.fillRect(HANG_WIDTH / 2 + 10, 10, HANG_WIDTH / 2 + HANG_WIDTH / 2, 3);
		g.fillRect(HANG_WIDTH * 3 / 2 + 9, 10, 3, HANG_HEIGHT / 3 + 1);

		// hanging images and wrong letters
		if (_wrongGuess.length() != 0) {
			g.drawImage(
				_hangImages[_wrongGuess.length()-1],
				HANG_WIDTH + 10, HANG_HEIGHT / 3, this);

			g.setColor(Color.RED);
			g.setFont(_wrongFont);
			g.drawChars(
				_wrongGuess.toUpperCase().toCharArray(), 0,
				_wrongGuess.length(), HANG_WIDTH * 2,
				_wrongMetrics.getHeight() + 1);
		}

		// blank lines and correct letters
		g.setColor(Color.BLACK);
		g.setFont(_rightFont);
		int width = _rightMetrics.charWidth(' ');
		char [] wordChars = _getWord().toCharArray();
		for (int i = 0; i < wordChars.length; i++) {
			if (wordChars[i] != ' ') {
				g.drawLine(
					HANG_WIDTH * 2 + 2 * i * width + 1, HANG_HEIGHT * 2 + 1,
					HANG_WIDTH * 2 + 2 * (i+1) * width - 1,
					HANG_HEIGHT * 2 + 1);

				if (_gameOver() || _rightGuess.indexOf(wordChars[i]) != -1) {
					g.drawChars(
						_getWord().toUpperCase().toCharArray(), i, 1,
						HANG_WIDTH * 2 + 2 * i * width + width / 2,
						HANG_HEIGHT * 2);
				}
			}
		}

		// dancing images
		g.clearRect(_danceX, _danceY, DANCE_WIDTH, DANCE_HEIGHT);
		if (_danceIndex != -1) {
			_danceX += DANCE_STEP[_danceIndex % DANCE_STEP.length];
			_danceX = Math.max(_danceX, _danceXLo);
			_danceX = Math.min(_danceX, _danceXHi);

			g.drawImage(
				_danceImages[_danceIndex % TOTAL_IMAGES_DANCE],
				_danceX, _danceY, this);
		}
	}

	public void keyPressed(KeyEvent e) { }

	public void keyReleased(KeyEvent e) {
		char key = e.getKeyChar();

		if (!_gameOver()) {
			if ((key < 'a' || key > 'z') ||
				(_rightGuess.indexOf(key) != -1) ||
				(_wrongGuess.indexOf(key) != -1)) {

				play(getCodeBase(), "audio/ding.au");
			}
			else {
				Character letter = new Character(key);
				if (_getWord().indexOf(key) != -1) {
					_rightGuess += letter;

					for (int i = 0; i < _getWord().length(); i++) {
						if (_getWord().charAt(i) == key) {
							_guessLength++;
						}
					}

					if (_guessLength == _getWord().length()) {
						play(getCodeBase(), "audio/whoopy.au");
						_startDance();
					}
					else {
						play(getCodeBase(), "audio/ah.au");
					}
				}
				else {
					_wrongGuess += letter;

					if (_wrongGuess.length() < TOTAL_IMAGES_HANG) {
						play(getCodeBase(), "audio/ooh.au");
					}
					else {
						play(getCodeBase(), "audio/scream.au");
					}
				}
			}

			repaint();
		}
		else {
			_stopDance();
			_newGame();
		}
		e.consume();
	}

	public void keyTyped(KeyEvent e) { }

	private void _initValues() {
		_tracker = new MediaTracker(this);
		_danceImages = new Image[TOTAL_IMAGES_DANCE];
		_hangImages = new Image[TOTAL_IMAGES_HANG];
		_danceIndex = -1;
		_danceY = HANG_HEIGHT / 2;
		_danceX = _danceXLo = HANG_WIDTH * 2;
		_danceXHi = Math.min(
			DANCE_WIDTH * 2 + HANG_WIDTH * 2, getWidth() - DANCE_WIDTH);
		_wordList = new ArrayList();
		_wrongFont = new Font("MONOSPACED", Font.BOLD, 16);
		_wrongMetrics = getFontMetrics(_wrongFont);
		_rightFont = new Font("MONOSPACED", Font.PLAIN, 14);
		_rightMetrics = getFontMetrics(_rightFont);
	}

	private void _buildWordList() {
		String paramWords = getParameter("word_list");
		if (paramWords != null) {
			StringTokenizer st = new StringTokenizer(paramWords, ",");

			while (st.hasMoreTokens()) {
				boolean skip = false;

				String token = st.nextToken().trim();
				for (int i = 0; i < token.length(); i++) {
					char c = token.charAt(i);
					if ((c < 'a' || c > 'z') && c != ' ') {
						skip = true;
						break;
					}
				}

				if (!skip) {
					_wordList.add(token);
				}
				else {
					System.err.println("Token '" + token +
						"' contains invalid characters");
				}
			}
		}

		// Populate list with something
		if (_wordList.isEmpty()) {
			_wordList.add("liferay");
			_wordList.add("open source");
			_wordList.add("enterprise");
			_wordList.add("for life");
		}
	}

	private void _loadResources() {
		for (int i = 0; i < TOTAL_IMAGES_HANG; i++) {
			Image img = getImage(
				getCodeBase(), "images/hanging/h" + (i+1) + ".gif");
			_tracker.addImage(img, MEDIA_TRACKER_HANG);
			_hangImages[i] = img;
		}

		for (int i = 0; i < TOTAL_IMAGES_DANCE; i++) {
			Image img = getImage(
				getCodeBase(), "images/dancing/d" + (i+1) + ".gif");
			_tracker.addImage(img, MEDIA_TRACKER_DANCE);
			_danceImages[i] = img;
		}

		_danceMusic = getAudioClip(getCodeBase(), "audio/dance.au");
	}

	private void _newGame() {
		try {
			_tracker.waitForID(MEDIA_TRACKER_HANG);
		} catch (InterruptedException ex) {
			// don't do anything
		}
		_tracker.checkAll(true);

		_rightGuess = new String();
		_wrongGuess = new String();
		_wordIndex = (int) (Math.random() * 100) % _wordList.size();

		_guessLength = 0;
		String word = _getWord();
		for (int i = 0; i < word.length(); i++) {
			if (word.charAt(i) == ' ') {
				_guessLength++;
			}
		}

		repaint();
	}

	private boolean _gameOver() {
		return
			_guessLength == _getWord().length() ||
			_wrongGuess.length() == TOTAL_IMAGES_HANG;
	}

	private String _getWord() {
		return (String) _wordList.get(_wordIndex);
	}

	private void _startDance() {
		_danceThread = new DanceThread();
		_danceThread.start();
	}

	private void _stopDance() {
		if (_danceThread != null) {
			_danceThread.interrupt();
			_danceThread = null;
		}
	}

	private class DanceThread extends Thread {
		public void run() {
			_danceX = _danceXLo;
			_danceX += (int) (Math.random() * 100) % (_danceXHi - _danceXLo);
			_danceIndex = 0;
			_danceMusic.loop();
			try {
				_tracker.waitForID(MEDIA_TRACKER_DANCE);

				for (;;) {
					_danceIndex++;
					repaint();
					sleep(250);
				}
			}
			catch (InterruptedException ex) {
				// do nothing
			}
			_danceIndex = -1;
			_danceMusic.stop();
			repaint();
		}
	}

	// Media variables
	private MediaTracker _tracker;
	private AudioClip _danceMusic;
	private Image[] _danceImages;
	private Image[] _hangImages;
	private Thread _danceThread;
	private int _danceIndex;
	private int _danceY;
	private int _danceX;
	private int _danceXLo;
	private int _danceXHi;

	// Specific to the words
	private List _wordList;
	private int _wordIndex;
	private String _rightGuess;
	private String _wrongGuess;
	private int _guessLength;

	// Font values
	private Font _wrongFont;
	private FontMetrics _wrongMetrics;
	private Font _rightFont;
	private FontMetrics _rightMetrics;

}