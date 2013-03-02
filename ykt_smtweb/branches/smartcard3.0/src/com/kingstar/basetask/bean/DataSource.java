package com.kingstar.basetask.bean;

public class DataSource {
	int id;
	String dbtype = "";
	String url = "";
	String driver_class = "";
	String username = "";
	String password = "";
	int maxconn;
	String comment = "";

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getDbtype() {
		return dbtype;
	}

	public void setDbtype(String dbtype) {
		this.dbtype = dbtype;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
	}

	public String getDriver_class() {
		return driver_class;
	}

	public void setDriver_class(String driver_class) {
		this.driver_class = driver_class;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public int getMaxconn() {
		return maxconn;
	}

	public void setMaxconn(int maxconn) {
		this.maxconn = maxconn;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}

}
