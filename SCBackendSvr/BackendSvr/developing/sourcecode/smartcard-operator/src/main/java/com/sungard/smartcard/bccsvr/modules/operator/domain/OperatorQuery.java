/*
 * OperatorQuery.java  v1.00  2012-1-4
 * Peoject	smartcard-operator
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	OperatorQuery.java  v1.00 2012-1-4
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.modules.operator.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeType;

/**
 * 查询参数.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-1-4
 * 
 */
@TransfersElement
public class OperatorQuery {

    @TransfersNodeIn(value = TransfersNodeType.vsvarstr0, desc = "接收参数")
    public String nameString;

    @TransfersNodeIn(value = TransfersNodeType.lcert_code, desc = "起始行号")
    public int offset = 1;

    @TransfersNodeIn(value = TransfersNodeType.lserial0, desc = "起始页")
    public int pageno = 1;

    @TransfersNodeIn(value = TransfersNodeType.lserial1, desc = "页大小")
    public int pagesize = 20;

    public String getNameString() {
        return nameString;
    }

    public int getOffset() {
        return offset;
    }

    public int getPageno() {
        return pageno;
    }

    public int getPagesize() {
        return pagesize;
    }

}
