package com.kingstargroup.ecard.hibernate.friendslink;

import java.io.Serializable;
import java.util.Date;
public abstract class AbstractFriendsLink     extends com.kingstargroup.ecard.common.BasicPersistence
implements Serializable {
	
	private Integer id;
	private String  linkName;
	private String  linkUrl;
	private Date    createDate;
	private String  creater;

	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public Date getCreateDate() {
		return createDate;
	}

	public void setCreateDate(Date createDate) {
		this.createDate = createDate;
	}

	public String getCreater() {
		return creater;
	}

	public void setCreater(String creater) {
		this.creater = creater;
	}

	public String getLinkName() {
		return linkName;
	}

	public void setLinkName(String linkName) {
		this.linkName = linkName;
	}

	public String getLinkUrl() {
		return linkUrl;
	}

	public void setLinkUrl(String linkUrl) {
		this.linkUrl = linkUrl;
	}

	public AbstractFriendsLink() {
		
	}
    public AbstractFriendsLink(Integer id) {
		this.id = id;
	}
	

}
