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

function validateImageFileName(fileName) {
	if (fileName == null || fileName == "") {
		return false;
	}

	if (fileName.toLowerCase().indexOf(".gif") == fileName.length - 4 ||
		fileName.toLowerCase().indexOf(".jpg") == fileName.length - 4 ||
		fileName.toLowerCase().indexOf(".png") == fileName.length - 4) {

		return true;
	}

	return false;
}

function monitorDateInput() {
	var keycode = String.fromCharCode(event.keyCode);
	if (keycode < '0' || keycode > '9') {
		if (event.keyCode != 8 && 
			event.keyCode != 13 && 
			event.keyCode != 16 && 
			event.keyCode != 46 && 
			event.keyCode != 37 && 			
			event.keyCode != 39 && 
			event.keyCode != 191) {
			event.returnValue=false;
		}
	}
}

function validateSearchForm(form, errormsg) {
	if (form.virtual_content.value.length > 20) {
		alert(errormsg);
		return false;
	}
	submitPortletForm(form);
}


