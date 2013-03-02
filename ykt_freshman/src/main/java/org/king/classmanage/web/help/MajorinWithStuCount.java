package org.king.classmanage.web.help;

public class MajorinWithStuCount {
	private String majorinCode;
	private int stuCount;
	private int stuMaleCount;
	private int stuFemaleCount;
	
	public MajorinWithStuCount(String majorinCode, int stuCount, int stuMaleCount, int stuFemaleCount) {
		this.majorinCode = majorinCode;
		this.stuCount = stuCount;
		this.stuMaleCount = stuMaleCount;
		this.stuFemaleCount = stuFemaleCount;
	}
	/**
	 * @return Returns the majorinCode.
	 */
	public String getMajorinCode() {
		return majorinCode;
	}
	/**
	 * @param majorinCode The majorinCode to set.
	 */
	public void setMajorinCode(String majorinCode) {
		this.majorinCode = majorinCode;
	}
	/**
	 * @return Returns the stuCount.
	 */
	public int getStuCount() {
		return stuCount;
	}
	/**
	 * @param stuCount The stuCount to set.
	 */
	public void setStuCount(int stuCount) {
		this.stuCount = stuCount;
	}
	/**
	 * @return Returns the stuFemaleCount.
	 */
	public int getStuFemaleCount() {
		return stuFemaleCount;
	}
	/**
	 * @param stuFemaleCount The stuFemaleCount to set.
	 */
	public void setStuFemaleCount(int stuFemaleCount) {
		this.stuFemaleCount = stuFemaleCount;
	}
	/**
	 * @return Returns the stuMaleCount.
	 */
	public int getStuMaleCount() {
		return stuMaleCount;
	}
	/**
	 * @param stuMaleCount The stuMaleCount to set.
	 */
	public void setStuMaleCount(int stuMaleCount) {
		this.stuMaleCount = stuMaleCount;
	}
	


}
