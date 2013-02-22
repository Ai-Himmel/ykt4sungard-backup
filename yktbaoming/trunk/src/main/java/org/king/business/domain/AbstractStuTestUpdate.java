package org.king.business.domain;

/**
 * AbstractStuTestUpdate entity provides the base persistence definition of the
 * StuTestUpdate entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractStuTestUpdate extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {


	private String id;
	private BmStudent bmStudent;
	private BmTest oldBmTest;
	private BmTest newBmTest;
	private String updateTime;
	private String updator;

	// Constructors

	public String getUpdator() {
		return updator;
	}

	public void setUpdator(String updator) {
		this.updator = updator;
	}

	/** default constructor */
	public AbstractStuTestUpdate() {
	}

	/** full constructor */
	public AbstractStuTestUpdate(String id, BmStudent bmStudent,
			BmTest oldBmTest, BmTest newBmTest, String updateTime,String updator) {
		this.id = id;
		this.bmStudent = bmStudent;
		this.oldBmTest = oldBmTest;
		this.newBmTest = newBmTest;
		this.updateTime = updateTime;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	

	public BmStudent getBmStudent() {
		return bmStudent;
	}

	public void setBmStudent(BmStudent bmStudent) {
		this.bmStudent = bmStudent;
	}


	public BmTest getOldBmTest() {
		return oldBmTest;
	}

	public void setOldBmTest(BmTest oldBmTest) {
		this.oldBmTest = oldBmTest;
	}

	public BmTest getNewBmTest() {
		return newBmTest;
	}

	public void setNewBmTest(BmTest newBmTest) {
		this.newBmTest = newBmTest;
	}

	public String getUpdateTime() {
		return this.updateTime;
	}

	public void setUpdateTime(String updateTime) {
		this.updateTime = updateTime;
	}

	
}