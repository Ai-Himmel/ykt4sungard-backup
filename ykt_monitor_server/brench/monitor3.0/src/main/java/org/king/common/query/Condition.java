package org.king.common.query;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-6
 */
public class Condition {

    //列名
    private String propertyName;

    //操作符
    private String operator;

    //between的第一个值
    private Object firstValue;

    //between的第二个值
    private Object secondValue;

    //类型（date,string。。。）
    private String type;

    //实体名
    //todo condition 中的entity暂时没有用到，目前处理多表查询的方式为在condition的property属性中指定，如entity.name
    private String entity;

    //条件
    private String andOr;

    //括号
    private String bracket;

    public String getPropertyName() {
        return propertyName;
    }

    public void setPropertyName(String propertyName) {
        this.propertyName = propertyName;
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public Object getFirstValue() {
        return firstValue;
    }

    public void setFirstValue(Object firstValue) {
        this.firstValue = firstValue;
    }

    public Object getSecondValue() {
        return secondValue;
    }

    public void setSecondValue(Object secondValue) {
        this.secondValue = secondValue;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getEntity() {
        return entity;
    }

    public void setEntity(String entity) {
        this.entity = entity;
    }

    public String getAndOr() {
        return andOr;
    }

    public void setAndOr(String andOr) {
        this.andOr = andOr;
    }

    public String getBracket() {
        return bracket;
    }

    public void setBracket(String bracket) {
        this.bracket = bracket;
    }
}