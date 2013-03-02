/**
 * UserProfile.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class UserProfile  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.PersonName name;
    private java.util.Calendar bdate;
    private java.lang.String gender;
    private oasis.names.tc.wsrp.v1.types.EmployerInfo employerInfo;
    private oasis.names.tc.wsrp.v1.types.Contact homeInfo;
    private oasis.names.tc.wsrp.v1.types.Contact businessInfo;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public UserProfile() {
    }

    public UserProfile(
           java.util.Calendar bdate,
           oasis.names.tc.wsrp.v1.types.Contact businessInfo,
           oasis.names.tc.wsrp.v1.types.EmployerInfo employerInfo,
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           java.lang.String gender,
           oasis.names.tc.wsrp.v1.types.Contact homeInfo,
           oasis.names.tc.wsrp.v1.types.PersonName name) {
           this.name = name;
           this.bdate = bdate;
           this.gender = gender;
           this.employerInfo = employerInfo;
           this.homeInfo = homeInfo;
           this.businessInfo = businessInfo;
           this.extensions = extensions;
    }


    /**
     * Gets the name value for this UserProfile.
     * 
     * @return name
     */
    public oasis.names.tc.wsrp.v1.types.PersonName getName() {
        return name;
    }


    /**
     * Sets the name value for this UserProfile.
     * 
     * @param name
     */
    public void setName(oasis.names.tc.wsrp.v1.types.PersonName name) {
        this.name = name;
    }


    /**
     * Gets the bdate value for this UserProfile.
     * 
     * @return bdate
     */
    public java.util.Calendar getBdate() {
        return bdate;
    }


    /**
     * Sets the bdate value for this UserProfile.
     * 
     * @param bdate
     */
    public void setBdate(java.util.Calendar bdate) {
        this.bdate = bdate;
    }


    /**
     * Gets the gender value for this UserProfile.
     * 
     * @return gender
     */
    public java.lang.String getGender() {
        return gender;
    }


    /**
     * Sets the gender value for this UserProfile.
     * 
     * @param gender
     */
    public void setGender(java.lang.String gender) {
        this.gender = gender;
    }


    /**
     * Gets the employerInfo value for this UserProfile.
     * 
     * @return employerInfo
     */
    public oasis.names.tc.wsrp.v1.types.EmployerInfo getEmployerInfo() {
        return employerInfo;
    }


    /**
     * Sets the employerInfo value for this UserProfile.
     * 
     * @param employerInfo
     */
    public void setEmployerInfo(oasis.names.tc.wsrp.v1.types.EmployerInfo employerInfo) {
        this.employerInfo = employerInfo;
    }


    /**
     * Gets the homeInfo value for this UserProfile.
     * 
     * @return homeInfo
     */
    public oasis.names.tc.wsrp.v1.types.Contact getHomeInfo() {
        return homeInfo;
    }


    /**
     * Sets the homeInfo value for this UserProfile.
     * 
     * @param homeInfo
     */
    public void setHomeInfo(oasis.names.tc.wsrp.v1.types.Contact homeInfo) {
        this.homeInfo = homeInfo;
    }


    /**
     * Gets the businessInfo value for this UserProfile.
     * 
     * @return businessInfo
     */
    public oasis.names.tc.wsrp.v1.types.Contact getBusinessInfo() {
        return businessInfo;
    }


    /**
     * Sets the businessInfo value for this UserProfile.
     * 
     * @param businessInfo
     */
    public void setBusinessInfo(oasis.names.tc.wsrp.v1.types.Contact businessInfo) {
        this.businessInfo = businessInfo;
    }


    /**
     * Gets the extensions value for this UserProfile.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this UserProfile.
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
        if (!(obj instanceof UserProfile)) return false;
        UserProfile other = (UserProfile) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.name==null && other.getName()==null) || 
             (this.name!=null &&
              this.name.equals(other.getName()))) &&
            ((this.bdate==null && other.getBdate()==null) || 
             (this.bdate!=null &&
              this.bdate.equals(other.getBdate()))) &&
            ((this.gender==null && other.getGender()==null) || 
             (this.gender!=null &&
              this.gender.equals(other.getGender()))) &&
            ((this.employerInfo==null && other.getEmployerInfo()==null) || 
             (this.employerInfo!=null &&
              this.employerInfo.equals(other.getEmployerInfo()))) &&
            ((this.homeInfo==null && other.getHomeInfo()==null) || 
             (this.homeInfo!=null &&
              this.homeInfo.equals(other.getHomeInfo()))) &&
            ((this.businessInfo==null && other.getBusinessInfo()==null) || 
             (this.businessInfo!=null &&
              this.businessInfo.equals(other.getBusinessInfo()))) &&
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
        if (getName() != null) {
            _hashCode += getName().hashCode();
        }
        if (getBdate() != null) {
            _hashCode += getBdate().hashCode();
        }
        if (getGender() != null) {
            _hashCode += getGender().hashCode();
        }
        if (getEmployerInfo() != null) {
            _hashCode += getEmployerInfo().hashCode();
        }
        if (getHomeInfo() != null) {
            _hashCode += getHomeInfo().hashCode();
        }
        if (getBusinessInfo() != null) {
            _hashCode += getBusinessInfo().hashCode();
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
        new org.apache.axis.description.TypeDesc(UserProfile.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UserProfile"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("name");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "name"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PersonName"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("bdate");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "bdate"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "dateTime"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("gender");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "gender"));
        elemField.setXmlType(new javax.xml.namespace.QName("http://www.w3.org/2001/XMLSchema", "string"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("employerInfo");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "employerInfo"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "EmployerInfo"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("homeInfo");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "homeInfo"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Contact"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("businessInfo");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "businessInfo"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Contact"));
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
