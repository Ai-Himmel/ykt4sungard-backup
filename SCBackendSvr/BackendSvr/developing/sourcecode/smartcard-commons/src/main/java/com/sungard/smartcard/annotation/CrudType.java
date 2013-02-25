/*
 * CrudType.java  v1.00  2011-12-21
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	CrudType.java  v1.00 2011-12-21
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.annotation;

/**
 * 数据库操作类型.
 * <p>
 * A 增
 * <p>
 * U 改
 * <p>
 * D 删除
 * <p>
 * Q 查询
 * <p>
 * Other 其它
 * <p>
 * DA 批量删除
 * <p>
 * V 审核
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-21
 * 
 */
public enum CrudType {

    A, U, D, Q, Other,DA,V

}
