package org.king.framework.dao;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

import org.king.framework.util.MyUtils;

public class test {

	/**
	 * Description: TODO
	 *@param args
	 * @return void
	 * Modify History: 2006-8-18 jackey create
	 */
	public static void main(String[] args) {
		String head="";
		String end="";
		FileReader fr= null;
		BufferedReader br = null;
		FileWriter fw=null;
		BufferedWriter bw= null;
		try {
			fr=new FileReader("d:/pwd.txt");
			fw=new FileWriter("d:/pass.txt"); 
			br=new BufferedReader(fr);//
			bw=new BufferedWriter(fw); 

			String Line=br.readLine(); 
			
			while(Line!=null){
				String [] abc = Line.split(",");
				head = abc[0];
				end = abc[1];
				bw.write(head);
				bw.write(",");
				bw.write(MyUtils.toMD5(end));
				bw.newLine();
				bw.flush();
				Line=br.readLine(); 
				System.out.println(MyUtils.toMD5(abc[1]));
			}
//			String [] abc = Line.split(",");
//			System.out.println(MyUtils.toMD5(abc[1]));
			br.close();
			fr.close(); 
			bw.close();
			fw.close();//关闭文件流 

			
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally{

		}
		
	}

}


