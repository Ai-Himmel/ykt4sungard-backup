package com.sungard.smartcard.modules.system.dao;

import com.sungard.smartcard.domain.Dpsoper;
import com.sungard.smartcard.domain.Dpsopercard;

import java.io.Serializable;
import java.util.List;

/**
 * 充值操作员与卡绑定关系的基本数据库操作接口
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-20
 */
public interface DpsoperDao {

    public List<Dpsoper> findAllDpsoper();

    public int isExistDpsopercard(String key, Serializable value);

    public int deleteDpsopercard(String opercode);

    public int saveDpsopercard(Dpsopercard dpsopercard);
}
