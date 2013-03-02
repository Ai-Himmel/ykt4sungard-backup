package org.king.yangong.dormitorymanage.web.help;

public class CollegeWithStuCount {
	private String collegeCode;

	private String stuType;

	private int stuCount;

	private int yjsMaleCount;

	private int yjsFemaleCount;

	private int bsMaleCount;

	private int bsFemaleCount;

	public CollegeWithStuCount(String collegeCode,String stuType, int stuCount,
			int yjsMaleCount, int yjsFemaleCount, int bsMaleCount,
			int bsFemaleCount) {
		this.collegeCode = collegeCode;
		this.stuType = stuType;
		this.stuCount = stuCount;
		this.yjsMaleCount = yjsMaleCount;
		this.yjsFemaleCount = yjsFemaleCount;
		this.bsMaleCount = bsMaleCount;
		this.bsFemaleCount = bsFemaleCount;
	}

	public int getBsFemaleCount() {
		return bsFemaleCount;
	}

	public void setBsFemaleCount(int bsFemaleCount) {
		this.bsFemaleCount = bsFemaleCount;
	}

	public int getBsMaleCount() {
		return bsMaleCount;
	}

	public void setBsMaleCount(int bsMaleCount) {
		this.bsMaleCount = bsMaleCount;
	}

	public String getCollegeCode() {
		return collegeCode;
	}

	public void setCollegeCode(String collegeCode) {
		this.collegeCode = collegeCode;
	}

	public int getStuCount() {
		return stuCount;
	}

	public void setStuCount(int stuCount) {
		this.stuCount = stuCount;
	}

	public String getStuType() {
		return stuType;
	}

	public void setStuType(String stuType) {
		this.stuType = stuType;
	}

	public int getYjsFemaleCount() {
		return yjsFemaleCount;
	}

	public void setYjsFemaleCount(int yjsFemaleCount) {
		this.yjsFemaleCount = yjsFemaleCount;
	}

	public int getYjsMaleCount() {
		return yjsMaleCount;
	}

	public void setYjsMaleCount(int yjsMaleCount) {
		this.yjsMaleCount = yjsMaleCount;
	}

}
