/**
 * ModelDescription.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.types;

public class ModelDescription  implements java.io.Serializable {
    private oasis.names.tc.wsrp.v1.types.PropertyDescription[] propertyDescriptions;
    private oasis.names.tc.wsrp.v1.types.ModelTypes modelTypes;
    private oasis.names.tc.wsrp.v1.types.Extension[] extensions;

    public ModelDescription() {
    }

    public ModelDescription(
           oasis.names.tc.wsrp.v1.types.Extension[] extensions,
           oasis.names.tc.wsrp.v1.types.ModelTypes modelTypes,
           oasis.names.tc.wsrp.v1.types.PropertyDescription[] propertyDescriptions) {
           this.propertyDescriptions = propertyDescriptions;
           this.modelTypes = modelTypes;
           this.extensions = extensions;
    }


    /**
     * Gets the propertyDescriptions value for this ModelDescription.
     * 
     * @return propertyDescriptions
     */
    public oasis.names.tc.wsrp.v1.types.PropertyDescription[] getPropertyDescriptions() {
        return propertyDescriptions;
    }


    /**
     * Sets the propertyDescriptions value for this ModelDescription.
     * 
     * @param propertyDescriptions
     */
    public void setPropertyDescriptions(oasis.names.tc.wsrp.v1.types.PropertyDescription[] propertyDescriptions) {
        this.propertyDescriptions = propertyDescriptions;
    }

    public oasis.names.tc.wsrp.v1.types.PropertyDescription getPropertyDescriptions(int i) {
        return this.propertyDescriptions[i];
    }

    public void setPropertyDescriptions(int i, oasis.names.tc.wsrp.v1.types.PropertyDescription _value) {
        this.propertyDescriptions[i] = _value;
    }


    /**
     * Gets the modelTypes value for this ModelDescription.
     * 
     * @return modelTypes
     */
    public oasis.names.tc.wsrp.v1.types.ModelTypes getModelTypes() {
        return modelTypes;
    }


    /**
     * Sets the modelTypes value for this ModelDescription.
     * 
     * @param modelTypes
     */
    public void setModelTypes(oasis.names.tc.wsrp.v1.types.ModelTypes modelTypes) {
        this.modelTypes = modelTypes;
    }


    /**
     * Gets the extensions value for this ModelDescription.
     * 
     * @return extensions
     */
    public oasis.names.tc.wsrp.v1.types.Extension[] getExtensions() {
        return extensions;
    }


    /**
     * Sets the extensions value for this ModelDescription.
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
        if (!(obj instanceof ModelDescription)) return false;
        ModelDescription other = (ModelDescription) obj;
        if (obj == null) return false;
        if (this == obj) return true;
        if (__equalsCalc != null) {
            return (__equalsCalc == obj);
        }
        __equalsCalc = obj;
        boolean _equals;
        _equals = true && 
            ((this.propertyDescriptions==null && other.getPropertyDescriptions()==null) || 
             (this.propertyDescriptions!=null &&
              java.util.Arrays.equals(this.propertyDescriptions, other.getPropertyDescriptions()))) &&
            ((this.modelTypes==null && other.getModelTypes()==null) || 
             (this.modelTypes!=null &&
              this.modelTypes.equals(other.getModelTypes()))) &&
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
        if (getPropertyDescriptions() != null) {
            for (int i=0;
                 i<java.lang.reflect.Array.getLength(getPropertyDescriptions());
                 i++) {
                java.lang.Object obj = java.lang.reflect.Array.get(getPropertyDescriptions(), i);
                if (obj != null &&
                    !obj.getClass().isArray()) {
                    _hashCode += obj.hashCode();
                }
            }
        }
        if (getModelTypes() != null) {
            _hashCode += getModelTypes().hashCode();
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
        new org.apache.axis.description.TypeDesc(ModelDescription.class, true);

    static {
        typeDesc.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ModelDescription"));
        org.apache.axis.description.ElementDesc elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("propertyDescriptions");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "propertyDescriptions"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "PropertyDescription"));
        elemField.setMinOccurs(0);
        typeDesc.addFieldDesc(elemField);
        elemField = new org.apache.axis.description.ElementDesc();
        elemField.setFieldName("modelTypes");
        elemField.setXmlName(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "modelTypes"));
        elemField.setXmlType(new javax.xml.namespace.QName("urn:oasis:names:tc:wsrp:v1:types", "ModelTypes"));
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
