package org.king.termdev.domain;

import java.math.BigDecimal;
import java.util.Date;

/**
 * AbstractMonitorDevicecomments entity provides the base persistence definition
 * of the MonitorDevicecomments entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorDevicecomments extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private BigDecimal commentId;
	private Date entryTime;
	private BigDecimal entryType;
	private BigDecimal deviceId;
	private String authorName;
	private String commentData;
	private BigDecimal isPersistent;
	private BigDecimal commentSource;
	private BigDecimal expires;
	private Date expirationTime;
	private BigDecimal isDeleted;
	private Date deletionTime;

	// Constructors

	/** default constructor */
	public AbstractMonitorDevicecomments() {
	}

	/** full constructor */
	public AbstractMonitorDevicecomments(Date entryTime, BigDecimal entryType,
			BigDecimal deviceId, String authorName, String commentData,
			BigDecimal isPersistent, BigDecimal commentSource,
			BigDecimal expires, Date expirationTime, BigDecimal isDeleted,
			Date deletionTime) {
		this.entryTime = entryTime;
		this.entryType = entryType;
		this.deviceId = deviceId;
		this.authorName = authorName;
		this.commentData = commentData;
		this.isPersistent = isPersistent;
		this.commentSource = commentSource;
		this.expires = expires;
		this.expirationTime = expirationTime;
		this.isDeleted = isDeleted;
		this.deletionTime = deletionTime;
	}

	// Property accessors

	public BigDecimal getCommentId() {
		return this.commentId;
	}

	public void setCommentId(BigDecimal commentId) {
		this.commentId = commentId;
	}

	public Date getEntryTime() {
		return this.entryTime;
	}

	public void setEntryTime(Date entryTime) {
		this.entryTime = entryTime;
	}

	public BigDecimal getEntryType() {
		return this.entryType;
	}

	public void setEntryType(BigDecimal entryType) {
		this.entryType = entryType;
	}

	public BigDecimal getDeviceId() {
		return this.deviceId;
	}

	public void setDeviceId(BigDecimal deviceId) {
		this.deviceId = deviceId;
	}

	public String getAuthorName() {
		return this.authorName;
	}

	public void setAuthorName(String authorName) {
		this.authorName = authorName;
	}

	public String getCommentData() {
		return this.commentData;
	}

	public void setCommentData(String commentData) {
		this.commentData = commentData;
	}

	public BigDecimal getIsPersistent() {
		return this.isPersistent;
	}

	public void setIsPersistent(BigDecimal isPersistent) {
		this.isPersistent = isPersistent;
	}

	public BigDecimal getCommentSource() {
		return this.commentSource;
	}

	public void setCommentSource(BigDecimal commentSource) {
		this.commentSource = commentSource;
	}

	public BigDecimal getExpires() {
		return this.expires;
	}

	public void setExpires(BigDecimal expires) {
		this.expires = expires;
	}

	public Date getExpirationTime() {
		return this.expirationTime;
	}

	public void setExpirationTime(Date expirationTime) {
		this.expirationTime = expirationTime;
	}

	public BigDecimal getIsDeleted() {
		return this.isDeleted;
	}

	public void setIsDeleted(BigDecimal isDeleted) {
		this.isDeleted = isDeleted;
	}

	public Date getDeletionTime() {
		return this.deletionTime;
	}

	public void setDeletionTime(Date deletionTime) {
		this.deletionTime = deletionTime;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((authorName == null) ? 0 : authorName.hashCode());
		result = prime * result
				+ ((commentData == null) ? 0 : commentData.hashCode());
		result = prime * result
				+ ((commentId == null) ? 0 : commentId.hashCode());
		result = prime * result
				+ ((commentSource == null) ? 0 : commentSource.hashCode());
		result = prime * result
				+ ((deletionTime == null) ? 0 : deletionTime.hashCode());
		result = prime * result
				+ ((deviceId == null) ? 0 : deviceId.hashCode());
		result = prime * result
				+ ((entryTime == null) ? 0 : entryTime.hashCode());
		result = prime * result
				+ ((entryType == null) ? 0 : entryType.hashCode());
		result = prime * result
				+ ((expirationTime == null) ? 0 : expirationTime.hashCode());
		result = prime * result + ((expires == null) ? 0 : expires.hashCode());
		result = prime * result
				+ ((isDeleted == null) ? 0 : isDeleted.hashCode());
		result = prime * result
				+ ((isPersistent == null) ? 0 : isPersistent.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorDevicecomments))
			return false;
		AbstractMonitorDevicecomments other = (AbstractMonitorDevicecomments) obj;
		if (authorName == null) {
			if (other.authorName != null)
				return false;
		} else if (!authorName.equals(other.authorName))
			return false;
		if (commentData == null) {
			if (other.commentData != null)
				return false;
		} else if (!commentData.equals(other.commentData))
			return false;
		if (commentId == null) {
			if (other.commentId != null)
				return false;
		} else if (!commentId.equals(other.commentId))
			return false;
		if (commentSource == null) {
			if (other.commentSource != null)
				return false;
		} else if (!commentSource.equals(other.commentSource))
			return false;
		if (deletionTime == null) {
			if (other.deletionTime != null)
				return false;
		} else if (!deletionTime.equals(other.deletionTime))
			return false;
		if (deviceId == null) {
			if (other.deviceId != null)
				return false;
		} else if (!deviceId.equals(other.deviceId))
			return false;
		if (entryTime == null) {
			if (other.entryTime != null)
				return false;
		} else if (!entryTime.equals(other.entryTime))
			return false;
		if (entryType == null) {
			if (other.entryType != null)
				return false;
		} else if (!entryType.equals(other.entryType))
			return false;
		if (expirationTime == null) {
			if (other.expirationTime != null)
				return false;
		} else if (!expirationTime.equals(other.expirationTime))
			return false;
		if (expires == null) {
			if (other.expires != null)
				return false;
		} else if (!expires.equals(other.expires))
			return false;
		if (isDeleted == null) {
			if (other.isDeleted != null)
				return false;
		} else if (!isDeleted.equals(other.isDeleted))
			return false;
		if (isPersistent == null) {
			if (other.isPersistent != null)
				return false;
		} else if (!isPersistent.equals(other.isPersistent))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorDevicecomments [authorName=" + authorName
				+ ", commentData=" + commentData + ", commentId=" + commentId
				+ ", commentSource=" + commentSource + ", deletionTime="
				+ deletionTime + ", deviceId=" + deviceId + ", entryTime="
				+ entryTime + ", entryType=" + entryType + ", expirationTime="
				+ expirationTime + ", expires=" + expires + ", isDeleted="
				+ isDeleted + ", isPersistent=" + isPersistent + "]";
	}

}