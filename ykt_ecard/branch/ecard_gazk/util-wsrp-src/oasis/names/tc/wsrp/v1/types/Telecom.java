/**
 * Telecom.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class Telecom  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.TelephoneNum telephone;
    private oasis.names.tc.wsrp.v1.types.TelephoneNum fax;
    private oasis.names.tc.wsrp.v1.types.TelephoneNum mobile;
    private oasis.names.tc.wsrp.v1.types.TelephoneNum pager;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public Telecom() {
    }

    public Telecom(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.TelephoneNum fax,
           oasis.names.tc.wsrp.v1.types.TelephoneNum mobile,
           oasis.names.tc.wsrp.v1.types.TelephoneNum pager,
           oasis.names.tc.wsrp.v1.types.TelephoneNum telephone) {
           this.telephone = telephone;
           this.fax = fax;
           this.mobile = mobile;
           this.pager = pager;
           this.extensions = extensions;
    }


    /**
     * Gets the telephone value for this Telecom.
     * 
     * @return telephone
     */
    public oasis.names.tc.wsrp.v1.types.TelephoneNum getTelephone() {
        return telephone;
    }


    /**
     * Sets the telephone value for this Telecom.
     * 
     * @param telephone
     */
    public void setTelephone(oasis.names.tc.wsrp.v1.types.TelephoneNum telephone) {
        this.telephone = telephone;
    }


    /**
     * Gets the fax value for this Telecom.
     * 
     * @return fax
     */
    public oasis.names.tc.wsrp.v1.types.TelephoneNum getFax() {
        return fax;
    }


    /**
     * Sets the fax value for this Telecom.
     * 
     * @param fax
     */
    public void setFax(oasis.names.tc.wsrp.v1.types.TelephoneNum fax) {
        this.fax = fax;
    }


    /**
     * Gets the mobile value for this Telecom.
     * 
     * @return mobile
     */
    public oasis.names.tc.wsrp.v1.types.TelephoneNum getMobile() {
        return mobile;
    }


    /**
     * Sets the mobile value for this Telecom.
     * 
     * @param mobile
     */
    public void setMobile(oasis.names.tc.wsrp.v1.types.TelephoneNum mobile) {
        this.mobile = mobile;
    }


    /**
     * Gets the pager value for this Telecom.
     * 
     * @return pager
     */
    public oasis.names.tc.wsrp.v1.types.TelephoneNum getPager() {
        return pager;
    }


    /**
     * Sets the pager value for this Telecom.
     * 
     * @param pager
     */
    public void setPager(oasis.names.tc.wsrp.v1.types.TelephoneNum pager) {
        this.pager = pager;
    }


    /**
     * Gets the extensions value for this Telecom.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this Telecom.
     * 
     * @param extensions
     */
    public void setExtensions(oasis.names.tc.wsrp.v1.types.Extension[] extensions) {
        this.extensions = extensions;
    }

    public oasis.names.tc.wsrp.v1.types.Extension getExtensions(int i) {
        return this.extensions[i];
    }

    public void setExtensions(int i, oasis.names.tc.wsrp.v1.types.Extension _value) {
        this.extensions[i] = _value;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof Telecom)) return false;
        Telecom other = (Telecom) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.telephone==null && other.getTelephone()==null) || 
             (this.telephone!=null &&
              this.telephone.equals(other.getTelephone()))) &&
            ((this.fax==null && other.getFax()==null) || 
             (this.fax!=null &&
              this.fax.equals(other.getFax()))) &&
            ((this.mobile==null && other.getMobile()==null) || 
             (this.mobile!=null &&
              this.mobile.equals(other.getMobile()))) &&
            ((this.pager==null && other.getPager()==null) || 
             (this.pager!=null &&
              this.pager.equals(other.getPager()))) &&
            ((this.extensions==null && other.getExtensions()==null) || 
             (this.extensions!=null &&
              java.util.Arrays.equals(this.extensions, other.getExtensions())));
        __equalsCalc = null;
        return _equals;
    }

    private boolean __hashCodeCalc = false;
    public synchronized int hashCode() {
        if (__hashCodeCalc) {
            return 0;
        }
        __hashCodeCalc = true;
        int _hashCode = 1;
        if (getTelephone() != null) {
            _hashCode += getTelephone().hashCode();
        }
        if (getFax() != null) {
            _hashCode += getFax().hashCode();
        }
        if (getMobile() != null) {
            _hashCode += getMobile().hashCode();
        }
        if (getPager() != null) {
            _hashCode += getPager().hashCode();
        }
        if (getExtensions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getExtensions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getExtensions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(Telecom.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Telecom"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("telephone");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "telephone"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "TelephoneNum"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("fax");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "fax"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "TelephoneNum"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("mobile");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "mobile"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "TelephoneNum"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("pager");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "pager"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "TelephoneNum"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("extensions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "extensions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Extension"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
    }

    /**
     * Return type metadata object
     */
    public static org.apache.axis.description.TypeDesc getTypeDesc() {
        return typeDesc;
    }

    /**
     * Get Custom Serializer
     */
    public static org.apache.axis.encoding.Serializer getSerializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanSerializer(
            _javaType, _xmlType, typeDesc);
    }

    /**
     * Get Custom Deserializer
     */
    public static org.apache.axis.encoding.Deserializer getDeserializer(
           java.lang.String mechType, 
           java.lang.Class _javaType,  
           javax.xml.namespace.QName _xmlType) {
        return 
          new  org.apache.axis.encoding.ser.BeanDeserializer(
            _javaType, _xmlType, typeDesc);
    }

}
