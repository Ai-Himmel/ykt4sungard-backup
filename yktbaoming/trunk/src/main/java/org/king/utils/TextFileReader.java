/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.utils.TextFileReader.java
 * �������ڣ� 2006-6-10 11:18:05
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-10 11:18:05      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.utils;

import java.io.*;
import java.util.ArrayList;

/**
 * <p>
 * TextFileReader.java
 * </p>
 * <p>
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="TextFileReader.java.html"><i>�鿴Դ����</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-10
 * 
 * 
 */
public class TextFileReader {

	private String fileName, errorMessage;

	private int columns, rowCount;

	/**
	 * Constructs a TextFileReader.
	 */
	public TextFileReader() {
		reset();
	}

	/**
	 * Resets all the variables in this bean.
	 */
	public void reset() {
		fileName = "";
		errorMessage = "";
		columns = 0;
		rowCount = 0;
	}

	/**
	 * Sets the error message, if an error occurs.
	 */
	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}

	/**
	 * Returns the error message, if any.
	 */
	public String getErrorMessage() {
		return errorMessage;
	}

	/**
	 * Returns the filename.
	 */
	public String getFileName() {
		return fileName;
	}

	/**
	 * Sets the filename.
	 */
	public void setFileName(String fileName) {
		this.fileName = fileName;
	}

	/**
	 * Returns the amount of rows in the file.
	 */
	public int getRows() {
		return rowCount;
	}

	/**
	 * Returns the maximum amount of columns in a row.
	 */
	public int getColumns() {
		return columns;
	}

	/**
	 * Returns the content of the file in a String. If an error occurs, like if
	 * the file does not exists, null is returned.
	 */
	public String getContent() {
		String content = "";
		File file = new File(fileName);
		if (!file.exists()) {
			setErrorMessage("Error: The file '" + fileName
					+ "' does not exists.");
			return null;
		} else if (file != null) {
			try {
				// Create an BufferedReader so we can read a line at the time.
				BufferedReader reader = new BufferedReader(new FileReader(file));
				String inLine = reader.readLine();
				while (inLine != null) {
					if (inLine.length() + 1 > columns)
						columns = inLine.length() + 1;
					content += (inLine + System.getProperty("line.separator"));
					inLine = reader.readLine();
					rowCount++;
				}
				return content;
			} catch (IOException e) {
				setErrorMessage("Error reading the file: " + e.getMessage());
				return null;
			}
		} else {
			setErrorMessage("Unknown error!");
			return null;
		}

	}
	


}
