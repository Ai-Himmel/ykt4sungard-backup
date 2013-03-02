package org.king.check.common.query;

import org.apache.commons.lang.StringUtils;
import org.king.check.Constants;
import org.king.framework.dao.MyQuery;
import org.king.framework.dao.Para;

import java.sql.Types;
import java.util.ArrayList;
import java.util.List;

/**
 * hql转换类，将各种条件组合成完整的hql
 * <p/>
 * User: Yiming.You
 * Date: 2010-09-17
 */
public class QueryTranslate extends MyQuery {

    private static final String blank = " ";

    private List conditions = new ArrayList();

    public QueryTranslate() {
    }

    public QueryTranslate(List conditions) {
        this.conditions = conditions;
    }

    public List getConditions() {
        return conditions;
    }

    public void setConditions(List conditions) {
        this.conditions = conditions;
    }

    /**
     * 添加And = 并且只有一个参数的条件
     *
     * @param propertyName .
     * @param firstValue   .
     */
    public void addEqualCondition(String propertyName, Object firstValue) {
        addCondition(propertyName, Constants.OPRATER_EQUAL, firstValue);
    }

    /**
     * 添加And like条件
     *
     * @param propertyName .
     * @param firstValue   .
     */
    public void addLikeCondition(String propertyName, Object firstValue) {
        addCondition(propertyName, Constants.OPRATER_CONTAINS, firstValue.toString().trim());
    }

    /**
     * 添加And，并且只有一个参数的条件
     *
     * @param propertyName .
     * @param operator     .
     * @param firstValue   .
     */
    public void addCondition(String propertyName, String operator, Object firstValue) {
        addCondition(propertyName, operator, firstValue, null, Constants.OPRATER_AND);
    }

    /**
     * 添加条件，并同时将条件中的参数添加到para中
     *
     * @param propertyName .
     * @param operator     .
     * @param firstValue   .
     * @param secondValue  .
     * @param andOr        .
     */
    public void addCondition(String propertyName, String operator, Object firstValue, Object secondValue, String andOr) {
        Condition condition = new Condition();
        condition.setPropertyName(propertyName);
        condition.setOperator(operator);
        condition.setFirstValue(firstValue);
        condition.setSecondValue(secondValue);
        condition.setAndOr(andOr);
        addCondition(condition);

        if (opContainsNull(condition)) {
            //nothing to do
        } else if (opContainsLike(condition)) {
            if (Constants.OPRATER_NOT_CONTAINS.equals(condition.getOperator())) {
                addParameter(condition.getOperator().replace("||", condition.getFirstValue().toString()));
            } else {
                addParameter(condition.getOperator().replace("|", condition.getFirstValue().toString()));
            }
        } else if (condition.getOperator().equals(Constants.OPRATER_BETWEEN)) {
            addParameter(firstValue);
            addParameter(secondValue);
        } else {
            addParameter(firstValue);
        }
    }

    public void addParameter(Object value) {
        if (value == null) {
            return;
        }
        String className = value.getClass().getName();

        if ("java.lang.Integer".equals(className)) {
            super.addPara(value, Types.INTEGER);
        } else if ("java.sql.Date".equals(className)) {
            super.addPara(value, Types.DATE);
        } else if ("java.lang.Double".equals(className)) {
            super.addPara(value, Types.DOUBLE);
        } else if ("java.lang.Boolean".equals(className)) {
            super.addPara(value, Types.BOOLEAN);
        } else if ("java.lang.Character".equals(className)) {
            super.addPara(value, Types.CHAR);
        } else {
            super.addPara(value.toString(), Types.VARCHAR);
        }
    }

    public void addCondition(Condition condition) {
        this.conditions.add(condition);
    }

    /**
     * to verdict the operator whether it is  a Comparison sign.
     *
     * @param condition .
     * @return .
     */
    public boolean opIsComparison(Condition condition) {
        boolean isComparison = false;
        if (StringUtils.isNotBlank(condition.getOperator())) {
            if (condition.getOperator().equals(Constants.OPRATER_EQUAL)) {
                isComparison = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_UNEQUAL)) {
                isComparison = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_GREATER)) {
                isComparison = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_GREATER_AND_EQUAL)) {
                isComparison = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_LESS)) {
                isComparison = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_LESS_AND_EQUAL)) {
                isComparison = true;
            }
        }
        return isComparison;
    }

    /**
     * to verdict the operator whether it is  contains "null".
     *
     * @param condition .
     * @return .
     */
    public boolean opContainsNull(Condition condition) {
        boolean containsNull = false;
        if (StringUtils.isNotBlank(condition.getOperator())) {
            if (condition.getOperator().equals(Constants.OPRATER_ISNULL)) {
                containsNull = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_ISNOTNULL)) {
                containsNull = true;
            }
        }
        return containsNull;
    }

    /**
     * to verdict the operator whether it is  contains "like".
     *
     * @param condition .
     * @return .
     */
    public boolean opContainsLike(Condition condition) {
        boolean containsLike = false;
        if (StringUtils.isNotBlank(condition.getOperator())) {
            if (condition.getOperator().equals(Constants.OPRATER_CONTAINS)) {
                containsLike = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_NOT_CONTAINS)) {
                containsLike = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_RIGHT_CONTAINS)) {
                containsLike = true;
            } else if (condition.getOperator().equals(Constants.OPRATER_LEFT_CONTAINS)) {
                containsLike = true;
            }
        }
        return containsLike;
    }

    /**
     * 获得简单比较条件的hql
     *
     * @param condition .
     * @return .
     */
    public String comparisonToQuery(Condition condition) {
        return condition.getPropertyName() + condition.getOperator() + "?";
    }

    /**
     * 获得包含null判断的hql
     *
     * @param condition .
     * @return .
     */
    public String containNullToQuery(Condition condition) {
        return condition.getPropertyName() + " " + condition.getOperator();
    }

    /**
     * 获得包含like条件的hql
     *
     * @param condition .
     * @return .
     */
    public String containLikeToQuery(Condition condition) {
//        return condition.getPropertyName() + " " + condition.getOperator().replace("|", condition.getFirstValue());
        if (Constants.OPRATER_NOT_CONTAINS.equals(condition.getOperator())) {
            return condition.getPropertyName() + " not like ?";
        } else {
            return condition.getPropertyName() + " like ?";
        }
    }

    /**
     * 获得包含between条件的hql
     *
     * @param condition .
     * @return .
     */
    public String betweenQuery(Condition condition) {
        return condition.getPropertyName() + " between ? and ?";
    }

    /**
     * 将所有的条件拼接成完整的条件hql，不包含basic hql
     *
     * @return .
     */
    public String conditionToString() {
        if (conditions == null || conditions.size() == 0) {
            return "";
        }
        StringBuffer queryConditon = new StringBuffer();
        for (int i = 0; i < conditions.size(); i++) {
            Condition condition = (Condition) conditions.get(i);

            if (opIsComparison(condition)) {
                queryConditon.append(comparisonToQuery(condition));
            } else if (opContainsNull(condition)) {
                queryConditon.append(containNullToQuery(condition));
            } else if (opContainsLike(condition)) {
                queryConditon.append(containLikeToQuery(condition));
            } else if (condition.getOperator().equals(Constants.OPRATER_BETWEEN)) {
                //todo 该判断严重影响方法结构，有待改进，目标：和以上三个判断统一
                queryConditon.append(betweenQuery(condition));
            }

            if (StringUtils.isNotEmpty(condition.getAndOr())) {
                queryConditon.append(blank).append(condition.getAndOr()).append(blank);
            } else {
                queryConditon.append(" and ");
            }
        }
        if (StringUtils.isNotEmpty(queryConditon.toString())) {
            //delete the last join-sign
            queryConditon.delete(queryConditon.length() - 4, queryConditon.length());
        }
        return queryConditon.toString();
    }

    /**
     * 获得完整的hql，包含basic hql
     *
     * @return .
     */
    @Override
    public String getQueryString() {
        //get the basic hql from the super class
        String baseHql = super.getQueryString();
        if (StringUtils.isBlank(baseHql)) {
            return "";
        }
        StringBuffer result = new StringBuffer(baseHql);

        String queryCondition = conditionToString();
        if (!"".equals(queryCondition)) {
            if (baseHql.toUpperCase().indexOf("WHERE") == -1) {
                result.append(" WHERE ");
            }
            if (!baseHql.endsWith(" ")) {
                result.append(" ");
            }
            if (!result.toString().trim().toUpperCase().endsWith("WHERE")) {
                result.append(" AND ");
            }
            result.append("(").append(queryCondition).append(")");
        }
        return result.toString();
    }

    public String toString() {
        return getQueryString();
    }

    public MyQuery cloneMyQuery() {
        MyQuery myQuery = new MyQuery();
        myQuery.setQueryString(this.getQueryString());
        myQuery.getParalist().addAll(this.getParalist());
        myQuery.setOrderby(this.getOrderby());
        myQuery.setGroupby(this.getGroupby());
        myQuery.setCache(this.isCache());
        myQuery.setOffset(this.isOffset());
        myQuery.setPageSize(this.getPageSize());
        myQuery.setPageStartNo(this.getPageStartNo());

        return myQuery;
    }

    public QueryTranslate cloneQueryTranslate() {
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(super.getQueryString());
        queryTranslate.getParalist().addAll(this.getParalist());
        queryTranslate.setOrderby(this.getOrderby());
        queryTranslate.setGroupby(this.getGroupby());
        queryTranslate.setCache(this.isCache());
        queryTranslate.setOffset(this.isOffset());
        queryTranslate.setPageSize(this.getPageSize());
        queryTranslate.setPageStartNo(this.getPageStartNo());

        return queryTranslate;
    }

    public static void main(String[] args) {
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString("from MonitorHostTemplate t");
        queryTranslate.addEqualCondition("t.templateId", Long.parseLong("1"));
        queryTranslate.addCondition("t.templateName", Constants.OPRATER_ISNULL, null);
        queryTranslate.addCondition("t.notificationsEnabled", Constants.OPRATER_ISNOTNULL, null);
        queryTranslate.addCondition("t.flapDetectionEnabled", Constants.OPRATER_LESS, Long.parseLong("3"));
        queryTranslate.addCondition("t.templateName", Constants.OPRATER_CONTAINS, "ddd");
        queryTranslate.addCondition("t.maxCheckAttempts", Constants.OPRATER_BETWEEN, Long.parseLong("1"), Long.parseLong("4"), Constants.OPRATER_OR);
        queryTranslate.addCondition("t.templateName", Constants.OPRATER_LEFT_CONTAINS, "ddd");

        System.out.println("queryTranslate.getQueryString() = " + queryTranslate.getQueryString());
        for (int i = 0; i < queryTranslate.getParalist().size(); i++) {
            Para param = (Para) queryTranslate.getParalist().get(i);
            System.out.println("param.getPName() = " + param.getPName() + "--------------param.getTypeNo() = " + param.getTypeNo());
        }
    }
}
