package com.kingstargroup.fdykt.util;

import java.io.*;

public class RSA 
{
    private int p=47;
    private int q=59;
    private long n=2773;
    private long m=2668;
    
    private long public_key=63;//公匙
    private long private_key=847;//密匙
    
    private long text=0;//明文
    private long secretword=0;//密文
    private long word=0;//解密后明文
    
    //判断是否为素数
    public boolean primenumber(long t)
    {
        long k=0;
        k=(long)Math.sqrt((double)t);
        boolean flag=true;
        for(int i=2;i<=k;i++)
        {
            if((t%i)==0)
            {
                flag = false;
                break;
            }
        }
        return flag;
    }
    //输入PQ
    public void inputPQ()throws Exception
    {
//        do{
//                System.out.println("请输入素数p: ");
//                BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
//                String br=stdin.readLine();
//                this.p=Integer.parseInt(br);
//         }
//        while(!primenumber(this.p));
//        do{
//            System.out.println("请输入素数q: ");
//            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
//            String br=stdin.readLine();
//            this.q=Integer.parseInt(br);
//        }
//        while(!primenumber(this.q));
    	
        this.n=this.p*this.q;
        this.m=(p-1)*(q-1);
        System.out.println("这两个素数的乘积为p*q："+this.n);
        System.out.println("所得的小于Ｎ并且与Ｎ互素的整数的个数为m=(p-1)(q-1)："+this.m);
    }
    //求最大公约数
    public long gcd(long a,long b)
    {
        long gcd;
        if(b==0)
            gcd=a;
        else
            gcd=gcd(b,a%b);
//        System.out.println("gcd:"+gcd);
        return gcd;
        
    }
    //输入公匙
    public void getPublic_key()throws Exception
    {
        do{
            System.out.println("请输入一个公钥的值，这个值要求小于m并且和m互质： ");
            BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
            String br=stdin.readLine();
            this.public_key=Long.parseLong(br);
        }while((this.public_key >= this.m) || (this.gcd(this.m,this.public_key)!=1));
        System.out.println("公钥为："+this.public_key);
    }
    //计算得到密匙
    public void getPrivate_key()
    {
        long value=1;
        for(long i=1;;i++)
        {
            value=i*this.m+1;
//            System.out.println("value:  "+value);
            if((value%this.public_key==0)&& (value/this.public_key < this.m))
            {
                this.private_key=value/this.public_key;
                break;
            }
        }
        System.out.println("产生的一个私钥为："+this.private_key);
    }
    //输入明文
    public void getText()throws Exception
    {
        System.out.println("请输入明文：");
        BufferedReader stdin=new BufferedReader(new InputStreamReader(System.in));
        String br=stdin.readLine();
        this.text=Long.parseLong(br);
    }
    //加密、解密计算
    public long colum(long y,long n,long key)
    {
        long mul = 0;
        if(key==1)
            mul=y%n;
        else 
            mul=y*this.colum(y,n,key-1)%n;
        return mul;
    }
    
    //加密后解密
    public void pascolum()throws Exception
    {
//        this.getText();
    	for(int i=10;i<20;i++){
    		this.text = i;
            System.out.println("输入明文为: "+this.text);
            //加密
            this.secretword=this.colum(this.text,this.n,this.private_key);
            System.out.println("所得的密文为："+this.secretword);
            //解密
            this.word=this.colum(this.secretword,this.n,this.public_key);
            System.out.println("解密后所得的明文为："+this.word);
    	}

        
    }
    
    public long ency(long y){
    	this.secretword = this.colum(y, n, this.private_key);
    	return secretword;
    }
    
    public long decode(long y){
    	this.word = this.colum(y, n, this.public_key);
    	return word;
    }
    
    
    public static void main(String []args)throws Exception
    {
        RSA t = new RSA();
//        t.inputPQ();
//        t.getPublic_key();
//        t.getPrivate_key();
        t.pascolum();
    }

}


