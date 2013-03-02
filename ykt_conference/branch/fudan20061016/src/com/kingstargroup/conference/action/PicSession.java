package com.kingstargroup.conference.action;

import java.util.HashMap;

import com.kingstargroup.conference.hibernate.form.TCifPhoto;

public class PicSession {


	private static HashMap photohash = new HashMap();

	private static PicSession intance = null;

	private static Object mutex = new Object();

	public static PicSession getIntance() {
		if (intance == null) {
			synchronized (mutex) {
				if (intance == null) {
					intance = new PicSession();
				}
			}
		}
		return intance;
	}
	
	private static PicSession instance = new PicSession();




	synchronized public void setPic(String stuempNo,TCifPhoto photo) {
		photohash.put(stuempNo, photo);

	}

	public  TCifPhoto getPic(String stuempNo) {
		return (TCifPhoto)photohash.get(stuempNo);
	}

	
	public  int getSize() {
		return photohash.size();
	}

	synchronized public  void clear() {
		photohash.clear();
	}


}
