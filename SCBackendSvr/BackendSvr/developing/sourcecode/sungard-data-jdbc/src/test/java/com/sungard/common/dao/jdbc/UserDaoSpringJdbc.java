/*
 * UserDaoSpringJdbc.java  v1.00  2012-2-16
 * Peoject	sungard-data-jdbc
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	UserDaoSpringJdbc.java  v1.00 2012-2-16
 * Project	: 	sungard-data-jdbc
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.common.dao.jdbc;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.springframework.stereotype.Repository;

import com.sungard.common.domain.User;
import com.sungard.common.page.PropertyFilter;
import com.sungard.common.page.build.AppBuildPropertyFilter;

/**
 * user spring jdbc dao.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-2-16
 * 
 */
@Repository
public class UserDaoSpringJdbc extends BaseDaoSpringJdbc<User, Long> {

    private static String SQL_QUERY = "SELECT ID ,EMAIL ,LOGIN_NAME ,NAME ,PASSWORD  FROM ACCT_USER where id=?";

    private static String SQL_SELECT_ALL = "SELECT ID ,EMAIL ,LOGIN_NAME ,NAME ,PASSWORD  FROM ACCT_USER";

    private Map<String, Object> parmMap;
    private Map<String, Object> condMap;

    public UserDaoSpringJdbc() {
        super(User.class);
    }

    @Override
    public List<User> getAll(User object) {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public String getSelectByPkSql() {
        return SQL_QUERY;
    }

    @Override
    public String getSelectAllSql() {
        return SQL_SELECT_ALL;
    }

    @Override
    public String getDeleteByPkSql() {
        return "DELETE FROM ACCT_USER where id=?";
    }

    @Override
    public String getInsertSql() {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    protected String getTableName() {
        return "ACCT_USER";
    }

    @Override
    protected String[] generatedKeyNames() {
        String[] ss = { "id" };
        return ss;
    }

    @Override
    protected List<PropertyFilter> getUpdatePrams() {
        return AppBuildPropertyFilter.buildFromAppRequest(parmMap, "prop");
    }

    @Override
    protected List<PropertyFilter> getUpdateConds() {
        return AppBuildPropertyFilter.buildFromAppRequest(condMap, "cond");
    }

    public Map<String, Object> getParmMap() {
        return parmMap;
    }

    public void setParmMap(Map<String, Object> parmMap) {
        this.parmMap = parmMap;
    }

    public Map<String, Object> getCondMap() {
        return condMap;
    }

    public void setCondMap(Map<String, Object> condMap) {
        this.condMap = condMap;
    }

}
