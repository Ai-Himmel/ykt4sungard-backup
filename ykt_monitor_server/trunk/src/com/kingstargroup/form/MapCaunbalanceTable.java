package com.kingstargroup.form;

/**
 * MapCaunbalanceTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapCaunbalanceTable extends AbstractMapCaunbalanceTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapCaunbalanceTable() {
	}

	/** minimal constructor */
	public MapCaunbalanceTable(MapCaunbalanceTableId id) {
		super(id);
	}

	/** full constructor */
	public MapCaunbalanceTable(MapCaunbalanceTableId id, String accname,
			String subjno, String accpwd, long custid, long cardno,
			long purseno, double daycostmaxamt, double cardmaxbal,
			String stoppayflag, String status, double ydaybal,
			double ydayavailbal, double ydayfrozebal, double balance,
			double availbal, double frozebal, double subsidybal,
			double foregift, long lastcardcnt, double lastcardbal,
			double daycostamt, String lasttransdate, String lastaccdate,
			long lastsubsidyno, String opendate, String closedate) {
		super(id, accname, subjno, accpwd, custid, cardno, purseno,
				daycostmaxamt, cardmaxbal, stoppayflag, status, ydaybal,
				ydayavailbal, ydayfrozebal, balance, availbal, frozebal,
				subsidybal, foregift, lastcardcnt, lastcardbal, daycostamt,
				lasttransdate, lastaccdate, lastsubsidyno, opendate, closedate);
	}

}
