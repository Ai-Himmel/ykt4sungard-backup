package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDNOCHANGE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardnochange implements Serializable {

    /**
     * 旧卡号
     */
    private Integer oldcardno;
    /**
     * 新卡号
     */
    private Integer newcardno;
    /**
     * 变更日期
     */
    private String changedate;

    public void setOldcardno(Integer oldcardno) {
        this.oldcardno = oldcardno;
    }

    public Integer getOldcardno() {
        return this.oldcardno;
    }

    public void setNewcardno(Integer newcardno) {
        this.newcardno = newcardno;
    }

    public Integer getNewcardno() {
        return this.newcardno;
    }

    public void setChangedate(String changedate) {
        this.changedate = changedate;
    }

    public String getChangedate() {
        return this.changedate;
    }
}