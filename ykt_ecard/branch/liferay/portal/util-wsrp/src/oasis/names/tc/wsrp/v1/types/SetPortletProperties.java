/**
 * SetPortletProperties.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class SetPortletProperties  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext;
    private oasis.names.tc.wsrp.v1.types.PortletContext portletContext;
    private oasis.names.tc.wsrp.v1.types.UserContext userContext;
    private oasis.names.tc.wsrp.v1.types.PropertyList propertyList;

    public SetPortletProperties() {
    }

    public SetPortletProperties(
           oasis.names.tc.wsrp.v1.types.PortletContext portletContext,
           oasis.names.tc.wsrp.v1.types.PropertyList propertyList,
           oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext,
           oasis.names.tc.wsrp.v1.types.UserContext userContext) {
           this.registrationContext = registrationContext;
           this.portletContext = portletContext;
           this.userContext = userContext;
           this.propertyList = propertyList;
    }


    /**
     * Gets the registrationContext value for this SetPortletProperties.
     * 
     * @return registrationContext
     */
    public oasis.names.tc.wsrp.v1.types.RegistrationContext getRegistrationContext() {
        return registrationContext;
    }


    /**
     * Sets the registrationContext value for this SetPortletProperties.
     * 
     * @param registrationContext
     */
    public void setRegistrationContext(oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext) {
        this.registrationContext = registrationContext;
    }


    /**
     * Gets the portletContext value for this SetPortletProperties.
     * 
     * @return portletContext
     */
    public oasis.names.tc.wsrp.v1.types.PortletContext getPortletContext() {
        return portletContext;
    }


    /**
     * Sets the portletContext value for this SetPortletProperties.
     * 
     * @param portletContext
     */
    public void setPortletContext(oasis.names.tc.wsrp.v1.types.PortletContext portletContext) {
        this.portletContext = portletContext;
    }


    /**
     * Gets the userContext value for this SetPortletProperties.
     * 
     * @return userContext
     */
    public oasis.names.tc.wsrp.v1.types.UserContext getUserContext() {
        return userContext;
    }


    /**
     * Sets the userContext value for this SetPortletProperties.
     * 
     * @param userContext
     */
    public void setUserContext(oasis.names.tc.wsrp.v1.types.UserContext userContext) {
        this.userContext = userContext;
    }


    /**
     * Gets the propertyList value for this SetPortletProperties.
     * 
     * @return propertyList
     */
    public oasis.names.tc.wsrp.v1.types.PropertyList getPropertyList() {
        return propertyList;
    }


    /**
     * Sets the propertyList value for this SetPortletProperties.
     * 
     * @param propertyList
     */
    public void setPropertyList(oasis.names.tc.wsrp.v1.types.PropertyList propertyList) {
        this.propertyList = propertyList;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof SetPortletProperties)) return false;
        SetPortletProperties other = (SetPortletProperties) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.registrationContext==null && other.getRegistrationContext()==null) || 
             (this.registrationContext!=null &&
              this.registrationContext.equals(other.getRegistrationContext()))) &&
            ((this.portletContext==null && other.getPortletContext()==null) || 
             (this.portletContext!=null &&
              this.portletContext.equals(other.getPortletContext()))) &&
            ((this.userContext==null && other.getUserContext()==null) || 
             (this.userContext!=null &&
              this.userContext.equals(other.getUserContext()))) &&
            ((this.propertyList==null && other.getPropertyList()==null) || 
             (this.propertyList!=null &&
              this.propertyList.equals(other.getPropertyList())));
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
        if (getRegistrationContext() != null) {
            _hashCode += getRegistrationContext().hashCode();
        }
        if (getPortletContext() != null) {
            _hashCode += getPortletContext().hashCode();
        }
        if (getUserContext() != null) {
            _hashCode += getUserContext().hashCode();
        }
        if (getPropertyList() != null) {
            _hashCode += getPropertyList().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(SetPortletProperties.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", ">setPortletProperties"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("registrationContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "registrationContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "RegistrationContext"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("portletContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "portletContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PortletContext"));
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("userContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "userContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "UserContext"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("propertyList");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "propertyList"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PropertyList"));
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
