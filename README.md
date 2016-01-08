# Realm-Study
###[Realm 官网](https://realm.io/cn/)
----------
###Realm 常用类介绍
#一、RLMRealm

 1. 父类 NSObject
 2. 描述
  1. 一个RLMRealm实例（也被称为一个realm）表示一个数据库。
  2. Realm 既可以被存储在磁盘中(见:+[RLMRealm realmWithPath:]) 也可以存储在内存中(见:RLMRealmConfiguration)
  3. Realm 是线程不安全的
 2. Creating & Initializing a Realm
  1. +defaultRealm  获取一个默认的Realm对象
  2. +realmWithConfiguration:error: 返回指定配置的Realm对象
  
