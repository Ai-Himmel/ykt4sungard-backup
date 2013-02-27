package org.king.monitor.domain;

/**
 * AbstractMapUserTable entity provides the base persistence definition of the
 * MapUserTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapUserTable implements java.io.Serializable {

	// Fields

	private long id;
	private String username;
	private String name;
	private String password;
	private String gender;
	private String company;
	private String email;
	private String phone;
	private String userrole;
	private String logintime;
	private long userstatus;
	private String adduser;
	private String createtime;

	// Constructors

	/** default constructor */
	public AbstractMapUserTable() {
	}

	/** full constructor */
	public AbstractMapUserTable(String username, String name, String password,
			String gender, String company, String email, String phone,
			String userrole, String logintime, long userstatus, String adduser,
			String createtime) {
		this.username = username;
		this.name = name;
		this.password = password;
		this.gender = gender;
		this.company = company;
		this.email = email;
		this.phone = phone;
		this.userrole = userrole;
		this.logintime = logintime;
		this.userstatus = userstatus;
		this.adduser = adduser;
		this.createtime = createtime;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public String getUsername() {
		return this.username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getPassword() {
		return this.password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public String getGender() {
		return this.gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}

	public String getCompany() {
		return this.company;
	}

	public void setCompany(String company) {
		this.company = company;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getPhone() {
		return this.phone;
	}

	public void setPhone(String phone) {
		this.phone = phone;
	}

	public String getUserrole() {
		return this.userrole;
	}

	public void setUserrole(String userrole) {
		this.userrole = userrole;
	}

	public String getLogintime() {
		return this.logintime;
	}

	public void setLogintime(String logintime) {
		this.logintime = logintime;
	}

	public long getUserstatus() {
		return this.userstatus;
	}

	public void setUserstatus(long userstatus) {
		this.userstatus = userstatus;
	}

	public String getAdduser() {
		return this.adduser;
	}

	public void setAdduser(String adduser) {
		this.adduser = adduser;
	}

	public String getCreatetime() {
		return this.createtime;
	}

	public void setCreatetime(String createtime) {
		this.createtime = createtime;
	}

}