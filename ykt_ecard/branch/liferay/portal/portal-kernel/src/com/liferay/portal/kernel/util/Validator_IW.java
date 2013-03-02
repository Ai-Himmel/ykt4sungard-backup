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

/**
 * <a href="Validator_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Raymond Augé
 *
 */
public class Validator_IW {
	public static Validator_IW getInstance() {
		return _instance;
	}

	public boolean equals(String s1, String s2) {
		return Validator.equals(s1, s2);
	}

	public boolean isAddress(String address) {
		return Validator.isAddress(address);
	}

	public boolean isChar(char c) {
		return Validator.isChar(c);
	}

	public boolean isChar(String s) {
		return Validator.isChar(s);
	}

	public boolean isDigit(char c) {
		return Validator.isDigit(c);
	}

	public boolean isDigit(String s) {
		return Validator.isDigit(s);
	}

	public boolean isHex(String s) {
		return Validator.isHex(s);
	}

	public boolean isHTML(String s) {
		return Validator.isHTML(s);
	}

	public boolean isLUHN(String number) {
		return Validator.isLUHN(number);
	}

	public boolean isDate(int month, int day, int year) {
		return Validator.isDate(month, day, year);
	}

	public boolean isGregorianDate(int month, int day, int year) {
		return Validator.isGregorianDate(month, day, year);
	}

	public boolean isJulianDate(int month, int day, int year) {
		return Validator.isJulianDate(month, day, year);
	}

	public boolean isEmailAddress(String emailAddress) {
		return Validator.isEmailAddress(emailAddress);
	}

	public boolean isEmailAddressSpecialChar(char c) {
		return Validator.isEmailAddressSpecialChar(c);
	}

	public boolean isName(String name) {
		return Validator.isName(name);
	}

	public boolean isNumber(String number) {
		return Validator.isNumber(number);
	}

	public boolean isNull(Object obj) {
		return Validator.isNull(obj);
	}

	public boolean isNull(Long l) {
		return Validator.isNull(l);
	}

	public boolean isNull(String s) {
		return Validator.isNull(s);
	}

	public boolean isNull(Object[] array) {
		return Validator.isNull(array);
	}

	public boolean isNotNull(Object obj) {
		return Validator.isNotNull(obj);
	}

	public boolean isNotNull(Long l) {
		return Validator.isNotNull(l);
	}

	public boolean isNotNull(String s) {
		return Validator.isNotNull(s);
	}

	public boolean isNotNull(Object[] array) {
		return Validator.isNotNull(array);
	}

	public boolean isPassword(String password) {
		return Validator.isPassword(password);
	}

	public boolean isPhoneNumber(String phoneNumber) {
		return Validator.isPhoneNumber(phoneNumber);
	}

	public boolean isVariableTerm(String s) {
		return Validator.isVariableTerm(s);
	}

	private Validator_IW() {
	}

	private static Validator_IW _instance = new Validator_IW();

}
