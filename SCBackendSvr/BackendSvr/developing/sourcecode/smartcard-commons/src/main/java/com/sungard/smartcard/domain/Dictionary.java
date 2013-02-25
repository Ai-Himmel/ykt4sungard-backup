package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_DICTIONARY的实体类
 * 数据字典表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@SuppressWarnings("serial")
@TransfersElement
public class Dictionary implements Serializable {

    /**
     * 字典类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "字典类型")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "字典类型")
    private Integer dicttype;
    /**
     * 字典类型名称
     */
    @TransfersNodeIn(value = TransfersNodeType.scusttypes, desc = "字典类型名称")
    @TransfersNodeOut(value = TransfersNodeType.scusttypes, desc = "字典类型名称")
    private String dicttypename;
    /**
     * 字典值
     */
    @TransfersNodeIn(value = TransfersNodeType.sdate1, desc = "字典值")
    @TransfersNodeOut(value = TransfersNodeType.sdate1, desc = "字典值")
    private String dictval;
    /**
     * 字典名称
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr1, desc = "字典名称")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr1, desc = "字典名称")
    private String dictcaption;

    public void setDicttype(Integer dicttype) {
        this.dicttype = dicttype;
    }

    public Integer getDicttype() {
        return this.dicttype;
    }

    public void setDicttypename(String dicttypename) {
        this.dicttypename = dicttypename;
    }

    public String getDicttypename() {
        return this.dicttypename;
    }

    public void setDictval(String dictval) {
        this.dictval = dictval;
    }

    public String getDictval() {
        return this.dictval;
    }

    public void setDictcaption(String dictcaption) {
        this.dictcaption = dictcaption;
    }

    public String getDictcaption() {
        return this.dictcaption;
    }
}