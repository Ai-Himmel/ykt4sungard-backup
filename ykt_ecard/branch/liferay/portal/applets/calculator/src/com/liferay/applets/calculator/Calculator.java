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

package com.liferay.applets.calculator;

import com.liferay.lawt.AppletFrame;

import java.applet.Applet;

import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Label;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * <a href="Calculator.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Calculator extends Applet {

	public static void main(String args[]) {
		new AppletFrame(new Calculator(), 600, 400);
	}

	public void init() {
		GridBagLayout gbl = new GridBagLayout();

		GridBagConstraints c = new GridBagConstraints();
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;
		c.weighty = 1.0;

		c.insets = new Insets(2, 2, 2, 2);

		setLayout(gbl);

		_inputLabel = new Label("0", Label.RIGHT);
		_inputLabel.setBackground(Color.white);

		c.gridwidth = GridBagConstraints.REMAINDER;
		gbl.setConstraints(_inputLabel, c);
		c.gridwidth = 1;

		add(_inputLabel);

		ActionListener al = new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				String s = e.getActionCommand();

				if ("0123456789.".indexOf(s) != -1) {
					if (_firstDigit) {
						_firstDigit = false;
						_inputLabel.setText(s);
					}
					else {
						_inputLabel.setText(_inputLabel.getText() + s);
					}
				}
				else if (s.equals("C")) {
					_inputLabel.setText("0.0");
					_value = 0.0f;
					_firstDigit = true;
					//_operator = "=";
				}
				else {
					if (!_firstDigit) {
						_compute(_inputLabel.getText());
						_firstDigit = true;
					}

					_operator = s;
				}
			}

		};

		_createButton(al, "7", Color.blue, gbl, c, this);
		_createButton(al, "8", Color.blue, gbl, c, this);
		_createButton(al, "9", Color.blue, gbl, c, this);

		c.gridwidth = GridBagConstraints.REMAINDER;
		_createButton(al, "/", Color.red, gbl, c, this);
		c.gridwidth = 1;

		_createButton(al, "4", Color.blue, gbl, c, this);
		_createButton(al, "5", Color.blue, gbl, c, this);
		_createButton(al, "6", Color.blue, gbl, c, this);

		c.gridwidth = GridBagConstraints.REMAINDER;
		_createButton(al, "*", Color.red, gbl, c, this);
		c.gridwidth = 1;

		_createButton(al, "1", Color.blue, gbl, c, this);
		_createButton(al, "2", Color.blue, gbl, c, this);
		_createButton(al, "3", Color.blue, gbl, c, this);

		c.gridwidth = GridBagConstraints.REMAINDER;
		_createButton(al, "-", Color.red, gbl, c, this);
		c.gridwidth = 1;

		_createButton(al, ".", Color.blue, gbl, c, this);
		_createButton(al, "0", Color.blue, gbl, c, this);
		_createButton(al, "=", Color.red, gbl, c, this);

		c.gridwidth = GridBagConstraints.REMAINDER;
		_createButton(al, "+", Color.red, gbl, c, this);

		_createButton(al, "C", Color.red, gbl, c, this);
	}

	public Insets getInsets() {
		return new Insets(5, 5, 5, 5);
	}

	public boolean keyDown(Event e, int key) {
		String s = (new Character((char)key)).toString();

		if (key == Event.ENTER) {
			key = '=';
		}

		if ((key == Event.ESCAPE) || (key == 'c')) {
			key = 'C';
		}

		if ((key == '1') || (key == '2') || (key == '3') || (key == '4') ||
			(key == '5') || (key == '6') || (key == '7') || (key == '8') ||
			(key == '9') || (key == '0')) {

			if (_firstDigit) {
				_firstDigit = false;
				_inputLabel.setText(s);
			}
			else {
				_inputLabel.setText(_inputLabel.getText() + s);
			}
		}
		else if (key == 'C') {
			_inputLabel.setText("0.0");
			_value = 0.0f;
			_firstDigit = true;
		}
		else if ((key == '=') || (key == '+') || (key == '-') ||
				 (key == '*') || (key == '/')) {

			if (!_firstDigit) {
				_compute(_inputLabel.getText());
				_firstDigit = true;
			}

			_operator = s;
		}

		repaint();

		return true;
	}

	public void paint(Graphics g) {
		Dimension d = getSize();
		g.drawRect(0, 0, d.width - 1, d.height - 1);
		g.drawLine(0, 0, 0, d.height);
	}

	private void _createButton(ActionListener al, String label, Color color,
							   GridBagLayout gbl, GridBagConstraints c,
							   Panel panel) {

		Button button = new Button(label);
		button.setFont(new Font("Arial", Font.PLAIN, 12));
		button.setForeground(color);
		button.addActionListener(al);

		gbl.setConstraints(button, c);

		panel.add(button);
	}

	private void _compute(String s) {
		float value = Float.valueOf(s).floatValue();
		char c = _operator.charAt(0);

		if (c == '=') {
			_value  = value;
		}
		else if (c == '+') {
			_value += value;
		}
		else if (c == '-') {
			_value -= value;
		}
		else if (c == '*') {
			_value *= value;
		}
		else if (c == '/') {
			_value /= value;
		}

		_inputLabel.setText(Float.toString(_value));
	}

	private Label _inputLabel;
	private boolean _firstDigit = true;
	private float _value = 0.0f;
	private String _operator = "=";

}