# QtSignalSlotManager

基于信号槽的简单管理类

> a simple management based on Signals and Slots

本项目旨在提供一个第三方信号槽管理类以减少模块间的耦合，使信号槽的连接分为两步进行，通过注册主题和订阅的方式更灵活的使用信号槽。

> This project aims to provide a third-party Signals & Slots management class to reduce the coupling between modules, so that the Signals & Slots connection is divided into two steps, and the Signals & Slots is more flexible by registering the subject and subscription.

## 使用限制：
仅支持使用SIGNAL/SLOT宏语法的信号槽

>## Requirements:
>Only Signals & Slots using the SIGNAL/SLOT macros syntax are supported

## 用法：
1. 获取QtSignalSlotManager实例，QtSignalSlotManager使用了单例模式，使用时通过`QtSignalSlotManager::getInstance()`即可得到QtSignalSlotManager实例。

2. 添加主题/移除主题

```
void addSubject(int subjectId, QObject *sender, const char *signal);
void removeSubject(int subjectId, QObject *sender, const char *signal);
```

3. 订阅/取消订阅

```
void subscribe(int subjectId, QObject *receiver, const char *slot);
void unsubscribe(int subjectId, QObject *receiver, const char *slot);
```

4. 添加/移除主题 与 订阅/取消订阅 没有操作顺序限制，即可以先注册主题后订阅，反之亦然。

5. 具体示例可参考 Demo

> ## Usage:
> 1. Get the QtSignalSlotManager instance. QtSignalSlotManager uses the singleton mode. You can get the QtSignalSlotManager instance by using `QtSignalSlotManager::getInstance()`.
>
> 2. Add subject/Remove subject
> 
> ```
> void addSubject(int subjectId, QObject *sender, const char *signal);
> void removeSubject(int subjectId, QObject *sender, const char *signal);
> ```
> 
> 3. Subscribe/Unsubscribe
> 
> ```
> void subscribe(int subjectId, QObject *receiver, const char *slot);
> void unsubscribe(int subjectId, QObject *receiver, const char *slot);
> ```
> 
> 4. Add/Remove subject and Subscribe/Unsubscribe There is no order restriction, that is, you can add a subject and then subscribe, and vice versa.
> 
> 5. More detail see Demo.

## License

[Apache-2.0](https://github.com/3gbywork/QtSignalSlotManager/blob/master/LICENSE)