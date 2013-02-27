package com.kingstargroup.form;

/**
 * MapUserTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapUserTable extends AbstractMapUserTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapUserTable() {
	}

	/** full constructor */
	public MapUserTable(String username, String name, String password,
			String gender, String company, String email, String phone,
			String userrole, String logintime, long userstatus, String adduser,
			String createtime) {
		super(username, name, password, gender, company, email, phone,
				userrole, logintime, userstatus, adduser, createtime);
	}

}
