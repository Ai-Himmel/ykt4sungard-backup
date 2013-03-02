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

package com.liferay.util.bridges.jsf.icefaces;

import com.icesoft.faces.async.render.RenderManager;
import com.icesoft.faces.async.render.Renderable;
import com.icesoft.faces.component.inputfile.InputFile;
import com.icesoft.faces.webapp.xmlhttp.PersistentFacesState;
import com.icesoft.faces.webapp.xmlhttp.RenderingException;

import com.liferay.util.bridges.jsf.common.FacesMessageUtil;

import java.text.DecimalFormat;

import java.util.EventObject;

import javax.faces.context.FacesContext;
import javax.faces.event.ActionEvent;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="FileUploadManagedBean.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class is a managed bean that is designed specifically to work with the
 * ICEfaces framework, by utilizing the <code><ice:inputFile/></code> component.
 * The basic ideas found in this bean were taken from the ICEfaces tuorial,
 * found here:
 * </p>
 *
 * <p>
 * http://facestutorials.icefaces.org/tutorial/inputFile-tutorial.html
 * </p>
 *
 * <p>
 * The server initiated rendering API documentation is found here:
 * </p>
 *
 * <p>
 * http://www.icesoft.com/developer_guides/icefaces/htmlguide/devguide/advanced_topics2.html
 * </p>
 *
 * @author Neil Griffin
 *
 */
public class FileUploadManagedBean implements Renderable {

	public FileUploadManagedBean() {
		_state = PersistentFacesState.getInstance();
	}

	public PersistentFacesState getState() {
		return _state;
	}

	public void setRenderManager(RenderManager renderManager) {
		_renderManager = renderManager;
	}

	public InputFile getInputFile() {
		return _inputFile;
	}

	public void setInputFile(InputFile inputFile) {
		_inputFile = inputFile;
	}

	public int getPercent() {
		return _percent;
	}

	public void setPercent(int percent) {
		_percent = percent;
	}

	public boolean isComplete() {
		if (_percent == 100) {
			return true;
		}
		else {
			return false;
		}
	}

	public void actionListener(ActionEvent actionEvent) {
		InputFile inputFile = (InputFile)actionEvent.getSource();

		int status = inputFile.getStatus();

		try {
			if (status == InputFile.INVALID) {
				addErrorMessage("file-type-is-invalid");

				_percent = 100;
			}
			else if (status == InputFile.SAVED) {
				_percent = 100;
			}
			else if (status == InputFile.SIZE_LIMIT_EXCEEDED) {
				long maxFileSizeInBytes = _inputFile.getSizeMax();

				DecimalFormat decimalFormat = new DecimalFormat();

				decimalFormat.setGroupingUsed(false);
				decimalFormat.setMaximumFractionDigits(2);
				decimalFormat.setMinimumFractionDigits(0);

				String maxFileSizeInMegs =
					decimalFormat.format(
						(double)maxFileSizeInBytes / 1024 / 1024);

				addErrorMessage(
					"file-size-is-larger-than-x-megabytes", maxFileSizeInMegs);

				_percent = 100;
			}
			else if (status == InputFile.UNKNOWN_SIZE) {
				addErrorMessage("file-size-was-not-specified-in-the-request");

				_percent = 100;
			}
		}
		catch (Exception e) {
			_log.error(e, e);

			addErrorMessage(e.getMessage());
		}
	}

	public void progressListener(EventObject eventObject) {
		InputFile inputFile = (InputFile)eventObject.getSource();

		_percent = inputFile.getFileInfo().getPercent();

		_renderManager.requestRender(this);
	}

	public void renderingException(RenderingException renderingException) {
		_log.error(renderingException.getMessage());
	}

	protected void addErrorMessage(String key) {
		addErrorMessage(key, null);
	}

	protected void addErrorMessage(String key, String argument) {
		FacesContext facesContext = FacesContext.getCurrentInstance();

		if (_inputFile == null) {
			FacesMessageUtil.error(facesContext, key, argument);
		}
		else {
			FacesMessageUtil.error(
				_inputFile.getClientId(facesContext), facesContext, key,
				argument);
		}
	}

	private static Log _log = LogFactory.getLog(FileUploadManagedBean.class);

	private PersistentFacesState _state;
	private RenderManager _renderManager;
	private InputFile _inputFile;
	private int _percent;

}