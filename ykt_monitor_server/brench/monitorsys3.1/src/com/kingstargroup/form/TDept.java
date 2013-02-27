package com.kingstargroup.form;

/**
 * TDept entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDept extends AbstractTDept implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDept() {
	}

	/** minimal constructor */
	public TDept(String deptcode) {
		super(deptcode);
	}

	/** full constructor */
	public TDept(String deptcode, String areacode, String deptname,
			String deptename, String deptfullname, String fdeptcode,
			long deptlevel, String olddeptcode, String useflag, String lastsaved) {
		super(deptcode, areacode, deptname, deptename, deptfullname, fdeptcode,
				deptlevel, olddeptcode, useflag, lastsaved);
	}

}
