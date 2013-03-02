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

package com.liferay.util;

import com.liferay.util.lang.FastStringBuffer;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;

import java.nio.channels.FileChannel;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Properties;

/**
 * <a href="FileUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class FileUtil {

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

	public static void copyFile(
		String sourceFileName, String destinationFileName) {

		copyFile(new File(sourceFileName), new File(destinationFileName));
	}

	public static void copyFile(File source, File destination) {
		if (!source.exists()) {
			return;
		}

		if ((destination.getParentFile() != null) &&
			(!destination.getParentFile().exists())) {

			destination.getParentFile().mkdirs();
		}

		try {
			FileChannel srcChannel = new FileInputStream(source).getChannel();
			FileChannel dstChannel = new FileOutputStream(
				destination).getChannel();

			dstChannel.transferFrom(srcChannel, 0, srcChannel.size());

			srcChannel.close();
			dstChannel.close();
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public static void copyFileLazy(String source, String destination)
		throws IOException {

		String oldContent = null;
		try {
			oldContent = FileUtil.read(source);
		}
		catch (FileNotFoundException fnfe) {
			return;
		}

		String newContent = null;
		try {
			newContent = FileUtil.read(destination);
		}
		catch (FileNotFoundException fnfe) {
		}

		if (oldContent == null || !oldContent.equals(newContent)) {
			FileUtil.copyFile(source, destination);
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

	public static byte[] getBytes(File file) throws IOException {
		if (file == null || !file.exists()) {
			return null;
		}

		ByteArrayOutputStream out = new ByteArrayOutputStream();
		FileInputStream in = new FileInputStream(file);

		int c = in.read();

		while (c != -1) {
			out.write(c);
			c = in.read();
		}

		in.close();
		out.close();

		return out.toByteArray();
	}

	public static String getPath(String fullFileName) {
		int pos = fullFileName.lastIndexOf("/");

		if (pos == -1) {
			pos = fullFileName.lastIndexOf("\\");
		}

		String shortFileName = fullFileName.substring(0, pos);

		if (Validator.isNull(shortFileName)) {
			return "/";
		}

		return shortFileName;
	}

	public static String getShortFileName(String fullFileName) {
		int pos = fullFileName.lastIndexOf("/");

		if (pos == -1) {
			pos = fullFileName.lastIndexOf("\\");
		}

		String shortFileName =
			fullFileName.substring(pos + 1, fullFileName.length());

		return shortFileName;
	}

	public static boolean exists(String fileName) {
		File file = new File(fileName);

		return file.exists();
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
		return listFiles(new File(fileName));
	}

	public static String[] listFiles(File file) throws IOException {
		List files = new ArrayList();

		File[] fileArray = file.listFiles();

		for (int i = 0; i < fileArray.length; i++) {
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
		BufferedReader br = new BufferedReader(new FileReader(file));

		FastStringBuffer sb = new FastStringBuffer();
		String line = null;

		while ((line = br.readLine()) != null) {
			sb.append(line).append('\n');
		}

		br.close();

		return sb.toString().trim();
	}

	public static File[] sortFiles(File[] files) {
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
		return StringUtil.replace(fileName, '\\', "/");
	}

	public static List toList(Reader reader) {
		List list = new ArrayList();

		try {
			BufferedReader br = new BufferedReader(reader);

			FastStringBuffer sb = new FastStringBuffer();
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

		if (file.getParent() != null) {
			mkdirs(file.getParent());
		}

		if (file.exists()) {
			String content = FileUtil.read(file);

			if (content.equals(s)) {
				return;
			}
		}

		BufferedWriter bw = new BufferedWriter(new FileWriter(file));

		bw.flush();
		bw.write(s);

		bw.close();
	}

}