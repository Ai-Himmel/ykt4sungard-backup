package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTGroup entity provides the base persistence definition of the TGroup
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTGroup implements java.io.Serializable {

	// Fields

	private long groupId;
	private String operId;
	private String groupName;
	private String comments;

	// Constructors

	/** default constructor */
	public AbstractTGroup() {
	}

	/** minimal constructor */
	public AbstractTGroup(String operId) {
		this.operId = operId;
	}

	/** full constructor */
	public AbstractTGroup(String operId, String groupName, String comments) {
		this.operId = operId;
		this.groupName = groupName;
		this.comments = comments;
	}

	// Property accessors

	public long getGroupId() {
		return this.groupId;
	}

	public void setGroupId(long groupId) {
		this.groupId = groupId;
	}

	public String getOperId() {
		return this.operId;
	}

	public void setOperId(String operId) {
		this.operId = operId;
	}

	public String getGroupName() {
		return this.groupName;
	}

	public void setGroupName(String groupName) {
		this.groupName = groupName;
	}

	public String getComments() {
		return this.comments;
	}

	public void setComments(String comments) {
		this.comments = comments;
	}

}