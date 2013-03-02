package org.king.classmanage.web.help;

public class MajorinInfo {
	
	private String dalei;
	private String yuanxi;
	private String daima;
	private String zhuanye;
	
	public MajorinInfo(String dalei, String yuanxi, String daima, String zhuanye) {
		this.dalei = dalei;
		this.yuanxi = yuanxi;
		this.daima = daima;
		this.zhuanye = zhuanye;
	}
	/**
	 * @return Returns the daima.
	 */
	public String getDaima() {
		return daima;
	}
	/**
	 * @param daima The daima to set.
	 */
	public void setDaima(String daima) {
		this.daima = daima;
	}
	/**
	 * @return Returns the dalei.
	 */
	public String getDalei() {
		return dalei;
	}
	/**
	 * @param dalei The dalei to set.
	 */
	public void setDalei(String dalei) {
		this.dalei = dalei;
	}
	/**
	 * @return Returns the yuanxi.
	 */
	public String getYuanxi() {
		return yuanxi;
	}
	/**
	 * @param yuanxi The yuanxi to set.
	 */
	public void setYuanxi(String yuanxi) {
		this.yuanxi = yuanxi;
	}
	/**
	 * @return Returns the zhuanye.
	 */
	public String getZhuanye() {
		return zhuanye;
	}
	/**
	 * @param zhuanye The zhuanye to set.
	 */
	public void setZhuanye(String zhuanye) {
		this.zhuanye = zhuanye;
	}
	
	
	

}
