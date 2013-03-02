package org.king.check.domain;

import org.apache.commons.lang.builder.ToStringBuilder;

/**
 * TCheckattReportId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TCheckattReportId extends AbstractTCheckattReportId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCheckattReportId() {
	}

	/** full constructor */
	public TCheckattReportId(long custId, String checkDate) {
		super(custId, checkDate);
	}

	/**
	 * @see java.lang.Object#toString()
	 */
	public String toString() {
		return new ToStringBuilder(this).append("custId", this.getCustId())
				.append("checkDate", this.getCheckDate()).toString();
	}

	public void setCustId(Integer valueOf) {
		// TODO Auto-generated method stub
		
	}

	
}
