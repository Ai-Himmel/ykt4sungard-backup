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

package com.liferay.util;

import com.liferay.portal.kernel.util.ByteArrayMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.Reader;

import java.nio.channels.FileChannel;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="FileUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class FileUtil {

	public static final String ENCODING = GetterUtil.getString(
		SystemProperties.get("file.encoding"), "UTF-8");

	public static void append(String fileName, String s) throws IOException {
		append(new File(fileName), s);
	}

	public static void append(String pathName, String fileName, String s)
		throws IOException {

		append(new File(pathName, fileName), s);
	}

	public static void append(File file, String s) throws IOException {
		if (file.getParent() != null) {
			mkdirs(file.getParent());
		}

		BufferedWriter bw = new BufferedWriter(new FileWriter(file, true));

		bw.write(s);

		bw.close();
	}

	public static void copyDirectory(
		String sourceDirName, String destinationDirName) {

		copyDirectory(new File(sourceDirName), new File(destinationDirName));
	}

	public static void copyDirectory(File source, File destination) {
		if (source.exists() && source.isDirectory()) {
			if (!destination.exists()) {
				destination.mkdirs();
			}

			File[] fileArray = source.listFiles();

			for (int i = 0; i < fileArray.length; i++) {
				if (fileArray[i].isDirectory()) {
					copyDirectory(
						fileArray[i],
						new File(destination.getPath() + File.separator
							+ fileArray[i].getName()));
				}
				else {
					copyFile(
						fileArray[i],
						new File(destination.getPath() + File.separator
							+ fileArray[i].getName()));
				}
			}
		}
	}

	public static void copyFile(String source, String destination) {
		copyFile(source, destination, false);
	}

	public static void copyFile(
		String source, String destination, boolean lazy) {

		copyFile(new File(source), new File(destination), lazy);
	}

	public static void copyFile(File source, File destination) {
		copyFile(source, destination, false);
	}

	public static void copyFile(File source, File destination, boolean lazy) {
		if (!source.exists()) {
			return;
		}

		if (lazy) {
			String oldContent = null;

			try {
				oldContent = read(source);
			}
			catch (Exception e) {
				return;
			}

			String newContent = null;

			try {
				newContent = read(destination);
			}
			catch (Exception e) {
			}

			if (oldContent == null || !oldContent.equals(newContent)) {
				copyFile(source, destination, false);
			}
		}
		else {
			if ((destination.getParentFile() != null) &&
				(!destination.getParentFile().exists())) {

				destination.getParentFile().mkdirs();
			}

			try {
				FileChannel srcChannel =
					new FileInputStream(source).getChannel();
				FileChannel dstChannel =
					new FileOutputStream(destination).getChannel();

				dstChannel.transferFrom(srcChannel, 0, srcChannel.size());

				srcChannel.close();
				dstChannel.close();
			}
			catch (IOException ioe) {
				_log.error(ioe.getMessage());
			}
		}
	}

	public static boolean delete(String file) {
		return delete(new File(file));
	}

	public static boolean delete(File file) {
		if (file.exists()) {
			return file.delete();
		}
		else {
			return false;
		}
	}

	public static void deltree(String directory) {
		deltree(new File(directory));
	}

	public static void deltree(File directory) {
		if (directory.exists() && directory.isDirectory()) {
			File[] fileArray = directory.listFiles();

			for (int i = 0; i < fileArray.length; i++) {
				if (fileArray[i].isDirectory()) {
					deltree(fileArray[i]);
				}
				else {
					fileArray[i].delete();
				}
			}

			directory.delete();
		}
	}

	public static boolean exists(String fileName) {
		return exists(new File(fileName));
	}

	public static boolean exists(File file) {
		return file.exists();
	}

	public static String getAbsolutePath(File file) {
		return StringUtil.replace(
			file.getAbsolutePath(), StringPool.BACK_SLASH, StringPool.SLASH);
	}

	public static byte[] getBytes(File file) throws IOException {
		if ((file == null) || !file.exists()) {
			return null;
		}

		FileInputStream in = new FileInputStream(file);

		byte[] bytes = getBytes(in, (int)file.length());

		in.close();

		return bytes;
	}

	public static byte[] getBytes(InputStream in) throws IOException {
		return getBytes(in, -1);
	}

	public static byte[] getBytes(InputStream in, int bufferSize)
		throws IOException {

		ByteArrayMaker out = null;

		if (bufferSize <= 0) {
			out = new ByteArrayMaker();
		}
		else {
			out = new ByteArrayMaker(bufferSize);
		}

		boolean createBuffered = false;

		try {
			if (!(in instanceof BufferedInputStream)) {
				in = new BufferedInputStream(in);

				createBuffered = true;
			}

			int c = in.read();

			while (c != -1) {
				out.write(c);

				c = in.read();
			}
		}
		finally {
			if (createBuffered) {
				in.close();
			}
		}

		out.close();

		return out.toByteArray();
	}

	public static String getExtension(String fileName) {
		if (fileName == null) {
			return null;
		}

		int pos = fileName.lastIndexOf(StringPool.PERIOD);

		if (pos != -1) {
			return fileName.substring(pos + 1, fileName.length()).toLowerCase();
		}
		else {
			return null;
		}
	}

	public static String getPath(String fullFileName) {
		int pos = fullFileName.lastIndexOf(StringPool.SLASH);

		if (pos == -1) {
			pos = fullFileName.lastIndexOf(StringPool.BACK_SLASH);
		}

		String shortFileName = fullFileName.substring(0, pos);

		if (Validator.isNull(shortFileName)) {
			return StringPool.SLASH;
		}

		return shortFileName;
	}

	public static String getShortFileName(String fullFileName) {
		int pos = fullFileName.lastIndexOf(StringPool.SLASH);

		if (pos == -1) {
			pos = fullFileName.lastIndexOf(StringPool.BACK_SLASH);
		}

		String shortFileName =
			fullFileName.substring(pos + 1, fullFileName.length());

		return shortFileName;
	}

	public static String[] listDirs(String fileName) throws IOException {
		return listDirs(new File(fileName));
	}

	public static String[] listDirs(File file) throws IOException {
		List dirs = new ArrayList();

		File[] fileArray = file.listFiles();

		for (int i = 0; i < fileArray.length; i++) {
			if (fileArray[i].isDirectory()) {
				dirs.add(fileArray[i].getName());
			}
		}

		return (String[])dirs.toArray(new String[0]);
	}

	public static String[] listFiles(String fileName) throws IOException {
		if (Validator.isNull(fileName)) {
			return new String[0];
		}

		return listFiles(new File(fileName));
	}

	public static String[] listFiles(File file) throws IOException {
		List files = new ArrayList();

		File[] fileArray = file.listFiles();

		for (int i = 0; (fileArray != null) && (i < fileArray.length); i++) {
			if (fileArray[i].isFile()) {
				files.add(fileArray[i].getName());
			}
		}

		return (String[])files.toArray(new String[0]);
	}

	public static void mkdirs(String pathName) {
		File file = new File(pathName);

		file.mkdirs();
	}

	public static boolean move(
		String sourceFileName, String destinationFileName) {

		return move(new File(sourceFileName), new File(destinationFileName));
	}

	public static boolean move(File source, File destination) {
		if (!source.exists()) {
			return false;
		}

		destination.delete();

		return source.renameTo(destination);
	}

	public static String read(String fileName) throws IOException {
		return read(new File(fileName));
	}

	public static String read(File file) throws IOException {
		return read(file, false);
	}

	public static String read(File file, boolean raw) throws IOException {
		return read(file, ENCODING, raw);
	}

	public static String read(File file, String encoding, boolean raw)
		throws IOException {

		FileInputStream fis = new FileInputStream(file);

		byte[] bytes = new byte[fis.available()];

		fis.read(bytes);

		fis.close();

		String s = new String(bytes, encoding);

		if (raw) {
			return s;
		}
		else {
			return StringUtil.replace(
				s, StringPool.RETURN_NEW_LINE, StringPool.NEW_LINE);
		}
	}

	public static File[] sortFiles(File[] files) {
		if (files == null) {
			return null;
		}

		Arrays.sort(files, new FileComparator());

		List directoryList = new ArrayList();
		List fileList = new ArrayList();

		for (int i = 0; i < files.length; i++) {
			if (files[i].isDirectory()) {
				directoryList.add(files[i]);
			}
			else {
				fileList.add(files[i]);
			}
		}

		directoryList.addAll(fileList);

		return (File[])directoryList.toArray(new File[0]);
	}

	public static String replaceSeparator(String fileName) {
		return StringUtil.replace(
			fileName, StringPool.BACK_SLASH, StringPool.SLASH);
	}

	public static List toList(Reader reader) {
		List list = new ArrayList();

		try {
			BufferedReader br = new BufferedReader(reader);

			String line = null;

			while ((line = br.readLine()) != null) {
				list.add(line);
			}

			br.close();
		}
		catch (IOException ioe) {
		}

		return list;
	}

	public static List toList(String fileName) {
		try {
			return toList(new FileReader(fileName));
		}
		catch (IOException ioe) {
			return new ArrayList();
		}
	}

	public static Properties toProperties(FileInputStream fis) {
		Properties props = new Properties();

		try {
			props.load(fis);
		}
		catch (IOException ioe) {
		}

		return props;
	}

	public static Properties toProperties(String fileName) {
		try {
			return toProperties(new FileInputStream(fileName));
		}
		catch (IOException ioe) {
			return new Properties();
		}
	}

	public static void write(String fileName, String s) throws IOException {
		write(new File(fileName), s);
	}

	public static void write(String fileName, String s, boolean lazy)
		throws IOException {

		write(new File(fileName), s, lazy);
	}

	public static void write(String pathName, String fileName, String s)
		throws IOException {

		write(new File(pathName, fileName), s);
	}

	public static void write(
			String pathName, String fileName, String s, boolean lazy)
		throws IOException {

		write(new File(pathName, fileName), s, lazy);
	}

	public static void write(File file, String s) throws IOException {
		write(file, s, false);
	}

	public static void write(File file, String s, boolean lazy)
		throws IOException {

		write(file, s, lazy, false);
	}

	public static void write(File file, String s, boolean lazy, boolean append)
		throws IOException {

		if (file.getParent() != null) {
			mkdirs(file.getParent());
		}

		if (lazy && file.exists()) {
			String content = read(file);

			if (content.equals(s)) {
				return;
			}
		}

		BufferedWriter bw = new BufferedWriter(new FileWriter(file, append));

		bw.write(s);

		bw.close();
	}

	public static void write(String fileName, byte[] byteArray)
		throws IOException {

		write(new File(fileName), byteArray);
	}

	public static void write(File file, byte[] byteArray) throws IOException {
		if (file.getParent() != null) {
			mkdirs(file.getParent());
		}

		FileOutputStream fos = new FileOutputStream(file);

		fos.write(byteArray);

		fos.close();
	}

	public static void write(String fileName, InputStream in)
		throws IOException {

		write(fileName, getBytes(in));
	}

	public static void write(File file, InputStream in) throws IOException {
		write(file, getBytes(in));
	}

	private static Log _log = LogFactory.getLog(FileUtil.class);

}