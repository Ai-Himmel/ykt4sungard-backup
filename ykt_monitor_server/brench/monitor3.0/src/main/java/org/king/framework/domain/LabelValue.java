package org.king.framework.domain;

import java.io.Serializable;
import java.util.Comparator;

public class LabelValue
  implements Comparable, Serializable
{
  private static final long serialVersionUID = 3689355407466181430L;
  public static final Comparator CASE_INSENSITIVE_ORDER = new Comparator() {
    public int compare(Object o1, Object o2) {
      String label1 = ((LabelValue)o1).getLabel();
      String label2 = ((LabelValue)o2).getLabel();
      return label1.compareToIgnoreCase(label2);
    }
  };

  private String label = null;

  private String value = null;

  public LabelValue()
  {
  }

  public LabelValue(String label, String value)
  {
    this.label = label;
    this.value = value;
  }

  public String getLabel()
  {
    return label;
  }

  public void setLabel(String label) {
    this.label = label;
  }

  public String getValue()
  {
    return value;
  }

  public void setValue(String value) {
    this.value = value;
  }

  public int compareTo(Object o)
  {
    String otherLabel = ((LabelValue)o).getLabel();

    return getLabel().compareTo(otherLabel);
  }

  public String toString()
  {
    StringBuffer sb = new StringBuffer("LabelValue[");
    sb.append(label);
    sb.append(", ");
    sb.append(value);
    sb.append("]");
    return sb.toString();
  }

  public boolean equals(Object obj)
  {
    if (obj == this) {
      return true;
    }

    if (!(obj instanceof LabelValue)) {
      return false;
    }

    LabelValue bean = (LabelValue)obj;
    int nil = getValue() == null ? 1 : 0;
    nil += (bean.getValue() == null ? 1 : 0);

    if (nil == 2)
      return true;
    if (nil == 1) {
      return false;
    }
    return getValue().equals(bean.getValue());
  }

  public int hashCode()
  {
    return getValue() == null ? 17 : getValue().hashCode();
  }
}