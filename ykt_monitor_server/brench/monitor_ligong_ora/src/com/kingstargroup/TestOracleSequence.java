/**
 * 
 */
package com.kingstargroup;

import java.util.Iterator;
import java.util.List;

import org.hibernate.Hibernate;
import org.hibernate.Query;

import com.kingstargroup.form.TTifMeslist;
import com.kingstargroup.utils.OracleTimeUtil;

/**
 * @author jackey
 *
 */
public class TestOracleSequence {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TTifMeslist mesList = new TTifMeslist();
		mesList.setCardNo(Long.parseLong("0"));
		mesList.setDelFlag("0");
		mesList.setDeviceId(Long.parseLong("539"));

		mesList.setDevid(Long.parseLong("541"));
		mesList.setFunid(Long.parseLong("930016"));
		mesList.setIncontent("<FEETYPE>0</FEETYPE><STARTNUM>103</STARTNUM><ENDNUM>103</ENDNUM>");
		mesList.setEcode(Long.parseLong("9999"));
		mesList.setIndt(OracleTimeUtil.getSysDate(0));
		mesList.setLevel(Long.parseLong("1"));
		mesList.setMaxSendCnt(Long.parseLong("100"));
		mesList.setPfunid(Long.parseLong("0"));
		mesList.setSendcount(Long.parseLong("0"));
		mesList.setStateid(Long.parseLong("1"));
		

	}

}
