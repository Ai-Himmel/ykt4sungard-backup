package com.kingstar.files;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Files {
	
	public static void main(String[] args) throws IOException {
		Files f = new Files();
		// System.out.println(f.readFile("f:\\LinkFile.java"));
		// f.readAllFile("f:\\","LinkFile.java");
		// f.readLineFile("f:\\","LinkFile.java");
		// System.out.println(f.fileIsNull("f:\\","122.txt"));
		// f.readFolderByFile("F:\\PDF");
		// System.out.println(f.createAndDeleteFolder("ss","f:\\"));
		// System.out.println(f.createAndDeleteFile("f:\\ss\\","TestFile.dat"));
		String[] ss = new String[50];
		for (int i = 0; i < ss.length; i++) {
			ss[i] = "��Ϣ�����ͻ�����(�������Ӳ��,ͨѶ) " + i;
		
		f.writeFile("","TestFile.txt",true, ss[i]);
	}
	}
	/**
	 * �ļ���д��
	 * 
	 * @param filePath(�ļ�·��)
	 * @param fileName(�ļ���)
	 * @param isappend
	 * @param s
	 * @throws IOException
	 */
	public void writeFile(String filePath, String fileName,boolean bool, String  s)
			throws IOException {
		FileWriter fw = new FileWriter(filePath + fileName,bool);
		BufferedWriter bw = new BufferedWriter(fw,10000);
		bw.write(s);
		
//  bw.write("\r\n");
		bw.newLine();
		bw.flush(); 
		bw.close();
		fw.close();
	}

 
	/**
	 * ������ɾ���ļ�
	 * 
	 * @param filePath
	 * @param fileName
	 * @return �����ɹ�����true
	 * @throws IOException
	 */
	public boolean createAndDeleteFile(String filePath, String fileName)
			throws IOException {
		boolean result = false;
		File file = new File(filePath, fileName);
		if (file.exists()) {
			file.delete();
			result = true;
			System.out.println("�ļ��Ѿ�ɾ����");
		} else {
			file.createNewFile();
			result = true;
			System.out.println("�ļ��Ѿ�������");
		}
		return result;
	}

	/**
	 * ������ɾ��Ŀ¼
	 * 
	 * @param folderName
	 * @param filePath
	 * @return ɾ���ɹ�����true
	 */
	public boolean createAndDeleteFolder(String folderName, String filePath) {
		boolean result = false;
		try {
			File file = new File(filePath + folderName);
			if (file.exists()) {
				file.delete();
				System.out.println("Ŀ¼�Ѿ����ڣ���ɾ��!");
				result = true;
			} else {
				file.mkdir();
				System.out.println("Ŀ¼�����ڣ��Ѿ�����!");
				result = true;
			}
		} catch (Exception ex) {
			result = false;
			System.out.println("CreateAndDeleteFolder is error:" + ex);
		}
		return result;
	}

	/**
	 * ���Ŀ¼�е������ļ���Ŀ¼����
	 * 
	 * @param filePath
	 */
	public void readFolderByFile(String filePath) {
		File file = new File(filePath);
		File[] tempFile = file.listFiles();
		for (int i = 0; i < tempFile.length; i++) {
			if (tempFile[i].isFile()) {
				System.out.println("File : " + tempFile[i].getName());
			}
			if (tempFile[i].isDirectory()) {
				System.out.println("Directory : " + tempFile[i].getName());
			}
		}
	}

	/**
	 * ����ļ����Ƿ�Ϊһ����
	 * 
	 * @param filePath
	 * @param fileName
	 * @return Ϊ�շ���true
	 * @throws IOException
	 */
	public boolean fileIsNull(String filePath, String fileName)
			throws IOException {
		boolean result = false;
		FileReader fr = new FileReader(filePath + fileName);
		if (fr.read() == -1) {
			result = true;
			System.out.println(fileName + " �ļ���û������!");
		} else {
			System.out.println(fileName + " �ļ���������!");
		}
		fr.close();
		return result;
	}

	/**
	 * ��ȡ�ļ��е���������
	 * 
	 * @param filePath
	 * @param fileName
	 * @throws IOException
	 */
	public void readAllFile(String filePath, String fileName)
			throws IOException {
		FileReader fr = new FileReader(filePath + fileName);
		BufferedReader br = new BufferedReader(fr,1000);
		int count = br.read();
		while (count != -1) {
			System.out.print((char) count);
			count = fr.read();
			if (count == 13) {
				fr.skip(1);
			}
		}
		br.close();
		fr.close();
	}

	/**
	 * һ��һ�еĶ�ȡ�ļ��е�����
	 * 
	 * @param filePath
	 * @param fileName
	 * @throws IOException
	 */
	public void readLineFile(String filePath, String fileName)
			throws IOException {
		FileReader fr = new FileReader(filePath + fileName);
		BufferedReader br = new BufferedReader(fr);
		String line = br.readLine();
		while (line != null) {
			System.out.println(line);
			line = br.readLine();
		}
		br.close();
		fr.close();
	}
}
