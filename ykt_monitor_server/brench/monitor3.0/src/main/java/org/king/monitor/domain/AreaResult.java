package org.king.monitor.domain;

public class AreaResult extends AbstractResult{
 /** The value of the simple setsid property. */
    private String itemNo;

    /** The value of the simple setname property. */
    private java.lang.String itemName;
    
    public java.lang.String getItemName() {
		return itemName;
	}

	public void setItemName(java.lang.String itemName) {
		this.itemName = itemName;
	}

	public String getItemNo() {
		return itemNo;
	}

	public void setItemNo(String itemNo) {
		this.itemNo = itemNo;
	}

	public AreaResult(String itemNo,String itemName) {
		super();
		// TODO Auto-generated constructor stub
		this.itemName = itemName;
		this.itemNo = itemNo;
	}


}

