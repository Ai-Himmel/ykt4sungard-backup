package com.kingstargroup.ecard.hibernate.hitinfo;

import java.util.Date;

public class HitInfoResult {

	
	    private java.lang.Integer id;

	    /** The value of the simple title property. */
	    private java.lang.String title;

	    /** The value of the simple infoId property. */
	    private java.lang.Integer infoId;
	    

	    /** The value of the simple infoType property. */
	    private java.lang.String infoType;

	    /** The value of the simple infoTitle property. */
	    private java.lang.String infoTitle;


	    /** The value of the simple attachments property. */
	    private java.lang.String attachments;

	    /** The value of the simple createDate property. */
	    private java.util.Date createDate;

		public java.lang.Integer getId() {
			return id;
		}

		public void setId(java.lang.Integer id) {
			this.id = id;
		}

		public java.lang.String getTitle() {
			return title;
		}

		public void setTitle(java.lang.String title) {
			this.title = title;
		}

		public java.lang.Integer getInfoId() {
			return infoId;
		}

		public void setInfoId(java.lang.Integer infoId) {
			this.infoId = infoId;
		}

		public java.lang.String getInfoType() {
			return infoType;
		}

		public void setInfoType(java.lang.String infoType) {
			this.infoType = infoType;
		}

		public java.lang.String getInfoTitle() {
			return infoTitle;
		}

		public void setInfoTitle(java.lang.String infoTitle) {
			this.infoTitle = infoTitle;
		}

		public java.lang.String getAttachments() {
			return attachments;
		}

		public void setAttachments(java.lang.String attachments) {
			this.attachments = attachments;
		}

		public java.util.Date getCreateDate() {
			return createDate;
		}

		public void setCreateDate(java.util.Date createDate) {
			this.createDate = createDate;
		}

		public HitInfoResult(Integer id, String title, Integer infoId,
				String infoType, String infoTitle, String attachments,
				Date createDate) {
			super();
			this.id = id;
			this.title = title;
			this.infoId = infoId;
			this.infoType = infoType;
			this.infoTitle = infoTitle;
			this.attachments = attachments;
			this.createDate = createDate;
		}

}
