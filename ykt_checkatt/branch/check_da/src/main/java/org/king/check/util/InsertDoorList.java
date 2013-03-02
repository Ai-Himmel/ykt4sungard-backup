package org.king.check.util;

import org.king.check.door.PersonsTaskBiz;
public class InsertDoorList extends Thread {
	
	public InsertDoorList(){
		start();
	}
	
	public void run() {
		try{
			System.out.println("-----begin--insert---");
		      PersonsTaskBiz.insertDoorList();
		    System.out.println("-------over---");
		}catch(Exception e){
			e.printStackTrace();
		}
		
	}

}
