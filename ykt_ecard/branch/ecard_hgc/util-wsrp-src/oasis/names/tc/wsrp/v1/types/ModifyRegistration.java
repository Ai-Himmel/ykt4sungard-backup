/**
 * ModifyRegistration.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class ModifyRegistration  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext;
    private oasis.names.tc.wsrp.v1.types.RegistrationData registrationData;

    public ModifyRegistration() {
    }

    public ModifyRegistration(
           oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext,
           oasis.names.tc.wsrp.v1.types.RegistrationData registrationData) {
           this.registrationContext = registrationContext;
           this.registrationData = registrationData;
    }


    /**
     * Gets the registrationContext value for this ModifyRegistration.
     * 
     * @return registrationContext
     */
    public oasis.names.tc.wsrp.v1.types.RegistrationContext getRegistrationContext() {
        return registrationContext;
    }


    /**
     * Sets the registrationContext value for this ModifyRegistration.
     * 
     * @param registrationContext
     */
    public void setRegistrationContext(oasis.names.tc.wsrp.v1.types.RegistrationContext registrationContext) {
        this.registrationContext = registrationContext;
    }


    /**
     * Gets the registrationData value for this ModifyRegistration.
     * 
     * @return registrationData
     */
    public oasis.names.tc.wsrp.v1.types.RegistrationData getRegistrationData() {
        return registrationData;
    }


    /**
     * Sets the registrationData value for this ModifyRegistration.
     * 
     * @param registrationData
     */
    public void setRegistrationData(oasis.names.tc.wsrp.v1.types.RegistrationData registrationData) {
        this.registrationData = registrationData;
    }

    private java.lang.Object __equalsCalc = null;
    public synchronized boolean equals(java.lang.Object obj) {
        if (!(obj instanceof ModifyRegistration)) return false;
        ModifyRegistration other = (ModifyRegistration) obj;
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
            ((this.registrationData==null && other.getRegistrationData()==null) || 
             (this.registrationData!=null &&
              this.registrationData.equals(other.getRegistrationData())));
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
        if (getRegistrationData() != null) {
            _hashCode += getRegistrationData().hashCode();
        }
        __hashCodeCalc = false;
        return _hashCode;
    }

    // Type metadata
    private static org.apache.axis.description.TypeDesc typeDesc =
        new org.apache.axis.description.TypeDesc(ModifyRegistration.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", ">modifyRegistration"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("registrationContext");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "registrationContext"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "RegistrationContext"));
        elemField.setNillable(true);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("registrationData");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "registrationData"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "RegistrationData"));
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
