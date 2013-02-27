package org.king.monitor.domain;

public class DictionaryResult extends AbstractResult {
	/** The value of the simple setsid property. */
	private long itemNo;

	/** The value of the simple setname property. */
	private String itemName;

	public String getItemName() {
		return itemName;
	}

	public void setItemName(String itemName) {
		this.itemName = itemName;
	}

	public long getItemNo() {
		return itemNo;
	}

	public void setItemNo(long itemNo) {
		this.itemNo = itemNo;
	}

	public DictionaryResult(long itemNo, String itemName) {
		super();
		// TODO Auto-generated constructor stub
		this.itemName = itemName;
		this.itemNo = itemNo;
	}

}
