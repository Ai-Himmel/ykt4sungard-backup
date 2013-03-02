/**
 * Contact.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class Contact  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.Postal postal;
    private oasis.names.tc.wsrp.v1.types.Telecom telecom;
    private oasis.names.tc.wsrp.v1.types.Online online;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public Contact() {
    }

    public Contact(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.Online online,
           oasis.names.tc.wsrp.v1.types.Postal postal,
           oasis.names.tc.wsrp.v1.types.Telecom telecom) {
           this.postal = postal;
           this.telecom = telecom;
           this.online = online;
           this.extensions = extensions;
    }


    /**
     * Gets the postal value for this Contact.
     * 
     * @return postal
     */
    public oasis.names.tc.wsrp.v1.types.Postal getPostal() {
        return postal;
    }


    /**
     * Sets the postal value for this Contact.
     * 
     * @param postal
     */
    public void setPostal(oasis.names.tc.wsrp.v1.types.Postal postal) {
        this.postal = postal;
    }


    /**
     * Gets the telecom value for this Contact.
     * 
     * @return telecom
     */
    public oasis.names.tc.wsrp.v1.types.Telecom getTelecom() {
        return telecom;
    }


    /**
     * Sets the telecom value for this Contact.
     * 
     * @param telecom
     */
    public void setTelecom(oasis.names.tc.wsrp.v1.types.Telecom telecom) {
        this.telecom = telecom;
    }


    /**
     * Gets the online value for this Contact.
     * 
     * @return online
     */
    public oasis.names.tc.wsrp.v1.types.Online getOnline() {
        return online;
    }


    /**
     * Sets the online value for this Contact.
     * 
     * @param online
     */
    public void setOnline(oasis.names.tc.wsrp.v1.types.Online online) {
        this.online = online;
    }


    /**
     * Gets the extensions value for this Contact.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this Contact.
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
        if (!(obj instanceof Contact)) return false;
        Contact other = (Contact) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.postal==null && other.getPostal()==null) || 
             (this.postal!=null &&
              this.postal.equals(other.getPostal()))) &&
            ((this.telecom==null && other.getTelecom()==null) || 
             (this.telecom!=null &&
              this.telecom.equals(other.getTelecom()))) &&
            ((this.online==null && other.getOnline()==null) || 
             (this.online!=null &&
              this.online.equals(other.getOnline()))) &&
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
        if (getPostal() != null) {
            _hashCode += getPostal().hashCode();
        }
        if (getTelecom() != null) {
            _hashCode += getTelecom().hashCode();
        }
        if (getOnline() != null) {
            _hashCode += getOnline().hashCode();
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
        new org.apache.axis.description.TypeDesc(Contact.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Contact"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("postal");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "postal"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Postal"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("telecom");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "telecom"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Telecom"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("online");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "online"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "Online"));
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
