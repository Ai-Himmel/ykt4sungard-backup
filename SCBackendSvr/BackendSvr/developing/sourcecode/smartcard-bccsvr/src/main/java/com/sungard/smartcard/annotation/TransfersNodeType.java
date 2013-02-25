/*
 * TransfersNodeType.java  v1.00  2011-12-31
 * Peoject	smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	TransfersNodeType.java  v1.00 2011-12-31
 * Project	: 	smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

/**
 * 传输节点类型. 对应于cpack.dat
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-31
 * 
 */
public enum TransfersNodeType {

    scust_no("scust_no", "char", 11), //
    scust_no2("scust_no2", "char", 11), //
    sholder_ac_no("sholder_ac_no", "char", 16), //
    sholder_ac_no2("sholder_ac_no2", "char", 16), //
    sholder_type("sholder_type", "char", 3), //
    sholder_type2("sholder_type2", "char", 3), //
    sname("sname", "char", 21), //
    sname2("sname2", "char", 21), //
    sall_name("sall_name", "char", 81), //
    smarket_code("smarket_code", "char", 2), //
    smarket_code2("smarket_code2", "char", 2), //
    sdate0("sdate0", "char", 9), //
    sdate1("sdate1", "char", 9), //
    sdate2("sdate2", "char", 9), //
    sdate3("sdate3", "char", 9), //
    stime0("stime0", "char", 9), //
    stime1("stime1", "char", 9), //
    stime2("stime2", "char", 9), //
    stime3("stime3", "char", 9), //
    lvol0("lvol0", "int", 4), //
    lvol1("lvol1", "int", 4), //
    lvol2("lvol2", "int", 4), //
    lvol3("lvol3", "int", 4), //
    lvol4("lvol4", "int", 4), //
    lvol5("lvol5", "int", 4), //
    lvol6("lvol6", "int", 4), //
    lvol7("lvol7", "int", 4), //
    lvol8("lvol8", "int", 4), //
    lvol9("lvol9", "int", 4), //
    lvol10("lvol10", "int", 4), //
    lvol11("lvol11", "int", 4), //
    lvol12("lvol12", "int", 4), //
    damt0("damt0", "double", 8), //
    damt1("damt1", "double", 8), //
    damt2("damt2", "double", 8), //
    damt3("damt3", "double", 8), //
    damt4("damt4", "double", 8), //
    damt5("damt5", "double", 8), //
    damt6("damt6", "double", 8), //
    damt7("damt7", "double", 8), //
    damt8("damt8", "double", 8), //
    damt9("damt9", "double", 8), //
    damt10("damt10", "double", 8), //
    damt11("damt11", "double", 8), //
    damt12("damt12", "double", 8), //
    damt13("damt13", "double", 8), //
    damt14("damt14", "double", 8), //
    damt15("damt15", "double", 8), //
    damt16("damt16", "double", 8), //
    damt17("damt17", "double", 8), //
    damt18("damt18", "double", 8), //
    damt19("damt19", "double", 8), //
    damt20("damt20", "double", 8), //
    damt21("damt21", "double", 8), //
    damt22("damt22", "double", 8), //
    damt23("damt23", "double", 8), //
    damt24("damt24", "double", 8), //
    damt25("damt25", "double", 8), //
    damt26("damt26", "double", 8), //
    damt27("damt27", "double", 8), //
    damt28("damt28", "double", 8), //
    damt29("damt29", "double", 8), //
    damt30("damt30", "double", 8), //
    damt31("damt31", "double", 8), //
    damt32("damt32", "double", 8), //
    damt33("damt33", "double", 8), //
    sstock_code("sstock_code", "char", 9), //
    sstock_code2("sstock_code2", "char", 9), //
    scust_type("scust_type", "char", 3), //
    scust_type2("scust_type2", "char", 3), //
    sstat_type("sstat_type", "char", 3), //
    sstat_type2("sstat_type2", "char", 3), //
    sroom_no("sroom_no", "char", 4), //
    sroom_no2("sroom_no2", "char", 4), //
    sopen_emp("sopen_emp", "char", 7), //
    sclose_emp("sclose_emp", "char", 7), //
    schange_emp("schange_emp", "char", 7), //
    scheck_emp("scheck_emp", "char", 7), //
    semp("semp", "char", 7), //
    snation_code("snation_code", "char", 4), //
    lcert_code("lcert_code", "int", 4), //
    stx_pwd("stx_pwd", "char", 9), //
    stx_pwd2("stx_pwd2", "char", 9), //
    swithdraw_pwd("swithdraw_pwd", "char", 9), //
    swithdraw_pwd2("swithdraw_pwd2", "char", 9), //
    semp_pwd("semp_pwd", "char", 9), //
    semp_pwd2("semp_pwd2", "char", 9), //
    sbank_pwd("sbank_pwd", "char", 9), //
    sbank_pwd2("sbank_pwd2", "char", 9), //
    scust_auth("scust_auth", "char", 21), //
    scust_auth2("scust_auth2", "char", 21), //
    scust_limit("scust_limit", "char", 33), //
    scust_limit2("scust_limit2", "char", 33), //
    lsafe_level("lsafe_level", "int", 4), //
    lsafe_level2("lsafe_level2", "int", 4), //
    spost_code("spost_code", "char", 7), //
    spost_code2("spost_code2", "char", 7), //
    sphone("sphone", "char", 31), //
    sphone2("sphone2", "char", 31), //
    sphone3("sphone3", "char", 31), //
    spager("spager", "char", 31), //
    semail("semail", "char", 61), //
    semail2("semail2", "char", 61), //
    snote("snote", "char", 81), //
    snote2("snote2", "char", 81), //
    scert_no("scert_no", "char", 51), //
    scert_no2("scert_no2", "char", 51), //
    scert_addr("scert_addr", "char", 81), //
    sstatus0("sstatus0", "char", 2), //
    sstatus1("sstatus1", "char", 2), //
    sstatus2("sstatus2", "char", 2), //
    sstatus3("sstatus3", "char", 2), //
    sstatus4("sstatus4", "char", 2), //
    lwithdraw_flag("lwithdraw_flag", "int", 4), //
    saddr("saddr", "char", 81), //
    saddr2("saddr2", "char", 81), //
    sserial0("sserial0", "char", 13), //
    sserial1("sserial1", "char", 13), //
    sserial2("sserial2", "char", 13), //
    sserial3("sserial3", "char", 13), //
    sserial4("sserial4", "char", 13), //
    scurrency_type("scurrency_type", "char", 3), //
    scurrency_type2("scurrency_type2", "char", 3), //
    sbranch_code0("sbranch_code0", "char", 4), //
    sbranch_code1("sbranch_code1", "char", 4), //
    sbranch_code2("sbranch_code2", "char", 4), //
    usset0("usset0", "unsignedchar", 100), //
    usset1("usset1", "unsignedchar", 100), //
    usset2("usset2", "unsignedchar", 100), //
    usset3("usset3", "unsignedchar", 100), //
    usset4("usset4", "unsignedchar", 100), //
    usset5("usset5", "unsignedchar", 100), //
    usset6("usset6", "unsignedchar", 100), //
    sstation0("sstation0", "char", 17), //
    sstation1("sstation1", "char", 17), //
    sbank_acc("sbank_acc", "char", 41), //
    sbank_acc2("sbank_acc2", "char", 41), //
    lbank_acc_type("lbank_acc_type", "int", 4), //
    lbank_acc_type2("lbank_acc_type2", "int", 4), //
    smain_flag("smain_flag", "char", 2), //
    smain_flag2("smain_flag2", "char", 2), //
    sbank_code("sbank_code", "char", 7), //
    sbank_code2("sbank_code2", "char", 7), //
    semp_no("semp_no", "char", 9), //
    semp_no2("semp_no2", "char", 9), //
    drate0("drate0", "double", 8), //
    drate1("drate1", "double", 8), //
    lserial0("lserial0", "int", 4), //
    lserial1("lserial1", "int", 4), //
    sbankname("sbankname", "char", 81), //
    sbankname2("sbankname2", "char", 81), //
    scard0("scard0", "char", 51), //
    scard1("scard1", "char", 51), //
    sorder0("sorder0", "char", 11), //
    sorder1("sorder1", "char", 11), //
    sorder2("sorder2", "char", 11), //
    scusttypes("scusttypes", "char", 201), //
    ssectypes("ssectypes", "char", 201), //
    vsmess("vsmess", "vs_char", 256), //
    vsvarstr0("vsvarstr0", "vs_char", 256), //
    vsvarstr1("vsvarstr1", "vs_char", 256), //
    vsvarstr2("vsvarstr2", "vs_char", 256), //
    vsvarstr3("vsvarstr3", "vs_char", 256);

    private final String name;
    private final String type;
    private final int length;

    TransfersNodeType(String name, String type, int length) {
        this.name = name;
        this.type = type;
        this.length = length;
    }

    /**
     * 返回操作时所使用的方法. 根据获取或传输需在前面加上Set 或 Get
     * 
     * @return String
     * @since v1.00
     */
    public String getOptMethodName() {

        if (this.type.equals("int")) {
            return "IntFieldByName";
        } else if (this.type.equals("double")) {
            return "DoubleFieldByName";
        } else {
            return "StringFieldByName";
        }
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public int getLength() {
        return length;
    }

}
